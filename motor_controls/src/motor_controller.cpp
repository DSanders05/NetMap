#include <iostream>
#include <cmath>
#include "../include/motor_controller.hpp"

// IP for antenna 130.74.33.50

/* 
   TODO LIST
   Target Direction Function
   Change Mode Function
*/

#define GPIO_LIM_SW_PIN 5          // Physical Pin - 29     changed to pin 29 for clock timing for callback function
#define GPIO_DIR_PIN 18             // Physical Pin - 15    HIGH IS CCW, LOW IS CW
#define GPIO_PUL_PIN 24             // Physical Pin - 10

// #define MID 176                     // (Degrees) 
#define WAIT_PERIOD 0.01             // Time between each step

#define STEP_MAX 1200               // Number of steps in full 360 degree rotation
#define DEG_TO_STEPS STEP_MAX/360   // Convert from degree to steps      

/* Motor Controller Functions */
Motor_Controller::Motor_Controller()
{
    pulse_pin = GPIO_PUL_PIN;
    lim_sw_pin = GPIO_LIM_SW_PIN;
    direction_pin = GPIO_DIR_PIN;

    board_address = {pigpio_start(NULL,NULL)};
    if (board_address < 0)
    {
        std::cout << "Unable to initialize motor controller." << std::endl;
        return;
    }

    control_mode={0};
    ctr_clockwise={false};
    heading_initialized={false};

    set_mode(board_address,lim_sw_pin,PI_INPUT);
    set_mode(board_address,lim_sw_pin,PI_PUD_UP);
    
    set_glitch_filter(board_address,5,0500);

    set_mode(board_address,pulse_pin,PI_INPUT);
    set_mode(board_address,direction_pin,PI_INPUT);
}

Motor_Controller::~Motor_Controller()
{
    release_controller(board_address);
}

// int Motor_Controller::initialize_motor_controller(int pulse, int limit_switch_pin, int direction)
// {
//     // This function establishes a connection between the 
//     // PIGPIO daemon and the RPi
//     board_address = {pigpio_start(NULL,NULL)};
//     if (board_address < 0)
//     {
//         std::cout << "Unable to initialize Motor Controller GPIO." << std::endl;
//         return -1;
//     }
//     control_mode={0}; // 0 - autonomous mode, 1 - manual mode
//     clockwise={true};
//     heading_initialized={false};
    
//     pulse_pin = {pulse};
//     lim_sw_pin = {limit_switch_pin};
//     direction_pin = {direction};

//     std::cout << "Motor Controller GPIO initialized successfully. Board Number: " << board_address << std::endl;

//     std::cout << "Pins have been set up." << std::endl;
//     return 0;
// }

void Motor_Controller::initialize_heading()
{
    // This function will run on initial startup of the antenna
    // to initialize the headings "zero"

    int cb_id = callback_ex(board_address,GPIO_LIM_SW_PIN,EITHER_EDGE,Motor_Controller::heading_callback,this);
    gpio_write(board_address,direction_pin,ctr_clockwise);
    
    while (!heading_initialized)
    {
        activate_motor();
    }
    
    std::cout << "Heading is initialized." << std::endl;
}

// int Motor_Controller::claim_pins()
// {
//     // This function sets the mode for all the pins to be used by the RPi
//     // int resistor_set;

//     set_mode(board_address,lim_sw_pin,PI_INPUT);
//     set_mode(board_address,lim_sw_pin,PI_PUD_UP);
    
//     set_glitch_filter(board_address,5,0500);

//     set_mode(board_address,pulse_pin,PI_INPUT);
//     set_mode(board_address,direction_pin,PI_INPUT);
//     return 0;
// }

void Motor_Controller::release_controller(int board_address)
{
    pigpio_stop(board_address);
}

void Motor_Controller::heading_callback(int pi,unsigned int pin,unsigned int level,uint32_t tick,void* user_data)
{
    // This is the callback function that runs once the limit switch is pressed
    // Ignored if heading has already been established
    // If not established then the heading will be set to 0
    
    Motor_Controller* controller = static_cast<Motor_Controller*>(user_data);

    if (controller->heading_initialized == true)
    {
        return;
    }
    
    if (level == PI_HIGH)
    {
        controller->heading_initialized={true};
        controller->heading={0};
        std::cout << "The current heading is: " << controller->get_heading() << std::endl;
        gpio_write(controller->board_address,controller->pulse_pin,PI_LOW);
    }
    
}

