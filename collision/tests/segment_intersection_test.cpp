
#include <gtest/gtest.h>

#include "../src/segment.h"

space::dim2::Segment defs(space::dim2::Vector({2, 1}),
                          space::dim2::Vector({0, 1}));

TEST(SegmentIntersection, notCollinear)
{
    space::dim2::Segment s1(space::dim2::Vector({1, 2}),
                            space::dim2::Vector({1, 0}));
    EXPECT_TRUE(space::dim2::intersection(s1, defs));

    space::dim2::Segment s2(space::dim2::Vector({2, 2}),
                            space::dim2::Vector({2, 0}));
    EXPECT_TRUE(space::dim2::intersection(s2, defs));

    space::dim2::Segment s3(space::dim2::Vector({3, 2}),
                            space::dim2::Vector({3, 0}));
    EXPECT_FALSE(space::dim2::intersection(s3, defs));   
}

TEST(SegmentIntersection, collinearNotLine)
{
    space::dim2::Segment s(space::dim2::Vector({2, 0}),
                           space::dim2::Vector({0, 0}));

    EXPECT_FALSE(space::dim2::intersection(s, defs));
}

TEST(SegmentIntersection, collinearLineNotOverlap)
{
    space::dim2::Segment s(space::dim2::Vector({3, 1}),
                           space::dim2::Vector({5, 1}));

    EXPECT_FALSE(space::dim2::intersection(s, defs));
}

TEST(SegmentIntersection, collinearLineOverlap)
{
    space::dim2::Segment s(space::dim2::Vector({2, 1}),
                           space::dim2::Vector({3, 1}));

    EXPECT_TRUE(space::dim2::intersection(s, defs));
}
