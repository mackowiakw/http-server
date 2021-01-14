#include <string>

namespace own
{

    std::string GET(std::string const& URL);
    
    std::string HEAD(std::string const& URL);

    std::string PUT(std::string const& URL, std::string const& body);

    std::string DELETE(std::string const& URL);
    
} // namespace own
