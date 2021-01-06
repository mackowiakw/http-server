#pragma once

#include <string>
#include <vector>
#include <sstream>

namespace own {

std::vector<std::string> splitByDelimiter(std::string const& input, char const& delimiter)
{
    std::stringstream ss(input);
    std::string tmp; 
    std::vector<std::string> words{};

    while(getline(ss, tmp, delimiter)) {
        words.push_back(tmp);
    }

    return words;
}

std::string getHttpRequestHeader(std::string const& input)
{
    std::string str2find ("\n\n");
    std::size_t pos = input.find(str2find);

    if (pos != std::string::npos) {
        return input.substr(0, pos);
    } else {
        return "";
    }
}

std::string getHttpRequestBody(std::string const& input)
{
    std::string str2find ("\n\n");
    std::size_t pos = input.find(str2find);

    if (pos != std::string::npos) {
        return input.substr(pos + str2find.length());
    } else {
        return "";
    }
}


}
