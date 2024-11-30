#include "../include/Client.hpp"

struct command
{
    std::string mode;
    int target;
};

Client::Client(const std::string& ip = {"192.168.3.10"}, int port = {12024}): server_ip(ip), server_port(port), client_socket(-1) {}

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

std::string Client::request_data() 
{
    if (client_socket == -1)
    {
        perror("ERROR: Not connected to server.");
    }
    
    std::string command = "DATA REQ";
    send(client_socket, command.c_str(), command.size(),0);

    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
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