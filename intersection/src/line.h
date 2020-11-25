
#ifndef LINE_H
#define LINE_H

#include "common.h"
#include "vector.h"
#include "point.h"
#include "segment.h"


namespace space
{

template <size_t Dim>
class Segment;

template <size_t Dim>
class Line
{
public:
    Line(const Vector<Dim> &direction, const Point<Dim> &initial):
        direction_(direction), initial_(initial)
    {}

    Line(const Segment<Dim> &segment):
        direction_(segment.vector()), initial_(segment.a())
    {}

    Vector<Dim> direction() const { return direction_; }
    Vector<Dim> initial()   const { return initial_; }

    bool belong(const Point<Dim> &point) const;
    
private:
    Vector<Dim> direction_;
    Point<Dim> initial_;
};

template <size_t Dim>
bool Line<Dim>::belong(const Point<Dim> &point) const
{
    auto tmp = initial_ - point;
    if(equal(crossProduct(direction_, tmp).length(), 0))
        return true;

    return false;
}

bool collinear(Line<2> &lhs, Line<2> &rhs);

}// namespace space

#endif

