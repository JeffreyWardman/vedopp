#include "points.h"

#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>

#include <memory>
#include <string_view>

#include "../file_io/reader.h"
#include "../types.h"

namespace vedo::points
{
    Points::Points()
    {
        this->Initialize();
        this->mapper->SetInputData(this->dataset);
    }
    // TODO pass in array of points

    Points::Points(std::string_view filename)
    {
        Dataset dataset = file_io::reader::load(filename);
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

    auto Points::copy(bool deep) -> Points
    {
        Dataset datasetCopy = Dataset::New();
        Transform transformCopy = Transform::New();

        if (deep)
        {
            datasetCopy->DeepCopy(this->dataset);
            transformCopy->DeepCopy(this->transform);
        }
        else
        {
            datasetCopy->ShallowCopy(this->dataset);
            transformCopy->DeepCopy(this->transform);
        }

        Points pointsCopy = Points(datasetCopy);
        pointsCopy.name = this->name;
        pointsCopy.filename = this->filename;
        pointsCopy.transform->DeepCopy(this->transform);
        pointsCopy.properties->DeepCopy(this->properties);
        return pointsCopy;
    }
}  // namespace vedo::points