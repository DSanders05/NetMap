#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include "../mavlink/generated/include/common/mavlink.h"

int open_serial_port(const char*);
void read_gps_data(int);
void read_and_parse_mavlink(int);

int main()
{
    const char* serial_port_name = "/dev/ttyACM0"; // Adjust based on USB device
    int serial_port = open_serial_port(serial_port_name);
    if (serial_port < 0)
    {
        return 1;
    }
    
    std::cout << "Serial port " << serial_port << " has been opened successfully." << std::endl;
    // read_gps_data(serial_port);
    read_and_parse_mavlink(serial_port);
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

void read_gps_data(int serial_port)
{
    mavlink_message_t msg;
    mavlink_status_t status;

    uint8_t byte;
    while (true) {
        int num_bytes = read(serial_port, &byte, 1);
        if (num_bytes > 0) {
            // Parse the incoming byte into a MAVLink message
            if (mavlink_parse_char(MAVLINK_COMM_0, byte, &msg, &status)) {
                // Message parsed successfully, check its type
                // std::cout << "Status (Message Received):" << status.msg_received << std::endl;
                if (msg.msgid == MAVLINK_MSG_ID_GPS_RAW_INT) {
                    mavlink_gps_raw_int_t gps_data;
                    mavlink_msg_gps_raw_int_decode(&msg, &gps_data);

                    // Print GPS data
                    std::cout << "GPS Fix Type: " << (uint8_t)gps_data.fix_type << std::endl;
                    std::cout << "Latitude: " << (int32_t)gps_data.lat / 1e7 << " deg" << std::endl;
                    std::cout << "Longitude: " << (int32_t)gps_data.lon / 1e7 << " deg" << std::endl;
                    std::cout << "Altitude: " << (int32_t)gps_data.alt / 1000.0 << " meters" << std::endl;
                }
            }
        }
    }
}

void read_and_parse_mavlink(int serial_port) {
    mavlink_message_t msg;
    mavlink_status_t status;
    char buf[256];

    while (true) {
        int num_bytes = read(serial_port, &buf, sizeof(buf));

        if (num_bytes > 0) {
            std::cout << "Read " << num_bytes << " bytes." << std::endl;

            // Feed each byte to mavlink_parse_char one by one
            for (int i = 0; i < num_bytes; ++i) {
                int mav_parse_correctly = mavlink_parse_char(MAVLINK_COMM_0, static_cast<uint8_t>(buf[i]),&msg,&status);
                std::cout << "Parse code for prev. byte: " << mav_parse_correctly << std::endl;
                if (mavlink_parse_char(MAVLINK_COMM_0, static_cast<uint8_t>(buf[i]), &msg, &status)) {
                    // Successfully parsed a MAVLink message
                    if (msg.msgid == MAVLINK_MSG_ID_GPS_RAW_INT) {
                        mavlink_gps_raw_int_t gps_data;
                        mavlink_msg_gps_raw_int_decode(&msg, &gps_data);

                        std::cout << "GPS Fix Type: " << static_cast<int>(gps_data.fix_type) << std::endl;
                        std::cout << "Latitude: " << gps_data.lat / 1e7 << " deg" << std::endl;
                        std::cout << "Longitude: " << gps_data.lon / 1e7 << " deg" << std::endl;
                        std::cout << "Altitude: " << gps_data.alt / 1000.0 << " meters" << std::endl;
                    }
                }
            }
        }
    }
}

