#include <vtkPolyDataMapper.h>
#include <vtkSmartPointer.h>

#include "../plotter/show.h"
#include "../types.h"

namespace vedo::visual
{
    template <typename Derived>
    void CommonVisual<Derived>::show()
    {
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(static_cast<Derived*>(this)->dataset);  // Set the dataset as input to the mapper

        Actor actor = Actor::New();
        actor->SetMapper(mapper);                                     // Set the mapper for the actor
        actor->SetProperty(static_cast<Derived*>(this)->properties);  // Set the properties for the actor

        vedo::plotter::show(actor);
    };
}  // namespace vedo::visual