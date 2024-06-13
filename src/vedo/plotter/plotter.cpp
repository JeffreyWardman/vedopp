#include "plotter.h"

#include <vtkActor.h>
#include <vtkArrowSource.h>
#include <vtkAxesActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkOrientationMarkerWidget.h>
#include <vtkPlaneSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkSmartPointer.h>
#include <vtkSphereSource.h>
#include <vtkTransformFilter.h>
#include <vtkTransformPolyDataFilter.h>

#include <array>
#include <string_view>
#include <tuple>
#include <vector>

#include "../types.h"

namespace vedo::plotter
{

    Plotter::Plotter(std::string_view title, const std::tuple<int, int> size)
    {
        this->title = title;
        this->size = size;
        this->renderer = vtkSmartPointer<vtkRenderer>::New();
        this->window = vtkSmartPointer<vtkRenderWindow>::New();
        this->interactor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

        // widget = vtkSmartPointer<vtkOrientationMarkerWidget>::New();

        this->window->SetWindowName(&this->title[0]);
        this->window->AddRenderer(this->renderer);
        this->window->SetSize(std::get<0>(this->size), std::get<1>(this->size));

        this->interactor->SetRenderWindow(this->window);
        this->prepare_scene();
    };

    void Plotter::add(Actor actor) { this->renderer->AddActor(actor); }

    void Plotter::add(const std::vector<Actor>& actors)
    {
        for (auto actor : actors)
        {
            this->renderer->AddActor(actor);
        }
    }

    void Plotter::add(const Dataset dataset)
    {
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputData(dataset);

        Actor actor = Actor::New();
        actor->SetMapper(mapper);

        this->renderer->AddActor(actor);
    }

    void Plotter::add(const std::vector<Dataset>& datasets)
    {
        for (auto dataset : datasets)
        {
            vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
            mapper->SetInputData(dataset);

            vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
            actor->SetMapper(mapper);

            this->renderer->AddActor(actor);
        }
    }

    void Plotter::show()
    {
        this->window->Render();
        this->interactor->Start();
    }

    void Plotter::show(const Dataset dataset)
    {
        this->add(dataset);

        this->window->Render();
        this->interactor->Start();
    }
    void Plotter::show(const std::vector<Dataset>& datasets)
    {
        for (auto dataset : datasets)
        {
            this->add(dataset);
        }

        this->window->Render();
        this->interactor->Start();
    }

    void Plotter::close()
    {
        // this->widgets.clear();

        this->renderer->RemoveAllViewProps();
        this->window->Finalize();
        this->interactor->TerminateApp();
    }

