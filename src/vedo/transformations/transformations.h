#pragma once

#include <vtkLinearTransform.h>
#include <vtkSmartPointer.h>

#include <array>
#include <optional>
#include <string>
#include <string_view>

#include "../types.h"

namespace vedo::transformations
{
    class LinearTransform
    {
    public:
        LinearTransform();
        LinearTransform(Matrix4x4 T);
        LinearTransform(Transform T);

        auto invert() -> LinearTransform;
        auto is_identity() const -> bool;
        auto copy() const -> LinearTransform;
        auto rotate(double angle,
                    const std::array<double, 3>& axis,
                    const std::array<double, 3>& point,
                    bool rad = false) -> LinearTransform;
        auto rotate_x(double angle, bool rad, const std::optional<std::array<double, 3>>& around = std::nullopt) -> LinearTransform;
        auto rotate_y(double angle, bool rad, const std::optional<std::array<double, 3>>& around = std::nullopt) -> LinearTransform;
        auto rotate_z(double angle, bool rad, const std::optional<std::array<double, 3>>& around = std::nullopt) -> LinearTransform;
        auto set_position(const std::array<double, 3>& position) -> LinearTransform;
        std::array<double, 3> get_scale() const;

        Transform T;
        std::string name = "LinearTransform";
        std::string filename = "";
        std::string comment = "";
        bool inverse_flag = false;

    private:
        auto _rotatexyz(std::string_view axe,
                        double angle,
                        bool rad = true,
                        const std::optional<std::array<double, 3>>& around = std::nullopt) -> LinearTransform;
    };
}  // namespace vedo::transformations