
#include <gtest/gtest.h>

#include "../src/plane.h"

TEST(plane, belong)
{
    space::dim3::Plane plane1(space::dim3::Vector({0, 0, 1}), -1);
    space::dim3::Vector v1({5, 5, 1});
    ASSERT_TRUE(plane1.belong(v1));
    space::dim3::Vector n({0, 0 , 1});
    ASSERT_TRUE(plane1.getNormal() == n);

    space::dim3::Plane plane2(space::dim3::Vector({1, 1, 1}), 0);
    space::dim3::Vector v2({1, 1, -2});
    ASSERT_TRUE(plane2.belong(v2));
    ASSERT_FALSE(plane2.belong(v1));
}



