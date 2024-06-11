#pragma once

#include <array>

#include "../types.h"

namespace vedo::core
{
    template <typename Derived>
    class CommonAlgorithms
    {
    public:
        std::array<double, 6> bounds();
        Vertices cell_centers();
    };
}  // namespace vedo::core

#include "common_algorithms.tpp"
