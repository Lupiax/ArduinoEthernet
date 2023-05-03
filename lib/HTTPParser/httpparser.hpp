#ifndef __ARDUINO_HTTPPARSER_H_
#define __ARDUINO_HTTPPARSER_H_

#include <Arduino.h>

struct HTTPHeader {
    String m_method;
    String m_path;
    String m_version;
    String m_userAgent;
}; // HTTPHeader

class HTTPParser {
private:
    String m_header;
public:
    /* reads header character by character til it's done reading it */
    void readHeader(char c) { m_header += c; }
    /* parses header into HTTPHeader struct which then you can access */
    HTTPHeader parseHeader();
};

#endif // __ARDUINO_HTTPPARSER_H_