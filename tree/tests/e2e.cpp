
#include <gtest/gtest.h>

#include "rbtree.h"
#include "range_query.h"

#include <fstream>
#include <vector>
#include <string>
#include <streambuf>

TEST(e2e, one)
{
    std::ifstream in("tests/e2e/one.in");
    std::ifstream out("tests/e2e/one.out");
    
    std::stringstream result;
    std::stringstream expected;

    range_query(in, result);
    expected << out.rdbuf();

    EXPECT_TRUE(result.str() == expected.str());
}




