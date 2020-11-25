#include <gtest/gtest.h>

#include "plane.h"
#include "segment.h"
#include "point.h"

TEST(segment, belong_3dim)
{
    space::Point<3> a = {0, 0, 0};
    space::Point<3> b = {1, 1, 1};

    space::Segment<3> segment(a, b);
    EXPECT_TRUE(segment.belong(a));
    EXPECT_TRUE(segment.belong(b));

    space::Point<3> p1 = {1, 1, 1 + 1e-5};
    space::Point<3> p2 = {0, 1, 1};
    space::Point<3> p3 = {0.5, 0.5, 0.5};
    EXPECT_FALSE(segment.belong(p1));
    EXPECT_FALSE(segment.belong(p2));
    EXPECT_TRUE(segment.belong(p3));
}

TEST(segment, belong_2dim)
{
    space::Point<2> a = {0, 0};
    space::Point<2> b = {1, 1};

    space::Segment<2> segment(a, b);
    EXPECT_TRUE(segment.belong(a));
    EXPECT_TRUE(segment.belong(b));

    space::Point<2> p1 = {1, 1 + 1e-5};
    space::Point<2> p2 = {0, 1};
    space::Point<2> p3 = {0.5, 0.5, 0.5};
    EXPECT_FALSE(segment.belong(p1));
    EXPECT_FALSE(segment.belong(p2));
    EXPECT_TRUE(segment.belong(p3));
}

