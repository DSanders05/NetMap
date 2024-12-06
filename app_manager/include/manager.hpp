#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "../../communications/client/include/Client.hpp"
#include "../../motor_controls/include/motor_controller.hpp"
#include <atomic>
#include <thread>

class Manager
{
private:
    Motor_Controller motor_controller;
    std::vector<const std::string> server_ips;
    std::atomic<bool> motor_running = {false};
    std::thread motor_thread;

    std::vector<std::pair<std::string, double>> rovers;
public:

    Manager(std::vector<const std::string>& server_ips, int server_port);

    ~Manager();

    void start_thread();

    void start_auto_mode();

    void init_zero();

    void update_rovers(const std::string& signal_strength);

    void turn_to_target(int target);

    void turn_to_zero();

    void stop_auto_mode();
};

#endif