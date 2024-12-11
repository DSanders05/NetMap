#include <pybind11/pybind11.h>
#include "../include/manager.hpp"
#include <thread>
#include <queue>
#include <mutex>

namespace py = pybind11;

std::queue<std::pair<std::string,int>> data_queue;
std::mutex queue_mutex;

// Manager Constructor
Manager::Manager(std::vector<std::string>& server_ips, int server_port)
    :motor_controller(),server_ips(server_ips)
{
}

// Manager Deconstructor (also deconstructs the RPi motor controller)
Manager::~Manager() 
{
    motor_controller.~Motor_Controller();

    std::cout << "App manager has been deconstructed." << std::endl;
}

void Manager::start_thread()
{
    std::cout << "Starting motor thread in C++ code..." << std::endl;
    if (!motor_running)
    {
        motor_running = {true};
        motor_thread = std::thread(&Manager::start_auto_mode, this);
        std::cout << "Thread started..." << std::endl;
    }
}

// Auto Mode Logic
void Manager::start_auto_mode()
{ 
    // First time entering auto mode will init heading
    // After that this will be bypassed
    if (!motor_controller.get_heading_init()) {
        std::cout << "Initializing heading..." << std::endl;
        motor_controller.initialize_heading();
    }

    while (motor_running) {
        //  Always enter this loop with heading = 0 and CCW flag set to false
        if (motor_controller.get_ctr_clockwise()) {
            motor_controller.set_ctr_clockwise(false);
            gpio_write(motor_controller.board_address, motor_controller.direction_pin, motor_controller.get_ctr_clockwise());

            // Make a full rotation (1200 steps)
            // This loop is for CW rotation so we subtract 0.3 for each step
            for (size_t i = 0; i < 1200; i++) {
                motor_controller.activate_motor();
                motor_controller.set_heading(-0.3f);

                 if (!motor_running)
                 {
                    gpio_write(motor_controller.board_address,motor_controller.pulse_pin,PI_LOW);
                    return;
                 }
                 
                // After every 15 degrees attempt to connect to ground vehicles
                if (i % 50 == 0) { 
                    for(auto ip : server_ips)
                    {
                        Client client(ip,8080);
                        if(client.attempt_connection() == 1)
                        {
                            add_to_queue(ip,motor_controller.get_heading());
                        }
                    }
                }
            }
        } 
        else 
        {
            // Swap rotation direction and repeat steps from above
            motor_controller.set_ctr_clockwise(true);
            gpio_write(motor_controller.board_address, motor_controller.direction_pin, motor_controller.get_ctr_clockwise());

            // Another 1200 steps for full rotation
            for (size_t i = 0; i < 1200; i++) {
                motor_controller.activate_motor();

                // This loop is for CCW rotation so we add 0.3 until 360 degrees
                motor_controller.set_heading(0.3f);

                 if (!motor_running)
                 {
                    gpio_write(motor_controller.board_address,motor_controller.pulse_pin,PI_LOW);
                    return;
                 }

                // After every 15 degrees we try to connect to ground vehicles
                if (i % 50 == 0) {
                    for(auto ip : server_ips)
                    {
                        Client client(ip,8080);
                        if(client.attempt_connection() == 1)
                        {
                            add_to_queue(ip,motor_controller.get_heading());
                        }
                    }
                }
            }
        }
        time_sleep(30);  // Pause between scans (seconds)
    }

    // After exiting while loop make sure the motor pulse pin is set low
    gpio_write(motor_controller.board_address, motor_controller.pulse_pin, PI_LOW);
}


void Manager::init_zero()
{
    motor_controller.initialize_heading();
}

void Manager::update_rovers(const std::string& signal_strength)
{
    double current_heading = motor_controller.get_heading();

    if (current_heading < 0)
    {
        std::cerr << "Error: Heading not initialized." << std::endl;
        return;
    }

    rovers.emplace_back(signal_strength,current_heading);
}

// Manual mode function to turn to specified "target" value
void Manager::turn_to_target(int target)
{
    motor_controller.rotate_to(target);
}

// Function to return to 0
void Manager::turn_to_zero()
{
    motor_controller.return_to_zero();
}

// Sets while loop flag to false
void Manager::stop_auto_mode()
{
    if (motor_running)
    {
        motor_running = {false};
        if (motor_thread.joinable())
        {
            motor_thread.join();
        }   
    }
}

void Manager::add_to_queue(const std::string& rover_ip, int heading)
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    data_queue.emplace(rover_ip,heading);
}

std::pair<std::string,int> get_from_queue()
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    if (data_queue.empty())
    {
        return {"",-1};
    }
    
    auto data = data_queue.front();
    data_queue.pop();
    return data;
}

bool is_queue_empty()
{
    std::lock_guard<std::mutex> lock(queue_mutex);
    return data_queue.empty();
}