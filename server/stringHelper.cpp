#pragma once

#include <ctime>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <unordered_map>

namespace own
{

    auto response(int const code)
    {
        const std::unordered_map<int, std::string> messages = {
            { 200, "OK"                         },
            { 201, "Created"                    },
            { 204, "No Content"                 },
            { 300, "Multiple Choices"           },
            { 302, "Found"                      },
            { 304, "Not Modified"               },
            { 400, "Bad Request"                },
            { 403, "Forbidden"                  },
            { 404, "Not Found"                  },
            { 500, "Internal Server Eror"       },
            { 501, "Not Implemented"            },
        };

        std::stringstream ss;

        if (messages.count(code) > 0) {
            ss << "HTTP/1.1 " << code << " " << messages.at(code) << "\n";
        }
        else {
            ss << "HTTP/1.1 500 " << messages.at(500) << "\n";
        }


        std::time_t t = std::time(nullptr);

        ss << "Server: SK inf1412(54|69)\n";
        ss << "Date: " << std::put_time(std::gmtime(&t), "%c %Z") << "\n";

        return ss.str();
    }

    auto getHttpRequestHeaders(std::string const &input)
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

    auto getHttpRequestBody(std::string const &input)
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

    auto splitByDelimiter(std::string const &input, char const &delimiter)
    {
        std::stringstream ss(input);
        std::string tmp;
        std::vector<std::string> words{};

        while (getline(ss, tmp, delimiter)) {
            words.push_back(tmp);
        }

        return words;
    }

    auto findAndReplaceAll(std::string const& input, std::string const& toSearch, std::string const& replaceStr)
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

} // namespace own
