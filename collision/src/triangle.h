
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include "segment.h"
#include "plane.h"

namespace space
{

template <size_t Dim>
class Triangle
{
    static_assert(2 <= Dim && Dim <= 3);
public:
    
    using Points = std::array<Vector<Dim>, 3>;
    using Edges = std::array<Segment<Dim>, 3>;

    Triangle(const Vector<Dim> &v1, const Vector<Dim> &v2, const Vector<Dim> &v3);
    Points getPoints() const { return points_; }
    Edges getEdges() const { return edges_; }
    
    double area() const;

private:

    Points points_;
    Edges edges_;
};


template <size_t Dim>
Triangle<Dim>::Triangle(const Vector<Dim> &v1, const Vector<Dim> &v2, const Vector<Dim> &v3):
    points_{v1, v2, v3},
    edges_{ Segment<Dim>(v2, v1), Segment<Dim>(v3, v2), Segment<Dim>(v1, v3) }
    {}

template <size_t Dim>
double Triangle<Dim>::area() const
{
    auto a = points_[1] - points_[0];
    auto b = points_[2] - points_[0];
    double s = crossProduct(a, b).length() / 2;
    return s;
}

Plane getPlane(const Triangle<3> &triangle);

Triangle<2> project(const Triangle<3> &triangle, size_t axis);

}// namespace space

#endif
