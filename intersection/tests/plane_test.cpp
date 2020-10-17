
#include <gtest/gtest.h>

#include "plane.h"

TEST(plane, belong)
{
    space::Plane plane1(space::Vector<3>({0, 0, 1}), -1);
    space::Vector<3> v1({5, 5, 1});
    ASSERT_TRUE(plane1.belong(v1));
    space::Vector<3> n({0, 0 , 1});
    ASSERT_TRUE(plane1.getNormal() == n);

    space::Plane plane2(space::Vector<3>({1, 1, 1}), 0);
    space::Vector<3> v2({1, 1, -2});
    ASSERT_TRUE(plane2.belong(v2));
    ASSERT_FALSE(plane2.belong(v1));
}



