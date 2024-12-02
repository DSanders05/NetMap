#include "../include/Client.hpp"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>


Client::Client(const std::string& server_ip, int server_port)
: server_ip(server_ip), server_port(server_port)  { }



std::string  Client::attempt_connection() 
{
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) 
    {
        return "Failed to create socket.";
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) 
    {
        close(sock);
        return "Invalid server IP address.";
    }

    if (connect(sock, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) 
    {
        close(sock);
        return "Connection failed.";
    }

    const char* message = "REQUEST_SIGNAL_STRENGTH\n";
    if (send(sock, message, strlen(message), 0) < 0) 
    {
        close(sock);
        return "Send failed.";
    }

    char buffer[128] = {0};
    ssize_t len = recv(sock, buffer, sizeof(buffer) - 1, 0);

    close(sock);

    if (len > 0) 
    {
        return std::string(buffer, len);
    }
     else if (len == 0) 
    {
        return "Server closed the connection.";
    }
    else 
    {
        return "Receive failed.";
    }
}