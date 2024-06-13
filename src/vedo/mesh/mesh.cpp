#include "mesh.h"

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>
#include <vtkTriangle.h>

#include <array>
#include <memory>
#include <vector>

#include "../points/points.h"
#include "../types.h"
#include "../visual/mesh_visual.h"

namespace vedo::mesh
{
    Mesh::Mesh(const std::vector<std::array<double, 3>>& points, const std::vector<std::array<int, 3>>& faces)
    {
        Dataset dataset = Dataset::New();
        Vertices vertices = Vertices::New();

        // Set points
        for (const auto& point : points)
        {
            vertices->InsertNextPoint(point.data());
        }
        dataset->SetPoints(vertices);

        // Set cells
        Cells cells = Cells::New();
        for (const auto& face : faces)
        {
            vtkSmartPointer<vtkTriangle> triangle = vtkSmartPointer<vtkTriangle>::New();
            triangle->GetPointIds()->SetId(0, face[0]);
            triangle->GetPointIds()->SetId(1, face[1]);
            triangle->GetPointIds()->SetId(2, face[2]);
            cells->InsertNextCell(triangle);
        }
        dataset->SetPolys(cells);

        this->Initialize(dataset);
    }
}  // namespace vedo::mesh