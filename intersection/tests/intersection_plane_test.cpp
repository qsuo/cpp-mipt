#include <gtest/gtest.h>

#include "plane.h"
#include "point.h"

#include "intersection.h"

TEST(intersection, plane_line)
{
    {
    space::Plane plane({0, 0, 1}, -1);
    space::Line<3> line({0, 0, 1}, {0, 0, 0});
    auto intpoint = intersection(plane, line);
    space::Point<3> expected = {0, 0, 1};
    
    EXPECT_TRUE(intpoint.point == expected);
    EXPECT_FALSE(intpoint.coplanar);
    EXPECT_TRUE(intpoint.intersect);
    }
    
    {
    space::Plane plane({0, 0, 1}, -1);
    space::Line<3> line({1, 1, 0}, {0, 0, 0});
    auto intpoint = intersection(plane, line);

    EXPECT_TRUE(intpoint.coplanar);
    EXPECT_FALSE(intpoint.intersect);
    }
    
    {
    space::Plane plane({0, 0, 1}, 0);
    space::Line<3> line({1, 1, 0}, {0, 0, 0});
    auto intpoint = intersection(plane, line);

    EXPECT_TRUE(intpoint.coplanar);
    EXPECT_TRUE(intpoint.intersect);
    }

}

TEST(intersection, plane_segment)
{
    {
    space::Plane plane({0, 0, 1}, -1);
    space::Segment<3> segment({0, 0, 1}, {0, 0, 0});
    auto intpoint = intersection(plane, segment);
    space::Point<3> expected = {0, 0, 1};
    
    EXPECT_TRUE(intpoint.point == expected);
    EXPECT_FALSE(intpoint.coplanar);
    EXPECT_TRUE(intpoint.intersect);
    }
    
    {
    space::Plane plane({0, 0, 1}, 1);
    space::Segment<3> segment({0, 0, 1}, {0, 0, 0});
    auto intpoint = intersection(plane, segment);

    EXPECT_FALSE(intpoint.coplanar);
    EXPECT_FALSE(intpoint.intersect);
    }
    
    {
    space::Plane plane({0, 0, 1}, -1);
    space::Segment<3> segment({0, 0, 2}, {0, 0, 0});
    auto intpoint = intersection(plane, segment);

    EXPECT_FALSE(intpoint.coplanar);
    EXPECT_TRUE(intpoint.intersect);
    }

    {
    space::Plane plane({0, 0, 1}, 0);
    space::Segment<3> segment({1, 1, 0}, {0, 0, 0});
    auto intpoint = intersection(plane, segment);

    EXPECT_TRUE(intpoint.coplanar);
    EXPECT_TRUE(intpoint.intersect);
    }

}

