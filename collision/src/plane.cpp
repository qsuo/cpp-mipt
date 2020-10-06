
#include "plane.h"

#include "common.h"

#include <iostream>
#include <cmath>


namespace space
{


double Plane::distance(const Vector &point) const
{
    double dist = normal_.dotProduct(point) + member_;
    return dist;
}

bool Plane::belong(const Vector &point) const
{
    auto dist = distance(point);
    return (std::abs(dist) < EPS);
}

} // namespace space

