#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock = 0;
    struct sockaddr_in serv_addr;
    const char* message={"Hello from client"};
    char buffer[BUFFER_SIZE] = {0};

    // Creating a socket file descriptor
    if ((sock = socket(AF_INET, SOCK_STREAM,0)) < 0)
    {
        std::cerr << "Socket creation error" << std::endl;
        return -1;
    }

    serv_addr.sin_family = {AF_INET};
    serv_addr.sin_port = {htons(PORT)};

    // Conver IPv4 and IPv6 addresses from test to binary form
    if (inet_pton(AF_INET, "192.168.3.22", &serv_addr.sin_addr) <= 0)
    {
        std::cerr << "Invalid address / Address not supported" << std::endl;
        return -1;
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Connection failed" << std::endl;
        return -1;
    }

    // Send message to server
    send(sock, message, strlen(message), 0);
    std::cout << "Message sent to server: " << message << std::endl;

    // Read acknowledgement from server
    read(sock, buffer, 1024);
    std::cout << "Acknowledgement received from server: " << buffer << std::endl;
    
    close(sock);

    return 0;
}
