#include "../include/Client.hpp"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>

#define PORT 8080

Client::Client(const std::string& ip, int port)
    : server_ip(ip), server_port(port) {}

int Client::attempt_connection()
{
    int sock = 0;
    struct sockaddr_in serv_addr{};
    const char* message={"Connection attempt."};
    char buffer[1024] = {0};

    if((sock=socket(AF_INET,SOCK_STREAM,0)) < 0)
    {
        std::cerr << "Unable to create socket." << strerror(errno) << std::endl;
        return -1;
    }

    // Set timeout so client does not block indefinitely
    // on failed connection attempts
    timeval timeout{};
    timeout.tv_sec = 2; // 2 second timeout
    timeout.tv_usec = 0;

    // Configure server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0 ||
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) 
    {
        std::cerr << "Failed to set socket timeout: " << strerror(errno) << std::endl;
        close(sock);
        return -1;
    }

    if (inet_pton(AF_INET, server_ip.c_str(), &serv_addr.sin_addr) <= 0) 
    {
        std::cerr << "Invalid server IP address: " << server_ip << std::endl;
        close(sock);
        return -1;
    }

    // Connect to the server
    if (connect(sock, reinterpret_cast<struct sockaddr*>(&serv_addr), sizeof(serv_addr)) < 0) 
    {
        std::cerr << "Connection failed to " << server_ip << ":" << server_port << " - " << strerror(errno) << std::endl;
        close(sock);
        return -1;
    }

    // Send a message to the server
    if (send(sock, message, strlen(message), 0) < 0) 
    {
        std::cerr << "Failed to send message to server: " << strerror(errno) << std::endl;
        close(sock);
        return -1;
    }
    std::cout << "Message sent to server: " << server_ip << ":" << server_port << std::endl;

    // Receive response from the server
    ssize_t len = read(sock, buffer, sizeof(buffer) - 1);
    if (len > 0) 
    {
        buffer[len] = '\0';  // Null-terminate the response
        std::cout << "Received response from server: " << buffer << std::endl;
    }
    else if (len == 0) 
    {
        std::cerr << "Server closed the connection: " << server_ip << std::endl;
    } 
    else 
    {
        std::cerr << "Failed to receive data from server: " << strerror(errno) << std::endl;
        close(sock);
        return -1;
    }

    close(sock);

    return 1;
}