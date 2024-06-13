#pragma once
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>

#include <array>
#include <string>
#include <string_view>
#include <vector>

#include "../core/core_utilties.h"
#include "../points/points.h"
#include "../types.h"
#include "../visual/mesh_visual.h"

namespace vedo::mesh
{
    class Mesh : public vedo::points::Points, public vedo::visual::MeshVisual<Mesh>, public vedo::core::CoreUtilities<Mesh>
    {
    public:
        using vedo::points::Points::Points;  // Inherit constructors from vedo::points::Points

        Mesh(const std::vector<std::array<double, 3>>& points, const std::vector<std::array<int, 3>>& faces);
        using vedo::visual::MeshVisual<Mesh>::show;
    };
}  // namespace vedo::mesh
