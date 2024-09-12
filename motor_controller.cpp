#include <iostream>
#include "./pigpiod_if2.h"

/* 
   TODO LIST
   Complete motor activation function
   Complete Heading init function
   Get Heading function
   Change Mode Function

   
   COMPLETED LIST
   Pin setup function
   Init Motor Function
   Default Motor_Controller Constructor
   Custom Motor_Controller Constructor
   Motor_Controller De-Constructor
   Release Controller Function

*/

#include "./motor_controller.hpp"
#define GPIO_LIM_SW_PIN 25          // Physical Pin - 22     ####NEED TO DOUBLE CHECK THESE PIN LOCATIONS####
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
    set_mode(board_address,lim_sw_pin,PI_INPUT);
    set_pull_up_down(board_address,lim_sw_pin,PI_PUD_DOWN);

    set_mode(board_address,pulse_pin,PI_INPUT);
    set_mode(board_address,direction_pin,PI_INPUT);
    return 0;
}

int Motor_Controller::activate_motor(bool rot_direction)
{
    if (gpio_read(board_address,direction_pin) != rot_direction)
    {
        /* If direction_pin does not match rot_direction (clockwise var) */
        
    }
    
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

int Motor_Controller::change_mode(int new_mode)
{
    return 0;
}