#pragma once

#include <string>
#include <sys/socket.h>

class Server 
{
public:
    Server(int16_t port) : _port(port) {}

    void run();

private:
    void _listen();

    int16_t _port;
};


