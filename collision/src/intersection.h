
#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "triangle.h"

namespace space
{
struct Line
{
    space::Vector first;
    space::Vector second;
};

namespace line
{

bool intersection(Line line1, Line line2, space::Vector norm);
}

bool intersection(const Triangle &first, const Triangle &second);

} //namespace space

#endif
