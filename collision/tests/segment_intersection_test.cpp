
#include <gtest/gtest.h>

#include "segment.h"
#include "intersection.h"

space::Segment<2> defs(space::Vector<2>({2, 1}),
                          space::Vector<2>({0, 1}));

TEST(SegmentIntersection, notCollinear)
{
    space::Segment<2> s1(space::Vector<2>({1, 2}),
                         space::Vector<2>({1, 0}));
    EXPECT_TRUE(space::intersection(s1, defs));

    space::Segment<2> s2(space::Vector<2>({2, 2}),
                         space::Vector<2>({2, 0}));
    EXPECT_TRUE(space::intersection(s2, defs));

    space::Segment<2> s3(space::Vector<2>({3, 2}),
                         space::Vector<2>({3, 0}));
    EXPECT_FALSE(space::intersection(s3, defs));   
}

TEST(SegmentIntersection, collinearNotLine)
{
    space::Segment<2> s(space::Vector<2>({2, 0}),
                        space::Vector<2>({0, 0}));

    EXPECT_FALSE(space::intersection(s, defs));
}

TEST(SegmentIntersection, collinearLineNotOverlap)
{
    space::Segment<2> s(space::Vector<2>({3, 1}),
                        space::Vector<2>({5, 1}));

    EXPECT_FALSE(space::intersection(s, defs));
}

TEST(SegmentIntersection, collinearLineOverlap)
{
    space::Segment<2> s(space::Vector<2>({2, 1}),
                        space::Vector<2>({3, 1}));

    EXPECT_TRUE(space::intersection(s, defs));
}
