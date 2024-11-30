#include "app_manager/include/manager.hpp"

int main(int argc, char* argv[])
{
    Manager net_map = Manager();

    net_map.start_auto_mode();
    return 0;
}