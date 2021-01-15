#pragma once
#include <array>
#include <string>
#include <vector>

namespace own
{

    std::string getHeadersFromRequest(std::string const& input);

    std::string getBodyFromRequest(std::string const& input);

    std::vector<std::string> splitByDelimiter(std::string const& input, char const& delimiter);

    std::string findAndReplaceAll(std::string const& input, std::string const& toSearch, std::string const& replaceStr);

    size_t getBodySizeFromRawRequest(std::string const& rawData);
    
} // namespace own
