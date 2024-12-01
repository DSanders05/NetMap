#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <iostream>
#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>
#include <vector>

class Client
{
private:
    int client_socket;
    std::string server_ip;
    int server_port;
    bool connected;

public:
    Client();

    ~Client();

    void attempt_connection();

    // std::string send_command(const std::string& command);

    std::string request_data();

    std::string send_command(const int& target,const std::string& mode);
};
#endif