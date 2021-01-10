#pragma once

#include <string>
#include <vector>
#include "stringHelper.cpp"
#include "httpMethods.cpp"
#include "config.hpp"

namespace own
{

    auto executeRequest(std::string const &method, std::string const &resource, std::string const &body)
    {
        const std::string URL = ROOT_FOLDER + resource;

        if (method == "GET") {
            return GET(URL);
        }
        if (method == "HEAD") {
            return HEAD(URL);
        }
        if (method == "PUT") {
            return PUT(URL, body);
        }
        if (method == "DELETE") {
            return DELETE(URL);
        }

        return response(501);
    }

    auto proceedRequest(std::string const &input)
    {
        const std::string header = getHttpRequestHeaders(input);
        if (header.empty())
        {
            return response(400);
        }

        std::vector<std::string> mainHeader = splitByDelimiter(header, '\n');
        std::vector<std::string> headerFirstLine = splitByDelimiter(mainHeader.at(0), ' ');
        if (headerFirstLine.size() != 3)
        {
            return response(400);
        }

        const std::string method = headerFirstLine.at(0);
        const std::string resource = headerFirstLine.at(1);
        const std::string body = getHttpRequestBody(input);

        // simple path traversal blocker
        if (resource.find("/../") != std::string::npos)
        {
            return response(403);
        }

        const std::string response = executeRequest(method, resource, body);

        return response;
    }

} // namespace own
