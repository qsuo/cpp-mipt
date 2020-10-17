
#ifndef SEGMENT_H
#define SEGMENT_H

#include "vector.h"

namespace space
{

template <size_t Dim>
struct Segment
{
    Segment(Vector<Dim> p1, Vector<Dim> p2): 
        a(p1), b(p2), vector(b - a) {}
    
    Vector<Dim> a;
    Vector<Dim> b;
    Vector<Dim> vector;
    
};


}// namespace space

#endif
