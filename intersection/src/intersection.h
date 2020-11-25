#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "segment.h"
#include "triangle.h"

namespace space
{

struct PlaneIntersectionPoint
{
    Point<3> point;
    bool coplanar;
    bool intersect; 
};


bool intersection(const Segment<2> &first, const Segment<2> &second);

bool intersection(const Triangle<2> &first, const Triangle<2> &second);
bool intersection(const Triangle<3> &first, const Triangle<3> &second);

bool intersection(const Triangle<3> &triangle, const Segment<3> &segment);

PlaneIntersectionPoint intersection(const Plane &plane, const Line<3> &line);
PlaneIntersectionPoint intersection(const Plane &plane, const Segment<3> &segment);

}// namespace space

#endif
