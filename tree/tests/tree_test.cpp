#include <gtest/gtest.h>

#include <cmath>

#include "rbtree.h"
#include "tree.h"

#include <set>
#include <chrono>

TEST(RBTree, functional)
{
    std::set<int> set;
    tree::RBTree<int> tree;
    
    const int NKEYS = 1000;
    for(int i = 0; i < NKEYS; ++i)
    {
        set.insert(i);
        tree.insert(i);
    }

    int nset = 0;
    int ntree = 0;
    for(int i = 0; i < 2 * NKEYS; ++i)
    {
        if(set.find(i) != set.end())
            nset++;
        if(tree.find(i) != nullptr)
            ntree++;
    }
    EXPECT_EQ(nset, ntree);

    for(int i = NKEYS / 2; i < NKEYS; i++)
    {
        set.erase(i);
        tree.remove(i);
    }

    nset = 0;
    ntree = 0;
    for(int i = 0; i < 2 * NKEYS; ++i)
    {
        if(set.find(i) != set.end())
            nset++;
        if(tree.find(i) != nullptr)
            ntree++;
    }

    EXPECT_EQ(nset, ntree);
}

TEST(RBTree, query)
{
    tree::RBTree<int> tree;
    
    const int NKEYS = 10;
    for(int i = 0; i < NKEYS; ++i)
        tree.insert(i);

    EXPECT_EQ((size_t) 10, tree.rangeQuery(0, 10));
    EXPECT_EQ((size_t) 5, tree.rangeQuery(5, 10));
    EXPECT_EQ((size_t) 1, tree.rangeQuery(9, 10));
    EXPECT_EQ((size_t) 1, tree.rangeQuery(9, 9));
    EXPECT_EQ((size_t) 0, tree.rangeQuery(10, 10));
    EXPECT_EQ((size_t) 0, tree.rangeQuery(10, 11));
    EXPECT_EQ((size_t) 0, tree.rangeQuery(11, 100));
}

TEST(RBTree, perfomance)
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
