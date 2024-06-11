#pragma once
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkSmartPointer.h>

#include <array>
#include <string>
#include <string_view>
#include <vector>

#include "../core/core_utilties.h"
#include "../core/point_algorithms.h"
#include "../types.h"
#include "../visual/points_visual.h"

namespace vedo::points
{
    class Points : public vedo::core::PointAlgorithms<Points>,
                   public vedo::visual::PointsVisual<Points>,
                   public vedo::core::CoreUtilities<Points>
    {
    public:
        Points();
        Points(std::string_view filename);
        Points(const std::vector<std::array<double, 3>>& points);
        Points(Dataset dataset);
        void Initialize();
        void Initialize(Dataset dataset);
        void Initialize(Actor actor);

        std::string name;
        std::string filename;
        Actor actor;
        vtkSmartPointer<vtkProperty> properties;
        vtkSmartPointer<vtkPolyDataMapper> mapper;
        Dataset dataset;
        Transform transform;
    };
}  // namespace vedo::points