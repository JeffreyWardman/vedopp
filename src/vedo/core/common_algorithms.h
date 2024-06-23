#pragma once

#include <array>
#include <tuple>

#include "../types.h"

namespace vedo::core
{
    template <typename Derived>
    class CommonAlgorithms
    {
    public:
        std::array<double, 6> bounds() const;
        std::tuple<double, double> xbounds() const;
        std::tuple<double, double> ybounds() const;
        std::tuple<double, double> zbounds() const;
        Vertices cell_centers() const;
        Vertices vertices() const;
        int nvertices() const;
        int npoints() const;
        Cells cells() const;
        int ncells() const;
        Derived& compute_cell_size();
        double calculate_average_size() const;
        double diagonal_size() const;
    };
}  // namespace vedo::core

#include "common_algorithms.tpp"
