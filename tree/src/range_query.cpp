
#include "rbtree.h"
#include "tree.h"
#include "range_query.h"

void range_query(std::istream &in, std::ostream &out)
{
    tree::RBTree<int> tree;

    int nkeys = 0;
    in >> nkeys;
    for(int i = 0; i < nkeys; i++)
    {
        int key = 0;
        in >> key;
        tree.insert(key);
    }

    int nrequests = 0;
    in >> nrequests;
    for(int i = 0; i < nrequests; i++)
    {
        int left = 0;
        int right = 0;
        in >> left >> right;
        out << tree.rangeQuery(left, right);
        if(i != nrequests - 1)
            out << " ";
    }
    out << std::endl;
}

