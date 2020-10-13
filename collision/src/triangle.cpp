
#include "triangle.h"
#include "common.h"

#include <cassert>
#include <iostream>
#include <cmath>

namespace space
{

Triangle::Triangle(const Vector &v1, const Vector &v2, const Vector &v3):
        points_{v1, v2, v3}
{
    auto firstSide = points_[1] - points_[0];
    auto secondSide = points_[2] - points_[0];
    auto normal = firstSide.crossProduct(secondSide);
    double member = -normal.dotProduct(points_[0]);
    plane_ = space::Plane(normal, member);
}

double Triangle::area()
{
    auto a = points_[1] - points_[0];
    auto b = points_[2] - points_[0];
    double s = a.crossProduct(b).length() / 2;
    return s;
}

Triangle Triangle::project(unsigned axis) const
{
    assert(axis < points_.size());
    if(axis == 0)
    {
        return Triangle(points_[0].projectX(),
                        points_[1].projectX(),
                        points_[2].projectX());
    }
    
    else if(axis == 1)
    {
        return Triangle(points_[0].projectY(),
                        points_[1].projectY(),
                        points_[2].projectY());
    }

    else
    {
        return Triangle(points_[0].projectZ(),
                        points_[1].projectZ(),
                        points_[2].projectZ());
    }


}

void Triangle::dump() const
{
    for(const auto &point : points_)
        point.dump();
}

} // namespace space
