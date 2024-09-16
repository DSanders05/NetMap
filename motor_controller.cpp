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

#define MID 176                     // (Degrees) 
#define READ_PERIOD 0.1             // (Seconds) Time between reads AND min time between steps?

#define STEP_MAX 1200               // Number of steps in full 360 degree rotation
#define DEG_TO_STEPS STEP_MAX/360   // Convert from degree to steps


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

int Motor_Controller::initialize_heading()
{
    gpio_write(board_address,direction_pin,clockwise);
    gpio_write(board_address,pulse_pin,PI_HIGH);
    gpioSetAlertFunc(board_address,heading_callback(board_address,PI_HIGH,gpioTick()));
    std::cout << "Heading is initialized." << std::endl;
    return 0;
}

gpioAlertFunc_t Motor_Controller::heading_callback(int gpio,int level,uint32_t tick)
{
    gpio_write(board_address,pulse_pin,PI_LOW);  
    std::cout << "GPIO Pin " << gpio << " changed output levels at: " << tick << std::endl;
    heading_initialized={true};
    set_mode(board_address,lim_sw_pin,PI_OFF);
    return;
}

void Motor_Controller::scan_area()
{
    /*
        Scan 360 degrees
        Wait 30 seconds
        Scan 360 degrees in opposite direction
    */
   activate_motor(clockwise);
}

int Motor_Controller::activate_motor(bool rot_direction)
{
    /*  
        check intended direction against current pin level
        if intended direction and pin level do not match, change pin level
        activate motor
        deactivate motor after step?
    */

    if (gpio_read(board_address,direction_pin) != rot_direction)
    {
        gpio_write(board_address,direction_pin,rot_direction);
    }

    gpio_write(board_address,pulse_pin,PI_HIGH);
    
    return 0;
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

int Motor_Controller::change_mode(int new_mode)
{
    if (control_mode != new_mode)
    {
        control_mode={new_mode};
    }
    else if (control_mode == new_mode)
    {
        switch (new_mode)
        {
        case 0:
            std::cout << "The antenna is already in autonomous mode." << std::endl;
            break;

        case 1:
            std::cout << "The antenna is already in user-controlled mode." << std::endl;
            break;
        }
    }
    return 0;
}

int Motor_Controller::release_controller(int board_address)
{
    pigpio_stop(board_address);
}