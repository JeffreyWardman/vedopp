#pragma once

#include <array>

#include "../types.h"

namespace vedo::core
{
    template <typename Derived>
    class CoreUtilities
    {
    public:
        Derived copy(bool deep = true) const;
    };
}  // namespace vedo::core

#include "core_utilities.tpp"
