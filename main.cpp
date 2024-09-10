#include "./motor_controller.cpp"

int main(int argc, char* argv[])
{
    Motor_Controller controller = Motor_Controller();
    controller.initialize_heading();
    controller.get_heading();
    controller.~Motor_Controller();

    return 0;
}