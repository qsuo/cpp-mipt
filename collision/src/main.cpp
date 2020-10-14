
#include "vector.h"
#include "triangle.h"
#include "intersection.h"

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
    
    space::Vector f1(0, 1, 0);
    space::Vector f2(2, 1, 0);
    space::Vector s1(0, 1, 0);
    space::Vector s2(2, 1, 0);
    

    space::Vector norm(0, 0, 1);
    bool a = space::line::intersection({f2, f1}, {s1, s2}, norm); 
    std::cout << a << std::endl;

    return 0;
}
