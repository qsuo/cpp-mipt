
#include "common.h"

#include <cmath>

namespace space
{

bool equal(double x, double y)
{
    return (std::abs(x - y) < EPS);
}

}// namespace space

