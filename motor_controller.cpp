#include <iostream>
#include "./pigpiod_if2.h"

#include "./motor_controller.hpp"
#define GPIO_LIM_SW_PIN 25          // Physical Pin - 22
#define GPIO_DIR_PIN 22             // Physical Pin - 15
#define GPIO_PUL_PIN 15             // Physical Pin - 10

/* Motor Controller Functions */

Motor_Controller::Motor_Controller()
{
    initialize_motor_controller(GPIO_PUL_PIN,GPIO_LIM_SW_PIN,GPIO_PUL_PIN);
}

Motor_Controller::Motor_Controller(int pulse,int limit_switch_pin, int direction)
{
    initialize_motor_controller(pulse,limit_switch_pin,direction);
}

Motor_Controller::~Motor_Controller()
{
    release_controller(board_address);
}

int Motor_Controller::initialize_motor_controller(int pulse={GPIO_PUL_PIN},int limit_switch_pin={GPIO_LIM_SW_PIN}, int direction={GPIO_DIR_PIN})
{
    board_address = {pigpio_start(NULL,NULL)};
    if (board_address < 0)
    {
        std::cout << "Unable to initialize Motor Controller GPIO." << std::endl;
        return -1;
    }
    control_mode={0};
    clockwise={true};
    heading_initialized={false};
    
    pulse_pin = {pulse};
    lim_sw_pin = {limit_switch_pin};
    direction_pin = {direction};
    std::cout << "Motor Controller GPIO initialized successfully" << std::endl;
    return 0;
}

int Motor_Controller::claim_pins()
{
    set_mode(board_address,pulse_pin,PI_INPUT);
    set_mode(board_address,lim_sw_pin,PI_INPUT);
    set_mode(board_address,direction_pin,PI_INPUT);
    return 0;
}

int Motor_Controller::initialize_heading()
{

    return 0;
}

int Motor_Controller::release_controller(int board_address)
{
    pigpio_stop(board_address);
}

int Motor_Controller::get_heading() const
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

int Motor_Controller::update_heading(int new_heading)
{
    return 0;
}

int Motor_Controller::step_motor(bool rot_direction)
{
    return 0;
}

int Motor_Controller::change_mode(int new_mode)
{
    if (new_mode < 0 || new_mode > 1)
    {
        std::cout << "Mode can only be switched between 0 (autonomous) and 1 (user-controlled) modes." << std::endl;
        return -1;
    }
    else if (control_mode == new_mode && new_mode == 0)
    {
        std::cout << "The Motor Controller is already in autonomous mode. Change to mode 1 for user-controlled mode." << std::endl;
        return 0;
    }
    else if (control_mode == new_mode && new_mode ==1)
    {
        std::cout << "The Motor Controller is already in user-controlled mode. Change to mode 0 for autonomous mode." << std::endl;
        return 0;
    }
    else
    {
        control_mode={new_mode};
        return 0;
    }
}