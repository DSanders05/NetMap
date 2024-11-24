#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <unistd.h>

class Client
{
private:
    int client_socket;
    std::string server_ip;
    int server_port;
public:
    Client(const std::string& ip, int port);

    ~Client();

    bool connect_to_server();

    std::string send_command(const std::string& command);
};
#endif