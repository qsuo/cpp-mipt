
#include "plane.h"

#include "vector.h"
#include "common.h"

#include <cmath>


namespace space
{

double Plane::distance(const Vector<3> &point) const
{
    auto dist = dotProduct(normal_, point) + member_;
    return dist;
}

bool Plane::belong(const Vector<3> &point) const
{
    auto dist = distance(point);
    return (equal(dist, 0));
}

} // namespace space

