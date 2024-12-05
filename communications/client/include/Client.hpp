#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
private:
    char* server_ip;
    int server_port;

public:
    Client(char* server_ip, int server_port);

    // std::string attempt_connection();

    int attempt_connection();
};
#endif