#ifndef PLANE_H
#define PLANE_H

#include "vector.h"
#include "point.h"

namespace space
{

class Plane
{
public:

    Plane(const Vector<3> &normal, double m): 
        normal_(normal), m_(m)
    {}

    Plane(const Point<3> &a, const Point<3> &b, const Point<3> &c);


    double distance (const Point<3> &point) const;
    bool belong     (const Point<3> &point) const;

    Vector<3> normal() const { return normal_; }
    double m() const { return m_; }
private:

    Vector<3> normal_ = {0, 0, 0};
    double m_ = 0;
};

}// namespace space

#endif
