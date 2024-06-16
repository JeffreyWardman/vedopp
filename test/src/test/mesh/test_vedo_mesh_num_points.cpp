// #define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <vedo/mesh/mesh.h>

#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <string>

TEST_CASE("Mesh loads", "[vedo][mesh][Mesh]")
{
    vedo::mesh::Mesh mesh("data/dragon.ply");
    auto num_points = static_cast<int>(mesh.dataset->GetNumberOfPoints());
    REQUIRE(num_points >= 0);
}
