
#ifndef PLANE_H
#define PLANE_H

#include "vector.h"

namespace space
{

class Plane
{
public:
    Plane(): normal_(Vector3d({0, 0, 0})), member_(0) {}

    Plane(const Vector3d &normal, double member):
        normal_(normal), member_(member) {}
    //Plane(const Vector &Plane);

    double distance(const Vector3d &point) const;
    bool belong(const Vector3d &point) const;

    Vector3d getNormal() const { return normal_; }
    double getMember() const { return member_; }
private:

    Vector3d normal_;
    double member_;
};

} // space

#endif
