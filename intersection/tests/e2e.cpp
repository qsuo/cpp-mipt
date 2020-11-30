#include <gtest/gtest.h>

#include "plane.h"
#include "point.h"
#include "triangles_set_intersection.h"

#include <string>
#include <fstream>

TEST(e2e, one)
{
    std::string expected = "0 1 2 3 4 5 ";
    
    std::ifstream in("tests/e2e/1.in");
    std::stringstream result;

    space::triangleIntersections(in, result);

    EXPECT_TRUE(result.str() == expected);
}
