#pragma once

#include <vtkOrientationMarkerWidget.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>

#include <array>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>

#include "../types.h"

namespace vedo::plotter
{
    const std::array<double, 3> DEFAULT_COLOR = {1.0, 0.843, 0.0};

    class Plotter
    {
    public:
        Plotter(std::string_view title = "vedo", std::tuple<int, int> size = std::make_tuple(800, 600));
        void add(Actor actor);
        void add(const std::vector<Actor>& actors);
        void add(Dataset dataset);
        void add(const std::vector<Dataset>& datasets);
        template <typename T>
        void add(const T& obj)
        {
            this->add(obj.actor);
        }
        void show();
        void show(Dataset dataset);
        void show(const std::vector<Dataset>& datasets);
        void close();

        void prepare_scene();
        auto createArrowActor(std::array<float, 3> start, std::array<float, 3> end, std::array<float, 3> color) -> Actor;

        std::string title;
        std::tuple<int, int> size;
        vtkSmartPointer<vtkRenderWindow> window;
        vtkSmartPointer<vtkRenderer> renderer;
        vtkSmartPointer<vtkRenderWindowInteractor> interactor;
        // std::vector<vtkSmartPointer<vtkOrientationMarkerWidget>> widgets;
    };
}  // namespace vedo::plotter