void Motor_Controller::rotate_to(int int_target)
{
    // Change target to double
    double target = static_cast<double>(int_target);
    // std::cout << "The provided target is: " << target << std::endl;

    // Determine number of steps to new target
    int difference = std::abs((get_heading() - target)/0.3);

    // If we're rotating CW and going to target will take us below 0
    // Swap rotation
    if (!ctr_clockwise && (get_heading() - difference) < 0)
    {
        ctr_clockwise = {true};
        gpio_write(board_address,direction_pin,ctr_clockwise);
        // std::cout << "Approaching target counter-clockwise." << std::endl;

        for (size_t i = 0; i <= difference; i++)
        {
            activate_motor();
            set_heading(0.3f);
        }
    }
    else if (!ctr_clockwise)
    {
        gpio_write(board_address,direction_pin,ctr_clockwise);
        // std::cout << "Approaching target clockwise." << std::endl;

        for (size_t i = 0; i <= difference; i++)
        {
            activate_motor();
            set_heading(-0.3f);
        }
    }
    else if (ctr_clockwise && (get_heading() + difference) > 360)
    {
        ctr_clockwise = {false};
        gpio_write(board_address,direction_pin,ctr_clockwise);
        // std::cout << "Approaching target clockwise." << std::endl;

        for (size_t i = 0; i <= difference; i++)
        {
            activate_motor();
            set_heading(-0.3f);
        }
    }
    else if (ctr_clockwise)
    {
        gpio_write(board_address,direction_pin,ctr_clockwise);
        // std::cout << "Approaching target counter clockwise." << std::endl;

        for (size_t i = 0; i <= difference; i++)
        {
            activate_motor();
            set_heading(0.3f);
        }
    }

    // std::cout << "After turning to target " << target << " degrees, the current heading is: " << get_heading() << std::endl;
}

void Motor_Controller::return_to_zero()
{
    // Rotate clockwise back to zero
    if (!ctr_clockwise)
    {
        ctr_clockwise={true};
        gpio_write(board_address,direction_pin,ctr_clockwise);
    }
    
    while (get_heading() != 0.0)
    {
        activate_motor();
    }
}

void Motor_Controller::activate_motor()
{
    // This function activates the stepper motor for one step
    // and then deactivates the motor.

    // One step   == 0.3 degrees of rotation
    // 1200 steps == full rotation

    try
    {
        gpio_write(board_address,pulse_pin,PI_HIGH);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    time_sleep(WAIT_PERIOD);

    try
    {
        gpio_write(board_address,pulse_pin,PI_LOW);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

bool Motor_Controller::get_heading_init()
{
    return heading_initialized;
}

void Motor_Controller::set_heading_init()
{
    if (heading_initialized)
    {
        std::cout << "Heading has already been initialized." << std::endl;
    }
    else
    {
        heading_initialized = {true};
    }
    
}

bool Motor_Controller::get_ctr_clockwise()
{
    return ctr_clockwise;
}

void Motor_Controller::set_ctr_clockwise(bool new_clockwise)
{
    ctr_clockwise = {new_clockwise};
}

double Motor_Controller::get_heading()
{
    // This function returns the heading if it has been initialized

    if (heading_initialized > 0)
    {
        return heading;
    }
    else
    {
        return -1;
    }
}

void Motor_Controller::set_heading(double increment)
{
    // If {heading + change} is going to make heading go above 360 degrees
    // then we will need to do 360 - change for update value.

    // Set_heading does not need to be used for every pulse unless in area_scan function.

    // Should we travel back to zero each time we go back into scan_area function?
    heading = {heading + increment};
}

int Motor_Controller::get_ctrl_mode()
{
    return control_mode;
}

void Motor_Controller::set_ctrl_mode()
{
    control_mode = {(control_mode + 1) % 2};

    if (control_mode == 0)
    {
        std::cout << "Auto mode activated." << std::endl;
    }
    else
    {
        std::cout << "Manual mode activated." << std::endl;
    }
    
}