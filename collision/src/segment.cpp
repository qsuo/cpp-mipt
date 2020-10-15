
#include "segment.h"
#include "vector.h"

#include <cmath>

namespace
{

bool collinear(const space::dim2::Segment &s1, const space::dim2::Segment &s2)
{
    auto prod = std::abs(space::dim2::pseudoProduct(s1.vector, s2.vector));
    auto expr = prod / (s1.vector.length() * s2.vector.length());
    return space::equal(expr, 0); 
}

bool onSameLine(const space::dim2::Segment &s1, const space::dim2::Segment &s2)
{
    auto r = s2.point1 - s1.point2;
    auto prod = std::abs(space::dim2::pseudoProduct(s2.vector, r));
    auto expr = prod / (s2.vector.length() * r.length());
    return space::equal(expr, 0);
}


bool overlap(const space::dim2::Segment &s1, const space::dim2::Segment &s2)
{
    bool result = (space::dotProduct(s1.point1 - s2.point2, s1.point1 - s2.point2) > 0) &&
                  (space::dotProduct(s1.point2 - s2.point2, s1.point2 - s2.point2) > 0) &&
                  (space::dotProduct(s2.point1 - s1.point1, s2.point1 - s1.point2) > 0) &&
                  (space::dotProduct(s2.point2 - s1.point1, s2.point2 - s1.point2) > 0);
    return !result;
}

} // namespace

namespace space
{
namespace dim2
{

bool intersection(const Segment &first, const Segment &second)
{
    
    if(collinear(first, second) && !onSameLine(first, second))
        return false;
    
    if(collinear(first, second) && onSameLine(first, second))
        return overlap(first, second);

    auto &r1 = first.vector;
    auto &r2 = second.vector;

    auto prod1 = pseudoProduct(second.point2, second.point1);
    auto prod2 = pseudoProduct(first.point2, first.point1);
    auto gprod = pseudoProduct(r2, r1);
    auto r = (r1 * (prod1 / gprod) - r2 * (prod2 / gprod));

    auto t1 = dotProduct(r - first.point1, r - first.point2); 
    auto t2 = dotProduct(r - second.point1, r - second.point2); 

    bool res1 = (t1 < 0) || equal(t1, 0); 
    bool res2 = (t2 < 0) || equal(t2, 0);
    return (res1 && res2);

}

}// namespace dim2
}// namespace space
