#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>

class Server
{
private:
    int server_port = {8080};

 public:
    Server();
    void start();
};

#endif