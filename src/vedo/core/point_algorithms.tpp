#include <vtkMath.h>
#include <vtkTransformPolyDataFilter.h>

#include <array>

#include "../types.h"

namespace vedo::core
{
    template <typename Derived>
    Derived& PointAlgorithms<Derived>::apply_transform(Transform LT, bool deep_copy)
    {
        if (this->dataset->GetNumberOfPoints() == 0 || LT->GetMatrix()->IsIdentity())
        {
            return static_cast<Derived&>(*this);
        }

        this->transform->concatenate(LT);

        vtkSmartPointer<vtkTransformPolyDataFilter> filter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
        filter->SetTransform(LT);
        filter->SetInputData(this->dataset);
        filter->Update();

        if (deep_copy)
        {
            this->dataset->DeepCopy(filter->GetOutput());
        }
        else
        {
            this->dataset->ShallowCopy(filter->GetOutput());
        }
        return static_cast<Derived&>(*this);
    }

    template <typename Derived>
    Derived& PointAlgorithms<Derived>::rotate(double angle, const std::array<double, 3>& axis, const std::array<double, 3>& point, bool rad)
    {
        if (!rad) angle = vtkMath::RadiansFromDegrees(angle);
        Transform transform = Transform::New();
        transform->Translate(-point[0], -point[1], -point[2]);
        transform->RotateWXYZ(vtkMath::DegreesFromRadians(angle), axis.begin());
        transform->Translate(point[0], point[1], point[2]);

        this->ApplyTransformation(transform);
        return static_cast<Derived&>(*this);
    }

    template <typename Derived>
    Derived& PointAlgorithms<Derived>::rotate_x(double angle, bool rad)  //, around = nullptr)
    {
        if (angle == 0)
        {
            return static_cast<Derived&>(*this);
        }
        if (!rad) angle = vtkMath::RadiansFromDegrees(angle);

        Transform LT = Transform::New();
        LT->RotateX(angle);
        return static_cast<Derived&>(*this->apply_transform(LT));
    }
}  // namespace vedo::core