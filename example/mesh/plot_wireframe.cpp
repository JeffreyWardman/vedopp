#include <fmt/core.h>
#include <vedo/file_io/reader.h>
#include <vedo/mesh/mesh.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

auto main() -> int
{
    vedo::mesh::Mesh mesh = vedo::mesh::Mesh("data/dragon.ply");
    auto numPoints = static_cast<int>(mesh.dataset->GetNumberOfPoints());
    mesh.show();
    fmt::print("Number of points is {}\n", numPoints);
    return 0;
}
