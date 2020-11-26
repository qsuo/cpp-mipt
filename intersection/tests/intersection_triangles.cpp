#include <gtest/gtest.h>

#include "triangle.h"
#include "intersection.h"

const space::Triangle<2> DEFAULT_2DIM({0, 0}, {4, 0}, {2, 4});

TEST(intersection_triangle, dim2)
{
    EXPECT_TRUE(space::intersection(DEFAULT_2DIM, DEFAULT_2DIM));

    space::Triangle<2> t1({0, 3}, {5, 3}, {2, 5});
    EXPECT_TRUE(space::intersection(t1, DEFAULT_2DIM));

    space::Triangle<2> t2({0, 5}, {5, 8}, {2, 7});
    EXPECT_FALSE(space::intersection(t2, DEFAULT_2DIM));

    space::Triangle<2> t3({2, 4}, {2, 5}, {3, 5});
    EXPECT_TRUE(space::intersection(t3, DEFAULT_2DIM));

    space::Triangle<2> t4({1, 1}, {2, 3}, {3, 1});
    EXPECT_TRUE(space::intersection(t4, DEFAULT_2DIM));
    
    space::Triangle<2> t5({0, 0}, {4, 0}, {2, 0});
    space::Triangle<2> t6({0, 0}, {5, 0}, {2, 0});
    EXPECT_TRUE(space::intersection(t5, t6));
}

const space::Triangle<3> DEFAULT({0, 0, 0}, {4, 0, 0},{2, 4, 0});

TEST(intersection, pos3)
{
    space::Triangle<3> t1({0, 0, 1}, {1, 0, 1}, {0, 1, 1});
    ASSERT_FALSE(space::intersection(DEFAULT, t1));
    
    space::Triangle<3> t2({0, 0, -1}, {1, 0, -1}, {0, 1, -1});
    ASSERT_FALSE(space::intersection(DEFAULT, t2));
}

TEST(intersection, pos2neg1)
{
    space::Triangle<3> t1({2, 0, 1}, {2, 2, -1}, {2, -2, -1});
    EXPECT_TRUE(space::intersection(t1, DEFAULT));
    
    space::Triangle<3> t2({2, 0, 1}, {2, 2, -1}, {2, -2, 1});
    EXPECT_TRUE(space::intersection(t2, DEFAULT));

    space::Triangle<3> t3({2, 0, 1}, {2, -1e3, -1}, {2, -2, 1});
    EXPECT_FALSE(space::intersection(t3, DEFAULT));


    space::Triangle<3> t4({2, 0, 1}, {10, 1, -1}, {10, -1, -1});
    EXPECT_FALSE(space::intersection(t4, DEFAULT));
    
    space::Triangle<3> t5({4, 0, 1}, {4, 4, -1}, {4, -1, -1});
    EXPECT_TRUE(space::intersection(t5, DEFAULT));
    
    space::Triangle<3> t6({2, 0, 1}, {2, 0, 0}, {2, -1, 0});
    EXPECT_TRUE(space::intersection(t6, DEFAULT));
    
    space::Triangle<3> t7({6, 1, 1}, {5, 1, -1}, {7, 1, -1});
    EXPECT_FALSE(space::intersection(t7, DEFAULT));

    space::Triangle<3> t8({2, 2, 1}, {-1, 2, -1}, {5, 2, -1});
    EXPECT_TRUE(space::intersection(t8, DEFAULT));
}

TEST(intersection, zero1pos2)
{
    space::Triangle<3> t1({2, 2, 0}, {1, 1, 1}, {1, -1, 1});
    EXPECT_TRUE(space::intersection(t1, DEFAULT));
    
    space::Triangle<3> t2({2, 0, 0}, {1, 1, 1}, {1, -1, 1});
    EXPECT_TRUE(space::intersection(t2, DEFAULT));
    
    space::Triangle<3> t3({0, 0, 0}, {1, 1, 1}, {1, -1, 1});
    EXPECT_TRUE(space::intersection(t3, DEFAULT));

    space::Triangle<3> t4({-1, -1, 0}, {1, 1, 1}, {1, -1, 1});
    EXPECT_FALSE(space::intersection(t4, DEFAULT));
}

