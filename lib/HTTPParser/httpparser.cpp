#include "httpparser.hpp"

HTTPHeader HTTPParser::parseHeader()
{
    HTTPHeader result;
    
    int pos = 0;
    int end_pos = 0;
    String line;

    // Parse request line
    end_pos = m_header.indexOf("\r\n", pos);
    line = m_header.substring(pos, end_pos);
    pos = end_pos + 2;  // Skip over \r\n

    int space_pos = line.indexOf(' ');
    if (space_pos != -1) {
        result.m_method = line.substring(0, space_pos);
        line = line.substring(space_pos + 1);

        space_pos = line.indexOf(' ');
        if (space_pos != -1) {
            result.m_path = line.substring(0, space_pos);
            line = line.substring(space_pos + 1);
            result.m_version = line;
        }
    }

    // Parse headers
    while (pos < m_header.length())
    {
        end_pos = m_header.indexOf("\r\n", pos);
        line = m_header.substring(pos, end_pos);
        pos = end_pos + 2;  // Skip over \r\n

        space_pos = line.indexOf(':');
        if (space_pos != -1) {
            String header_name = line.substring(0, space_pos);
            String header_value = line.substring(space_pos + 2);  // Skip over ': '

            if (header_name.equalsIgnoreCase("User-Agent")) {
                result.m_userAgent = header_value;
            }
        }
    }

    this->m_header = ""; // NULL, was not accepted.
    return result;
}