
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <array>

#include "vector.h"
#include "point.h"
#include "segment.h"
#include "plane.h"

namespace space
{

template <size_t Dim>
class TriangleBase
{
public:
    
    using Points = std::array<Point<Dim>, 3>;
    using Edges = std::array<Segment<Dim>, 3>;

    TriangleBase(const Point<Dim> &a, const Point<Dim> &b, const Point<Dim> &c);
    
    Points points()  const { return points_; }
    Edges edges()    const { return edges_; }

    double area() const
    {
        auto a = points_[1] - points_[0];
        auto b = points_[2] - points_[0];
        double s = crossProduct(a, b).length() / 2;
        return s;
    }
    bool isPoint = false;
    bool isSegment = false;
    Segment<Dim> segment; 

protected:

    Points points_;
    Edges edges_;

};
template <size_t Dim>
TriangleBase<Dim>::TriangleBase( const Point<Dim> &a,
                                 const Point<Dim> &b,
                                 const Point<Dim> &c):
    points_{a, b, c},
    edges_{ Segment<Dim>(a, b),
            Segment<Dim>(b, c),
            Segment<Dim>(a, c) }
{
    if(a == b && b == c)
        isPoint = true;
    if( (a == b) && !(b == c) )
    {
        isSegment = true;
        segment = Segment<Dim>(a, c);
    }
    if( (b == c) && !(b == a) )
    {
        isSegment = true;
        segment = Segment<Dim>(b, c);
    }
    
}

template <size_t Dim>
class Triangle : public TriangleBase<Dim>
{
public:
    Triangle(const Point<Dim> &a, const Point<Dim> &b, const Point<Dim> &c):
        TriangleBase<Dim>(a, b, c)
    {}
};

template <>
class Triangle<3> : public TriangleBase<3>
{ 

public:
    
    struct BoundBox
    {
        Point<3> min = {};
        Point<3> max = {};
    } box;


    
    Triangle(const Point<3> &a, const Point<3> &b, const Point<3> &c):
        TriangleBase(a, b, c)
    {
        auto minx = points_[0][0];
        auto miny = points_[0][1];
        auto minz = points_[0][2];

        auto maxx = points_[0][0];
        auto maxy = points_[0][1];
        auto maxz = points_[0][2];

        for(size_t i = 1; i < 3; i++)
        {
            if(points_[i][0] < minx)
                minx = points_[i][0];
            if(points_[i][1] < miny)
                miny = points_[i][1];
            if(points_[i][2] < minz)
                minz = points_[i][2];

            if(points_[i][0] > maxx)
                maxx = points_[i][0];
            if(points_[i][1] > maxy)
                maxy = points_[i][1];
            if(points_[i][2] > maxz)
                maxz = points_[i][2];
        }

        box = { {minx, miny, minz}, {maxx, maxy, maxz} };
    }

    Plane plane() const
    {
        auto a = points_[1] - points_[0];
        auto b = points_[2] - points_[0];
        auto normal = crossProduct(a, b);
        double m = -dotProduct(normal, points_[0]);
        return Plane(normal, m);
    }

};

Triangle<2> project(const Triangle<3> &triangle, size_t axis);

}// namespace space

#endif

