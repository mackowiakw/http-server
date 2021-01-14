#include <filesystem>
#include <fstream>
#include <sstream>
#include <string>

#include "config.hpp"
#include "httpResponse.hpp"
#include "stringHelper.hpp"

#include "httpMethods.hpp"


namespace own
{

    std::string GET(std::string const &URL)
    {
        if (std::string body; std::filesystem::is_directory(URL)) {
            body += URL.substr(ROOT_FOLDER.length()) + " is not a file, it's a directory";

            std::stringstream headers;
            headers << "Content-Type: text/plain; charset=ASCII\n";
            headers << "Content-Length: " << body.size() << "\n\n";

            // Found (resource is a directory, not a file)
            return response(302) + headers.str() + body;
        }

        if (std::stringstream headers; std::filesystem::exists(URL)) {
            headers << "Content-Type: text/plain; charset=ASCII\n";
            headers << "Content-Length: " << std::filesystem::file_size(URL) << "\n\n";

            std::stringstream body;
            body << std::ifstream(URL).rdbuf();

            // OK (Succes)
            return response(200) + headers.str() + body.str();
        }

        // Not Found
        return response(404);
    }

    std::string HEAD(std::string const &URL)
    {
        // Same as GET but without response body
        // Important: newline at the EOF (body is removed with leading \n\n)
        return getHeadersFromRequest(GET(URL)) + "\n";
    }

    std::string PUT(std::string const &URL, std::string const &body)
    {
        if (std::filesystem::exists(URL)) {
            return response(304);
        }

        // Assuming URL is a folderName unless contains any '.' (dot) character
        if (URL.find(".") == std::string::npos) {
            try {
                std::filesystem::create_directory(URL);
            }
            catch (std::filesystem::filesystem_error &) {
                // Multiple Choices (Create many folders at one time)
                return response(300);
            }

            // Created (Succes)
            return response(201);
        }

        if (std::ofstream fout(URL); fout) {
            fout << body;
            fout.close();

            std::stringstream headers;
            headers << "Content-Location: " << URL.substr(ROOT_FOLDER.length()) << "\n";

            // Created (Succes)
            return response(201) + headers.str();
        }

        // Bad Request (Create file in not existing directory)
        return response(400);
    }

    std::string DELETE(std::string const &URL)
    {
        try {
            if (std::filesystem::remove(URL)) {
                // OK (Succes)
                return response(200);
            }
        }
        catch (std::filesystem::filesystem_error &) {
            // Not Modified (Directory is not empty)
            return response(304);
        }

        // No Content (There is no such file to delete)
        return response(204);
    }

} // namespace own
