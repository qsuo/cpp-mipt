

#ifndef TREE_H
#define TREE_H

#include <set>
#include <iterator>

namespace tree
{

template <typename KeyT>
class Tree
{
public:
    void insert(const KeyT &key) { set.insert(key); }
    typename std::set<KeyT>::iterator find(const KeyT &key) const
    {
        return set.find(key);
    }
    void remove(const KeyT &key) { set.erase(key); }
    size_t rangeQuery(const KeyT &low, const KeyT &high) const
    {
        size_t count = 0;
        auto lower = set.lower_bound(low);
        auto higher = set.lower_bound(high);
        count = std::distance(lower, higher);
        if(*higher == high)
            count++;
        return count;
    }

private:

    std::set<KeyT> set;

};

}// namespace tree

#endif
