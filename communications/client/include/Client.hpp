#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
private:
    std::string server_ip;
    int server_port;

public:
    Client(const std::string& server_ip, int server_port);

    std::string attempt_connection();
};
#endif