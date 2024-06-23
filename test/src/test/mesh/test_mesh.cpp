// #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vedo/mesh/mesh.h>

#include <catch2/catch_test_macros.hpp>
#include <string>

const std::string EXAMPLE_MESH_PATH = "data/dragon.ply";

TEST_CASE("Mesh number of points", "[vedo][mesh][Mesh]")
{
    vedo::mesh::Mesh mesh(EXAMPLE_MESH_PATH);
    int num_points = mesh.npoints();
    REQUIRE(num_points >= 0);
}

TEST_CASE("Mesh number of cells", "[vedo][mesh][Mesh]")
{
    vedo::mesh::Mesh mesh(EXAMPLE_MESH_PATH);
    int num_cells = mesh.ncells();
    REQUIRE(num_cells >= 0);
}

TEST_CASE("Mesh area", "[vedo][mesh][Mesh]")
{
    vedo::mesh::Mesh mesh(EXAMPLE_MESH_PATH);
    double area = mesh.area();
    REQUIRE(area >= 0);
}

TEST_CASE("Mesh volume", "[vedo][mesh][Mesh]")
{
    vedo::mesh::Mesh mesh(EXAMPLE_MESH_PATH);
    double volume = mesh.volume();
    REQUIRE(volume >= 0);
}

TEST_CASE("Mesh decimated by fraction", "[vedo][mesh][Mesh]")
{
    vedo::mesh::Mesh mesh(EXAMPLE_MESH_PATH);
    vedo::mesh::Mesh decimated = mesh.decimate(0.5);
    REQUIRE(mesh.npoints() >= decimated.npoints());
}

TEST_CASE("Mesh decimated by n", "[vedo][mesh][Mesh]")
{
    vedo::mesh::Mesh mesh(EXAMPLE_MESH_PATH);
    vedo::mesh::Mesh decimated = mesh.decimate(1, 100);
    REQUIRE(mesh.npoints() >= decimated.npoints());
    REQUIRE(decimated.npoints() == 100);
}

TEST_CASE("Mesh triangulate", "[vedo][mesh][Mesh]")
{
    vedo::mesh::Mesh mesh(EXAMPLE_MESH_PATH);
    vedo::mesh::Mesh triangulated = mesh.triangulate();
}

TEST_CASE("Mesh copy", "[vedo][mesh][Mesh]")
{
    vedo::mesh::Mesh mesh(EXAMPLE_MESH_PATH);
    vedo::mesh::Mesh copy = mesh.copy();

    int num_points = mesh.npoints();
    int num_points_copy = copy.npoints();

    REQUIRE(num_points == num_points_copy);
    REQUIRE(num_points >= 0);
}
