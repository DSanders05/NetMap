#ifndef SERVER_HPP
#define SERVER_HPP

#include <iostream>
#include <string.h>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <functional>

class Server
{
    private:
        int server_socket;
        int port;
        bool running;
        std::vector<std::thread> client_threads;

        void handle_client(int client_socket);
    public:
        Server(int port);
        
        ~Server();

        void start_server();

        void stop_server();
};

Server::Server(int port) {}

Server::~Server() {}

#endif