

#include "shapes.h"

#include <vtkDataSetSurfaceFilter.h>
#include <vtkDelaunay2D.h>
#include <vtkDelaunay3D.h>
#include <vtkFeatureEdges.h>
#include <vtkGeometryFilter.h>
#include <vtkSmartPointer.h>
#include <vtkUnstructuredGrid.h>

#include "../mesh/mesh.h"
#include "../types.h"

namespace vedo::shapes
{
    ConvexHull::ConvexHull(Mesh& mesh)
    {
        Dataset apoly = mesh.clean().dataset;

        // Create the convex hull
        auto [z0, z1] = mesh.zbounds();
        double d = mesh.diagonal_size();

        Dataset out;
        if (z1 - z0 / d > EPSILON4)
        {
            // Create a Delaunay3D filter
            vtkSmartPointer<vtkDelaunay3D> delaunay = vtkSmartPointer<vtkDelaunay3D>::New();
            delaunay->SetInputData(apoly);
            delaunay->Update();

            // Extract surface geometry
            vtkSmartPointer<vtkDataSetSurfaceFilter> surfaceFilter = vtkSmartPointer<vtkDataSetSurfaceFilter>::New();
            surfaceFilter->SetInputConnection(delaunay->GetOutputPort());
            surfaceFilter->Update();
            out = surfaceFilter->GetOutput();
        }
        else
        {
            vtkSmartPointer<vtkDelaunay2D> delaunay = vtkSmartPointer<vtkDelaunay2D>::New();
            delaunay->SetInputData(apoly);
            delaunay->Update();

            vtkSmartPointer<vtkFeatureEdges> fe = vtkSmartPointer<vtkFeatureEdges>::New();
            fe->BoundaryEdgesOn();
            fe->Update();
            out = fe->GetOutput();
        }

        auto convex_hull = Mesh(out);
        this->name = convex_hull.name;
        this->filename = convex_hull.filename;
        this->actor = convex_hull.actor;
        this->properties = convex_hull.properties;
        this->properties_backface = convex_hull.properties_backface;
        this->mapper = convex_hull.mapper;
        this->dataset = convex_hull.dataset;
        this->transform = convex_hull.transform;
    }
}  // namespace vedo::shapes