#pragma once

#include <vtkPolyData.h>

#include <string_view>

#include "../types.h"

namespace vedo::file_io::reader
{
    Dataset load(std::string_view filename);
}  // namespace vedo::file_io::reader