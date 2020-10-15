
#include "intersection.h"
#include "vector.h"
#include "common.h"
#include "segment.h"
#include "triangle.h"

#include <cstdio>
#include <iostream>
#include <cmath>
#include <cassert>
#include <array>
#include <algorithm>

namespace
{


struct DistPoint
{
    space::dim3::Vector point;
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

SelectedPoints computeDistances(const space::dim3::Triangle &triangle, const space::dim3::Triangle::Points& points)
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

Interval intersectionInterval(SelectedPoints &points, const space::dim3::Vector line)
{
    std::vector<DistPoint> major;
    std::vector<DistPoint> minor;
   
    classifyPoints(major, minor, points);
    
    assert(major.size() == 2);
    assert(minor.size() == 1);

    std::vector<double> proj;
    for(const auto &p : major)
    {
        double tproj = dotProduct(p.point, line);
        proj.push_back(tproj);
    }
    proj.push_back(dotProduct(minor[0].point, line));
   
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

bool sameSide(space::dim2::Vector p1, space::dim2::Vector p2, space::dim2::Segment segment)
{
    auto prod1 = space::dim2::crossProduct(segment.point2 - segment.point1, p1 - segment.point1);
    auto prod2 = space::dim2::crossProduct(segment.point2 - segment.point1, p2 - segment.point1);
    auto sprod = space::dotProduct(prod1, prod2);
    if(sprod > 0 || space::equal(sprod, 0))
        return true;
    return false;
}

bool pointInsideTriangle(space::dim2::Vector point, space::dim2::Triangle &triangle)
{
    auto tpoints = triangle.getPoints();
    bool in = (sameSide(point, tpoints[0], {tpoints[1], tpoints[2]})) &&
              (sameSide(point, tpoints[1], {tpoints[2], tpoints[0]})) &&
              (sameSide(point, tpoints[2], {tpoints[0], tpoints[1]}));
    return in;
}

size_t mostAreaAxis(const space::dim3::Triangle &first, const space::dim3::Triangle &second)
{
    size_t axis = 0;
    double maxArea = 0;
    for(size_t i = 0; i < 3; ++i)
    {
        auto area = first.project(i).area();
        if(area > maxArea)
        {
            area = maxArea;
            axis = i;
        }
    }
    return axis;
}

bool edgesIntersection(const std::vector<space::dim2::Segment> &fedges, const std::vector<space::dim2::Segment> &sedges)
{
    for(size_t i = 0; i < fedges.size(); ++i)
    {
        for(size_t j = 0; j < sedges.size(); ++j)
        {
            if(space::dim2::intersection(fedges[i], sedges[j]))
                return true;
        }
    }
    return false;
}

bool coplanarIntersection(const space::dim3::Triangle &first, const space::dim3::Triangle &second)
{
    auto axis = mostAreaAxis(first, second);

    auto pfirst = first.project(axis);
    auto psecond = second.project(axis);
    
    std::vector<space::dim2::Segment> fsides;
    std::vector<space::dim2::Segment> ssides;
    
    auto fpoints = pfirst.getPoints();
    auto spoints = psecond.getPoints();
    for(size_t i = 1, size = fpoints.size(); i <= size; ++i)
    {
        fsides.push_back({fpoints[i % size], fpoints[i - 1]});
        ssides.push_back({spoints[i % size], spoints[i - 1]});
    }

    if(edgesIntersection(fsides, ssides))
        return true;

    if(pointInsideTriangle(fpoints[0], psecond) || pointInsideTriangle(spoints[0], pfirst))
        return true;
    
    return false;

}


} // namespace

namespace space
{

namespace dim3
{

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
    auto intersectLine = crossProduct(fplane.getNormal(), splane.getNormal());
    
    auto finterval =  intersectionInterval(fpoints, intersectLine);   
    auto sinterval =  intersectionInterval(spoints, intersectLine);   
    
    return overlap(finterval, sinterval);
}

}

} // namespace space
