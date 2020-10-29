#include <gtest/gtest.h>

#include <cmath>

#include "tree.h"
#include <set>

TEST(Tree, functional)
{
    std::set<int> set;
    Tree<int> tree;
    
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

