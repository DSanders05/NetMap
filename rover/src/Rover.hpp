/* 
    ROVER CLASS
*/

#pragma once
#ifndef ROVER_H
#define ROVER_H

#include <vector>
#include <string>
//#include <mavlink> - Import the mavlink message structure so that as we read them in we just bind the whole message to each rover instance?

class Rover
{
private:
    std::string rover_ip = {""};
    double gps_lat = {};
    double gps_lon = {};
public:
    Rover(/* args */);
    ~Rover();
};

Rover::Rover(/* args */)
{
}

Rover::~Rover()
{
}

#endif