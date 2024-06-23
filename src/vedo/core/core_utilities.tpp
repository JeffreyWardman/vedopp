#include <vtkMath.h>
#include <vtkTransformPolyDataFilter.h>

#include <array>

#include "../types.h"

namespace vedo::core
{
    template <typename Derived>
    Derived CoreUtilities<Derived>::copy(bool deep)
    {
        Dataset datasetCopy = Dataset::New();
        Transform transformCopy = Transform::New();

        if (deep)
        {
            datasetCopy->DeepCopy(static_cast<Derived&>(*this).dataset);
            transformCopy->DeepCopy(static_cast<Derived&>(*this).transform);
        }
        else
        {
            datasetCopy->ShallowCopy(static_cast<Derived&>(*this).dataset);
            transformCopy->DeepCopy(static_cast<Derived&>(*this).transform);
        }

        Derived copy = Derived(datasetCopy);
        copy.name = static_cast<Derived&>(*this).name;
        copy.filename = static_cast<Derived&>(*this).filename;
        copy.transform->DeepCopy(static_cast<Derived&>(*this).transform);
        copy.properties->DeepCopy(static_cast<Derived&>(*this).properties);
        copy.properties_backface->DeepCopy(static_cast<Derived&>(*this).properties_backface);
        return copy;
    }
}  // namespace vedo::core