
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

    static bool intersection(const Triangle &first, const Triangle &second);
    static bool coplanarIntersection(const Triangle &first, const Triangle &second);
private:

    bool fromOneSide(const Points& points) const;
    std::vector<double> distances(const Points& points) const;


    Points points_;
    Plane plane_;
};

} // namespace space

#endif
