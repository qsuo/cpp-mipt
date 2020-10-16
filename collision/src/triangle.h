
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include "plane.h"

#include <vector>
#include <array>

namespace space
{


namespace dim2
{

class Triangle
{
public:
    using Points = std::array<Vector, 3>;

    Triangle(const Vector &v1, const Vector &v2, const Vector &v3);
    
    const Points& getPoints() const { return points_; }
    
    double area() const;

    void dump() const;
private:
    Points points_;
};

bool intersection(const Triangle &first, const Triangle &second);

}// namespace dim2

namespace dim3
{

class Triangle
{
public:
    
    using Points = std::array<Vector, 3>;

    Triangle(const Vector &v1, const Vector &v2, const Vector &v3);
    
    Plane getPlane() const { return plane_; }
    const Points& getPoints() const { return points_; }
    dim2::Triangle project(size_t axis = 0) const;
    
    double area() const;

    void dump() const;
private:

    Points points_;
    dim3::Plane plane_;
};

bool intersection(const Triangle &first, const Triangle &second);

}// namespace dim3


} // namespace space

#endif
