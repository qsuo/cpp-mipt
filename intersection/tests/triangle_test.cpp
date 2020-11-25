#include <gtest/gtest.h>
#include <iostream>

#include "vector.h"
#include "point.h"
#include "triangle.h"

TEST(Triangle, init)
{
    space::Point<3> a = {0, 0, 1};
    space::Point<3> b = {1, 1, 1};
    space::Point<3> c = {1, 2, 1};
    space::Triangle<3> triangle(a, b, c);
    
    auto points = triangle.points();
    ASSERT_TRUE(points[0] == a);
    ASSERT_TRUE(points[1] == b);
    ASSERT_TRUE(points[2] == c);

}

TEST(Triangle, plane)
{
    space::Point<3> a = {0, 0, 1};
    space::Point<3> b = {1, 1, 1};
    space::Point<3> c = {1, 2, 1};
    space::Triangle<3> triangle(a, b, c);

    auto plane = triangle.plane();
    
    space::Vector<3> realNormal = {0, 0, 1};
    double realM = -1.0;

    ASSERT_TRUE(plane.normal() == realNormal);
    ASSERT_TRUE(plane.m() == realM);

}

TEST(Triangle, area)
{
    space::Triangle<3> triangle({0, 0, 0},
                                {4, 0, 0},
                                {2, 4, 0});
    double realArea = 4 * 4 / 2;
    ASSERT_DOUBLE_EQ(triangle.area(), realArea);
}

