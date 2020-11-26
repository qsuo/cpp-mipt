
#include "triangles_set_intersection.h"

#include <vector>
#include <iostream>
#include <array>
#include <set>

using Triangle  = space::Triangle<3>;
using Vector    = space::Vector<3>;
using Point     = space::Point<3>;

Point inputPoint()
{
    std::vector<double> coord(3);
    for(size_t i = 0; i < coord.size(); ++i)
        std::cin >> coord[i];
    return Vector(coord);
}

Triangle* createTriangle(Vector &a, Vector &b, Vector &c)
{
    return new Triangle(a, b, c);
}

std::vector<Triangle*> inputTriangles(size_t n = 1)
{
    std::vector<Triangle*> triangles(n);
    for(size_t i = 0; i < n; i++)
    {
        auto a = inputPoint();
        auto b = inputPoint();
        auto c = inputPoint();
        triangles[i] = createTriangle(a, b, c);
    }
    return triangles;
}

void deleteTriangles(std::vector<Triangle*> &triangles)
{
    for(auto triangle : triangles)
        delete triangle;
}

int main()
{
    size_t n = 0;
    std::cin >> n;
    auto triangles = inputTriangles(n);
    
    auto intersect = space::findIntersections(triangles);
    
    for(auto i : intersect)
        std::cout << i << " ";
    std::cout << std::endl;

    deleteTriangles(triangles);
    return 0;
}


