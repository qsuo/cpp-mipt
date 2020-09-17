
#include <gtest/gtest.h>

#include "../cache/lru_cache.h"

const size_t CACHE_SIZE = 100;

TEST(CacheLRU, init)
{
    LRU<size_t, size_t> lru(0);    
    ASSERT_EQ(lru.size(), static_cast<size_t>(1));
}


TEST(CacheLRU, minimalFunctional)
{
    const size_t CACHE_SIZE = 2;
    LRU<size_t, size_t> lru(CACHE_SIZE);

    ASSERT_FALSE(lru.full());
    ASSERT_FALSE(lru.hit(0));
    ASSERT_FALSE(lru.hit(1));
    
    auto tmp = lru.insert(0, 0);
    ASSERT_EQ(tmp, static_cast<size_t>(0));
    ASSERT_TRUE(lru.hit(0));
    ASSERT_FALSE(lru.hit(1));
    ASSERT_FALSE(lru.full());

    tmp = lru.insert(1, 1);
    ASSERT_EQ(tmp, static_cast<size_t>(1));
    ASSERT_TRUE(lru.hit(0));
    ASSERT_TRUE(lru.hit(1));
    ASSERT_TRUE(lru.full());

    tmp = lru.insert(0, 0);
    ASSERT_EQ(tmp, static_cast<size_t>(0));
    ASSERT_TRUE(lru.hit(0));

    tmp = lru.insert(2, 2);
    ASSERT_EQ(tmp, static_cast<size_t>(1));
    ASSERT_TRUE(lru.hit(0));
    ASSERT_FALSE(lru.hit(1));
    ASSERT_TRUE(lru.hit(2));
    ASSERT_TRUE(lru.full());
    
    tmp = lru.insert(2, 2);
    ASSERT_EQ(tmp, static_cast<size_t>(2));
    ASSERT_TRUE(lru.hit(0));
    ASSERT_TRUE(lru.hit(2));
    ASSERT_TRUE(lru.full());

    ASSERT_TRUE(lru.pull(2));
    ASSERT_FALSE(lru.hit(2));
    ASSERT_FALSE(lru.pull(2));

    LRU<size_t, size_t> lru2(CACHE_SIZE + 1);
    for(size_t i = 0; i < CACHE_SIZE + 1; i++)
        lru2.insert(i, i);
    ASSERT_TRUE(lru2.full());
    lru2.pull(1);
    ASSERT_FALSE(lru2.hit(1));
}

TEST(CacheLRU, popFromTail)
{
    LRU<size_t, size_t> lru(CACHE_SIZE);

    for(size_t i = 0; i < CACHE_SIZE + 1; i++)
        lru.lookup(i, i);

    ASSERT_TRUE(lru.full());
    ASSERT_FALSE(lru.hit(0));
    ASSERT_FALSE(lru.lookup(0, 0));
    ASSERT_TRUE(lru.lookup(0, 0));
}       

TEST(CacheLRU, moveToHead)
{
    LRU<size_t, size_t> lru(CACHE_SIZE);

    for(size_t i = 0; i < CACHE_SIZE + 1; i++)
        lru.lookup(i, i);

    ASSERT_TRUE(lru.hit(1));
    ASSERT_TRUE(lru.lookup(1, 1));
    ASSERT_FALSE(lru.lookup(0, 0));
    ASSERT_TRUE(lru.hit(1));
} 

TEST(CacheLRU, zeroHits)
{
    LRU<size_t, size_t> lru(CACHE_SIZE);

    size_t hits = 0;
    for(size_t i = 0; i < CACHE_SIZE + 1; i++)
        if(lru.lookup(i, i))
            hits++;

    ASSERT_EQ(hits, static_cast<size_t>(0));
}

TEST(CacheLRU, hits)
{
    const size_t nloops = 2;
    LRU<size_t, size_t> lru(CACHE_SIZE);

    size_t hits = 0;
    for(size_t loop = 0; loop < nloops; loop++)
    {
        for(size_t i = 0; i < CACHE_SIZE; i++)
        {
            if(lru.lookup(i, i))
                hits++;
        }
    }
    ASSERT_EQ(hits, static_cast<size_t>(CACHE_SIZE));
}


