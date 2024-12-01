#include "app_manager/include/manager.hpp"

int main(int argc, char* argv[])
{
    int target = {};
    Manager net_map = Manager();

    net_map.setup_zero();

    // net_map.start_auto_mode();
    net_map.change_controller_mode();
    std::cout << "Enter a heading to turn to: " << std::endl;
    std::cin >> target;

    net_map.enter_target(target);

    std::cout << "Enter the next heading to turn to: " << std::endl;
    std::cin >> target;

    net_map.enter_target(target);
    return 0;
}