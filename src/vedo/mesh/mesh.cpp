#include "mesh.h"

#include <vtkCamera.h>
#include <vtkContourTriangulator.h>
#include <vtkMassProperties.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkQuadricDecimation.h>
#include <vtkSmartPointer.h>
#include <vtkTriangle.h>
#include <vtkTriangleFilter.h>
#include <vtkWindowToImageFilter.h>

#include <array>
#include <memory>
#include <utility>
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

    auto Mesh::thumbnail(double zoom, std::pair<int, int> size, double azimuth, double elevation) -> Image
    {
        // Convert dataset to actor
        DatasetMapper mapper = DatasetMapper::New();
        mapper->SetInputData(dataset);
        Actor actor = Actor::New();
        actor->SetMapper(mapper);
        actor->GetProperty()->SetColor(vedo::plotter::DEFAULT_COLOR[0], vedo::plotter::DEFAULT_COLOR[1], vedo::plotter::DEFAULT_COLOR[2]);

        plotter::Plotter plotter;
        plotter.add(actor);

        plotter.renderer->ResetCamera();
        vtkSmartPointer<vtkCamera> camera = plotter.renderer->GetActiveCamera();
        camera->Zoom(zoom);
        camera->Elevation(elevation);
        camera->Azimuth(azimuth);

        plotter.window->SetOffScreenRendering(true);
        plotter.window->SetSize(size.first, size.second);
        plotter.renderer->ResetCameraClippingRange();
        plotter.window->Render();

        vtkSmartPointer<vtkWindowToImageFilter> windowToImageFilter = vtkSmartPointer<vtkWindowToImageFilter>::New();
        windowToImageFilter->SetInput(plotter.window);
        windowToImageFilter->Update();

        Image imageData = Image::New();
        imageData->ShallowCopy(windowToImageFilter->GetOutput());

        plotter.renderer->RemoveActor(actor);
        plotter.window->Finalize();

        return imageData;
    }

    auto Mesh::decimate(float fraction, int n, bool preserveVolume, double regularization) -> Mesh&
    {
        if (n > 0)
        {  // n is the desired number of points
            int numPts = this->npoints();
            fraction = static_cast<double>(n) / numPts;
            if (fraction >= 1)
            {
                return *this;
            }
        }

        auto decimate = vtkSmartPointer<vtkQuadricDecimation>::New();
        decimate->SetVolumePreservation(preserveVolume);
        if (regularization > 0.0)
        {
            decimate->SetRegularize(true);
            decimate->SetRegularization(regularization);
        }

        decimate->SetTargetReduction(1.0 - fraction);
        decimate->SetInputData(this->dataset);
        decimate->Update();

        Dataset decimatedDataset = decimate->GetOutput();
        this->dataset->ShallowCopy(decimatedDataset);

        return *this;
    }

    double Mesh::area()
    {
        vtkSmartPointer<vtkMassProperties> mass = vtkSmartPointer<vtkMassProperties>::New();
        mass->SetGlobalWarningDisplay(0);
        mass->SetInputData(this->dataset);
        mass->Update();
        return mass->GetSurfaceArea();
    }

    double Mesh::volume()
    {
        vtkSmartPointer<vtkMassProperties> mass = vtkSmartPointer<vtkMassProperties>::New();
        mass->SetGlobalWarningDisplay(0);
        mass->SetInputData(this->dataset);
        mass->Update();
        return mass->GetVolume();
    }

    auto Mesh::triangulate(bool verts, bool lines) -> Mesh&
    {
        vtkSmartPointer<vtkPolyDataAlgorithm> tf;

        if (this->dataset->GetNumberOfPolys() > 0 || this->dataset->GetNumberOfStrips() > 0)
        {
            // Use vtkTriangleFilter
            vtkSmartPointer<vtkTriangleFilter> triangleFilter = vtkSmartPointer<vtkTriangleFilter>::New();
            triangleFilter->SetPassLines(lines);
            triangleFilter->SetPassVerts(verts);
            tf = triangleFilter;
        }
        else if (this->dataset->GetNumberOfLines() > 0)
        {
            // Use vtkContourTriangulator
            vtkSmartPointer<vtkContourTriangulator> contourTriangulator = vtkSmartPointer<vtkContourTriangulator>::New();
            contourTriangulator->TriangulationErrorDisplayOn();
            tf = contourTriangulator;
        }

        tf->SetInputData(this->dataset);
        tf->Update();
        this->dataset->ShallowCopy(tf->GetOutput());
        return *this;
    }

}  // namespace vedo::mesh