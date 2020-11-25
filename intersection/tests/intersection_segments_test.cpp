#include <gtest/gtest.h>

#include "point.h"
#include "segment.h"
#include "intersection.h"

TEST(intersection_segment, dim2)
{
    {
    space::Segment<2> seg1({0, 0}, {1, 1});    
    space::Segment<2> seg2({0, 0}, {1, 1}); 
    EXPECT_TRUE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({0, 0}, {1, 1});    
    space::Segment<2> seg2({1, 1}, {2, 2}); 
    EXPECT_TRUE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({0, 0}, {1, 1});    
    space::Segment<2> seg2({1 + 1e-3, 1 + 1e-3}, {2, 2}); 
    EXPECT_FALSE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({0, 0}, {1, 1});    
    space::Segment<2> seg2({1, 0}, {2, 1}); 
    EXPECT_FALSE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({0, 0}, {1, 1});    
    space::Segment<2> seg2({1, 0}, {0, 1}); 
    EXPECT_TRUE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({0, 0}, {1, 1});    
    space::Segment<2> seg2({2, 0}, {0, 2}); 
    EXPECT_TRUE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({0, 0}, {1, 1});    
    space::Segment<2> seg2({2 + 1e-3, 0}, {0, 2}); 
    EXPECT_FALSE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({0, 0}, {0, 0});    
    space::Segment<2> seg2({0, 0}, {2, 2}); 
    EXPECT_TRUE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({1, 1}, {-1, -1});    
    space::Segment<2> seg2({0, 0}, {2, 2}); 
    EXPECT_TRUE(space::intersection(seg1, seg2));
    }
    
    {
    space::Segment<2> seg1({0, 0}, {0, 0});    
    space::Segment<2> seg2({0, 0}, {0, 0}); 
    EXPECT_TRUE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({0, 0}, {2, 2});    
    space::Segment<2> seg2({1, 1}, {1, 1}); 
    EXPECT_TRUE(space::intersection(seg1, seg2));
    }
    {
    space::Segment<2> seg1({0, 0}, {0, 0});    
    space::Segment<2> seg2({1, 1}, {1, 1}); 
    EXPECT_FALSE(space::intersection(seg1, seg2));
    }
}


