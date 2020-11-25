
#include <gtest/gtest.h>

#include "plane.h"
#include "point.h"

TEST(plane, belong)
{
    {
    space::Vector<3> normal = {0, 0 , 1};
    space::Plane plane(normal, -1);
    space::Point<3> point = {5, 5, 1};
    ASSERT_TRUE(plane.belong(point));

    ASSERT_TRUE(plane.normal() == normal);
    }

    {
    space::Plane plane = { {1, 1, 1}, 0 };
    space::Vector<3> point1 = {1, 1, -2};
    space::Vector<3> point2 = {5, 5, 1};
    
    ASSERT_TRUE(plane.belong(point1));
    ASSERT_FALSE(plane.belong(point2));
    }
}



