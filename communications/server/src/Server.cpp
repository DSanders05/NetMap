#include "../include/Server.hpp"

Server::Server(int port = {55555}) 
    : port(port),server_socket(-1),running(false) 
{}

Server::~Server() {
    Server::stop_server();
}

void Server::handle_client(int client_socket)
{
    bool handling = {true};
    char buffer[1024];
    while (handling)
    {
        memset(buffer,0,sizeof(buffer));
        int bytes_received = recv(client_socket,buffer,sizeof(buffer)-1,0);

        if (bytes_received <= 0)
        {
            std::cout << "Client not connected." << std::endl;
            break;
        }
        
        std::string message(buffer);
        std::cout << "Received message: " << message << std::endl;

        std::string response;
        response = ("Message received: " + message);
        
        send(client_socket,response.c_str(),response.size(),0);
        handling = {false};

    }

    close(client_socket);
}

void Server::start_server() 
{
    server_socket = socket(AF_INET, SOCK_STREAM,0);
    if (server_socket == -1)
    {
        perror("Socket creation failed.");
        return;
    }
    
    sockaddr_in server_address={};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    server_address.sin_addr.s_addr = INADDR_ANY;

    if (bind(server_socket, (sockaddr*)&server_address,sizeof(server_address)) == -1)
    {
        perror("Server socket binding failed.");
        return;
    }

    if (listen(server_socket,5)==-1)
    {
        perror("Socket failed to listening for incoming connections.");
        return;
    }
    
    running = true;

    std::cout << "Server listening on port: " << port << std::endl;

    while (running)
    {
        sockaddr_in client_address = {};
        socklen_t client_len = sizeof(client_address);
        int client_socket = accept(server_socket, (sockaddr*)&client_address,&client_len);
        if (client_socket == -1)
        {
            if (running)
            {
                perror("Accept failed.");
            }
            continue;
        }

        std::cout << "Client connected." << std::endl;
        client_threads.emplace_back(&Server::handle_client,this,client_socket);
    }
}

void Server::stop_server()
{
    running = false;
    close(server_socket);
    for (auto& thread : client_threads)
    {
        if (thread.joinable())
        {
            thread.join();
        }
    }
}