TEST(intersection, zero1pos1neg1)
{
    space::Triangle<3> t1({2, 2, 0}, {1, 1, 1}, {1, 1, -1});
    EXPECT_TRUE(space::intersection(t1, DEFAULT));

    space::Triangle<3> t2({2, 2, 0}, {1, -1, 1}, {1, -1, -1});
    EXPECT_TRUE(space::intersection(t2, DEFAULT));

    space::Triangle<3> t3({0, 1, 0}, {4, 1, 1}, {4, 1, -1});
    EXPECT_TRUE(space::intersection(t3, DEFAULT));
}

TEST(intersection, zero2)
{
    space::Triangle<3> t1({1, 1, 1}, {2, 2, 0}, {1, 1, 0});
    EXPECT_TRUE(space::intersection(t1, DEFAULT));

    space::Triangle<3> t2({1, 1, 1}, {2, 2, 0}, {5, 5, 0});
    EXPECT_TRUE(space::intersection(t2, DEFAULT));

    space::Triangle<3> t3({1, 1, 1}, {0, 1, 0}, {4, 1, 0});
    EXPECT_TRUE(space::intersection(t3, DEFAULT));

}

TEST(intersection, coplanar)
{
    EXPECT_TRUE(space::intersection(DEFAULT, DEFAULT));
    space::Triangle<3> t1({0, 3, 0}, {5, 3, 0}, {2, 5, 0});
    EXPECT_TRUE(space::intersection(t1, DEFAULT));

    space::Triangle<3> t2({0, 5, 0}, {5, 8, 0}, {2, 7, 0});
    EXPECT_FALSE(space::intersection(t2, DEFAULT));

    space::Triangle<3> t3({2, 4, 0}, {2, 5, 0}, {3, 5< 0});
    EXPECT_TRUE(space::intersection(t3, DEFAULT));

    space::Triangle<3> t4({1, 1, 0}, {2, 3, 0}, {3, 1, 0});
    EXPECT_TRUE(space::intersection(t4, DEFAULT));

    space::Triangle<3> t5({0, 0, 0}, {4, 0, 0}, {2, 0, 4});
    space::Triangle<3> t6({0, 0, 3}, {5, 0, 3}, {2, 0, 5});
    EXPECT_TRUE(space::intersection(t5, t6));
}

TEST(intersection, decay_dim2)
{
    space::Triangle<2> t2({1, 1}, {1, 1}, {1, 1});
    EXPECT_TRUE(space::intersection(t2, DEFAULT_2DIM));
    
    space::Triangle<2> t3({4, 4}, {4, 4}, {4, 4});
    EXPECT_FALSE(space::intersection(t3, DEFAULT_2DIM));
    
    space::Triangle<2> t4({0, 1}, {4, 1}, {4, 1});
    EXPECT_TRUE(space::intersection(t4, DEFAULT_2DIM));
    
    space::Triangle<2> t5({0, 5}, {4, 5}, {4, 5});
    EXPECT_TRUE(space::intersection(t5, DEFAULT_2DIM));
}

TEST(intersection, decay)
{
    space::Triangle<3> t1({1, 1, 1}, {1, 1, 1}, {1, 1, 1});
    EXPECT_FALSE(space::intersection(t1, DEFAULT));
    
    space::Triangle<3> t2({1, 1, 0}, {1, 1, 0}, {1, 1, 0});
    EXPECT_TRUE(space::intersection(t2, DEFAULT));
    
    space::Triangle<3> t3({4, 4, 0}, {4, 4, 0}, {4, 4, 0});
    EXPECT_FALSE(space::intersection(t3, DEFAULT));

    space::Triangle<3> t4({0, 1, 0}, {4, 1, 0}, {4, 1, 0});
    EXPECT_TRUE(space::intersection(t4, DEFAULT));

    space::Triangle<3> t5({0, 5, 0}, {4, 5, 0}, {4, 5, 0});
    EXPECT_TRUE(space::intersection(t5, DEFAULT));
    
    space::Triangle<3> t6({1, 1, 1}, {1, 1, 1}, {1, 1, -1});
    EXPECT_TRUE(space::intersection(t6, DEFAULT));

    space::Triangle<3> t7({1, 1, 1}, {1, 1, 1}, {1, 1, 0});
    EXPECT_TRUE(space::intersection(t7, DEFAULT));
    
    space::Triangle<3> t8({1, 1, 1}, {1, 1, 1}, {1, 1, 0 + 1e3});
    EXPECT_FALSE(space::intersection(t8, DEFAULT));
    
    space::Triangle<3> t9({1, 1, 1}, {1, 1, 1}, {2, 4 + 1e3, 0});
    EXPECT_FALSE(space::intersection(t9, DEFAULT));
}



