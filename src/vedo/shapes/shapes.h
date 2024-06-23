#pragma once

#include "../mesh/mesh.h"
#include "../types.h"

namespace vedo::shapes
{
    class ConvexHull : public vedo::mesh::Mesh
    {
    public:
        using vedo::mesh::Mesh::copy;  // Inherit constructors from vedo::points::Points

        ConvexHull(Mesh& mesh);
    };
}  // namespace vedo::shapes