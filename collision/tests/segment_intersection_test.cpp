
#include <gtest/gtest.h>

#include "../src/segment.h"

TEST(segment, intersection)
{
    space::dim2::Segment s1(space::dim2::Vector({2, 1}),
                         space::dim2::Vector({0, 1}));

    space::dim2::Segment s2(space::dim2::Vector({1, 2}),
                         space::dim2::Vector({1, 0}));

    EXPECT_TRUE(space::dim2::intersection(s2, s1));
}
