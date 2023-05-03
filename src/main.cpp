#include <Arduino.h>

#include "server.hpp"
#include "config.hpp"

// Create our HTTPServer object with our information from config.hpp
HTTPServer server(ETHERNET_ADDRESS, HTTPSERVER_PORT);

void setup() {
    // Start logging Serial with 9600 baudi rate.
    Serial.begin(9600);
    
    // Initialize some of our devices.
    pinMode(SDCARD_CS, OUTPUT);
    digitalWrite(SDCARD_CS, HIGH);

    // Initialize server.
    server.connect();
}

void loop() {
    if (server.checkAvaibility())
        server.listen(); // Start listening for new HTTP requests.
}