
#ifndef POINT_H
#define POINT_H

#include "vector.h"

namespace space
{

template <size_t Dim>
using Point = Vector<Dim>;

}// namespace space
#endif

