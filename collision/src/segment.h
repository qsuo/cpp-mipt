
#ifndef SEGMENT_H
#define SEGMENT_H

#include "vector.h"

namespace space
{

namespace dim2
{

struct Segment
{
    Segment(Vector p1, Vector p2): point1(p1), point2(p2), vector(p2 - p1) {}
    
    Vector point1;
    Vector point2;
    Vector vector;
    
};

bool intersection(Segment first, Segment second);

}// namespace dim2
}// namespace space
#endif
