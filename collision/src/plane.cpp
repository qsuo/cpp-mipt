
#include "plane.h"
#include "vector.h"

#include "common.h"

#include <iostream>
#include <cmath>


namespace space
{


double Plane::distance(const Vector3d &point) const
{
    double dist = dotProduct(normal_, point) + member_;
    return dist;
}

bool Plane::belong(const Vector3d &point) const
{
    auto dist = distance(point);
    return (equal(dist, 0));
}

} // namespace space
