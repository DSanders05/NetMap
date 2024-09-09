#include <iostream>
#include "./pigpiod_if2.h"

#include "./motor_controller.hpp"

/* Motor Controller Functions */

Motor_Controller::Motor_Controller()
{
    // initialize_motor_controller();
}

Motor_Controller::Motor_Controller(int pulse,int enable, int direction)
{
    /* Custom Constructor Function */
    initialize_motor_controller(pulse,enable,direction);
}

Motor_Controller::~Motor_Controller()
{
    /* Destructor Function, this function will end pigpio process */
    release_controller(board_address);
}

int Motor_Controller::initialize_motor_controller(int pulse,int enable, int direction)
{
    board_address = {pigpio_start(NULL,NULL)};
    if (board_address < 0)
    {
        std::cout << "Unable to initialize Motor Controller GPIO." << std::endl;
        return -1;
    }
    clockwise={true};
    heading_initialized={false};
    
    pulse_pin = {pulse};
    enable_pin = {enable};
    direction_pin = {direction};
    std::cout << "Motor Controller GPIO initialized successfully" << std::endl;
    return 0;
}

int Motor_Controller::release_controller(int board_address)
{
    pigpio_stop(board_address);
}

int Motor_Controller::get_heading()
{
    if (heading_initialized > 0)
    {
        return heading;
    }
    else
    {
        return -1;
    }
}