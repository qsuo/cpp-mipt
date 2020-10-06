
#include "triangle.h"
#include "common.h"

#include <iostream>

namespace space
{

Triangle::Triangle(const Vector &v1, const Vector &v2, const Vector &v3):
        points_{v1, v2, v3}
{
    auto firstSide = points_[1] - points_[0];
    auto secondSide = points_[2] - points_[0];
    auto normal = firstSide.crossProduct(secondSide);
    double member = - normal.dotProduct(points_[0]);
    plane_ = space::Plane(normal, member);
}


std::vector<double> Triangle::distances(const Points& points) const
{
    
    std::vector<double> dists;
    for(const auto& point : points)
        dists.push_back(plane_.distance(point));
    return dists;
}

bool Triangle::fromOneSide(const Points& points) const
{
    auto dists = distances(points);

    unsigned posCount = 0;
    unsigned negCount = 0;
    for(const auto& dist : dists)
    {
        if(dist < space::EPS) continue;
        if(dist > 0)          posCount++;
        if(dist < 0)          negCount++;
    }
    if(posCount == points.size() || negCount == points.size())
        return false;
    
    return true;
    
}


bool Triangle::coplanarIntersection(const Triangle &first, const Triangle &second)
{
    return true;
}

bool Triangle::intersection(const Triangle &first, const Triangle &second)
{
    for(auto& point : first.points_)
        point.dump();
   
    if(first.fromOneSide(second.points_) || second.fromOneSide(first.points_))
        return false;
    
    auto distsFirstToSecond = first.distances(second.points_);
    unsigned zeroCount = 0;
    for(const auto& dist : distsFirstToSecond)
    {
        if(dist < space::EPS) zeroCount++;
    }

    if(zeroCount == distsFirstToSecond.size())
        return coplanarIntersection(first, second);

    


    return true;
}


} // namespace space
