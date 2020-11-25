
#include "vector.h"

#include "common.h"

#include <iostream>
#include <cmath>

namespace space
{

Vector<3> crossProduct(const Vector<3> &lhs, const Vector<3> &rhs)
{
    double x = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    double y = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    double z = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return Vector<3>({x, y, z});
}

Vector<3> crossProduct(const Vector<2> &lhs, const Vector<2> &rhs)
{
    double z = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return Vector<3>({0, 0, z});
}

double pseudoProduct(const Vector<2> &lhs, const Vector<2> &rhs)
{
    return lhs[0] * rhs[1] - lhs[1] * rhs[0];
}

}// namespace space
