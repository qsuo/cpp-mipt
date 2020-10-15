
#include "segment.h"

namespace space
{
namespace dim2
{

bool intersection(Segment first, Segment second)
{
    auto r1 = first.point2 - first.point1;
    auto r2 = second.point2 - second.point1;

    auto cross1 = pseudoProduct(second.point2, second.point1);
    auto cross2 = pseudoProduct(first.point2, first.point1);
    auto gcross = pseudoProduct(r2, r1);
    auto r = (r1 * (cross1 / gcross) - r2 * (cross2 / gcross));
    
    r.dump();   

    auto t1 = dotProduct(r - first.point1, r - first.point2); 
    auto t2 = dotProduct(r - second.point1, r - second.point2); 

    bool res1 = (t1 < 0) || equal(t1, 0); 
    bool res2 = (t2 < 0) || equal(t2, 0);
    return (res1 && res2);

}

}// namespace dim2
}// namespace space
