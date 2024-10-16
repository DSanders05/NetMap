#include <iostream>
#include "./motor_controller.hpp"
// #include <Python.h/>

/* Python API will need to be imported to call python commands */

int main(int argc, char* argv[])
{
    Motor_Controller controller = Motor_Controller();
    controller.claim_pins();
    controller.initialize_heading();
    controller.get_heading();
    controller.scan_area();
    
    std::cout << "Test Scan Complete." << std::endl;

    return 0;
}