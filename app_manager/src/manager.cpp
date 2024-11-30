#include "../include/manager.hpp"

Manager::Manager()
    : app_client(), motor_controller()
{
}

Manager::~Manager() 
{
    motor_controller.~Motor_Controller();
    app_client.~Client();

    std::cout << "App manager has been deconstructed." << std::endl;
}

void Manager::start_auto_mode()
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

    if (motor_controller.get_ctrl_mode() != 0)
    {
        motor_controller.set_ctrl_mode();
    }

    if (motor_controller.get_heading_init() == false)
        {
            motor_controller.initialize_heading();
        }

    bool scanning={true};

    time_sleep(2);  // 2 second pause

    if (motor_controller.get_heading() != 0.0)
    {
        motor_controller.return_to_zero();
    }

    while (scanning)
    {
        if (motor_controller.get_clockwise())
        {
            motor_controller.set_clockwise(false);
            gpio_write(motor_controller.board_address,motor_controller.direction_pin,motor_controller.get_clockwise());

            for (size_t i = 0; i < 1200; i++)
            {
                motor_controller.activate_motor();
                motor_controller.set_heading(0.3f);
                // if (i % 2 == 0)
                // {
                //     app_client.attempt_connection();
                // }
            }
            
            std::cout << "Heading after CCW rotation: " << motor_controller.get_heading() << std::endl;
        }
        else
        {
            motor_controller.set_clockwise(true);
            gpio_write(motor_controller.board_address,motor_controller.direction_pin,motor_controller.get_clockwise());

            for (size_t i = 0; i < 1200; i++)
            {
                motor_controller.activate_motor();
                motor_controller.set_heading(-0.3f);
                // if (i % 2 == 0)
                // {
                //     app_client.attempt_connection();
                // }
            }
            
            std::cout << "Heading after CW rotation: " << motor_controller.get_heading() << std::endl;
        }

        time_sleep(10);
    }
    
    gpio_write(motor_controller.board_address,motor_controller.pulse_pin,PI_LOW);
}

void Manager::change_controller_mode()
{
    motor_controller.set_ctrl_mode();
}