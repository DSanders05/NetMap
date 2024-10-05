#include <iostream>
#include "./motor_controller.hpp"

int main(int argc, char* argv[])
{
    Motor_Controller controller = Motor_Controller();
    controller.claim_pins();
    controller.initialize_heading();
    controller.get_heading();

    // controller.scan_area();
    std::cout << "Test Scan Complete." << std::endl;

    return 0;
}