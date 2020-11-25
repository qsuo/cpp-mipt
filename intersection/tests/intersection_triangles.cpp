#include <gtest/gtest.h>

#include "triangle.h"
#include "intersection.h"

const space::Triangle<2> deftr2({0, 0}, {4, 0}, {2, 4});

TEST(intersection_triangle, dim2)
{
    space::Triangle<2> t1({0, 3}, {5, 3}, {2, 5});

    space::Triangle<2> t2({0, 5}, {5, 8}, {2, 7});

    space::Triangle<2> t3({2, 4}, {2, 5}, {3, 5});

    space::Triangle<2> t4({1, 1}, {2, 3}, {3, 1});
    
    space::Triangle<2> t5({0, 0}, {4, 0}, {2, 0});

    space::Triangle<2> t6({0, 0}, {5, 0}, {2, 0});


    EXPECT_TRUE(space::intersection(deftr2, deftr2));
    EXPECT_TRUE(space::intersection(t1, deftr2));
    EXPECT_FALSE(space::intersection(t2, deftr2));
    EXPECT_TRUE(space::intersection(t3, deftr2));
    EXPECT_TRUE(space::intersection(t4, deftr2));
    EXPECT_TRUE(space::intersection(t5, t6));
}

const space::Triangle<3> deftr(space::Vector<3>({0, 0, 0}),
                            space::Vector<3>({4, 0, 0}),
                            space::Vector<3>({2, 4, 0}));

TEST(intersection, pos3)
{
    space::Triangle<3> first(space::Vector<3>({0, 0, 0}),
                          space::Vector<3>({1, 0, 0}),
                          space::Vector<3>({0, 1, 0}));

    space::Triangle<3> second(space::Vector<3>({0, 0, 1}),
                           space::Vector<3>({1, 0, 1}),
                           space::Vector<3>({0, 1, 1}));

    space::Triangle<3> third(space::Vector<3>({0, 0, -1}),
                          space::Vector<3>({1, 0, -1}),
                          space::Vector<3>({0, 1, -1}));


    ASSERT_FALSE(space::intersection(deftr, second));
    ASSERT_FALSE(space::intersection(deftr, third));
}

TEST(intersection, pos2neg1)
{
    space::Triangle<3> t1(space::Vector<3>({2, 0, 1}),
                       space::Vector<3>({2, 2, -1}),
                       space::Vector<3>({2, -2, -1}));
    
    space::Triangle<3> t2(space::Vector<3>({2, 0, 1}),
                       space::Vector<3>({2, 2, -1}),
                       space::Vector<3>({2, -2, 1}));

    space::Triangle<3> t3(space::Vector<3>({2, 0, 1}),
                       space::Vector<3>({2, -1e3, -1}),
                       space::Vector<3>({2, -2, 1}));


    space::Triangle<3> t4(space::Vector<3>({2, 0, 1}),
                       space::Vector<3>({10, 1, -1}),
                       space::Vector<3>({10, -1, -1}));
    
    space::Triangle<3> t5(space::Vector<3>({4, 0, 1}),
                       space::Vector<3>({4, 4, -1}),
                       space::Vector<3>({4, -1, -1}));
    
    space::Triangle<3> t6(space::Vector<3>({2, 0, 1}),
                       space::Vector<3>({2, 0, 0}),
                       space::Vector<3>({2, -1, 0}));
    
    space::Triangle<3> t7(space::Vector<3>({6, 1, 1}),
                       space::Vector<3>({5, 1, -1}),
                       space::Vector<3>({7, 1, -1}));

    space::Triangle<3> t8(space::Vector<3>({2, 2, 1}),
                       space::Vector<3>({-1, 2, -1}),
                       space::Vector<3>({5, 2, -1}));



    EXPECT_TRUE(space::intersection(t1, deftr));
    EXPECT_TRUE(space::intersection(t2, deftr));
    EXPECT_FALSE(space::intersection(t3, deftr));
    EXPECT_FALSE(space::intersection(t4, deftr));
    EXPECT_TRUE(space::intersection(t5, deftr));
    EXPECT_TRUE(space::intersection(t6, deftr));
    EXPECT_FALSE(space::intersection(t7, deftr));
    EXPECT_TRUE(space::intersection(t8, deftr));
}

TEST(intersection, zero1pos2)
{
    space::Triangle<3> t1(space::Vector<3>({2, 2, 0}),
                       space::Vector<3>({1, 1, 1}),
                       space::Vector<3>({1, -1, 1}));
    
    space::Triangle<3> t2(space::Vector<3>({2, 0, 0}),
                       space::Vector<3>({1, 1, 1}),
                       space::Vector<3>({1, -1, 1}));
    
    space::Triangle<3> t3(space::Vector<3>({0, 0, 0}),
                       space::Vector<3>({1, 1, 1}),
                       space::Vector<3>({1, -1, 1}));

    space::Triangle<3> t4(space::Vector<3>({-1, -1, 0}),
                       space::Vector<3>({1, 1, 1}),
                       space::Vector<3>({1, -1, 1}));

    EXPECT_TRUE(space::intersection(t1, deftr));
    EXPECT_TRUE(space::intersection(t2, deftr));
    EXPECT_TRUE(space::intersection(t3, deftr));
    EXPECT_FALSE(space::intersection(t4, deftr));
}

