#include "../include/manager.hpp"
#include <thread>

// Manager Constructor
Manager::Manager(std::vector<char*> server_ips, int server_port)
    :motor_controller(),server_ips(server_ips)
{
}

// Manager Deconstructor (also deconstructs the RPi motor controller)
Manager::~Manager() 
{
    motor_controller.~Motor_Controller();

    std::cout << "App manager has been deconstructed." << std::endl;
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

    // If we're re-entering from manual mode go back to "0" before continuing
    // Going back to "0" just lets us ignore our heading when re-entering and gives a 
    // common starting point for code below.
    motor_controller.return_to_zero();

    // Flag to exit loop when we change modes
    motor_running = {true};

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

                // After every 15 degrees attempt to connect to ground vehicles
                if (i % 50 == 0) { 
                        for(auto ip : server_ips){
                            Client client(ip,8080);
                            if(client.attempt_connection() == 1)
                            {
                                std::cout << "Successfully connected to " << ip << std::endl;
                            }
                        }
                    // Poll servers every 4 motor activations
                    // std::vector<std::thread> threads;

                    // for (const auto& ip : server_ips) {
                    //     threads.emplace_back([this, ip]() {
                    //         Client client(ip, 8080);
                    //         std::string response = client.attempt_connection();
                    //         if (!response.empty()) {
                    //             update_rovers(response);
                    //          }
                    //     });
                    // }


                    // // Join threads after polling all IPs
                    // for (auto& thread : threads) {
                    //     thread.join();
                    // }
                }
            }
        } else {
            // Swap rotation direction and repeat steps from above
            motor_controller.set_ctr_clockwise(true);
            gpio_write(motor_controller.board_address, motor_controller.direction_pin, motor_controller.get_ctr_clockwise());

            // Another 1200 steps for full rotation
            for (size_t i = 0; i < 1200; i++) {
                motor_controller.activate_motor();

                // This loop is for CCW rotation so we add 0.3 until 360 degrees
                motor_controller.set_heading(0.3f);

                // After every 15 degrees we try to connect to ground vehicles
                if (i % 50 == 0) {
                    for(auto ip : server_ips){
                        Client client(ip,8080);
                       if(client.attempt_connection() == 1)
                       {
                            std::cout << "Successfully connected to " << ip << std::endl;
                       }
                    };
                //     std::vector<std::thread> threads;

                //     for (const auto& ip : server_ips) {
                //         threads.emplace_back([this, ip]() {
                //             Client client(ip, 8080);
                //             std::string response = client.attempt_connection();
                //             if (!response.empty()) {
                //                 update_rovers(response);
                //             }
                //         });
                //     }


                //     for (auto& thread : threads) {
                //         thread.join();
                //     }
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

std::vector<std::pair<std::string,double>> Manager::get_rovers() const 
{
    return rovers;
}

// Sets while loop flag to false
void Manager::stop_auto_mode()
{
    motor_running = false;
}