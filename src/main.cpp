#include <iostream>
#include "./motor_controller.hpp"

int main(int argc, char* argv[])
{
    Motor_Controller controller = Motor_Controller();
    controller.initialize_heading();
    controller.scan_area();
    controller.get_heading();

    // controller.scan_area();
    std::cout << "Test Scan Complete." << std::endl;

    return 0;
}