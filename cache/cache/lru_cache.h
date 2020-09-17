
#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <iostream>
#include <unordered_map>
#include <list>

template <typename T, typename KeyT>
class LRU
{
public:
    explicit LRU(size_t size): size_(size > 0 ? size : 1) {}

    bool full() const;
    bool hit(const KeyT &key) const;
    void dump() const;
    size_t size() const
    {
        return size_;
    }

    T insert(const T &data, const KeyT &key);
    bool pull(const KeyT &key);
    bool lookup(const T &data, const KeyT &key);


private:

    struct Item
    {
        T data;
        KeyT key;
    };


    size_t size_;
    std::list<Item> cache_;

    using listIt =  typename std::list<Item>::iterator;
    std::unordered_map<KeyT, listIt> hash_;

};

template <typename T, typename KeyT>
void LRU<T, KeyT>::dump() const
{
    for(auto elem : cache_)
        std::cout << elem.key << " --> ";
    std::cout << std::endl;
}


template <typename T, typename KeyT>
bool LRU<T, KeyT>::hit(const KeyT &key) const
{
    auto hit = hash_.find(key);
    return (hit != hash_.end());
}

template <typename T, typename KeyT>
bool LRU<T, KeyT>::full() const
{    
    return (cache_.size() == size_);
}

/*
 * insert element in cache
 * return this element if cache has free place
 * return poped element if cache is full
*/
template <typename T, typename KeyT>
T LRU<T, KeyT>::insert(const T &elem, const KeyT &key)
{    
    Item item = {elem, key};
    auto hit = hash_.find(item.key);
    
    if(hit == hash_.end())
    {
        if(full())
        {
            auto poped = cache_.back();
            hash_.erase(poped.key);
            cache_.pop_back();

            cache_.push_front(item);
            hash_[item.key] = cache_.begin();
            return poped.data;
        }

        cache_.push_front(item);
        hash_[item.key] = cache_.begin();
        return item.data;
    }

    auto eltit = hit->second;
    if (eltit != cache_.begin())
        cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));

    return item.data;
}


template <typename T, typename KeyT>
bool LRU<T, KeyT>::pull(const KeyT &key)
{
    auto hit = hash_.find(key);

    if(hit == hash_.end())
        return false;

    cache_.erase(hit->second);
    hash_.erase(key);
    return true;
}

template <typename T, typename KeyT>
bool LRU<T, KeyT>::lookup(const T &data, const KeyT &key)
{
    auto hitted = hit(key);
    insert(data, key);
    return hitted;
}

#endif
