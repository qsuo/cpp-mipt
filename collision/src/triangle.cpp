
#include "triangle.h"
#include "common.h"
#include "vector.h"
#include "plane.h"

#include <cassert>
#include <iostream>
#include <cmath>

namespace space
{

namespace dim3
{

Triangle::Triangle(const Vector &v1, const Vector &v2, const Vector &v3):
points_{v1, v2, v3}
{
    auto firstSide = points_[1] - points_[0];
    auto secondSide = points_[2] - points_[0];
    auto normal = crossProduct(firstSide, secondSide);
    double member = -dotProduct(normal, points_[0]);
    plane_ = dim3::Plane(normal, member);
}

double Triangle::area() const
{
    auto a = points_[1] - points_[0];
    auto b = points_[2] - points_[0];
    double s = crossProduct(a, b).length() / 2;
    return s;
}

void Triangle::dump() const
{
    for(const auto &point : points_)
        point.dump();
}

dim2::Triangle Triangle::project(size_t axis) const
{
    assert(axis < points_.size());
    return dim2::Triangle(points_[0].project(axis),
                          points_[1].project(axis),
                          points_[2].project(axis));
    
}

}// namespace dim3

namespace dim2
{

Triangle::Triangle(const Vector &v1, const Vector &v2, const Vector &v3):
points_{v1, v2, v3}
{}

double Triangle::area() const
{
    auto a = points_[1] - points_[0];
    auto b = points_[2] - points_[0];
    double s = crossProduct(a, b).length() / 2;
    return s;
}

void Triangle::dump() const
{
    for(const auto &point : points_)
        point.dump();
}


}// namespace dim2
} // namespace space
