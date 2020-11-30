
#ifndef TRIANGLES_SET_INTERSECTION_H
#define TRIANGLES_SET_INTERSECTION_H

#include "triangle.h"
#include "intersection.h"
#include "common.h"

#include <vector>
#include <set>
#include <sstream>


namespace space
{

std::set<size_t> findIntersections_naive(std::vector<Triangle<3>*> triangles);
std::set<size_t> findIntersections(std::vector<Triangle<3>*> triangles);

void triangleIntersections(std::istream &in, std::ostream &out);

}// namespace space

#endif
