#include <array>

#include "../types.h"

namespace vedo::core
{
    template <typename Derived>
    std::array<double, 6> CommonAlgorithms<Derived>::bounds()
    {
        std::array<double, 6> bounds;
        static_cast<Derived&>(*this)->dataset->GetBounds(&bounds[0]);
        return bounds;
    }

    template <typename Derived>
    Vertices CommonAlgorithms<Derived>::cell_centers()
    {
        Vertices centers = static_cast<Derived&>(*this)->dataset->GetCellCenters();
        return centers;
    }
}  // namespace vedo::core
