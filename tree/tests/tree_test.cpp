#include <gtest/gtest.h>

#include <cmath>

#include "rbtree.h"
#include "tree.h"

#include <set>
#include <vector>
#include <chrono>
#include <string>
#include <sstream>
#include <algorithm>

namespace ut
{

std::string toString(std::vector<int> array)
{
    std::stringstream out;
    std::copy(array.begin(), array.end(), std::ostream_iterator<int>(out, " "));
    return out.str();
}

TEST(RBTree, insert)
{
    tree::RBTree<int> tree;
    std::vector<int> keys;

    for(int i = 10; i >= 0; i--)
    {
        tree.insert(i);
        keys.push_back(i);
    }
    std::sort(keys.begin(), keys.end());
    auto sorted = tree.getSorted();

    auto real = toString(keys);
    auto out = toString(sorted);

    EXPECT_TRUE(out == real);
}

TEST(RBTree, find)
{
    tree::RBTree<int> tree;
    std::vector<int> keys;

    for(int i = 10; i >= 0; i--)
        tree.insert(i);

    EXPECT_EQ(tree.find(10)->key, 10);
    EXPECT_EQ(tree.find(5)->key, 5);
    EXPECT_EQ(tree.find(0)->key, 0);

    EXPECT_EQ(tree.find(11), nullptr);
}

TEST(RBTree, remove)
{
    tree::RBTree<int> tree;

    for(int i = 10; i >= 0; i--)
        tree.insert(i);
    
    tree.remove(10);
    tree.remove(5);
    tree.remove(0);

    EXPECT_EQ(tree.find(10), nullptr);
    EXPECT_EQ(tree.find(5), nullptr);
    EXPECT_EQ(tree.find(0), nullptr);
}


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

TEST(RBTree, bound)
{
    tree::RBTree<int> tree;

    EXPECT_EQ(tree.lowerBound(0), nullptr);

    for(int i = 10; i >= 0; i--)
        tree.insert(i);
    tree.insert(12);

    EXPECT_EQ(tree.lowerBound(0)->key, 0);
    EXPECT_EQ(tree.lowerBound(5)->key, 5);
    EXPECT_EQ(tree.lowerBound(10)->key, 10);

    EXPECT_EQ(tree.lowerBound(11)->key, 12);
    EXPECT_EQ(tree.lowerBound(12)->key, 12);

    EXPECT_EQ(tree.lowerBound(13), nullptr);
    EXPECT_EQ(tree.lowerBound(-1)->key, 0);

}


TEST(RBTree, query)
{
    tree::RBTree<int> tree;
    
    EXPECT_EQ((size_t) 0, tree.rangeQuery(0, 10));

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

TEST(RBTree, structure)
{
    tree::RBTree<int> tree;
    for(int i = 10; i >= 1; i--)
        tree.insert(i);

    auto root = tree.root();

    /* test structure of rb tree after inserts */
    EXPECT_EQ(root->key, 7);
    EXPECT_EQ(root->color, tree::RBTree<int>::BLACK);

    EXPECT_EQ(root->right->key, 9);
    EXPECT_EQ(root->right->color, tree::RBTree<int>::BLACK);

    EXPECT_EQ(root->right->right->key, 10);
    EXPECT_EQ(root->right->right->color, tree::RBTree<int>::BLACK);

    EXPECT_EQ(root->right->left->key, 8);
    EXPECT_EQ(root->right->left->color, tree::RBTree<int>::BLACK);

    EXPECT_EQ(root->left->key, 5);
    EXPECT_EQ(root->left->color, tree::RBTree<int>::BLACK);
    
    EXPECT_EQ(root->left->right->key, 6);
    EXPECT_EQ(root->left->right->color, tree::RBTree<int>::BLACK);

    EXPECT_EQ(root->left->left->key, 3);
    EXPECT_EQ(root->left->left->color, tree::RBTree<int>::RED);

    EXPECT_EQ(root->left->left->left->key, 2);
    EXPECT_EQ(root->left->left->left->color, tree::RBTree<int>::BLACK);
    
    EXPECT_EQ(root->left->left->right->key, 4);
    EXPECT_EQ(root->left->left->right->color, tree::RBTree<int>::BLACK);
    
    EXPECT_EQ(root->left->left->left->left->key, 1);
    EXPECT_EQ(root->left->left->color, tree::RBTree<int>::RED);


    tree.remove(7);
    root = tree.root();

    /* test structure of rb tree after root remove */
    EXPECT_EQ(root->key, 5);
    EXPECT_EQ(root->left->left->color, tree::RBTree<int>::BLACK);

    EXPECT_EQ(root->left->key, 3);
    EXPECT_EQ(root->left->left->color, tree::RBTree<int>::BLACK);

    EXPECT_EQ(root->left->right->key, 4);
    EXPECT_EQ(root->left->right->color, tree::RBTree<int>::BLACK);

    EXPECT_EQ(root->left->left->left->key, 1);
    EXPECT_EQ(root->left->left->left->color, tree::RBTree<int>::RED);

    EXPECT_EQ(root->right->right->right->key, 10);
    EXPECT_EQ(root->right->right->right->color, tree::RBTree<int>::RED);
}


}// namespace ut
