#pragma once

#include <iostream>
#include <string>

namespace own
{
    std::vector<std::string> splitByDelimiter(std::string const& input, char const& delimiter)
    {
        std::stringstream ss(input);
        std::string tmp;
        std::vector<std::string> words{};

        while (getline(ss, tmp, delimiter))
        {
            words.push_back(tmp);
        }

        return words;
    }

    void findAndReplaceAll(std::string& data, std::string toSearch, std::string replaceStr)
    {
        // Get the first occurrence
        size_t pos = data.find(toSearch);
        // Repeat till end is reached
        while (pos != std::string::npos)
        {
            // Replace this occurrence of Sub String
            data.replace(pos, toSearch.size(), replaceStr);
            // Get the next occurrence from the current position
            pos = data.find(toSearch, pos + replaceStr.size());
        }
    }

} // namespace own
