#include <array>
#include <iostream>
#include <string>

#include "stringHelper.hpp"


namespace own
{

    std::array<std::string, 4> parseRequest(std::string const &rawData)
    {
        const auto input = own::findAndReplaceAll(rawData, "\r\n", "\n");

        const auto headers = getHeadersFromRequest(input);
        const auto mainHeader = splitByDelimiter(headers, '\n');

        auto headerFirstLine = splitByDelimiter(mainHeader.at(0), ' ');

        // That's because first line of request must contain exactly 3 words
        // If less provided, URL and httpVersion are set to empty strings
        headerFirstLine.push_back("");
        headerFirstLine.push_back("");

        const auto method = headerFirstLine.at(0);
        const auto resource = headerFirstLine.at(1);
        const auto version = headerFirstLine.at(2);
        const auto body = getBodyFromRequest(input);

        std::cout << "\n" << method << " " << resource << std::flush;

        return std::array{method, resource, version, body};
    }
    
} // namespace own
