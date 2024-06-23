#include "transformations.h"

#include <vtkLinearTransform.h>
#include <vtkMath.h>
#include <vtkSmartPointer.h>

#include <array>
#include <optional>
#include <stdexcept>
#include <string_view>

#include "../types.h"

namespace vedo::transformations
{
    LinearTransform::LinearTransform() { this->T = Transform::New(); }
    LinearTransform::LinearTransform(Matrix4x4 T)
    {
        this->T = Transform::New();
        this->T->SetMatrix(T);
    }

    LinearTransform::LinearTransform(Transform T)
    {
        this->T = Transform::New();
        this->T->DeepCopy(T);
    }

    auto LinearTransform::invert() -> LinearTransform
    {
        this->T->Inverse();
        this->inverse_flag = static_cast<bool>(this->T->GetInverseFlag());
        return *this;
    }

    auto LinearTransform::is_identity() const -> bool
    {
        Matrix4x4 matrix = this->T->GetMatrix();
        return matrix->IsIdentity();
    }

    auto LinearTransform::copy() const -> LinearTransform { return LinearTransform(this->T); }
    auto LinearTransform::rotate(double angle,
                                 const std::array<double, 3>& axis,
                                 const std::array<double, 3>& point,
                                 bool rad) -> LinearTransform
    {
        if (vtkMath::Norm(axis.data()) == 0.0)  // TODO don't use norm for this
        {
            return *this;  // If axis is zero vector, no rotation
        }
        if (angle == 0.0)
        {
            return *this;  // If angle is zero, no rotation
        }

        double anglerad = rad ? angle : vtkMath::RadiansFromDegrees(angle);

        // Normalize axis
        double axisNorm = vtkMath::Norm(axis.data());
        std::array<double, 3> axisNormalized = {axis[0] / axisNorm, axis[1] / axisNorm, axis[2] / axisNorm};

        // Calculate quaternion parameters
        double a = cos(anglerad / 2);
        double b = -axisNormalized[0] * sin(anglerad / 2);
        double c = -axisNormalized[1] * sin(anglerad / 2);
        double d = -axisNormalized[2] * sin(anglerad / 2);

        // Construct rotation matrix from quaternion
        std::array<std::array<double, 3>, 3> R;
        R[0][0] = a * a + b * b - c * c - d * d;
        R[0][1] = 2 * (b * c - a * d);
        R[0][2] = 2 * (b * d + a * c);
        R[1][0] = 2 * (b * c + a * d);
        R[1][1] = a * a + c * c - b * b - d * d;
        R[1][2] = 2 * (c * d - a * b);
        R[2][0] = 2 * (b * d - a * c);
        R[2][1] = 2 * (c * d + a * b);
        R[2][2] = a * a + d * d - b * b - c * c;

        // Perform rotation
        std::array<double, 3> currentPosition;
        this->T->GetPosition(currentPosition.data());
        std::array<double, 3> rotatedPosition;
        std::array<double, 3> posMinusPoint;
        vtkMath::Subtract(currentPosition.data(), point.data(), posMinusPoint.data());
        vtkMath::Multiply3x3(reinterpret_cast<const double(*)[3]>(&R[0][0]), posMinusPoint.data(), rotatedPosition.data());
        vtkMath::Add(rotatedPosition.data(), point.data(), rotatedPosition.data());

        // Apply rotation and translation to VTK transform
        this->T->RotateWXYZ(angle, axis[0], axis[1], axis[2]);
        this->T->Translate(rotatedPosition[0] - currentPosition[0], rotatedPosition[1] - currentPosition[1],
                           rotatedPosition[2] - currentPosition[2]);
        return *this;
    }

    auto LinearTransform::rotate_x(double angle, bool rad, const std::optional<std::array<double, 3>>& around) -> LinearTransform
    {
        return this->_rotatexyz("x", angle, rad, around);
    }

    auto LinearTransform::rotate_y(double angle, bool rad, const std::optional<std::array<double, 3>>& around) -> LinearTransform
    {
        return this->_rotatexyz("y", angle, rad, around);
    }

    auto LinearTransform::rotate_z(double angle, bool rad, const std::optional<std::array<double, 3>>& around) -> LinearTransform
    {
        return this->_rotatexyz("z", angle, rad, around);
    }

    auto LinearTransform::set_position(const std::array<double, 3>& position) -> LinearTransform
    {
        std::array<double, 3> current_pos;
        this->T->GetPosition(current_pos.data());
        this->T->Translate(position[0] - current_pos[0], position[1] - current_pos[1], position[2] - current_pos[2]);
        return *this;
    }

    LinearTransform LinearTransform::_rotatexyz(std::string_view axe,
                                                double angle,
                                                bool rad,
                                                const std::optional<std::array<double, 3>>& around)
    {
        if (angle == 0.0)
        {
            // No rotation
            return *this;
        }

        // Validate the axis
        if (axe != "x" && axe != "y" && axe != "z")
        {
            throw std::invalid_argument("Invalid axis provided. Valid axes are 'x', 'y', or 'z'.");
        }

        if (!rad)
        {
            angle *= 180.0 / vtkMath::Pi();
        }

        if (!around.has_value())
        {
            if (axe == "x")
            {
                this->T->RotateX(angle);
            }
            else if (axe == "y")
            {
                this->T->RotateY(angle);
            }
            else if (axe == "z")
            {
                this->T->RotateZ(angle);
            }
        }
        else
        {
            const auto& _around = around.value();
            // Perform rotation around a specified point if around is not NULL
            std::array<double, 3> currentPosition;
            this->T->GetPosition(currentPosition.data());

            // Translate to the origin
            this->T->Translate(-_around[0], -_around[1], -_around[2]);

            // Rotate around the origin
            if (axe == "x")
            {
                this->T->RotateX(angle);
            }
            else if (axe == "y")
            {
                this->T->RotateY(angle);
            }
            else if (axe == "z")
            {
                this->T->RotateZ(angle);
            }

            // Translate back to the original position
            this->T->Translate(_around[0], _around[1], _around[2]);
        }

        return *this;
    }

    std::array<double, 3> LinearTransform::get_scale() const
    {
        std::array<double, 3> scale;
        Matrix4x4 matrix = Matrix4x4::New();
        T->GetMatrix(matrix);
        T->GetScale(scale.data());
        return {scale[0], scale[1], scale[2]};
    }
}  // namespace vedo::transformations