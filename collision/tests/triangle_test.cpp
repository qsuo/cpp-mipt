
#include <gtest/gtest.h>
#include <iostream>

#include "../src/triangle.h"

TEST(Triangle, plane)
{
    space::Vector p1(0, 0, 1);
    space::Vector p2(1, 1, 1);
    space::Vector p3(1, 2, 1);
    space::Triangle triangle(p1, p2, p3);

    auto plane = triangle.getPlane();
    
    space::Vector realNormal(0, 0, 1);
    double realMember = -1.0;

    ASSERT_TRUE(plane.getNormal() == realNormal);
    ASSERT_TRUE(plane.getMember() == realMember);

    auto points = triangle.getPoints();
    ASSERT_TRUE(points[0] == p1);
    ASSERT_TRUE(points[1] == p2);
    ASSERT_TRUE(points[2] == p3);
}

TEST(Triangle, intersection)
{
    //space::triangle t1
}
