#pragma once

#include <array>

#include "../types.h"
#include "common_algorithms.h"

namespace vedo::core
{
    template <typename Derived>
    class PointAlgorithms : public CommonAlgorithms<Derived>
    {
    public:
        Derived& apply_transform(Transform LT, bool deep_copy = true);

        std::array<double, 3> origin();
        Derived& rotate(double angle,
                        const std::array<double, 3>& axis = {1.0, 0.0, 0.0},
                        const std::array<double, 3>& point = {0.0, 0.0, 0.0},
                        bool rad = false);
        Derived& rotate_x(double angle, bool rad = false);  //, std::array<double, 3> around = nullptr);
    };
}  // namespace vedo::core

#include "point_algorithms.tpp"
