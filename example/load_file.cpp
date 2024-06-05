
#include <fmt/core.h>
#include <vedo/file_io/reader.h>
#include <vedo/points/points.h>
#include <vtkPoints.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>

auto main() -> int
{
    vedo::points::Points points = vedo::points::Points("data/dragon.ply");
    auto numPoints = static_cast<int>(points.dataset->GetNumberOfPoints());
    points.show();
    fmt::print("Number of points is {}\n", numPoints);
    return 0;
}
