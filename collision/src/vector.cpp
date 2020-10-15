
#include "vector.h"

#include "common.h"

#include <iostream>
#include <cmath>

namespace space
{

namespace dim3
{

Vector crossProduct(const Vector &lhs, const Vector &rhs)
{
    double x = lhs[1] * rhs[2] - lhs[2] * rhs[1];
    double y = lhs[2] * rhs[0] - lhs[0] * rhs[2];
    double z = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return Vector({x, y, z});
}

}// namespace 3d

namespace dim2
{

double pseudoProduct(const Vector &lhs, const Vector &rhs)
{
    return lhs[0] * rhs[1] - lhs[1] * rhs[0];
}

dim3::Vector crossProduct(const Vector &lhs, const Vector &rhs)
{
    double z = lhs[0] * rhs[1] - lhs[1] * rhs[0];
    return dim3::Vector({0, 0, z});
}


}// namespace 2d

} //namespace space
