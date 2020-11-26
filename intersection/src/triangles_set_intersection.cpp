
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

}// namespace space
