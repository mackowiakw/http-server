#include <sstream>
#include <string>
#include <vector>
#include <unistd.h>

#include "requestReader.hpp"
#include "stringHelper.hpp"


namespace own
{

    std::string readRawRequestFromSocket(const int cfd)
    {
        // 1450 due to TCP MTU
        char buffer[1450] = {};
        read(cfd, buffer, 1450);
        std::stringstream firstPacket{buffer};
        std::string request{firstPacket.str()};

        size_t contentLength = 0;

        // Read Content-Length from the first recived TCP packet
        // If header not provided Content-Length equals 0
        std::string line;
        while (std::getline(firstPacket, line)) {

            auto words = own::splitByDelimiter(line, ' ');

            if (words.at(0) == "Content-Length:") {
                contentLength = std::stoi(words.at(1));
                break;
            }
        };

        // Read entire request body
        while (own::getBodySizeFromRawRequest(request) < contentLength) {
            char buffer[1450] = {};
            read(cfd, buffer, 1450);
            request += buffer;
        }

        return request;
    }

} // namespace own
