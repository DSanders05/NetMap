#include <string>

class Server
{
private:
    std::string rover_address = {};
    /* data */
public:
    Server(/* args */);
    ~Server();
    void send_gps_data();
};

Server::Server(/* args */)
{
}

Server::~Server()
{
}

void send_gps_data()
{
    
}