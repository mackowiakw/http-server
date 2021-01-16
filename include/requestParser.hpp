#pragma once
#include <array>
#include <string>

namespace own
{

    [[nodiscard]] std::array<std::string, 4> parseRequest(std::string const& rawData);
    
} // namespace own
