#include "Server.hpp"

int main()
{
    Server app_server = Server(8080);
    app_server.start();
    return 0;
}