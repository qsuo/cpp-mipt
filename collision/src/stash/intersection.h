
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "triangle.h"

namespace space
{

bool lineIntersection(space::Vector f1, space::Vector f2,
                      space::Vector s1, space::Vector s2);

bool intersection(const Triangle &first, const Triangle &second);

} //namespace space

#endif