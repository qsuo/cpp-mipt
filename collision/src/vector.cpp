
#include "vector.h"

#include "common.h"

#include <iostream>
#include <cmath>

namespace space
{

Vector3d crossProduct(const Vector3d &lhs, const Vector3d &rhs)
{
    double x = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    double y = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    double z = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return Vector3d({x, y, z});
}

double pseudoProduct(const Vector2d &lhs, const Vector2d &rhs)
{
    return lhs[0] * lhs[1] - lhs[1] * rhs[0];
}

} //namespace space
