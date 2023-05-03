#include "server.hpp"
#include "httpparser.hpp"

// this is the mac address specified to our device.
byte mac_address[] = {
    0xDE,
    0xAD,
    0xBE,
    0xEF,
    0xFE,
    0xED
};

HTTPServer::HTTPServer(const char* address, uint32_t port)
{
    // set address & port.
    this->m_address = address;
    this->m_port = port;
}

HTTPServer::~HTTPServer()
{
    // Are we supposed to do any cleaning afterwards?
}

void HTTPServer::connect()
{
    IPAddress ip;
    ip.fromString(this->m_address); // load ip from our string.

    // start the Ethernet connection.
    Ethernet.begin(mac_address, ip);

    Serial.println(Ethernet.localIP());

    // begin our server.
    m_server = EthernetServer(this->m_port);
    m_server.begin();

    this->m_ready = true; // Tell, the server is running and we're ready to inspect information.
}

bool led_state = false;
HTTPParser parser;

void HTTPServer::listen()
{
    EthernetClient client = this->m_server.available();
    if (client) {
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                parser.readHeader(c);
                if (c == '\n' && currentLineIsBlank) {

                    auto header = parser.parseHeader();

                    Serial.println(header.m_method);
                    Serial.println(header.m_path);
                    Serial.println(header.m_userAgent);

                    if (header.m_method == "GET" && header.m_path == "/analog")
                    {
                        int data = analogRead(ANALOG_PIN);
                        // send a standard http response header
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-Type: text/html");
                        client.println("Connnection: close");
                        client.println();
                        client.println("<!DOCTYPE HTML>");
                        client.println("<html>");
                        String _data = String(data);
                        client.println("<h1>Analog data is " + _data + "</h1>");
                        client.println("</html>");
                    }

                    break;
                }

                if (c == '\n') {
                    // you're starting a new line
                    currentLineIsBlank = true;
                } 
                
                else if (c != '\r') {
                    // you've gotten a character on the current line
                    currentLineIsBlank = false;
                }
            }
        }
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();
    }
}