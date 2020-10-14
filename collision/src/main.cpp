
#include "vector.h"
//#include "triangle.h"
//#include "intersection.h"

#include <iostream>

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
    space::Vector<3> v({1, 2, 3});
    space::Vector<3> v1({1, 5, 3});

    std::cout << space::dotProduct(v, v1) << std::endl;
    return 0;
}
