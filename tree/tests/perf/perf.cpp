
#include <gtest/gtest.h>
#include <chrono>

#include "rbtree.h"
#include "tree.h"

namespace benchmark
{

TEST(RBTree, bench)
{
    const int NKEYS = 10000000;
    const int STRIDE = 100;

    tree::RBTree<int> rb;
    tree::Tree<int> base;

    for(int i = 0; i < NKEYS; i++)
    {
        rb.insert(i);
        base.insert(i);
    }

    auto t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < NKEYS; i = i + STRIDE)
        rb.rangeQuery(i, i + STRIDE);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto rb_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "RB tree time: " << rb_time << std::endl;
    
    t1 = std::chrono::high_resolution_clock::now();
    for(int i = 0; i < NKEYS; i = i + STRIDE)
        base.rangeQuery(i, i + STRIDE);
    t2 = std::chrono::high_resolution_clock::now();
    auto set_time = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    
    std::cout << "std::set time: " << set_time << std::endl;

    EXPECT_TRUE(rb_time < set_time);
}

}// namespace benchmark
