#pragma once

#include <SPI.h>
#include <EthernetV2_0.h>
#include "config.hpp"

class HTTPServer
{
private:
    const char* m_address = NULL;
    uint32_t m_port = 0;
    EthernetServer m_server = NULL;
    bool m_ready = false;
public:
    HTTPServer(const char* address, uint32_t port);
    ~HTTPServer();
    void connect();
    void listen(); // Okay, so just keep this in the main loop and we're good to go.
    bool checkAvaibility() { return this->m_ready; }
};
