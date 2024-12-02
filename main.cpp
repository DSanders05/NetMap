// #include <pybind11/pybind11.h>
#include "app_manager/include/manager.hpp"


int main(int argc, char* argv[])
{
    std::vector<std::string> rover_ips = {
        "192.168.2.22",
        "192.168.2.33",
        "192.168.2.44",
        "192.168.2.55"
    };

    Manager net_map = Manager(rover_ips, 8080);

    net_map.start_auto_mode();
    
    return 0;
}