
#include "vector.h"
#include "triangle.h"
#include "intersection.h"

int main()
{
    /*
    space::Triangle triangle(space::Vector(0, 1, 2),
                             space::Vector(1, 2, 3),
                             space::Vector(2, 3, 4));
    
    space::Triangle t(space::Vector(5, 6, 7),
                      space::Vector(-1, -1, -1),
                      space::Vector(0, 3, 4));
    */
    const space::Triangle first(space::Vector(0, 0, 0),
                            space::Vector(4, 0, 0),
                            space::Vector(2, 4, 0));
    
    space::Triangle second(space::Vector(2, 0, 1.001),
                       space::Vector(6, 1, -1),
                       space::Vector(6, -1, -1));

   
    space::intersection(second, first);

    return 0;
}
