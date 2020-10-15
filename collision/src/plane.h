
#ifndef PLANE_H
#define PLANE_H

#include "vector.h"

namespace space
{

namespace dim3
{

class Plane
{
public:
    Plane(): normal_(Vector({0, 0, 0})), member_(0) {}

    Plane(const Vector &normal, double member):
        normal_(normal), member_(member) {}

    double distance(const Vector &point) const;
    bool belong(const Vector &point) const;

    Vector getNormal() const { return normal_; }
    double getMember() const { return member_; }
private:

    Vector normal_;
    double member_;
};

} // namespace dim3
} // namespace space

#endif
