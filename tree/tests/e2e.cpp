
#include <gtest/gtest.h>

#include "rbtree.h"

#include <iostream>
#include <fstream>
#include <vector>


std::string output(std::string fileName)
{
    std::ifstream file(fileName);
    std::string out;

    file.seekg(0, std::ios::end);   
    out.reserve(file.tellg());
    file.seekg(0, std::ios::beg);

    out.assign((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>()); 

    return out;

}

std::string test(std::string name)
{
    std::ifstream input(name);
    if(!input.is_open())
    {
        std::cerr << "Cannot open " << name << "\n";
        return "";
    }


    tree::RBTree<int> tree;
    
    int nkeys = 0;
    input >> nkeys;
    for(int i = 0; i < nkeys; i++)
    {
        int key = 0;
        input >> key;
        tree.insert(key);
    }

    int nrequests = 0;
    input >> nrequests;
    
    std::string out;
    for(int i = 0; i < nrequests; i++)
    {
        int left = 0;
        int right = 0;
        input >> left >> right;
        auto q = tree.rangeQuery(left, right);
        out = out + std::to_string(q);
        if(i != nrequests - 1)
            out += " ";
    }
    out += "\n";

    return out;    
}

TEST(e2e, one)
{
    auto generated = test("tests/e2e/one.in");
    auto out = output("tests/e2e/one.out");
    EXPECT_TRUE(out == generated);
}




