#include <vedo/file_io/reader.h>
#include <vedo/mesh/mesh.h>
#include <vedo/plotter/show.h>
#include <vedo/shapes/shapes.h>

auto main() -> int
{
    vedo::mesh::Mesh mesh = vedo::mesh::Mesh("data/spider.ply");
    vedo::shapes::ConvexHull convex_hull = vedo::shapes::ConvexHull(mesh);
    convex_hull.alpha(0.2);
    vedo::plotter::show(mesh, convex_hull);
    return 0;
}
