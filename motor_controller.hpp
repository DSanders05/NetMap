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
    int pulse_pin;                  // physical pin location for pulse_pin
    int enable_pin;                 // physical pin location for enable_pin
    int direction_pin;              // physical pin location for direction_pin

public:
    /* Public Functions */
    Motor_Controller();                             // Motor Controller Default Constructor
    Motor_Controller(int,int,int);                  // Motor Controller Custom Constructor
    ~Motor_Controller();                            // Motor Controller Deconstructor

    int initialize_motor_controller(int,int,int);   // Function to set Controller Variables
    int get_heading();                              // Returns current heading if initialized
    int update_heading(int);                        // Updates heading if initialized
    int step_motor(int);                            // Steps Motor
    int release_controller(int);                    // Deconstructs controller ending pigpio daemon
};
#endif