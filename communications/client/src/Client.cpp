#include "../include/Client.hpp"

Client::Client(const std::string& ip, int port): server_ip(ip), server_port(port), client_socket(-1) {}

Client::~Client() 
{
    if (client_socket != -1)
    {
        close(client_socket);
    }
}

bool Client::connect_to_server() 
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("Socket creation failed.");
        return false;
    }
    
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip.c_str(), &server_address.sin_addr) <= 0 )
    {
        perror("Invalid address");
        return false;
    }

    if (connect(client_socket,(sockaddr*)&server_address,sizeof(server_address)) == -1)
    {
        perror("Connection failed.");
        return false;
    }
    
    std::cout << "Connected to server at " << server_ip << ":" << server_port << std::endl;
    return true;
}

std::string Client::send_command(const std::string& command) 
{
    if (client_socket == -1)
    {
        return "ERROR: Not connected to server.";
    }
    
    send(client_socket, command.c_str(), command.size(),0);

    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    int bytes_received = recv(client_socket,buffer,sizeof(buffer)-1,0);

    if (bytes_received <= 0)
    {
        return "ERROR: Failed to receive response from server.";
    }
    
    return std::string(buffer);
}