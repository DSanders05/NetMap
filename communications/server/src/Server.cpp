#include "../include/Server.hpp"
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>
#include <cstdlib>
#include <sstream>
#include <fstream>
#include <arpa/inet.h>

Server::Server() {}

void Server::start()
{
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = {1};
    int addrlen = sizeof(address);
    char buffer[1024]={0};
    std::string ack_message = {"Connection to server successful"};

    // Create socket file descriptor
    if ((server_fd = socket(AF_INET,SOCK_STREAM,0)) == 0)
    {
        std::cerr << "Socket failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    // Attach socket to port
    if (setsockopt(server_fd,SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
    {
        std::cerr << "Setsockopt failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = {AF_INET};
    address.sin_addr.s_addr = {inet_addr("127.0.0.1")};
    address.sin_port = {htons(8080)};

    // Bind socket to IP and port    
    if (bind(server_fd,(struct sockaddr*)&address,sizeof(address)) < 0)
    {
        std::cerr << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connection
    if (listen(server_fd, 3) <0)
    {
        std::cerr << "Listen failed." << std::endl;
        exit(EXIT_FAILURE);
    }
    
    std::cout << "Listening on port: " << 8080 << std::endl;

    while (true)
    {
        
    
    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0)
    {
        std::cerr << "Accept failed." << std::endl;
        exit(EXIT_FAILURE);
    }


    // Read message from client
    read(new_socket,buffer,1024);

    // Send acknowledgement message
    send(new_socket, ack_message.c_str(), ack_message.size(),0);
    
    close(new_socket);
    memset(buffer,0,sizeof(buffer));
    }
    close(server_fd);
}