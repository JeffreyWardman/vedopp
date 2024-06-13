#pragma once

#include "points_visual.h"

namespace vedo::visual
{

    template <typename Derived>
    class MeshVisual : public PointsVisual<Derived>
    {
    public:
        Derived& wireframe(bool value = true);
    };
}  // namespace vedo::visual

#include "mesh_visual.tpp"
