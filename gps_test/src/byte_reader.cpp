#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "../mavlink/generated/include/common/mavlink.h"

int open_serial_port(const char*);
void measure_bytes(int);

int main()
{
    const char* serial_port_name = "/dev/ttyACM0"; // USB port
    int serial_port = open_serial_port(serial_port_name);
    if (serial_port < 0)
    {
        return 1;
    }

    std::cout << "Serial Port " << serial_port << " was opened successfully." << std::endl;
    measure_bytes(serial_port);

    close(serial_port);
    
    return 0;
}

int open_serial_port(const char* port)
{
    int serial_port = open(port, O_RDWR);
    if (serial_port < 0)
    {
        std::cerr << "Error " << errno << " opening " << port << ": " << strerror(errno) << std::endl;
        return -1;
    }

    struct termios tty;
    if (tcgetattr(serial_port, &tty) != 0)
    {
        std::cerr << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
        return -1;
    }
    
    tty.c_cflag &= ~PARENB;
    tty.c_cflag &= ~CSTOPB;
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    tty.c_cflag |= CREAD | CLOCAL;

    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);

    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        std::cerr << "Error " << errno << " from tcsetattr: " << strerror(errno) << std::endl;
        return -1;
    }
    

    return serial_port;
}

void measure_bytes(int port)
{
    while (true)
    {
        char buf[256];
        int num_bytes = read(port, &buf, sizeof(buf));
        
        std::cout << "Number of bytes received: " << num_bytes << std::endl;
    }
}