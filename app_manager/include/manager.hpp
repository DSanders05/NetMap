#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "../../communications/client/include/Client.hpp"
#include "../../motor_controls/include/motor_controller.hpp"

class Manager
{
private:
    Motor_Controller motor_controller;
    std::vector<std::string> server_ips;
    
    std::vector<std::pair<std::string, double>> rovers;
public:
    Manager(const std::vector<std::string>& server_ips, int server_port);

    ~Manager();

    void start_auto_mode();

    void setup_zero();

    void update_rovers(const std::string& signal_strength);

    std::vector<std::pair<std::string,double>> get_rovers() const;
};

#endif