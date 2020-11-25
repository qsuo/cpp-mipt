#include "plane.h"

#include "vector.h"
#include "common.h"

#include <cmath>


namespace space
{

Plane::Plane(const Point<3> &a, const Point<3> &b, const Point<3> &c)
{
    auto ab = b - a;
    auto ac = c - a;
    normal_ = crossProduct(ab, ac);
    m_ = -dotProduct(normal_, a);
}

double Plane::distance(const Point<3> &point) const
{
    auto dist = dotProduct(normal_, point) + m_;
    return dist;
}

bool Plane::belong(const Point<3> &point) const
{
    auto dist = distance(point);
    return (equal(dist, 0));
}

} // namespace space

