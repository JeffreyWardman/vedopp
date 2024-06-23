#include <vtkCellSizeFilter.h>

#include <Eigen/Dense>
#include <array>
#include <tuple>

#include "../types.h"

namespace vedo::core
{
    template <typename Derived>
    auto CommonAlgorithms<Derived>::bounds() const -> std::array<double, 6>
    {
        std::array<double, 6> bounds;
        auto* non_const_this = const_cast<Derived*>(static_cast<const Derived*>(this));  // TODO need concast?
        non_const_this->dataset->GetBounds(bounds.data());
        return bounds;
    }

    template <typename Derived>
    auto CommonAlgorithms<Derived>::xbounds() const -> std::tuple<double, double>
    {
        std::array<double, 6> bounds = static_cast<const Derived&>(*this).bounds();
        return {bounds[0], bounds[1]};
    }

    template <typename Derived>
    auto CommonAlgorithms<Derived>::ybounds() const -> std::tuple<double, double>
    {
        std::array<double, 6> bounds = static_cast<const Derived&>(*this).bounds();
        return {bounds[2], bounds[3]};
    }

    template <typename Derived>
    auto CommonAlgorithms<Derived>::zbounds() const -> std::tuple<double, double>
    {
        std::array<double, 6> bounds = static_cast<const Derived&>(*this).bounds();
        return {bounds[4], bounds[5]};
    }

    template <typename Derived>
    Vertices CommonAlgorithms<Derived>::cell_centers() const
    {
        Vertices centers = static_cast<const Derived&>(*this).dataset->GetCellCenters();
        return centers;
    }

    template <typename Derived>
    Vertices CommonAlgorithms<Derived>::vertices() const
    {
        Vertices vertices = static_cast<const Derived&>(*this).dataset->GetPoints();
        return vertices;
    }

    template <typename Derived>
    int CommonAlgorithms<Derived>::nvertices() const
    {
        return static_cast<const Derived&>(*this).npoints();
    }

    template <typename Derived>
    int CommonAlgorithms<Derived>::npoints() const
    {
        int npoints = static_cast<const Derived&>(*this).dataset->GetNumberOfPoints();
        return npoints;
    }

    template <typename Derived>
    Cells CommonAlgorithms<Derived>::cells() const
    {
        Cells cells = static_cast<const Derived&>(*this).dataset->GetPolys();
        return cells;
    }

    template <typename Derived>
    int CommonAlgorithms<Derived>::ncells() const
    {
        return static_cast<const Derived&>(*this).dataset->GetNumberOfCells();
    }

    template <typename Derived>
    Derived& CommonAlgorithms<Derived>::compute_cell_size()
    {
        vtkSmartPointer<vtkCellSizeFilter> filter = vtkSmartPointer<vtkCellSizeFilter>::New();
        filter->SetInputData(static_cast<Derived&>(*this).dataset);
        filter->SetComputeArea(1);
        filter->SetComputeVolume(1);
        filter->SetComputeLength(1);
        filter->SetComputeVertexCount(0);
        filter->SetAreaArrayName("Area");
        filter->SetVolumeArrayName("Volume");
        filter->SetLengthArrayName("Length");
        filter->Update();

        static_cast<Derived&>(*this).dataset->ShallowCopy(filter->GetOutput());
        return static_cast<Derived&>(*this);
    }

    template <typename Derived>
    double CommonAlgorithms<Derived>::calculate_average_size() const
    {
        Vertices vertices = static_cast<const Derived&>(*this).vertices();
        int num_points = static_cast<const Derived&>(*this).npoints();
        if (!vertices || num_points == 0)
        {
            return 0.0;
        }

        // Store point coordinates
        Eigen::MatrixXd coords(num_points, 3);
        for (vtkIdType i = 0; i < num_points; ++i)
        {
            double p[3];
            vertices->GetPoint(i, p);
            coords(i, 0) = p[0];
            coords(i, 1) = p[1];
            coords(i, 2) = p[2];
        }

        // Calculate the center of mass using Eigen
        Eigen::Vector3d center = coords.colwise().mean();

        // Subtract center from all points
        Eigen::MatrixXd centered = coords.rowwise() - center.transpose();

        // Calculate the distances from the center of mass
        Eigen::VectorXd distances = centered.rowwise().norm();

        // Calculate and return the average distance
        double average_size = distances.mean();

        return average_size;
    }

    template <typename Derived>
    double CommonAlgorithms<Derived>::diagonal_size() const
    {
        std::array<double, 6> bounds = static_cast<const Derived&>(*this).bounds();
        return std::sqrt((bounds[1] - bounds[0]) * (bounds[1] - bounds[0]) + (bounds[3] - bounds[2]) * (bounds[3] - bounds[2]) +
                         (bounds[5] - bounds[4]) * (bounds[5] - bounds[4]));
    }
}  // namespace vedo::core
