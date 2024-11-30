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
    Client();

    Client(const std::string& ip, int port);

    ~Client();

    bool connect_to_server();

    // std::string send_command(const std::string& command);

    std::string request_data();

    std::string send_command(const int& target,const std::string& mode);
};
#endif