
#ifndef PLANE_H
#define PLANE_H

#include "vector.h"

namespace space
{

class Plane
{
public:
    Plane(): normal_(Vector<3>({0, 0, 0})), member_(0) {}

    Plane(const Vector<3> &normal, double member): 
        normal_(normal), member_(member) {}

    double distance(const Vector<3> &point) const;
    bool belong(const Vector<3> &point) const;

    Vector<3> getNormal() const { return normal_; }
    double getMember() const { return member_; }
private:

    Vector<3> normal_;
    double member_;
};

} // namespace space

#endif
