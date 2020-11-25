#include "triangle.h"

namespace space
{

Triangle<2> project(const Triangle<3> &triangle, size_t axis)
{
    auto points = triangle.points();
    return Triangle<2>(points[0].project(axis),
                       points[1].project(axis),
                       points[2].project(axis));
}

}// namespace space

