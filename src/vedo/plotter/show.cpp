#include "show.h"

#include <tuple>
#include <vector>

#include "../types.h"
#include "plotter.h"

namespace vedo::plotter
{
    void show(Dataset dataset, const std::string& title, const std::tuple<int, int>& size)
    {
        Plotter plotter = Plotter(title, size);
        plotter.add(dataset);
        plotter.show();
        plotter.close();
    }
    void show(const std::vector<Dataset>& datasets, const std::string& title, const std::tuple<int, int>& size)
    {
        Plotter plotter = Plotter(title, size);
        plotter.add(datasets);
        plotter.show();
        plotter.close();
    }
    void show(Actor actor, const std::string& title, const std::tuple<int, int>& size)
    {
        Plotter plotter = Plotter(title, size);
        plotter.add(actor);
        plotter.show();
        plotter.close();
    }
    void show(const std::vector<Actor>& actors, const std::string& title, const std::tuple<int, int>& size)
    {
        Plotter plotter = Plotter(title, size);
        plotter.add(actors);
        plotter.show();
        plotter.close();
    }
}  // namespace vedo::plotter