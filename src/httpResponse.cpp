#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <unordered_map>

#include "httpResponse.hpp"


namespace own
{

    std::string response(int const code)
    {
        const std::unordered_map<int, std::string> messages = {
            {200, "OK"},
            {201, "Created"},
            {204, "No Content"},
            {300, "Multiple Choices"},
            {302, "Found"},
            {304, "Not Modified"},
            {400, "Bad Request"},
            {403, "Forbidden"},
            {404, "Not Found"},
            {405, "Method Not Allowed"},
            {500, "Internal Server Error"},
            {501, "Not Implemented"},
        };

        std::stringstream ss;

        if (messages.count(code) > 0)
        {
            ss << "HTTP/1.1 " << code << " " << messages.at(code) << "\n";
        }
        else
        {
            ss << "HTTP/1.1 500 " << messages.at(500) << "\n";
        }

        std::time_t t = std::time(nullptr);

        ss << "Server: SK inf1412(54|69)\n";
        ss << "Date: " << std::put_time(std::gmtime(&t), "%c %Z") << "\n";

        return ss.str();
    }
    
} // namespace own
