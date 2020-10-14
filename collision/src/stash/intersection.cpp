
#include "intersection.h"
#include "vector.h"
#include "common.h"

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cassert>
#include <array>

namespace
{

struct DistPoint
{
    space::Vector point;
    double dist;
};

struct SelectedPoints
{
    std::vector<DistPoint> pos;
    std::vector<DistPoint> neg;
    std::vector<DistPoint> zero;
};

struct Interval
{
    double start;
    double end;
};

SelectedPoints computeDistances(const space::Triangle &triangle, const space::Triangle::Points& points)
{
    SelectedPoints spoints;
    auto plane = triangle.getPlane();
    for(const auto& point : points)
    {
        auto dist = plane.distance(point);
        DistPoint tmp{point, dist};

        if(space::equal(dist, 0)) 
            spoints.zero.push_back(tmp);
        if(dist > 0)
            spoints.pos.push_back(tmp);
        if(dist < 0)
            spoints.neg.push_back(tmp);
    }

    return spoints;
}

bool fromOneSide(const SelectedPoints &points)
{
    if(points.pos.size() == 3 || points.neg.size() == 3)
        return true;
    return false;
}

void classifyPoints(std::vector<DistPoint> &major, std::vector<DistPoint> &minor,
                    const SelectedPoints &points)
{
    if(points.zero.size() == 0)
    {
        if(points.pos.size() == 2)
        {
            major = points.pos;
            minor = points.neg;
        }
        else
        {
            major = points.neg;
            minor = points.pos;
        }
    }

    if(points.zero.size() == 1)
    {
        if(points.pos.size() == 2)
        {
            major = points.pos;
            minor = points.zero;
        }
        if(points.neg.size() == 2)
        {
            major = points.neg;
            minor = points.zero;
        }
        if(points.pos.size() == 1)
        {
            major = points.pos;
            major.insert(major.end(), points.zero.begin(), points.zero.end());
            minor = points.neg;
        }
    }

    if(points.zero.size() == 2)
    {
        major = points.zero;
        if(points.pos.size() == 1)
            minor = points.pos;
        else
            minor = points.neg;
    }

}

Interval intersectionInterval(SelectedPoints &points, const space::Vector line)
{
    std::vector<DistPoint> major;
    std::vector<DistPoint> minor;
   
    classifyPoints(major, minor, points);
    
    assert(major.size() == 2);
    assert(minor.size() == 1);

    std::vector<double> proj;
    for(const auto &p : major)
    {
        double tproj = p.point.dotProduct(line);
        proj.push_back(tproj);
    }
    proj.push_back(minor[0].point.dotProduct(line));
   
    std::vector<double> interval;
    for(decltype(major.size()) i = 0; i < major.size(); i++)
    {
        double t = proj[i] + (proj[2] - proj[i]) * major[i].dist / (major[i].dist - minor[0].dist);
        interval.push_back(t);
    }

    assert(interval.size() == 2);
    
    Interval inter {0, 0};
    inter.start = (interval[0] < interval[1]) ? interval[0] : interval[1];
    inter.end   = (interval[0] < interval[1]) ? interval[1] : interval[0];
    return inter;
}

bool overlap(Interval in1, Interval in2)
{
    if(in1.start < in2.start)
    {
        if((in1.end > in2.start) || space::equal(in1.end, in2.start))
            return true;
    }
    else
    {
        if((in2.end > in1.start) || space::equal(in2.end, in1.start))
            return true;
    }
    return false;
}

bool coplanarIntersection(const space::Triangle &first, const space::Triangle &second)
{
    auto ft = first.project();
    auto st = second.project();

    return false;
}

  


} // namespace

namespace space
{

bool lineIntersection(space::Vector f1, space::Vector f2,
                      space::Vector s1, space::Vector s2)
{
    auto r1 = f2 - f1;
    auto r2 = s2 - s1;

    auto cross1 = s2.crossProduct(s1).z_;
    auto cross2 = f2.crossProduct(f1).z_;
    auto gcross = r2.crossProduct(r1).z_;


    auto r = (r1 * (cross1 / gcross) - r2 * (cross2 / gcross));

    r.dump();
    
    auto t1 = (r - f1).dotProduct(r - f2); 
    auto t2 = (r - s1).dotProduct(r - s2);
    bool res1 = (t1 < 0) || equal(t1, 0); 
    bool res2 = (t2 < 0) || equal(t2, 0);
    return (res1 && res2);
}


bool intersection(const Triangle &first, const Triangle &second)
{
    auto fpoints = computeDistances(first, second.getPoints());
    auto spoints = computeDistances(second, first.getPoints());
   
    if(fromOneSide(fpoints) || fromOneSide(spoints))
        return false;

    if(fpoints.zero.size() == 3)
    {
        assert(spoints.zero.size() == 3);
        return coplanarIntersection(first, second);
    }

    auto fplane = first.getPlane();
    auto splane = second.getPlane();
    auto intersectLine = fplane.getNormal().crossProduct(splane.getNormal());
    
    auto finterval =  intersectionInterval(fpoints, intersectLine);   
    auto sinterval =  intersectionInterval(spoints, intersectLine);   
    
    return overlap(finterval, sinterval);
}

} // namespace space
