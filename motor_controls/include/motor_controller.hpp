#include <pigpiod_if2.h>

#pragma once

#ifndef MOTOR_CONTROLLER_H
#define MOTOR_CONTROLLER_H


class Motor_Controller
{
    private:
        /* Data Variables */
        bool heading_initialized;       // flag used to track when heading becomes initialized
        bool clockwise;                 // flag to track current rotating direction 
        int control_mode;               // 0 - autonomous, 1 - user controlled
        double heading;                 // current heading relative to antenna's initialized zero

    public:
        /* Pins */
        int board_address;              // board address returned from pigpio_start
        int pulse_pin;                  // gpio pin for pulse_pin
        int lim_sw_pin;                 // gpio pin for enable_pin
        int direction_pin;              // gpio pin for direction_pin
        
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

        ~Motor_Controller();
        // Motor Controller Deconstructor

        int initialize_motor_controller(int pulse, int limit_switch_pin, int direction);
        // Sets Motor Controller Variables

        void initialize_heading();
        // Function to initialize heading of antenna 

        int claim_pins();
        // Function to set initial pin values

        void release_controller(int);
        // Function to end pigpio daemon

        static void heading_callback(int,unsigned int,unsigned int,uint32_t,void*);
        // Callback function for when GPIO Alert is triggered by limit switch

        void rotate_to(int int_target);
        // Directional Scan based on target (degree value) location

        void return_to_zero();
        // Rotate antenna back to "zero" heading

        void activate_motor();
        // Function to activate motor and update heading

        bool get_heading_init();
        // Returns heading_initialized flag

        void set_heading_init();
        // Sets heading_initialized flag

        bool get_clockwise();
        // Returns current clockwise flag

        void set_clockwise(bool new_clockwise);
        // Sets clockwise flag

        double get_heading();
        // Returns the current heading

        void set_heading(double increment);
        // Function to update the heading variable

        int get_ctrl_mode();
        // Returns the current controller mode

        void set_ctrl_mode();
        // Changes the controller mode
};

#endif