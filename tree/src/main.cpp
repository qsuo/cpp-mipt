
#include "rbtree.h"
#include "tree.h"

#include <chrono>
#include <set>
#include <iterator>
#include <fstream>
#include <string>

const int NKEYS = 5000000;
const int STRIDE = 1000;

int main()
{
    tree::RBTree<int> tree;

    int nkeys = 0;
    std::cin >> nkeys;
    for(int i = 0; i < nkeys; i++)
    {
        int key = 0;
        std::cin >> key;
        tree.insert(key);
    }

    int nrequests = 0;
    std::cin >> nrequests;
    for(int i = 0; i < nrequests; i++)
    {
        int left = 0;
        int right = 0;
        std::cin >> left >> right;
        std::cout << tree.rangeQuery(left, right) << " ";
    }
    std::cout << std::endl;
    return 0;
}
