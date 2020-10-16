#include "segment.h"
#include "vector.h"
#include "triangle.h"

#include <cmath>
#include <vector>
#include <cassert>

namespace
{

bool collinear(const space::Segment<2> &s1, const space::Segment<2> &s2)
{
    auto prod = std::abs(space::pseudoProduct(s1.vector, s2.vector));
    auto expr = prod / (s1.vector.length() * s2.vector.length());
    return space::equal(expr, 0); 
}

bool onSameLine(const space::Segment<2> &s1, const space::Segment<2> &s2)
{
    auto r = s2.a - s1.b;
    auto prod = std::abs(space::pseudoProduct(s2.vector, r));
    auto expr = prod / (s2.vector.length() * r.length());
    return space::equal(expr, 0);
}

bool overlap(const space::Segment<2> &s1, const space::Segment<2> &s2)
{
    bool result = (space::dotProduct(s1.a - s2.b, s1.a - s2.b) > 0) &&
                  (space::dotProduct(s1.b - s2.b, s1.b - s2.b) > 0) &&
                  (space::dotProduct(s2.a - s1.a, s2.a - s1.b) > 0) &&
                  (space::dotProduct(s2.b - s1.a, s2.b - s1.b) > 0);
    return !result;
}
}// namespace 


namespace space
{

bool intersection(const Segment<2> &first, const Segment<2> &second)
{
    
    bool coll = collinear(first, second);
    bool sameLine = onSameLine(first, second);
    if(coll && !sameLine)
        return false;
    if(coll && sameLine)
        return overlap(first, second);

    auto &r1 = first.vector;
    auto &r2 = second.vector;

    auto prod1 = pseudoProduct(second.b, second.a);
    auto prod2 = pseudoProduct(first.b, first.a);
    auto gprod = pseudoProduct(r2, r1);
    auto r = (r1 * (prod1 / gprod) - r2 * (prod2 / gprod));

    auto t1 = dotProduct(r - first.a, r - first.b); 
    auto t2 = dotProduct(r - second.a, r - second.b); 

    bool res1 = (t1 < 0) || equal(t1, 0); 
    bool res2 = (t2 < 0) || equal(t2, 0);
    return (res1 && res2);

}

}// namespace space

namespace
{
bool sameSide(space::Vector<2> p1, space::Vector<2> p2, space::Segment<2> segment)
{
    auto prod1 = space::crossProduct(segment.b - segment.a, p1 - segment.a);
    auto prod2 = space::crossProduct(segment.b - segment.a, p2 - segment.a);
    auto sprod = space::dotProduct(prod1, prod2);
    if(sprod > 0 || space::equal(sprod, 0))
        return true;
    return false;
}


bool pointInsideTriangle(const space::Vector<2> &point, const space::Triangle<2> &triangle)
{
    auto tpoints = triangle.getPoints();
    bool in = (sameSide(point, tpoints[0], {tpoints[1], tpoints[2]})) &&
              (sameSide(point, tpoints[1], {tpoints[2], tpoints[0]})) &&
              (sameSide(point, tpoints[2], {tpoints[0], tpoints[1]}));
    return in;
}

bool edgesIntersection(const space::Triangle<2>::Edges &fedges, const space::Triangle<2>::Edges &sedges)
{
    for(size_t i = 0; i < fedges.size(); ++i)
    {
        for(size_t j = 0; j < sedges.size(); ++j)
        {
            if(space::intersection(fedges[i], sedges[j]))
                return true;
        }
    }
    return false;
}

}//namespace


namespace space
{

bool intersection(const Triangle<2> &first, const Triangle<2> &second)
{
    auto fpoints = first.getPoints();
    auto spoints = second.getPoints();
    if(edgesIntersection(first.getEdges(), second.getEdges()))
        return true;

    if(pointInsideTriangle(fpoints[0], second) || pointInsideTriangle(spoints[0], first))
        return true;
    
    return false;
}

}//namespace space

namespace
{

struct DistPoint
{
    space::Vector<3> point;
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

SelectedPoints computeDistances(const space::Triangle<3> &triangle, const space::Triangle<3>::Points& points)
{
    SelectedPoints spoints;
    auto plane = getPlane(triangle);
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

Interval intersectionInterval(SelectedPoints &points, const space::Vector<3> line)
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

size_t mostAreaAxis(const space::Triangle<3> &first, const space::Triangle<3> &second)
{
    size_t axis = 0;
    double maxArea = 0;
    for(size_t i = 0; i < 3; ++i)
    {
        auto area = project(first, i).area();
        if(area > maxArea)
        {
            area = maxArea;
            axis = i;
        }
    }
    return axis;
}


bool coplanarIntersection(const space::Triangle<3> &first, const space::Triangle<3> &second)
{
    auto axis = mostAreaAxis(first, second);

    auto pfirst = project(first, axis);
    auto psecond = project(second, axis);
    
    return intersection(pfirst, psecond);
}


} // namespace



namespace space
{
bool intersection(const Triangle<3> &first, const Triangle<3> &second)
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

    auto fplane = getPlane(first);
    auto splane = getPlane(second);
    auto intersectLine = crossProduct(fplane.getNormal(), splane.getNormal());
    
    auto finterval =  intersectionInterval(fpoints, intersectLine);   
    auto sinterval =  intersectionInterval(spoints, intersectLine);   
    
    return overlap(finterval, sinterval);
}

}// namespace space
