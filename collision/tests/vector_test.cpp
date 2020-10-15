
#include <gtest/gtest.h>

#include <cmath>

#include "../src/vector.h"


TEST(Vector, addition)
{
    space::dim3::Vector vector1({1, 1, 1});
    space::dim3::Vector vector2({2, 2, 2});
    space::dim3::Vector addVector({3, 3, 3});
    EXPECT_TRUE(vector1 + vector2 == addVector);
    vector1 += vector2;
    EXPECT_TRUE(vector1 == addVector);
}

TEST(Vector, substraction)
{
    space::dim3::Vector vector1({1, 1, 1});
    space::dim3::Vector vector2({4, 4, 4});
    space::dim3::Vector subVector({3, 3, 3});
    EXPECT_TRUE(vector2 - vector1 == subVector);
    vector2 -= vector1;
    EXPECT_TRUE(vector2 == subVector);
}

TEST(Vector, multiplication)
{
    space::dim3::Vector vector({1, 1, 1});
    const double factor = 3;
    space::dim3::Vector mulVector({3, 3, 3});
    EXPECT_TRUE(vector * factor == mulVector);
    vector *= factor;
    EXPECT_TRUE(vector == mulVector);
}

TEST(Vector, length)
{
    space::dim3::Vector vector({1, 2, 3});
    double realLength = std::sqrt(1 * 1 + 2 * 2 + 3 * 3);
    EXPECT_DOUBLE_EQ(vector.length(), realLength);
}

TEST(Vector, dotProduct)
{
    space::dim3::Vector vector1({1, 2, 3});
    space::dim3::Vector vector2({4, 5, 6});
    double realProduct = 1 * 4 + 2 * 5 + 3 * 6;
    auto product = space::dotProduct(vector1, vector2);
    EXPECT_DOUBLE_EQ(product, realProduct);
}

TEST(Vector, crossProduct)
{
    space::dim3::Vector vector1({1, 2, 3});
    space::dim3::Vector vector2({4, 5, 6});
    space::dim3::Vector realProduct({2 * 6 - 3 * 5, 3 * 4 - 1 * 6, 1 * 5 - 2 * 4});
    auto product = space::dim3::crossProduct(vector1, vector2);
    EXPECT_TRUE(product == realProduct);
}
