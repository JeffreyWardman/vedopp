#pragma once

#include <stdexcept>

namespace vedo::errors
{
    class UnsupportedFileTypeException : public std::runtime_error
    {
    public:
        using runtime_error::runtime_error;
    };
}  // namespace vedo::errors