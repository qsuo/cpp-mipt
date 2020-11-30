
#include "triangles_set_intersection.h"

namespace
{

bool operator<=(const space::Point<3> &lhs, const space::Point<3> &rhs)
{
    bool less = (lhs[0] < rhs[0] || space::equal(lhs[0], rhs[0])) &&
                (lhs[1] < rhs[1] || space::equal(lhs[1], rhs[1])) &&
                (lhs[2] < rhs[2] || space::equal(lhs[2], rhs[2]));
    return less;
}

bool operator>=(const space::Point<3> &lhs, const space::Point<3> &rhs)
{
    bool greater =  (lhs[0] > rhs[0] || space::equal(lhs[0], rhs[0])) &&
                    (lhs[1] > rhs[1] || space::equal(lhs[1], rhs[1])) &&
                    (lhs[2] > rhs[2] || space::equal(lhs[2], rhs[2]));
    return greater;
}

bool operator==(const space::Triangle<3> &lhs, const space::Triangle<3> &rhs)
{
    return (lhs.box.min <= rhs.box.max &&
            lhs.box.max >= rhs.box.min);
}

bool operator<(const space::Triangle<3> &lhs, const space::Triangle<3> &rhs)
{
    return ( (lhs.box.min <= rhs.box.max) && !(lhs == rhs) ); 
}


struct ComparatorPtr
{
    bool operator()(const space::Triangle<3> *lhs, const space::Triangle<3> *rhs) const
    {
        return (*lhs < *rhs);
    }
};

}//namespace

namespace space
{

Point<3> inputPoint(std::istream &in)
{
    std::vector<double> coord(3);
    for(size_t i = 0; i < coord.size(); ++i)
        in >> coord[i];
    return Point<3>(coord);
}

Triangle<3>* createTriangle(Point<3> &a, Point<3> &b, Point<3> &c)
{
    return new Triangle<3>(a, b, c);
}

std::vector<Triangle<3>*> inputTriangles(std::istream &in)
{
    size_t n = 0;
    in >> n;
    std::vector<Triangle<3>*> triangles(n);
    for(size_t i = 0; i < n; i++)
    {
        auto a = inputPoint(in);
        auto b = inputPoint(in);
        auto c = inputPoint(in);
        triangles[i] = createTriangle(a, b, c);
    }
    return triangles;
}

void deleteTriangles(std::vector<Triangle<3>*> &triangles)
{
    for(auto triangle : triangles)
        delete triangle;
}

}// namespace
namespace space
{

std::set<size_t> findIntersections_naive(std::vector<Triangle<3>*> triangles)
{
    std::set<size_t> idx;
    auto size = triangles.size();
    for(size_t i = 0; i < size - 1; ++i)
    {
        for(size_t j = i + 1; j < size; ++j)
        {
            if(intersection(*triangles[i], *triangles[j]))
            {
                idx.insert(i);
                idx.insert(j);
            }
        }
    }
    return idx;
}


std::set<size_t> findIntersections(std::vector<Triangle<3>*> triangles)
{
    std::multiset<Triangle<3>*, ComparatorPtr> mset;
    std::set<size_t> idx;
    for(auto triangle : triangles)
        mset.insert(triangle);

    for(size_t i = 0; i < triangles.size(); i++)
    {
        auto localSize = mset.count(triangles[i]);
        auto local = mset.find(triangles[i]);
        
        for(size_t j = 0; j < localSize - 1; j++)
        {
            if(intersection(*(*(local++)), *(*local)))
            {
                idx.insert(i);
                break;
            }
        }
    }
    return idx;
}


void triangleIntersections(std::istream &in, std::ostream &out)
{
    auto triangles = inputTriangles(in);
    
    auto intersect = findIntersections(triangles);
    
    for(auto i : intersect)
        out << i << " ";
    deleteTriangles(triangles);

}


}// namespace space
