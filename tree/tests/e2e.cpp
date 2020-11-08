
#include <gtest/gtest.h>

#include "rbtree.h"
#include "range_query.h"

#include <fstream>
#include <vector>
#include <string>
#include <streambuf>

namespace e2e
{

TEST(e2e, one)
{
    std::ifstream in("tests/e2e/one.in");
    std::string expected = "3 0 2 0 ";
    
    std::stringstream result;

    query::range_query(in, result);
    EXPECT_TRUE(result.str() == expected);
}

TEST(e2e, two)
{
    std::ifstream in("tests/e2e/two.in");
    
    std::stringstream result;
    std::string expected = "INVALID REQUEST";

    query::range_query(in, result);

    EXPECT_TRUE(result.str() == expected);
}

TEST(e2e, three)
{
    std::ifstream in("tests/e2e/three.in");
    
    std::stringstream result;
    std::string expected = "0 ";

    query::range_query(in, result);

    EXPECT_TRUE(result.str() == expected);
}

TEST(e2e, four)
{
    std::ifstream in("tests/e2e/four.in");
    
    std::stringstream result;
    std::string expected = "INVALID NKEYS";

    query::range_query(in, result);

    EXPECT_TRUE(result.str() == expected);
}

TEST(e2e, five)
{
    std::ifstream in("tests/e2e/five.in");
    
    std::stringstream result;
    std::string expected = "EOF";

    query::range_query(in, result);

    EXPECT_TRUE(result.str() == expected);
}


TEST(e2e, six)
{
    std::ifstream in("tests/e2e/six.in");
    
    std::stringstream result;
    std::string expected = "INVALID";

    query::range_query(in, result);

    EXPECT_TRUE(result.str() == expected);
}

TEST(e2e, seven)
{
    std::ifstream in("tests/e2e/seven.in");
    
    std::stringstream result;
    std::string expected = "EOF";

    query::range_query(in, result);

    EXPECT_TRUE(result.str() == expected);
}

TEST(e2e, eight)
{
    std::ifstream in("tests/e2e/eight.in");
    
    std::stringstream result;
    std::string expected = "";

    query::range_query(in, result);

    EXPECT_TRUE(result.str() == expected);
}


TEST(e2e, nine)
{
    std::ifstream in("tests/e2e/nine.in");
    
    std::stringstream result;
    std::string expected = "INVALID NREQUESTS";

    query::range_query(in, result);

    EXPECT_TRUE(result.str() == expected);
}
}// namespace e2e

