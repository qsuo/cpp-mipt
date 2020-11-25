
#ifndef SEGMENT_H
#define SEGMENT_H

#include "vector.h"
#include "point.h"
#include "line.h"


namespace space
{
template <size_t Dim>
class Line;

template <size_t Dim>
struct Segment
{
public:

    Segment(): 
        a_({0, 0, 0}), b_({0, 0, 0}), vector_(b_ - a_)
    {}


    Segment(Point<Dim> a, Point<Dim> b): 
        a_(a), b_(b), vector_(b - a)
    {}

    Point<Dim> a()          const { return a_; }
    Point<Dim> b()          const { return b_; }
    Vector<Dim> vector()    const { return vector_; }

    bool belong(const Point<Dim> &point) const;
    
    bool operator==(const Segment &rhs) const;

private:
    Point<Dim> a_;
    Point<Dim> b_;
    Vector<Dim> vector_;
    
};

template <size_t Dim>
bool Segment<Dim>::belong(const Point<Dim> &point) const
{
    Line<Dim> line(*this);
    if(!line.belong(point))
        return false;

    auto a_c = a_ - point;
    auto b_c = b_ - point;

    auto x = a_c.length() + b_c.length();
    if(equal(x - vector_.length(), 0))
        return true;
    return false;
}

template <size_t Dim>
bool Segment<Dim>::operator==(const Segment &rhs) const
{
    return (a_ == rhs.a_ && b == rhs.b_);
}


}// namespace space

#endif
