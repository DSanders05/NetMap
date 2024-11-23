#include <iostream>
#include "../pigpio-master/pigpiod_if2.h"
#include "../include/motor_controller.hpp"

// IP for antenna 130.74.33.50

/* 
   TODO LIST
   Target Direction Function
   Change Mode Function
*/

#define GPIO_LIM_SW_PIN 5          // Physical Pin - 29     Had to change to pin 29 for clock timing for callback function
#define GPIO_DIR_PIN 18             // Physical Pin - 15    HIGH IS CW, LOW IS CCW
#define GPIO_PUL_PIN 24             // Physical Pin - 10

#define MID 176                     // (Degrees) 
#define WAIT_PERIOD 0.01             // Time between each step

#define STEP_MAX 1200               // Number of steps in full 360 degree rotation
#define DEG_TO_STEPS STEP_MAX/360   // Convert from degree to steps

#define STEPS_PER_REV 360/1200

Motor_Controller::Motor_Controller()
{
    initialize_motor_controller(GPIO_PUL_PIN,GPIO_LIM_SW_PIN,GPIO_DIR_PIN);
}

/* Motor Controller Functions */
Motor_Controller::Motor_Controller(int pulse={GPIO_PUL_PIN},int limit_switch_pin={GPIO_LIM_SW_PIN}, int direction={GPIO_DIR_PIN})
{
    initialize_motor_controller(pulse,limit_switch_pin,direction);
}

Motor_Controller::~Motor_Controller()
{
    release_controller(board_address);
}

int Motor_Controller::initialize_motor_controller(int pulse, int limit_switch_pin, int direction)
{
    // This function establishes a connection between the 
    // PIGPIO daemon and the RPi
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

    std::cout << "Motor Controller GPIO initialized successfully. Board Number: " << board_address << std::endl;
    return 0;
}

int Motor_Controller::claim_pins()
{
    // This function sets the mode for all the pins to be used by the RPi
    int resistor_set;

    set_mode(board_address,lim_sw_pin,PI_INPUT);
    set_mode(board_address,lim_sw_pin,PI_PUD_UP);
    
    set_glitch_filter(board_address,5,0500);

    set_mode(board_address,pulse_pin,PI_INPUT);
    set_mode(board_address,direction_pin,PI_INPUT);
    return 0;
}

void Motor_Controller::initialize_heading()
{
    // This function will run on initial startup of the antenna
    // to initialize the heading to a relative 0 degrees

    int cb_id = callback_ex(board_address,GPIO_LIM_SW_PIN,EITHER_EDGE,Motor_Controller::heading_callback,this);
    gpio_write(board_address,direction_pin,clockwise);

    while (!heading_initialized)
    {
        activate_motor();
    }
    
    std::cout << "Heading is initialized." << std::endl;
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

void Motor_Controller::scan_area()      // NEED TO FINISH
{
    /*
        Start at 0
        Scan clockwise until 360 degrees
        Reverse direction
        Scan back other way 
        Wait 15 sec.
        Repeat
    */

   // TODO - Listen for keyboard interrupt to change modes?

    bool scanning={true};
   
     if (heading_initialized == false)
         {
             initialize_heading();
         }

    time_sleep(2);
    std::cout << "Beginning area scan..." << std::endl;
    

    while (scanning)
    {
        if (clockwise)
        {
            clockwise={false};
            gpio_write(board_address,direction_pin,clockwise);
        }
        else
        {
            clockwise={true};
            gpio_write(board_address,direction_pin,clockwise);
        }
        

         for (size_t i = 0; i < 1200; i++)
        {
            activate_motor();
            set_heading(0.3f);
        }

        std::cout << "Heading after first rotation: " << get_heading() << std::endl;

        time_sleep(15);

        if (clockwise)
        {
            clockwise={false};
            gpio_write(board_address,direction_pin,clockwise);
        }
        else
        {
            clockwise={true};
            gpio_write(board_address,direction_pin,clockwise);
        }

        for (size_t i = 0; i < 1200; i++)
        {
            activate_motor();
            set_heading(0.3f);
        }

        std::cout << "Heading after second rotation: " << get_heading() << std::endl;

        time_sleep(15);
    }
    
    gpio_write(board_address,pulse_pin,PI_LOW);
}

void Motor_Controller::scan_area(int target)  // FINISH LAST
{
    // Change target to double
    // Find which direction would be more efficient to move in
    // Change direction
    // Move to target location and update when target has been reached
    activate_motor();
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

float Motor_Controller::get_heading() const
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

void Motor_Controller::set_heading(double change)
{
    // If {heading + change} is going to make heading go above 360 degrees
    // then we will need to do 360 - change for update value.

    // Set_heading does not need to be used for every pulse unless in area_scan function.

    // Should we travel back to zero each time we go back into scan_area function?
    heading = {heading + change};
}

int Motor_Controller::change_mode(int new_mode)
{
    // This function should change the mode of operation of the antenna
    // 0 - autonomous mode 
    // 1 - user controlled mode 

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

void Motor_Controller::release_controller(int board_address)
{
    pigpio_stop(board_address);
}