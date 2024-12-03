#ifndef SERVER_HPP
#define SERVER_HPP

class Server
{
private:
    int server_port;

 public:
    Server(int port);
    void start();
    std::string get_sig_str();
};

#endif