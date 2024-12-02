#include "../include/Server.hpp"
#include <iostream>
#include <cstring>
#include <netinet/in.h>
#include <unistd.h>
#include <errno.h>

Server::Server(int port) : server_port(port) {}

void Server::start() {
    int server_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (server_sock < 0) {
        std::cerr << "Failed to create socket: " << strerror(errno) << "\n";
        return;
    }

    // Enable SO_REUSEADDR to avoid "address already in use" errors
    int opt = 1;
    if (setsockopt(server_sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Failed to set socket options: " << strerror(errno) << "\n";
        close(server_sock);
        return;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(server_port);

    if (bind(server_sock, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        std::cerr << "Binding failed: " << strerror(errno) << "\n";
        close(server_sock);
        return;
    }

    if (listen(server_sock, 5) < 0) {
        std::cerr << "Listening failed: " << strerror(errno) << "\n";
        close(server_sock);
        return;
    }

    std::cout << "Server is running on port " << server_port << "...\n";

    while (true) {
        sockaddr_in client_addr{};
        socklen_t client_len = sizeof(client_addr);
        int client_sock = accept(server_sock, reinterpret_cast<sockaddr*>(&client_addr), &client_len);

        if (client_sock < 0) {
            std::cerr << "Failed to accept connection: " << strerror(errno) << "\n";
            continue;
        }

        char buffer[128] = {0};
        ssize_t len = recv(client_sock, buffer, sizeof(buffer) - 1, 0);

        if (len > 0) {
            std::string request(buffer, len);
            std::cout << "Received request: " << request;

            if (request == "REQUEST_SIGNAL_STRENGTH\n") {
                std::string response = "Signal Strength: 75%\n";
                send(client_sock, response.c_str(), response.size(), 0);
            } else {
                std::cerr << "Invalid request received: " << request << "\n";
            }
        } else if (len == 0) {
            std::cerr << "Client disconnected gracefully.\n";
        } else {
            std::cerr << "Receive error: " << strerror(errno) << "\n";
        }

        close(client_sock);
    }

    close(server_sock);
}
