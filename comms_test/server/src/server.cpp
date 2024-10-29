#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = {1};
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE] = {0};
    const char* ack_message = {" --- message from client acknowledged."};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cerr << "Socket failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "Setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = {AF_INET};
    address.sin_addr.s_addr = {inet_addr("192.168.3.22")}; // Server IP
    address.sin_port = {htons(PORT)};

    // Bind the socket to the IP and port
    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0)
    {
        std::cerr << "Listen failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Accept the incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
        std::cerr << "Accept failed." << std::endl;
        exit(EXIT_FAILURE);
    }

    // Read message from client
    read(new_socket, buffer, 1024);
    std::cout << "Message received from client: " << buffer << std::endl;

    // Create acknowledgement message
    std::string response = std::string(buffer) + ack_message;

    // Send acknowledgement back to the client
    send(new_socket, response.c_str(), response.size(), 0);
    std::cout << "Acknowledgement sent to client: " << response << std::endl;

    close(new_socket);
    close(server_fd);

    return 0;
}
