#ifndef MANAGER_HPP
#define MANAGER_HPP

#include <thread>
#include <atomic>
#include <iostream>
#include <vector>
#include <string>
#include "../../communications/client/include/Client.hpp"
#include "../../motor_controls/include/motor_controller.hpp"

class Manager
{
private:
    Client app_client;
    Motor_Controller motor_controller;
    
public:
    Manager();

    ~Manager();

    void start_auto_mode();

    void change_controller_mode();
};

#endif