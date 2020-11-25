#include <gtest/gtest.h>

#include "plane.h"
#include "line.h"
#include "point.h"

TEST(line, belong_3dim)
{
    space::Point<3> initial = {0, 0, 0};
    space::Vector<3> direction = {1, 1, 1};
    space::Line<3> line(direction, initial);

    space::Point<3> point1 = {5, 5, 5};
    space::Point<3> point2 = {5, 5, 6};
    EXPECT_TRUE(line.belong(point1));
    EXPECT_FALSE(line.belong(point2));
}


TEST(line, belong_2dim)
{
    space::Point<2> initial = {0, 0};
    space::Vector<2> direction = {1, 1};
    space::Line<2> line(direction, initial);

    space::Point<2> point1 = {5, 5};
    space::Point<2> point2 = {5, 6};
    EXPECT_TRUE(line.belong(point1));
    EXPECT_FALSE(line.belong(point2));
}