TEST(intersection, zero1pos1neg1)
{
    space::Triangle<3> t1(space::Vector<3>({2, 2, 0}),
                       space::Vector<3>({1, 1, 1}),
                       space::Vector<3>({1, 1, -1}));
    EXPECT_TRUE(space::intersection(t1, deftr));

    space::Triangle<3> t2(space::Vector<3>({2, 2, 0}),
                       space::Vector<3>({1, -1, 1}),
                       space::Vector<3>({1, -1, -1}));
    EXPECT_TRUE(space::intersection(t2, deftr));

    space::Triangle<3> t3(space::Vector<3>({0, 1, 0}),
                       space::Vector<3>({4, 1, 1}),
                       space::Vector<3>({4, 1, -1}));
    EXPECT_TRUE(space::intersection(t3, deftr));
}

TEST(intersection, zero2)
{
    space::Triangle<3> t1(space::Vector<3>({1, 1, 1}),
                       space::Vector<3>({2, 2, 0}),
                       space::Vector<3>({1, 1, 0}));
    EXPECT_TRUE(space::intersection(t1, deftr));

    space::Triangle<3> t2(space::Vector<3>({1, 1, 1}),
                       space::Vector<3>({2, 2, 0}),
                       space::Vector<3>({5, 5, 0}));
    EXPECT_TRUE(space::intersection(t2, deftr));

    space::Triangle<3> t3(space::Vector<3>({1, 1, 1}),
                       space::Vector<3>({0, 1, 0}),
                       space::Vector<3>({4, 1, 0}));
    EXPECT_TRUE(space::intersection(t3, deftr));

}

TEST(intersection, coplanar)
{
    space::Triangle<3> t1(space::Vector<3>({0, 3, 0}),
                             space::Vector<3>({5, 3, 0}),
                             space::Vector<3>({2, 5, 0}));

    space::Triangle<3> t2(space::Vector<3>({0, 5, 0}),
                             space::Vector<3>({5, 8, 0}),
                             space::Vector<3>({2, 7, 0}));

    space::Triangle<3> t3(space::Vector<3>({2, 4, 0}),
                             space::Vector<3>({2, 5, 0}),
                             space::Vector<3>({3, 5, 0}));

    space::Triangle<3> t4(space::Vector<3>({1, 1, 0}),
                             space::Vector<3>({2, 3, 0}),
                             space::Vector<3>({3, 1, 0}));


    EXPECT_TRUE(space::intersection(deftr, deftr));
    EXPECT_TRUE(space::intersection(t1, deftr));
    EXPECT_FALSE(space::intersection(t2, deftr));
    EXPECT_TRUE(space::intersection(t3, deftr));
    EXPECT_TRUE(space::intersection(t4, deftr));

    space::Triangle<3> t5(space::Vector<3>({0, 0, 0}),
                             space::Vector<3>({4, 0, 0}),
                             space::Vector<3>({2, 0, 4}));

    space::Triangle<3> t6(space::Vector<3>({0, 0, 3}),
                             space::Vector<3>({5, 0, 3}),
                             space::Vector<3>({2, 0, 5}));

    EXPECT_TRUE(space::intersection(t5, t6));
}

TEST(intersection, decay_dim2)
{
    space::Triangle<2> t2({1, 1}, {1, 1}, {1, 1});
    space::Triangle<2> t3({4, 4}, {4, 4}, {4, 4});

    space::Triangle<2> t4({0, 1}, {4, 1}, {4, 1});
    space::Triangle<2> t5({0, 5}, {4, 5}, {4, 5});

    EXPECT_TRUE(space::intersection(t2, deftr2));
    EXPECT_FALSE(space::intersection(t3, deftr2));
    EXPECT_TRUE(space::intersection(t4, deftr2));
    EXPECT_TRUE(space::intersection(t5, deftr2));
}

TEST(intersection, decay)
{
    space::Triangle<3> t1({1, 1, 1}, {1, 1, 1}, {1, 1, 1});
    space::Triangle<3> t2({1, 1, 0}, {1, 1, 0}, {1, 1, 0});
    space::Triangle<3> t3({4, 4, 0}, {4, 4, 0}, {4, 4, 0});
    
    EXPECT_FALSE(space::intersection(t1, deftr));
    EXPECT_TRUE(space::intersection(t2, deftr));
    EXPECT_FALSE(space::intersection(t3, deftr));

    space::Triangle<3> t4({0, 1, 0}, {4, 1, 0}, {4, 1, 0});
    EXPECT_TRUE(space::intersection(t4, deftr));

    space::Triangle<3> t5({0, 5, 0}, {4, 5, 0}, {4, 5, 0});
    EXPECT_TRUE(space::intersection(t5, deftr));
    
    space::Triangle<3> t6({1, 1, 1}, {1, 1, 1}, {1, 1, -1});
    EXPECT_TRUE(space::intersection(t6, deftr));

    space::Triangle<3> t7({1, 1, 1}, {1, 1, 1}, {1, 1, 0});
    EXPECT_TRUE(space::intersection(t7, deftr));
    
    space::Triangle<3> t8({1, 1, 1}, {1, 1, 1}, {1, 1, 0 + 1e3});
    EXPECT_FALSE(space::intersection(t8, deftr));
    
    space::Triangle<3> t9({1, 1, 1}, {1, 1, 1}, {2, 4 + 1e3, 0});
    EXPECT_FALSE(space::intersection(t9, deftr));
}



