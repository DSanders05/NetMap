#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include "../../communications/client/include/Client.hpp"
#include "../../motor_controls/include/motor_controller.hpp"

class Manager
{
private:
    Motor_Controller motor_controller;
    std::vector<std::string> server_ips;
    
public:
    Manager(const std::vector<std::string>& server_ips, int server_port);

    ~Manager();

    void start_auto_mode();

    void setup_zero();

    // void enter_target(int target);
};

#endif