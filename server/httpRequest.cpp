#include <string>
#include <vector>
#include "httpParser.cpp"

namespace own{

std::string executeRequest(std::string const& method, std::string const& resource,
                           std::string const& version, std::string const& body)
{
    // IMPLEMENT GET HEAD POST DELETE METHODS
    // AND CALL THEM HERE

    // return "HTTP1.0 200 OK";
    return "HTTP1.0 501 Not Implemented";
}

std::string proceedRequest(std::string const& input)
{
    const std::string header = own::getHttpHeader(input);
    if (header == "") {
        return "HTTP/1.0 400 Bad Request";
    }

    std::vector<std::string> headerByLines = own::splitByDelimiter(header, '\n');
    std::vector<std::string> headerFirstLine = own::splitByDelimiter(headerByLines.at(0), ' ');
    if (headerFirstLine.size() != 3) {
        return "HTTP/1.0 400 Bad Request";
    }
    
    const std::string method = headerFirstLine.at(0);
    const std::string resource = headerFirstLine.at(1);
    const std::string version = headerFirstLine.at(2);
    const std::string body = own::getHttpBody(input);

    const std::string response = own::executeRequest(method, resource, version, body);

    return response;
}

}
