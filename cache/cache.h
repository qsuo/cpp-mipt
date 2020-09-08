
#ifndef CACHE_H
#define CACHE_H

#include <list>
#include <unordered_map>

#include <stddef.h>


#include "page.h"


template <typename T>
class LRU
{
public:
    explicit LRU(size_t size): size_(size) {}

    bool full();
    T insert(const T &elem);
    bool hit(const T &elem);
    bool pull(const T &elem);
    
    void dump();

private:
    size_t size_;
    std::list<T> cache_;

    typedef typename std::list<T>::iterator ListIt;
    std::unordered_map<typename T::Id, ListIt> hash_;

};

template <typename T>
void LRU<T>::dump()
{
    for(auto elem : cache_)
        std::cout << elem.id << " --> ";
    std::cout << std::endl;
}


template <typename T>
bool LRU<T>::full()
{    
    return (cache_.size() == size_);
}

template <typename T>
T LRU<T>::insert(const T &elem)
{    
    auto hit = hash_.find(elem.id);
    if(hit == hash_.end())
    {
        if(full())
        {
            hash_.erase(cache_.back().id);
            T poped = cache_.back();
            cache_.pop_back();
            cache_.push_front(elem);
            hash_[elem.id] = cache_.begin();
            return poped;
        }
        cache_.push_front(elem);
        hash_[elem.id] = cache_.begin();
        return elem;
    }
    auto eltit = hit->second;
    if (eltit != cache_.begin())
        cache_.splice(cache_.begin(), cache_, eltit, std::next(eltit));
    return elem;
}


template <typename T>
bool LRU<T>::pull(const T &elem)
{
    auto hit = hash_.find(elem.id);
    if(hit == hash_.end())
        return false;
    cache_.erase(hit->second);
    hash_.erase(elem.id);
    return true;
}

template <typename T>
bool LRU<T>::hit(const T &elem)
{
    auto hit = hash_.find(elem.id);
    return (hit != hash_.end());
}


template <typename T>
class Cache2Q
{
public:
    explicit Cache2Q(size_t size);
    Cache2Q(size_t mainSize, size_t inSize, size_t outSize);
    size_t getSize()
    {
        return size_;
    }

    struct Id_t
    {
        typedef typename T::Id Id;
        Id id;
    };

    bool full();
    bool hit(const T &elem);
    void dump();
    bool lookup(const T &elem);

private:
    size_t size_;

    LRU<T> main_;
    LRU<T> in_;
    LRU<Id_t> out_;

};


template <typename T>
Cache2Q<T>::Cache2Q(size_t size):
    size_(size),
    main_(size - size / 4),
    in_(size / 4),
    out_(size - size / 4) {}

template <typename T>
Cache2Q<T>::Cache2Q(size_t mainSize, size_t inSize, size_t outSize):
    size_(mainSize + inSize),
    main_(mainSize),
    in_(inSize),
    out_(outSize) {}


template <typename T>
void Cache2Q<T>::dump()
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

template <typename T>
bool Cache2Q<T>::hit(const T &elem)
{
    auto mainHit = main_.hit(elem);
    auto inHit = in_.hit(elem);

    return (mainHit || inHit);
}


template <typename T>
bool Cache2Q<T>::lookup(const T &elem)
{
    auto mainHit = main_.hit(elem);
    auto inHit = in_.hit(elem);

    if(!mainHit)
    {
        Id_t id = {elem.id};
        auto outHit = out_.hit(id);
        if(outHit)
        {
            main_.insert(elem);
            out_.pull(id);
            return false;
        }

        if(!inHit)
        {
            if(in_.full())
            {
                auto poped = in_.insert(elem);
                Id_t id = {poped.id};
                out_.insert(id);
            }
            else
                in_.insert(elem);
            
            return false;
        }
        else
        {
            in_.insert(elem);
            return true;
        }

    }
    else
    {
        main_.insert(elem);
        return true;
    }
}


#endif
