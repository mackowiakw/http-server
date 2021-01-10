#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "stringHelper.cpp"
#include "httpMethods.cpp"
#include "httpResponse.cpp"
#include "config.hpp"

namespace own
{

    auto getBodySizeFromRawRequest(std::string const& rawData)
    {
        const auto input = findAndReplaceAll(rawData, "\r\n", "\n");
        return getHttpRequestBody(input).size();
    }

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

    auto proceedRequest(std::string const &rawData)
    {
        const auto input = own::findAndReplaceAll(rawData, "\r\n", "\n");

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

        std::cout << "\n" << method << " " << resource << std::flush;

        // simple path traversal blocker
        if (resource.find("/../") != std::string::npos)
        {
            return response(403);
        }

        std::string response = executeRequest(method, resource, body) + "\n";
        response = own::findAndReplaceAll(response, "\n", "\r\n");

        return response;
    }

} // namespace own
