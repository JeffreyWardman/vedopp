#include <fmt/core.h>
#include <vedo/file_io/reader.h>
#include <vedo/mesh/mesh.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

auto main() -> int
{
    vedo::mesh::Mesh mesh = vedo::mesh::Mesh("data/dragon.ply");
    auto numPoints = mesh.npoints();
    auto numFaces = mesh.ncells();
    fmt::print("Number of points is {}\nNumber of faces is {}\n", numPoints, numFaces);

    mesh.wireframe(true).show();
    return 0;
}
