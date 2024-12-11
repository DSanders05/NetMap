#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <string>

class Client
{
private:
    const std::string& server_ip;
    int server_port;

public:
    Client(const std::string& server_ip, int server_port);

    int attempt_connection();
};
#endif