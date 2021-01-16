#pragma once
#include <string>

namespace own
{

    [[nodiscard]] std::string readRawRequestFromSocket(const int cfd);

} // namespace own
