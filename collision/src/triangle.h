
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"
#include "plane.h"

#include <vector>

namespace space
{

class Triangle
{
public:
    
    using Points = std::vector<Vector>;

    Triangle(const Vector &v1, const Vector &v2, const Vector &v3);
    
    Plane getPlane() const { return plane_; }
    const Points& getPoints() const { return points_; }
    Triangle project(unsigned axis = 0) const;
    
    double area(); //TODO const???

    void dump() const;
private:

    Points points_;
    Plane plane_;
};

} // namespace space

#endif
