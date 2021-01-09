#pragma once

#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>

namespace own
{

    auto getBasicHeaders()
    {
        std::time_t t = std::time(nullptr);

        std::stringstream headers;
        headers << "Server: SK inf1412(54|69)\n";
        headers << "Date: " << std::put_time(std::gmtime(&t), "%c %Z") << "\n";

        return headers;
    }


    auto getHttpRequestHeaders(std::string const& input)
    {
        std::string str2find("\n\n");
        std::size_t pos = input.find(str2find);

        if (pos != std::string::npos)
        {
            return input.substr(0, pos);
        }
        else
        {
            return input;
        }
    }


    auto getHttpRequestBody(std::string const& input)
    {
        std::string str2find("\n\n");
        std::size_t pos = input.find(str2find);

        if (pos != std::string::npos)
        {
            return input.substr(pos + str2find.length());
        }
        else
        {
            return std::string{""};
        }
    }


    auto splitByDelimiter(std::string const& input, char const& delimiter)
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


    auto findAndReplaceAll(std::string input, std::string toSearch, std::string replaceStr)
    {
        std::string data{ input };

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

        return data;
    }

} // namespace own
