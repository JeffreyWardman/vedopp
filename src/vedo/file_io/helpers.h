#pragma once

#include <string_view>

namespace vedo::file_io
{
    auto getFileExtension(std::string_view filename) -> std::string_view;
}  // namespace vedo::file_io
