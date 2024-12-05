#include "../include/manager.hpp"
#include <thread>

Manager::Manager(std::vector<char*> server_ips, int server_port)
    :motor_controller(),server_ips(server_ips)
{
}

Manager::~Manager() 
{
    motor_controller.~Motor_Controller();

    std::cout << "App manager has been deconstructed." << std::endl;
}

void Manager::start_auto_mode()
{
    if (!motor_controller.get_heading_init()) {
        std::cout << "Initializing heading..." << std::endl;
        motor_controller.initialize_heading();
    }

    bool scanning = true;

    time_sleep(2);  // Initial pause

    std::cout << "Starting scan..." << std::endl;
    while (scanning) {
        if (motor_controller.get_ctr_clockwise()) {
            motor_controller.set_ctr_clockwise(false);
            gpio_write(motor_controller.board_address, motor_controller.direction_pin, motor_controller.get_ctr_clockwise());

            for (size_t i = 0; i < 1200; i++) {
                motor_controller.activate_motor();
                motor_controller.set_heading(-0.3f);

                if (i % 50 == 0) { 
                        for(auto ip : server_ips){
                            Client client(ip);
                            client.attempt_connection(ip);
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

            std::cout << "Heading after CCW rotation: " << motor_controller.get_heading() << std::endl;
        } else {
            motor_controller.set_ctr_clockwise(true);
            gpio_write(motor_controller.board_address, motor_controller.direction_pin, motor_controller.get_ctr_clockwise());

            for (size_t i = 0; i < 1200; i++) {
                motor_controller.activate_motor();
                motor_controller.set_heading(0.3f);

                if (i % 50 == 0) {
                    for(auto ip : server_ips){
                        Client client(ip);
                        client.attempt_connection(ip);
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

            std::cout << "Heading after CW rotation: " << motor_controller.get_heading() << std::endl;
        }

        time_sleep(10);  // Pause between scans
    }

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

void Manager::turn_to_target(int target)
{
    motor_controller.rotate_to(target);
}

void Manager::turn_to_zero()
{
    motor_controller.return_to_zero();
}

std::vector<std::pair<std::string,double>> Manager::get_rovers() const 
{
    return rovers;
}