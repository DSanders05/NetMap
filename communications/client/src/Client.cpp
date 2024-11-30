#include "../include/Client.hpp"

struct command
{
    std::string mode;
    int target;
};

Client::Client()
: server_ip(""), server_port(0), client_socket(-1),connected(false) 
{
}

Client::~Client() 
{
    if (client_socket != -1)
    {
        close(client_socket);
    }
}

void Client::attempt_connection() 
{
    client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1)
    {
        perror("Socket creation failed.");
    }
    
    sockaddr_in server_address{};
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(server_port);

    if (inet_pton(AF_INET, server_ip.c_str(), &server_address.sin_addr) <= 0 )
    {
        perror("Invalid address");
    }

    if (connect(client_socket,(sockaddr*)&server_address,sizeof(server_address)) == -1)
    {
        perror("Connection failed.");
    }
    
    std::cout << "Connected to server at " << server_ip << ":" << server_port << std::endl;
}

std::string Client::request_data() 
{
    if (client_socket == -1)
    {
        perror("ERROR: Not connected to server.");
    }
    
    std::string command = "DATA REQ";
    send(client_socket, command.c_str(), command.size(),0);

    char buffer[1024];
    std::memset(buffer,0,sizeof(buffer));
    int bytes_received = recv(client_socket,buffer,sizeof(buffer)-1,0);

    if (bytes_received <= 0)
    {
        perror("ERROR: Failed to receive response from server.");
    }

    return buffer;
}

std::string Client::send_command(const int& target, const std::string& mode)
{
    if (mode != "MANU")
    {
        return "ERROR: Not in manual mode.";
    }

    std::string command = std::to_string(target);

    send(client_socket,command.c_str(),command.size(),0);
    
    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    int bytes_received = recv(client_socket,buffer,sizeof(buffer)-1,0);

    if (bytes_received <=0)
    {
        return "ERROR: Failed to received response from server.";
    }
    
    return buffer;
}