#pragma once
#include <array>

#include "common_visual.h"

namespace vedo::visual
{

    template <typename Derived>
    class PointsVisual : public CommonVisual<Derived>
    {
    public:
        std::array<double, 3> color() { return static_cast<Derived&>(*this)->properties->GetColor(); }
        std::array<double, 3> c() const { return color(); }
        Derived& color(const std::array<double, 3>& value);
        Derived& c(const std::array<double, 3>& value);
        Derived& opacity(float alpha);
        float opacity();
        Derived& alpha(float alpha);
        float alpha();
        Derived& point_size(int value);
        int point_size();
        Derived& ps(int value);
        int ps();
    };
}  // namespace vedo::visual

#include "points_visual.tpp"
