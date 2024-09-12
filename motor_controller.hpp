#pragma once 

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H


class Motor_Controller
{
private:
    /* Data Variables */
    bool heading_initialized;       // flag used to track when heading becomes initialized on startup
    bool clockwise;                 // flag to track current turning direction 
    int control_mode;               // 0 - autonomous, 1 - user controlled
    int heading;                    // current heading relative to antenna's initialized zero
    int board_address;              // board address returned from pigpio_start


    /* Pins */
    int pulse_pin;                  // gpio pin for pulse_pin
    int lim_sw_pin;                 // gpio pin for enable_pin
    int direction_pin;              // gpio pin for direction_pin

public:
    /* Public Functions */
    Motor_Controller();
    // Default Motor Controller Constructor
    // Calls Motor Controller initializer function

    // Postcondition: heading_initialized = {false};
    //                clockwise = {true};
    //                control_mode = {0};
    //                heading = {0}
    //                board_address = {pigpio(NULL,NULL)};
    //                pulse_pin = {};
    //                lim_sw_pin = {};
    //                direction_pin = {};

    Motor_Controller(int pulse,int lim_sw,int dir);
    // Motor Controller Custom Constructor

    // Postcondition: A new Motor Controller object is instantiated

    ~Motor_Controller();
    // Motor Controller Deconstructor

    // Postcondition: Motor Controller is destroyed
    // and the pigpio connection is also ended.

    int initialize_motor_controller(int pul,int lim_sw,int dir);
    // Function to set Controller Variables

    // Precondition: Function must be called by the instantiation
    // of a new Motor Controller object constructor.

    // Postcondition: Motor Controller Variables set
    //                heading_initialized = {false};
    //                clockwise = {true};
    //                control_mode = {0};
    //                heading = {0}
    //                board_address = {pigpio(NULL,NULL)};
    //                pulse_pin = {pul};
    //                lim_sw_pin = {lim_sw};
    //                direction_pin = {dir};

    // Error: Returns < 0

    int claim_pins();
    // Function to set initial pin values

    // Postcondition: 

    int initialize_heading();
    // Function to initialize heading of antenna 

    // Postcondition: heading_initialized={true};
    //                heading={0};

    // Error: Returns < 0

    int get_heading() const;
    // Function to return the current heading

    // Precondition: heading_initialized={true};

    // Postcondition: Returns current heading if initialized

    // Error: Returns < 0

    int update_heading(int);
    // Function to update the current heading

    // Precondition: heading_initialized={true};

    // Postcondition: Updates heading if initialized

    // Error: Returns < 0

    int activate_motor(bool clockwise);
    // Function to activate motor in provided direction and then update
    // heading to reflect the changes

    // Precondition: heading_initialized={true};

    // Postcondition: heading={heading+step} 

    // Error: Returns < 0

    int release_controller(int);
    // Function to end pigpio daemon

    // Postcondition: Pigpio daemon stopped

    // Error: Returns < 0

    int change_mode(int new_mode);
    // Function to change the operating mode of the Motor Controller

    // Precondition: heading_initialized={true};

    // Postcondition: control_mode={new_mode};

    // Error: Returns < 0
};
#endif