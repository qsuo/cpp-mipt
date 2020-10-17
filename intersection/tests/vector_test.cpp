
#include <gtest/gtest.h>

#include <cmath>

#include "vector.h"


TEST(Vector, addition)
{
    space::Vector<3> v1({1, 1, 1});
    space::Vector<3> v2({2, 2, 2});
    space::Vector<3> addVector({3, 3, 3});
    EXPECT_TRUE(v1 + v2 == addVector);
    v1 += v2;
    EXPECT_TRUE(v1 == addVector);
}

TEST(Vector, substraction)
{
    space::Vector<3> v1({1, 1, 1});
    space::Vector<3> v2({4, 4, 4});
    space::Vector<3> subVector({3, 3, 3});
    EXPECT_TRUE(v2 - v1 == subVector);
    v2 -= v1;
    EXPECT_TRUE(v2 == subVector);
}

TEST(Vector, multiplication)
{
    space::Vector<3> vector({1, 1, 1});
    const double factor = 3;
    space::Vector<3> mulVector({3, 3, 3});
    EXPECT_TRUE(vector * factor == mulVector);
    vector *= factor;
    EXPECT_TRUE(vector == mulVector);
}

TEST(Vector, length)
{
    space::Vector<3> vector({1, 2, 3});
    double realLength = std::sqrt(1 * 1 + 2 * 2 + 3 * 3);
    EXPECT_DOUBLE_EQ(vector.length(), realLength);
}

TEST(Vector, dotProduct)
{
    space::Vector<3> v1({1, 2, 3});
    space::Vector<3> v2({4, 5, 6});
    double realProduct = 1 * 4 + 2 * 5 + 3 * 6;
    auto product = space::dotProduct(v1, v2);
    EXPECT_DOUBLE_EQ(product, realProduct);
}

TEST(Vector, crossProduct)
{
    space::Vector<3> v1({1, 2, 3});
    space::Vector<3> v2({4, 5, 6});
    space::Vector<3> realProduct({2 * 6 - 3 * 5, 3 * 4 - 1 * 6, 1 * 5 - 2 * 4});
    auto product = space::crossProduct(v1, v2);
    EXPECT_TRUE(product == realProduct);
}

TEST(Vector, pseudoProduct)
{
    space::Vector<2> v1({1, 2});
    space::Vector<2> v2({3, 4});
    auto realProduct = space::crossProduct(v1, v2)[2];
    auto product = space::pseudoProduct(v1, v2);
    EXPECT_TRUE(product == realProduct);
}


