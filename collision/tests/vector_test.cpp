
#include <gtest/gtest.h>

#include <cmath>

#include "../src/vector.h"


TEST(Vector, addition)
{
    space::Vector vector1(1, 1, 1);
    space::Vector vector2(2, 2, 2);
    space::Vector addVector(3, 3, 3);
    ASSERT_TRUE(vector1 + vector2 == addVector);
    vector1 += vector2;
    ASSERT_TRUE(vector1 == addVector);
}

TEST(Vector, substraction)
{
    space::Vector vector1(1, 1, 1);
    space::Vector vector2(4, 4, 4);
    space::Vector subVector(3, 3, 3);
    ASSERT_TRUE(vector2 - vector1 == subVector);
    vector2 -= vector1;
    ASSERT_TRUE(vector2 == subVector);
}

TEST(Vector, multiplication)
{
    space::Vector vector(1, 1, 1);
    const double factor = 3;
    space::Vector mulVector(3, 3, 3);
    ASSERT_TRUE(vector * factor == mulVector);
    vector *= factor;
    ASSERT_TRUE(vector == mulVector);
}

TEST(Vector, length)
{
    space::Vector vector(1, 2, 3);
    double realLength = std::sqrt(1 * 1 + 2 * 2 + 3 * 3);
    ASSERT_DOUBLE_EQ(vector.length(), realLength);
}

TEST(Vector, dotProduct)
{
    space::Vector vector1(1, 2, 3);
    space::Vector vector2(4, 5, 6);
    double realProduct = 1 * 4 + 2 * 5 + 3 * 6;
    auto product = vector1.dotProduct(vector2);
    ASSERT_DOUBLE_EQ(product, realProduct);
}


TEST(Vector, crossProduct)
{
    space::Vector vector1(1, 2, 3);
    space::Vector vector2(4, 5, 6);
    space::Vector realProduct(2 * 6 - 3 * 5, 3 * 4 - 1 * 6, 1 * 5 - 2 * 4);
    auto product = vector1.crossProduct(vector2);
    ASSERT_TRUE(product == realProduct);
}


