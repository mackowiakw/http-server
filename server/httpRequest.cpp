#pragma once

#include <string>
#include <vector>
#include "stringHelper.cpp"
#include "httpMethods.cpp"
#include "config.hpp"


namespace own
{

    auto executeRequest(std::string const& method, std::string const& resource, std::string const& body)
    {
        const std::string URL = ROOT_FOLDER + resource;

        if (method == "GET") {
            return own::GET(URL);
        }
        if (method == "HEAD") {
            return own::HEAD(URL);
        }
        if (method == "PUT") {
            return own::PUT(URL, body);
        }
        if (method == "DELETE") {
            return own::DELETE(URL);
        }

        return "HTTP/1.1 501 Not Implemented\n" + own::getBasicHeaders().str();
    }


    auto proceedRequest(std::string const& input)
    {
        const std::string header = own::getHttpRequestHeaders(input);
        if (header.empty())
        {
            return "HTTP/1.1 400 Bad Request\n" + own::getBasicHeaders().str();
        }

        std::vector<std::string> headerByLines = own::splitByDelimiter(header, '\n');
        std::vector<std::string> headerFirstLine = own::splitByDelimiter(headerByLines.at(0), ' ');
        if (headerFirstLine.size() != 3)
        {
            return "HTTP/1.1 400 Bad Request\n" + own::getBasicHeaders().str();
        }

        const std::string method = headerFirstLine.at(0);
        const std::string resource = headerFirstLine.at(1);
        const std::string version = headerFirstLine.at(2);
        const std::string body = own::getHttpRequestBody(input);

        // simple path traversal blocker
        if (resource.find("/../") != std::string::npos)
        {
            return "HTTP/1.1 403 Forbidden\n" + own::getBasicHeaders().str();
        }

        const std::string response = own::executeRequest(method, resource, body);

        return response;
    }

} // namespace own