    void Plotter::prepare_scene()
    {
        this->renderer->SetBackground(1.0f, 1.0f, 1.0f);

        /*****
        Camera
        *****/
        // Set camera view perpendicular to ZX plane, facing Y+
        // renderer->GetActiveCamera()->SetPosition(0.0, -10.0, 0.0);  // Camera position
        // renderer->GetActiveCamera()->SetFocalPoint(0.0, 0.0, 0.0);  // Look at origin
        // renderer->GetActiveCamera()->SetViewUp(0.0, 0.0, 1.0);      // Up direction (Z+)
        // renderer->ResetCamera();

        /*****
        ORIGIN
        *****/
        // Create a sphere source for the point at the origin
        vtkSmartPointer<vtkSphereSource> sphereSource = vtkSmartPointer<vtkSphereSource>::New();
        sphereSource->SetCenter(0, 0, 0);  // Set the center of the sphere
        sphereSource->SetRadius(1);        // Set the radius of the sphere
        sphereSource->Update();            // Update to generate data

        // Create a mapper for the sphere
        vtkSmartPointer<vtkPolyDataMapper> sphereMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        sphereMapper->SetInputConnection(sphereSource->GetOutputPort());

        // Create an actor for the sphere
        vtkSmartPointer<vtkActor> sphereActor = vtkSmartPointer<vtkActor>::New();
        sphereActor->SetMapper(sphereMapper);
        // this->renderer->AddActor(sphereActor);

        /*****
        Plane Arrows
        *****/
        // Define colors directly using RGB values
        std::array<float, 3> red = {1.0, 0.0, 0.0};
        std::array<float, 3> green = {0.0, 1.0, 0.0};
        std::array<float, 3> blue = {0.0, 0.0, 1.0};

        // Define start and end points for the arrows
        std::array<float, 3> origin = {0.0, 0.0, 0.0};
        float scale = 100.0;  // Adjust to change the arrow size

        std::array<float, 3> xEnd = {scale, 0.0, 0.0};
        std::array<float, 3> yEnd = {0.0, scale, 0.0};
        std::array<float, 3> zEnd = {0.0, 0.0, scale};

        // Create arrow actors
        vtkSmartPointer<vtkActor> xArrow = createArrowActor(origin, xEnd, red);
        vtkSmartPointer<vtkActor> yArrow = createArrowActor(origin, yEnd, green);
        vtkSmartPointer<vtkActor> zArrow = createArrowActor(origin, zEnd, blue);

        // this->renderer->AddActor(xArrow);
        // this->renderer->AddActor(yArrow);
        // this->renderer->AddActor(zArrow);

        /*****
        Scene Floor
        *****/
        // Add z plane floor to renderer
        // Create plane to show XY plane at Z=0
        vtkSmartPointer<vtkPlaneSource> floorPlaneSource = vtkSmartPointer<vtkPlaneSource>::New();
        floorPlaneSource->SetOrigin(0, 0, 0);    // Set the origin
        floorPlaneSource->SetPoint1(100, 0, 0);  // Set the first point
        floorPlaneSource->SetPoint2(0, 100, 0);  // Set the second point
        floorPlaneSource->SetNormal(0, 0, 1);    // Set the normal to define XY plane
        floorPlaneSource->Update();              // Update to generate data
        // Create a mapper for the floor
        vtkSmartPointer<vtkPolyDataMapper> floorMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        floorMapper->SetInputConnection(floorPlaneSource->GetOutputPort());
        // Create an actor for the floor
        vtkSmartPointer<vtkActor> floorActor = vtkSmartPointer<vtkActor>::New();
        floorActor->SetMapper(floorMapper);
        // this->renderer->AddActor(floorActor);

        /*****
        AXES
        *****/
        // Create axes
        vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
        axes->SetPosition(0.0, 0.0, 0.0);

        /*****
        Scene Interactivity
        *****/
        // Set the interaction style to trackball camera
        vtkSmartPointer<vtkInteractorStyleTrackballCamera> style = vtkSmartPointer<vtkInteractorStyleTrackballCamera>::New();
        this->interactor->SetInteractorStyle(style);
        this->renderer->ResetCamera();

        /*****
        Orientation Marker Widget
        *****/

        // widget->SetOutlineColor(0.9300, 0.5700, 0.1300);
        // widget->SetOrientationMarker(axes);
        // widget->SetInteractor(this->interactor);
        // widget->SetViewport(0.0, 0.0, 0.3, 0.3);
        // widget->SetEnabled(1);
        // widget->InteractiveOff();

        // this->renderer->ResetCamera();
    }

    auto Plotter::createArrowActor(std::array<float, 3> start, std::array<float, 3> end, std::array<float, 3> color) -> Actor
    {
        // Create an arrow source
        vtkSmartPointer<vtkArrowSource> arrowSource = vtkSmartPointer<vtkArrowSource>::New();

        // Adjust the size of the arrowhead
        arrowSource->SetTipLength(0.05);
        arrowSource->SetTipRadius(0.02);
        arrowSource->SetTipResolution(20);  // Default is 6

        // Adjust the shaft radius to make the arrow thinner
        arrowSource->SetShaftRadius(0.01);

        // Compute the direction and length of the arrow
        double direction[3] = {end[0] - start[0], end[1] - start[1], end[2] - start[2]};
        double length = vtkMath::Norm(direction);
        vtkMath::Normalize(direction);

        // Create a transform to position and scale the arrow
        Transform transform = Transform::New();
        transform->Translate(&start[0]);

        // Compute the rotation needed to align the arrow with the direction vector
        double defaultDirection[3] = {1.0, 0.0, 0.0};  // Default arrow direction is along X axis
        double rotationAxis[3];
        vtkMath::Cross(defaultDirection, direction, rotationAxis);
        double angle = vtkMath::DegreesFromRadians(acos(vtkMath::Dot(defaultDirection, direction)));

        transform->RotateWXYZ(angle, rotationAxis);
        transform->Scale(length, length, length);

        // Apply the transform
        vtkSmartPointer<vtkTransformPolyDataFilter> transformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
        transformPD->SetTransform(transform);
        transformPD->SetInputConnection(arrowSource->GetOutputPort());

        // Create a mapper and actor
        vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
        mapper->SetInputConnection(transformPD->GetOutputPort());

        vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
        actor->SetMapper(mapper);
        // actor->GetProperty()->SetColor(color);

        return actor;
    };
}  // namespace vedo::plotter