#include "../include/Client.hpp"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <errno.h>

#define PORT 8080

Client::Client(char* server_ip, int server_port)
    : server_ip(server_ip), server_port(server_port) {}

// std::string Client::attempt_connection() {
//     std::cout << "Attempting to connect to server: " << server_ip << ":" << server_port << std::endl;

//     int sock = socket(AF_INET, SOCK_STREAM, 0);
//     if (sock < 0)
//      {
//         return "Failed to create socket: " + std::string(strerror(errno));
//     }

//     // Set timeout for connect and recv operations
//     timeval timeout;
//     timeout.tv_sec = 2;  // 2 seconds
//     timeout.tv_usec = 0;

//     if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0 ||
//         setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0)
//      {
//         close(sock);
//         return "Failed to set socket timeout: " + std::string(strerror(errno));
//     }

//     sockaddr_in server_addr{};
//     server_addr.sin_family = AF_INET;
//     server_addr.sin_port = htons(server_port);

//     if (inet_pton(AF_INET, server_ip.c_str(), &server_addr.sin_addr) <= 0) 
//     {
//         close(sock);
//         return "Invalid server IP address: " + server_ip+"\n";
//     }

//     if (connect(sock, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) 
//     {
//         close(sock);
//         return "Connection failed to " + server_ip + ": " + std::string(strerror(errno))+"\n";
//     }

//     const char* message = "REQUEST_SIGNAL_STRENGTH\n";
//     if (send(sock, message, strlen(message), 0) < 0) 
//     {
//         close(sock);
//         return "Send failed to " + server_ip + ": " + std::string(strerror(errno))+"\n";
//     }

//     char buffer[128] = {0};
//     ssize_t len = recv(sock, buffer, sizeof(buffer) - 1, 0);

//     close(sock);

//     if (len > 0) 
//     {
//         return std::string(buffer, len) +"\n";
//     } 
//     else if (len == 0) 
//     {
//         return "Server " + server_ip + " closed the connection.";
//     }
//     else 
//     {
//         return "Receive failed from " + server_ip + ": " + std::string(strerror(errno)) +"\n";
//     }
// }


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

    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout)) < 0 ||
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout)) < 0) 
    {
        std::cerr << "Failed to set socket timeout: " << strerror(errno) << std::endl;
        close(sock);
        return -1;
    }

    // Configure server address
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) 
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