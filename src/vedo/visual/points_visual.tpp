
#include <array>

namespace vedo::visual
{
    template <typename Derived>
    Derived& PointsVisual<Derived>::color(const std::array<double, 3>& value)
    {
        this->properties->SetColor(value);
        return static_cast<Derived&>(*this);
    }
    template <typename Derived>
    Derived& PointsVisual<Derived>::c(const std::array<double, 3>& value)
    {
        return this->color(value);
    }

}  // namespace vedo::visual