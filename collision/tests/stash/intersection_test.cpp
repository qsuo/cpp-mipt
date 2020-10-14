
#include <gtest/gtest.h>


#include "../src/intersection.h"
#include "../src/triangle.h"

const space::Triangle deftr(space::Vector(0, 0, 0),
                            space::Vector(4, 0, 0),
                            space::Vector(2, 4, 0));

/*----------------------------------------------------*/
/*
 * Three points on the one side from triangle 
*/
TEST(Intersection, pos3)
{
    space::Triangle first(space::Vector(0, 0, 0),
                          space::Vector(1, 0, 0),
                          space::Vector(0, 1, 0));

    space::Triangle second(space::Vector(0, 0, 1),
                           space::Vector(1, 0, 1),
                           space::Vector(0, 1, 1));

    space::Triangle third(space::Vector(0, 0, -1),
                          space::Vector(1, 0, -1),
                          space::Vector(0, 1, -1));


    ASSERT_FALSE(intersection(deftr, second));
    ASSERT_FALSE(intersection(deftr, third));
}

/*----------------------------------------------------*/
/*
 * Two points on the one side from, one point on the another
*/
TEST(Intersection, pos2neg1)
{
    space::Triangle t1(space::Vector(2, 0, 1),
                       space::Vector(2, 2, -1),
                       space::Vector(2, -2, -1));
    
    space::Triangle t2(space::Vector(2, 0, 1),
                       space::Vector(2, 2, -1),
                       space::Vector(2, -2, 1));

    space::Triangle t3(space::Vector(2, 0, 1),
                       space::Vector(2, -1e3, -1),
                       space::Vector(2, -2, 1));


    space::Triangle t4(space::Vector(2, 0, 1),
                       space::Vector(10, 1, -1),
                       space::Vector(10, -1, -1));
    
    space::Triangle t5(space::Vector(4, 0, 1),
                       space::Vector(4, 4, -1),
                       space::Vector(4, -1, -1));
    
    space::Triangle t6(space::Vector(2, 0, 1),
                       space::Vector(2, 0, 0),
                       space::Vector(2, -1, 0));
    
    space::Triangle t7(space::Vector(6, 1, 1),
                       space::Vector(5, 1, -1),
                       space::Vector(7, 1, -1));

    space::Triangle t8(space::Vector(2, 2, 1),
                       space::Vector(-1, 2, -1),
                       space::Vector(5, 2, -1));



    EXPECT_TRUE(space::intersection(t1, deftr));
    EXPECT_TRUE(space::intersection(t2, deftr));
    EXPECT_FALSE(space::intersection(t3, deftr));
    EXPECT_FALSE(space::intersection(t4, deftr));
    EXPECT_TRUE(space::intersection(t5, deftr));
    EXPECT_TRUE(space::intersection(t6, deftr));
    EXPECT_FALSE(space::intersection(t7, deftr));
    EXPECT_TRUE(space::intersection(t8, deftr));
}

/*----------------------------------------------------*/

TEST(Intersection, zero1pos2)
{
    space::Triangle t1(space::Vector(2, 2, 0),
                       space::Vector(1, 1, 1),
                       space::Vector(1, -1, 1));
    
    space::Triangle t2(space::Vector(2, 0, 0),
                       space::Vector(1, 1, 1),
                       space::Vector(1, -1, 1));
    
    space::Triangle t3(space::Vector(0, 0, 0),
                       space::Vector(1, 1, 1),
                       space::Vector(1, -1, 1));

    space::Triangle t4(space::Vector(-1, -1, 0),
                       space::Vector(1, 1, 1),
                       space::Vector(1, -1, 1));

    EXPECT_TRUE(intersection(t1, deftr));
    EXPECT_TRUE(intersection(t2, deftr));
    EXPECT_TRUE(intersection(t3, deftr));
    EXPECT_FALSE(intersection(t4, deftr));
}

TEST(Intersection, zero1pos1neg1)
{
    space::Triangle t1(space::Vector(2, 2, 0),
                       space::Vector(1, 1, 1),
                       space::Vector(1, 1, -1));
    EXPECT_TRUE(intersection(t1, deftr));

    space::Triangle t2(space::Vector(2, 2, 0),
                       space::Vector(1, -1, 1),
                       space::Vector(1, -1, -1));
    EXPECT_TRUE(intersection(t2, deftr));

    space::Triangle t3(space::Vector(0, 1, 0),
                       space::Vector(4, 1, 1),
                       space::Vector(4, 1, -1));
    EXPECT_TRUE(intersection(t3, deftr));
}

TEST(Intersection, zero2)
{
    space::Triangle t1(space::Vector(1, 1, 1),
                       space::Vector(2, 2, 0),
                       space::Vector(1, 1, 0));
    EXPECT_TRUE(intersection(t1, deftr));

    space::Triangle t2(space::Vector(1, 1, 1),
                       space::Vector(2, 2, 0),
                       space::Vector(5, 5, 0));
    EXPECT_TRUE(intersection(t2, deftr));

    space::Triangle t3(space::Vector(1, 1, 1),
                       space::Vector(0, 1, 0),
                       space::Vector(4, 1, 0));
    EXPECT_TRUE(intersection(t3, deftr));

}


TEST(Intersection, coplanar)
{

}

