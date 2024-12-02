#include "../include/manager.hpp"
#include <thread>

Manager::Manager(const std::vector<std::string>& server_ips, int server_port)
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

                if (i % 40 == 0) {  // Poll servers every 4 motor activations
                    std::vector<std::thread> threads;

                    for (const auto& ip : server_ips) {
                        threads.emplace_back([ip]() {
                            Client client(ip, 8080);
                            std::string response = client.attempt_connection();
                            std::cout << "Response from " << ip << ": " << response << std::endl;
                        });
                    }

                    // Join threads after polling all IPs
                    for (auto& thread : threads) {
                        thread.join();
                    }
                }
            }

            std::cout << "Heading after CCW rotation: " << motor_controller.get_heading() << std::endl;
        } else {
            motor_controller.set_ctr_clockwise(true);
            gpio_write(motor_controller.board_address, motor_controller.direction_pin, motor_controller.get_ctr_clockwise());

            for (size_t i = 0; i < 1200; i++) {
                motor_controller.activate_motor();
                motor_controller.set_heading(0.3f);

                if (i % 40 == 0) {
                    std::vector<std::thread> threads;

                    for (const auto& ip : server_ips) {
                        threads.emplace_back([ip]() {
                            Client client(ip, 8080);
                            std::string response = client.attempt_connection();
                            std::cout << "Response from " << ip << ": " << response << std::endl;
                        });
                    }

                    for (auto& thread : threads) {
                        thread.join();
                    }
                }
            }

            std::cout << "Heading after CW rotation: " << motor_controller.get_heading() << std::endl;
        }

        time_sleep(10);  // Pause between scans
    }

    gpio_write(motor_controller.board_address, motor_controller.pulse_pin, PI_LOW);
}


void Manager::setup_zero()
{
    motor_controller.initialize_heading();
}