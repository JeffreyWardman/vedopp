#pragma once
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>

#include <string>
#include <string_view>

#include "../core/point_algorithms.h"
#include "../types.h"
#include "../visual/points_visual.h"

namespace vedo::points
{
    class Points : public vedo::core::PointAlgorithms<Points>, public vedo::visual::PointsVisual<Points>
    {
    public:
        Points();
        Points(std::string_view filename);
        Points(Dataset dataset);
        void Initialize();
        void Initialize(Dataset dataset);
        void Initialize(Actor actor);

        auto copy(bool deep = true) -> Points;

        std::string name;
        std::string filename;
        Actor actor;
        vtkSmartPointer<vtkProperty> properties;
        vtkSmartPointer<vtkPolyDataMapper> mapper;
        Dataset dataset;
        Transform transform;
    };
}  // namespace vedo::points