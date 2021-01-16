#pragma once
#include <array>
#include <string>
#include <vector>

namespace own
{

    [[nodiscard]] std::string getHeadersFromRequest(std::string const& input);

    [[nodiscard]] std::string getBodyFromRequest(std::string const& input);

    [[nodiscard]] std::vector<std::string> splitByDelimiter(std::string const& input, char const& delimiter);

    [[nodiscard]] std::string findAndReplaceAll(std::string const& input, std::string const& toSearch, std::string const& replaceStr);

    [[nodiscard]] std::string encodeNewlinesInResponseHeaders(std::string const& input);
    
    [[nodiscard]] size_t getBodySizeFromRawRequest(std::string const& rawData);

} // namespace own
