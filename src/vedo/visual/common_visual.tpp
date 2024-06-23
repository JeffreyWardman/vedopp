#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>

#include "../plotter/show.h"
#include "../types.h"

namespace vedo::visual
{
    template <typename Derived>
    void CommonVisual<Derived>::show()
    {
        vedo::plotter::show(static_cast<Derived&>(*this));
    };
}  // namespace vedo::visual