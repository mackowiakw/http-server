#include <sstream>
#include <string>
#include <vector>

#include "stringHelper.hpp"


namespace own
{

    std::string getHeadersFromRequest(std::string const &input)
    {
        std::string str2find("\n\n");
        std::size_t pos = input.find(str2find);

        if (pos != std::string::npos) {
            return input.substr(0, pos);
        }
        else {
            return input;
        }
    }

    std::string getBodyFromRequest(std::string const &input)
    {
        std::string str2find("\n\n");
        std::size_t pos = input.find(str2find);

        if (pos != std::string::npos) {
            return input.substr(pos + str2find.length());
        }
        else {
            return std::string{""};
        }
    }

    std::vector<std::string> splitByDelimiter(std::string const &input, char const &delimiter)
    {
        std::stringstream ss(input);
        std::string tmp;
        std::vector<std::string> words{};

        while (getline(ss, tmp, delimiter)) {
            words.push_back(tmp);
        }

        return words;
    }

    std::string findAndReplaceAll(std::string const& input, std::string const& toSearch, std::string const& replaceStr)
    {
        std::string data{ input };
        size_t pos = data.find(toSearch);

        while (pos != std::string::npos) {
            // Replace this occurrence of Sub String
            data.replace(pos, toSearch.size(), replaceStr);
            // Get the next occurrence from the current position
            pos = data.find(toSearch, pos + replaceStr.size());
        }

        return data;
    }

    size_t getBodySizeFromRawRequest(std::string const& rawData)
    {
        const auto input = findAndReplaceAll(rawData, "\r\n", "\n");
        return getBodyFromRequest(input).size();
    }

} // namespace own
