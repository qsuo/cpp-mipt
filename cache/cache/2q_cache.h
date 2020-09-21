
#ifndef CACHE_H
#define CACHE_H

#include <list>
#include <unordered_map>
#include <cassert>

#include "lru_cache.h"

template <typename T,  typename KeyT>
class Cache2Q
{
public:
    explicit Cache2Q(size_t size);
    Cache2Q(size_t mainSize, size_t inSize, size_t outSize);
 
    size_t sizeMain() const
    {
        return main_.size();
    }

    size_t sizeIn() const
    {
        return in_.size();
    }

    size_t sizeOut() const
    {
        return out_.size();
    }

    size_t size() const
    {
        return main_.size() + in_.size();
    }

    bool full() const;
    bool hit(const KeyT &key) const;
    void dump() const;

    bool lookup(const T &data, const KeyT &key);

private:

    static const size_t divider_ = 4;

    struct Item
    {
        T data;
        KeyT key;
    };

    size_t size_;

    LRU<Item, KeyT> main_;
    LRU<Item, KeyT> in_;
    LRU<KeyT, KeyT> out_;

};


template <typename T, typename KeyT>
Cache2Q<T, KeyT>::Cache2Q(size_t size):
    size_((size >= divider_) ? size : 2),
    main_((size >= divider_) ? (size - size / 4) : 1),
    in_((size >= divider_) ? (size / 4) : 1),
    out_((size >= divider_) ? (size - size / 4) : 1) {}

template <typename T, typename KeyT>
Cache2Q<T, KeyT>::Cache2Q(size_t mainSize, size_t inSize, size_t outSize):
    size_(mainSize + inSize),
    main_(mainSize),
    in_(inSize),
    out_(outSize) {}

template <typename T, typename KeyT>
void Cache2Q<T, KeyT>::dump() const
{
    std::cout << "*************" << std::endl;
    std::cout << "MAIN:" << std::endl;
    main_.dump();
    
    std::cout << "IN:" << std::endl;
    in_.dump();
    
    std::cout << "OUT:" << std::endl;
    out_.dump();

    std::cout << "*************" << std::endl;
}

template <typename T, typename KeyT>
bool Cache2Q<T, KeyT>::full() const
{
    return (main_.full() && in_.full());
}

template <typename T, typename KeyT>
bool Cache2Q<T, KeyT>::hit(const KeyT &key) const
{
    auto mainHit = main_.hit(key);
    auto inHit = in_.hit(key);

    return (mainHit || inHit);
}


template <typename T, typename KeyT>
bool Cache2Q<T, KeyT>::lookup(const T &data, const KeyT &key)
{
    Item item = {data, key};

    auto mainHit = main_.hit(key);
    auto inHit = in_.hit(key);
    auto outHit = out_.hit(item.key);
    
    if(mainHit)
    {
        main_.insert(item, item.key);
        return true;
    }
    
    else if(!mainHit && inHit)
    {
        in_.insert(item, item.key);
        return true;
    }

    else if(!mainHit && outHit)
    {
        main_.insert(item, item.key);
        out_.pull(item.key);
        return false;
    }

    else // if(!mainHit && !inHit)
    {
        if(in_.full())
        {
            auto poped = in_.insert(item, item.key);
            out_.insert(poped.key, poped.key);
        }
        else
            in_.insert(item, item.key);
        
        return false;
    }

}


#endif
