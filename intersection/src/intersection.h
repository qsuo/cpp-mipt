
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "segment.h"
#include "triangle.h"

namespace space
{

bool intersection(const Segment<2> &first, const Segment<2> &second);
bool intersection(const Triangle<2> &first, const Triangle<2> &second);
bool intersection(const Triangle<3> &first, const Triangle<3> &second);

}// namespace space

#endif
