#include <gtest/gtest.h>


#include "../src/intersection.h"
#include "../src/triangle.h"

TEST(line, test)
{

    space::Vector f1(0, 0, 1);
    space::Vector f2(0, 2, 1);
    space::Vector s1(0, 1, 2);
    space::Vector s2(0, 1, 0);

    space::Vector norm(1, 0, 0);
    bool a = space::line::intersection({f2, f1}, {s2, s1}, norm); 
    EXPECT_TRUE(a);
}
