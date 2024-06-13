#pragma once

#include <string>
#include <tuple>
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
}  // namespace vedo::plotter