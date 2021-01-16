#pragma once
#include <string>


namespace own
{

    [[nodiscard]] std::string GET(std::string const& URL, const bool isHEAD = false);
    
    [[nodiscard]] std::string HEAD(std::string const& URL);

    [[nodiscard]] std::string PUT(std::string const& URL, std::string const& body);

    [[nodiscard]] std::string DELETE(std::string const& URL);
    
} // namespace own
