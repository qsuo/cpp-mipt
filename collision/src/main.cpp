
#include "vector.h"
#include "triangle.h"


int main()
{
    space::Triangle triangle(space::Vector(0, 1, 2),
                             space::Vector(1, 2, 3),
                             space::Vector(2, 3, 4));
    
    space::Triangle t(space::Vector(0, 1, 2),
                      space::Vector(1, 2, 3),
                      space::Vector(2, 3, 4));

    space::Triangle::intersection(triangle, t);


    return 0;
}
