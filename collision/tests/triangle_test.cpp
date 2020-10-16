
#include <gtest/gtest.h>
#include <iostream>

#include "vector.h"
#include "triangle.h"

TEST(Triangle, plane)
{
    space::Vector<3> p1({0, 0, 1});
    space::Vector<3> p2({1, 1, 1});
    space::Vector<3> p3({1, 2, 1});
    space::Triangle<3> triangle(p1, p2, p3);

    auto plane = getPlane(triangle);
    
    space::Vector<3> realNormal({0, 0, 1});
    double realMember = -1.0;

    ASSERT_TRUE(plane.getNormal() == realNormal);
    ASSERT_TRUE(plane.getMember() == realMember);

    auto points = triangle.getPoints();
    ASSERT_TRUE(points[0] == p1);
    ASSERT_TRUE(points[1] == p2);
    ASSERT_TRUE(points[2] == p3);
}

TEST(Triangle, area)
{
    space::Triangle<3> triangle(space::Vector<3>({0, 0, 0}),
                                space::Vector<3>({4, 0, 0}),
                                space::Vector<3>({2, 4, 0}));
    double realArea = 4 * 4 / 2;
    ASSERT_DOUBLE_EQ(triangle.area(), realArea);
}

TEST(Triangle, projection)
{
    space::Triangle<3> triangle(space::Vector<3>({1, 2, 3}),
                                space::Vector<3>({4, 5, 6}),
                                space::Vector<3>({7, 8, 9}));

}
