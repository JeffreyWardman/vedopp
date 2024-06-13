#include "points.h"

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>

#include <array>
#include <memory>
#include <string_view>
#include <vector>

#include "../file_io/reader.h"
#include "../types.h"

namespace vedo::points
{
    Points::Points()
    {
        this->Initialize();
        this->mapper->SetInputData(this->dataset);
    }

    Points::Points(std::string_view filename)
    {
        Dataset dataset = file_io::reader::load(filename);
        this->Initialize(dataset);
    }

    Points::Points(const std::vector<std::array<double, 3>>& points)
    {
        Dataset dataset = Dataset::New();
        Vertices vertices = Vertices::New();

        for (const auto& point : points)
        {
            vertices->InsertNextPoint(point.data());
        }

        dataset->SetPoints(vertices);
        this->Initialize(dataset);
    }

    Points::Points(Dataset dataset) { this->Initialize(dataset); }

    void Points::Initialize()
    {
        this->actor = Actor::New();
        this->properties = this->actor->GetProperty();
        this->mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        this->dataset = Dataset::New();
        this->transform = Transform::New();
        this->actor->SetMapper(this->mapper);
        this->mapper->SetInputData(this->dataset);
    }

    void Points::Initialize(Dataset dataset)
    {
        this->actor = Actor::New();
        this->properties = this->actor->GetProperty();
        this->mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        this->dataset = dataset;
        this->transform = Transform::New();
        this->actor->SetMapper(this->mapper);
        this->mapper->SetInputData(this->dataset);
    }

    void Points::Initialize(Actor actor)
    {
        this->actor = actor;
        this->properties = this->actor->GetProperty();
        this->mapper = vtkPolyDataMapper::SafeDownCast(this->actor->GetMapper());

        this->dataset = vtkPolyData::SafeDownCast(this->mapper->GetInput());
        this->transform = Transform::New();
    }
}  // namespace vedo::points
