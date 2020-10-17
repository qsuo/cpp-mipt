
#include "triangle.h"


namespace space
{

Plane getPlane(const Triangle<3> &triangle)
{
    auto points = triangle.getPoints();
    auto a = points[1] - points[0];
    auto b = points[2] - points[0];
    auto normal = crossProduct(a, b);
    double member = -dotProduct(normal, points[0]);
    return Plane(normal, member);
}

Triangle<2> project(const Triangle<3> &triangle, size_t axis)
{
    auto points = triangle.getPoints();
    return Triangle<2>(points[0].project(axis),
                       points[1].project(axis),
                       points[2].project(axis));
}

}


