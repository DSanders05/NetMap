#pragma once

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H


class Motor_Controller
{
private:
    /* 
    Create a private variable socket for the motor controller?
        - No way to differentiate ground vehicles when creating map
        - Limits the amount of connections for ground vehicles?
        - How to handle vehicles that are in a line? (this should be tested)
    */

    /* Data Variables */
    bool heading_initialized;       // flag used to track when heading becomes initialized on startup
    bool clockwise;                 // flag to track current turning direction 
    int control_mode;               // 0 - autonomous, 1 - user controlled
    double heading;                    // current heading relative to antenna's initialized zero
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

    int initialize_motor_controller(int, int, int);
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

    void initialize_heading();
    // Function to initialize heading of antenna 

    // Postcondition: heading_initialized={true};
    //                heading={0};

    // Error: Returns < 0

    static void heading_callback(int,unsigned int,unsigned int,uint32_t,void*);
    // Callback function for when GPIO Alert is triggered by limit switch

    // Precondition: limit switch must be enabled

    // Postcondition: heading_initialized={true};
    //                lim_sw_pin disabled

    // Error throws an exception

    void scan_area();
    // Non-Directional Scan area function to evaluate possible GV locations within area
    // Once full circle has been made, wait defined amount of time and repeat 
    // in reverse direction.

    // Precondition: heading_initialized={true};

    // Postcondition: 

    // Error: throw error

    void scan_area(int target);
    // Directional Scan based on target (degree value) location

    // Precondition: heading_initialized={true};

    // Postcondition: heading == target

    // Error: throw error

    void activate_motor();
    // Function to activate motor in provided direction and then update
    // heading to reflect the changes

    // Precondition: heading_initialized={true};

    // Postcondition: heading={heading+step} 

    // Error: Returns < 0

    float get_heading() const;
    // Function to return the current heading

    // Precondition: heading_initialized={true};

    // Postcondition: Returns current heading if initialized

    // Error: Returns < 0

    void set_heading(double change);
    // Function to update the heading variable

    // Precondition: heading_initialized={true}

    // Postcondition: heading = {heading + change};

    int change_mode(int new_mode);
    // Function to change the operating mode of the Motor Controller

    // Precondition: heading_initialized={true};

    // Postcondition: control_mode={new_mode};

    // Error: Returns < 0

    void release_controller(int);
    // Function to end pigpio daemon

    // Postcondition: Pigpio daemon stopped

    // Error: Returns < 0
};

#endif