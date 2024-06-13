#include "helpers.h"

#include <string>
#include <string_view>

namespace vedo::file_io
{
    auto getFileExtension(std::string_view filename) -> std::string_view
    {
        size_t pos = filename.find_last_of('.');
        if (pos != std::string::npos)
        {
            return filename.substr(pos + 1);
        }
        return "";
    }
}  // namespace vedo::file_io
