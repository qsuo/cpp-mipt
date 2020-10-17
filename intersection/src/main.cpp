
#include "triangle.h"
#include "intersection.h"

#include <vector>
#include <iostream>
#include <array>
#include <set>

using Triangle = space::Triangle<3>;
using Vector = space::Vector<3>;

Vector inputPoint()
{
    std::array<double, 3> coord;
    for(size_t i = 0; i < coord.size(); ++i)
        std::cin >> coord[i];
    return Vector(coord);
}

Triangle* createTriangle(Vector a, Vector b, Vector c)
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

std::set<size_t> findIntersections(std::vector<Triangle*> triangles)
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

int main()
{
    size_t n = 0;
    std::cin >> n;
    auto triangles = inputTriangles(n);

    auto intersect = findIntersections(triangles);
    for(auto i : intersect)
        std::cout << i << " ";
    std::cout << std::endl;

    deleteTriangles(triangles);
    return 0;
}




