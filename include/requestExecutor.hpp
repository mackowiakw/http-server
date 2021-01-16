#pragma once
#include <array>
#include <string>

namespace own
{
    
    [[nodiscard]] std::string executeRequest(std::array<std::string, 4> const& params);

} // namespace own
