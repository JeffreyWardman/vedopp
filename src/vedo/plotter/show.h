#pragma once

#include <memory>  // For std::shared_ptr
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>  // For std::is_base_of
#include <vector>

#include "../types.h"
#include "plotter.h"

namespace vedo::plotter
{
    void show(Dataset dataset, const std::string& title = "vedo", const std::tuple<int, int>& size = std::make_tuple(800, 600));
    void show(const std::vector<Dataset>& datasets,
              const std::string& title = "vedo",
              const std::tuple<int, int>& size = std::make_tuple(800, 600));
    void show(Actor actor, const std::string& title = "vedo", const std::tuple<int, int>& size = std::make_tuple(800, 600));
    void show(const std::vector<Actor>& actors,
              const std::string& title = "vedo",
              const std::tuple<int, int>& size = std::make_tuple(800, 600));

    template <typename... Objects>
    void show(Objects&&... objs)
    {
        std::string_view title = "vedo";
        const std::tuple<int, int>& size = {800, 600};
        Plotter plotter = Plotter(title, size);

        auto add_to_plotter = [&](auto&& obj) { plotter.add(obj.actor); };
        (add_to_plotter(std::forward<Objects>(objs)), ...);

        plotter.show();
        plotter.close();
    }

    template <typename... Objects>
    void show(Objects&&... objs, std::string_view title = "vedo", const std::tuple<int, int>& size = {800, 600})
    {
        Plotter plotter = Plotter(title, size);

        auto add_to_plotter = [&](auto&& obj) { plotter.add(obj.actor); };
        (add_to_plotter(std::forward<Objects>(objs)), ...);

        plotter.show();
        plotter.close();
    }

    template <typename T>
    void show(T&& obj, const std::string& title = "vedo", const std::tuple<int, int>& size = {800, 600})
    {
        Plotter plotter = Plotter(title, size);
        plotter.add(obj.actor);
        plotter.show();
        plotter.close();
    }
}  // namespace vedo::plotter