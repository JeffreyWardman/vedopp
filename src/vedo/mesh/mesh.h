#pragma once
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>

#include <array>
#include <string>
#include <string_view>
#include <utility>
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
        using vedo::core::CoreUtilities<Mesh>::copy;
        using vedo::points::Points::Points;  // Inherit constructors from vedo::points::Points
        using vedo::visual::MeshVisual<Mesh>::show;
        using vedo::visual::MeshVisual<Mesh>::alpha;

        Mesh(const std::vector<std::array<double, 3>>& points, const std::vector<std::array<int, 3>>& faces);

        auto area() -> double;
        auto volume() -> double;
        auto thumbnail(double zoom = 1.25, std::pair<int, int> size = {200, 200}, double azimuth = 0.0, double elevation = 0.0) -> Image;
        auto decimate(float fraction = 0.5f, int n = -1, bool preserveVolume = true, double regularization = 0.0) -> Mesh&;
        auto triangulate(bool verts = true, bool lines = true) -> Mesh&;
    };
}  // namespace vedo::mesh
