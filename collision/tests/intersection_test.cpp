
#include <gtest/gtest.h>


#include "../src/intersection.h"
#include "../src/triangle.h"

const space::dim3::Triangle deftr(space::dim3::Vector({0, 0, 0}),
                            space::dim3::Vector({4, 0, 0}),
                            space::dim3::Vector({2, 4, 0}));

TEST(Intersection, pos3)
{
    space::dim3::Triangle first(space::dim3::Vector({0, 0, 0}),
                          space::dim3::Vector({1, 0, 0}),
                          space::dim3::Vector({0, 1, 0}));

    space::dim3::Triangle second(space::dim3::Vector({0, 0, 1}),
                           space::dim3::Vector({1, 0, 1}),
                           space::dim3::Vector({0, 1, 1}));

    space::dim3::Triangle third(space::dim3::Vector({0, 0, -1}),
                          space::dim3::Vector({1, 0, -1}),
                          space::dim3::Vector({0, 1, -1}));


    ASSERT_FALSE(intersection(deftr, second));
    ASSERT_FALSE(intersection(deftr, third));
}

TEST(Intersection, pos2neg1)
{
    space::dim3::Triangle t1(space::dim3::Vector({2, 0, 1}),
                       space::dim3::Vector({2, 2, -1}),
                       space::dim3::Vector({2, -2, -1}));
    
    space::dim3::Triangle t2(space::dim3::Vector({2, 0, 1}),
                       space::dim3::Vector({2, 2, -1}),
                       space::dim3::Vector({2, -2, 1}));

    space::dim3::Triangle t3(space::dim3::Vector({2, 0, 1}),
                       space::dim3::Vector({2, -1e3, -1}),
                       space::dim3::Vector({2, -2, 1}));


    space::dim3::Triangle t4(space::dim3::Vector({2, 0, 1}),
                       space::dim3::Vector({10, 1, -1}),
                       space::dim3::Vector({10, -1, -1}));
    
    space::dim3::Triangle t5(space::dim3::Vector({4, 0, 1}),
                       space::dim3::Vector({4, 4, -1}),
                       space::dim3::Vector({4, -1, -1}));
    
    space::dim3::Triangle t6(space::dim3::Vector({2, 0, 1}),
                       space::dim3::Vector({2, 0, 0}),
                       space::dim3::Vector({2, -1, 0}));
    
    space::dim3::Triangle t7(space::dim3::Vector({6, 1, 1}),
                       space::dim3::Vector({5, 1, -1}),
                       space::dim3::Vector({7, 1, -1}));

    space::dim3::Triangle t8(space::dim3::Vector({2, 2, 1}),
                       space::dim3::Vector({-1, 2, -1}),
                       space::dim3::Vector({5, 2, -1}));



    EXPECT_TRUE(intersection(t1, deftr));
    EXPECT_TRUE(intersection(t2, deftr));
    EXPECT_FALSE(intersection(t3, deftr));
    EXPECT_FALSE(intersection(t4, deftr));
    EXPECT_TRUE(intersection(t5, deftr));
    EXPECT_TRUE(intersection(t6, deftr));
    EXPECT_FALSE(intersection(t7, deftr));
    EXPECT_TRUE(intersection(t8, deftr));
}


TEST(Intersection, zero1pos2)
{
    space::dim3::Triangle t1(space::dim3::Vector({2, 2, 0}),
                       space::dim3::Vector({1, 1, 1}),
                       space::dim3::Vector({1, -1, 1}));
    
    space::dim3::Triangle t2(space::dim3::Vector({2, 0, 0}),
                       space::dim3::Vector({1, 1, 1}),
                       space::dim3::Vector({1, -1, 1}));
    
    space::dim3::Triangle t3(space::dim3::Vector({0, 0, 0}),
                       space::dim3::Vector({1, 1, 1}),
                       space::dim3::Vector({1, -1, 1}));

    space::dim3::Triangle t4(space::dim3::Vector({-1, -1, 0}),
                       space::dim3::Vector({1, 1, 1}),
                       space::dim3::Vector({1, -1, 1}));

    EXPECT_TRUE(intersection(t1, deftr));
    EXPECT_TRUE(intersection(t2, deftr));
    EXPECT_TRUE(intersection(t3, deftr));
    EXPECT_FALSE(intersection(t4, deftr));
}

TEST(Intersection, zero1pos1neg1)
{
    space::dim3::Triangle t1(space::dim3::Vector({2, 2, 0}),
                       space::dim3::Vector({1, 1, 1}),
                       space::dim3::Vector({1, 1, -1}));
    EXPECT_TRUE(intersection(t1, deftr));

    space::dim3::Triangle t2(space::dim3::Vector({2, 2, 0}),
                       space::dim3::Vector({1, -1, 1}),
                       space::dim3::Vector({1, -1, -1}));
    EXPECT_TRUE(intersection(t2, deftr));

    space::dim3::Triangle t3(space::dim3::Vector({0, 1, 0}),
                       space::dim3::Vector({4, 1, 1}),
                       space::dim3::Vector({4, 1, -1}));
    EXPECT_TRUE(intersection(t3, deftr));
}

TEST(Intersection, zero2)
{
    space::dim3::Triangle t1(space::dim3::Vector({1, 1, 1}),
                       space::dim3::Vector({2, 2, 0}),
                       space::dim3::Vector({1, 1, 0}));
    EXPECT_TRUE(intersection(t1, deftr));

    space::dim3::Triangle t2(space::dim3::Vector({1, 1, 1}),
                       space::dim3::Vector({2, 2, 0}),
                       space::dim3::Vector({5, 5, 0}));
    EXPECT_TRUE(intersection(t2, deftr));

    space::dim3::Triangle t3(space::dim3::Vector({1, 1, 1}),
                       space::dim3::Vector({0, 1, 0}),
                       space::dim3::Vector({4, 1, 0}));
    EXPECT_TRUE(intersection(t3, deftr));

}

TEST(Intersection, coplanar)
{
    space::dim3::Triangle t1(space::dim3::Vector({0, 3, 0}),
                             space::dim3::Vector({5, 3, 0}),
                             space::dim3::Vector({2, 5, 0}));

    space::dim3::Triangle t2(space::dim3::Vector({0, 5, 0}),
                             space::dim3::Vector({5, 8, 0}),
                             space::dim3::Vector({2, 7, 0}));

    space::dim3::Triangle t3(space::dim3::Vector({2, 4, 0}),
                             space::dim3::Vector({2, 5, 0}),
                             space::dim3::Vector({3, 5, 0}));

    space::dim3::Triangle t4(space::dim3::Vector({1, 1, 0}),
                             space::dim3::Vector({2, 3, 0}),
                             space::dim3::Vector({3, 1, 0}));


    EXPECT_TRUE(intersection(deftr, deftr));
    EXPECT_TRUE(intersection(t1, deftr));
    EXPECT_FALSE(intersection(t2, deftr));
    EXPECT_TRUE(intersection(t3, deftr));
    EXPECT_TRUE(intersection(t4, deftr));

    space::dim3::Triangle t5(space::dim3::Vector({0, 0, 0}),
                             space::dim3::Vector({4, 0, 0}),
                             space::dim3::Vector({2, 0, 4}));

    space::dim3::Triangle t6(space::dim3::Vector({0, 0, 3}),
                             space::dim3::Vector({5, 0, 3}),
                             space::dim3::Vector({2, 0, 5}));

    EXPECT_TRUE(intersection(t5, t6));
}

