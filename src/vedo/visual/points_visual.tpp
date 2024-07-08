#include <array>

namespace vedo::visual
{
    template <typename Derived>
    Derived& PointsVisual<Derived>::color(const std::array<double, 3>& value)
    {
        static_cast<Derived&>(*this)->properties->SetColor(value);
        return static_cast<Derived&>(*this);
    }
    template <typename Derived>
    Derived& PointsVisual<Derived>::c(const std::array<double, 3>& value)
    {
        return static_cast<Derived&>(*this)->actor->color(value);
    }

    template <typename Derived>
    Derived& PointsVisual<Derived>::alpha(float opacity)
    {
        static_cast<Derived&>(*this).properties->SetOpacity(opacity);
        auto bfp = static_cast<Derived&>(*this).actor->GetBackfaceProperty();
        if (bfp)
        {
            if (opacity < 1)
            {
                static_cast<Derived&>(*this).properties_backface = bfp;
                static_cast<Derived&>(*this).actor->SetBackfaceProperty(nullptr);
            }
            else
            {
                static_cast<Derived&>(*this).actor->SetBackfaceProperty(static_cast<Derived&>(*this).properties_backface);
            }
        }
        return static_cast<Derived&>(*this);
    }

    template <typename Derived>
    Derived& PointsVisual<Derived>::opacity(float opacity)
    {
        return static_cast<Derived&>(*this)->alpha(opacity);
    }

    template <typename Derived>
    float PointsVisual<Derived>::alpha()
    {
        return static_cast<Derived&>(*this)->properties->GetOpacity();
    }

    template <typename Derived>
    float PointsVisual<Derived>::opacity()
    {
        return static_cast<Derived&>(*this)->alpha();
    }

    template <typename Derived>
    int PointsVisual<Derived>::point_size()
    {
        return static_cast<Derived&>(*this)->properties->GetPointSize();
    }

    template <typename Derived>
    int PointsVisual<Derived>::ps()
    {
        return static_cast<Derived&>(*this)->point_size();
    }

    template <typename Derived>
    Derived& PointsVisual<Derived>::point_size(const int value)
    {
        static_cast<Derived&>(*this)->properties->SetRepresentationToPoints();
        static_cast<Derived&>(*this)->properties->SetPointSize(value);
        return static_cast<Derived&>(*this);
    }

    template <typename Derived>
    Derived& PointsVisual<Derived>::ps(const int value)
    {
        return static_cast<Derived&>(*this)->point_size(value);
    }

}  // namespace vedo::visual