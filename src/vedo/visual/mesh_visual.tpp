#include <vtkProperty.h>
#include <vtkSmartPointer.h>

namespace vedo::visual
{
    template <typename Derived>
    Derived& MeshVisual<Derived>::wireframe(bool value)
    {
        if (value)
            static_cast<Derived*>(this)->properties->SetRepresentationToWireframe();
        else
            static_cast<Derived*>(this)->properties->SetRepresentationToSurface();
        return static_cast<Derived&>(*this);
    }
}  // namespace vedo::visual