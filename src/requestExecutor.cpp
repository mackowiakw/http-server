#include <array>
#include <string>
#include <regex>

#include "requestExecutor.hpp"
#include "httpMethods.hpp"
#include "httpResponse.hpp"
#include "config.hpp"


namespace own
{
    
    std::string executeRequest(std::array<std::string, 4> const& params)
    {
        const auto [method, resource, version, body] = params;

        // Bad Request
        if (resource.empty() || version.empty()) {
            return response(400);
        }

        // Forbidden (simple path traversal blocker)
        if (resource.find("/../") != std::string::npos) {
            return response(403);
        }

        // Method Not Allowed (POST, PATCH and PUT)
        if (std::regex_match(method, std::regex("POST|PATCH|OPTIONS"))) {
            return response(405);
        }

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

        // Not Implemented (non standard (user-defined) methods)
        return response(501);
    }

} // namespace own
