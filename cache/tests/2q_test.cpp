
#include <gtest/gtest.h>

#include "../cache/2q_cache.h"

const size_t CACHE_SIZE = 100;

TEST(Cache2Q, minimalFunctional)
{
    const size_t MAIN_SIZE = 3;
    const size_t IN_SIZE = 2;
    const size_t OUT_SIZE = 2;

    Cache2Q<size_t, size_t> cache(MAIN_SIZE, IN_SIZE, OUT_SIZE);
    
    ASSERT_FALSE(cache.lookup(0, 0));
    ASSERT_TRUE(cache.hit(0));
    ASSERT_FALSE(cache.lookup(1, 1));
    ASSERT_TRUE(cache.hit(1));

    ASSERT_FALSE(cache.lookup(2, 2));
    ASSERT_TRUE(cache.hit(2));
    ASSERT_TRUE(cache.hit(1));
    ASSERT_FALSE(cache.hit(0));

    ASSERT_FALSE(cache.lookup(3, 3));
    ASSERT_TRUE(cache.hit(3));

    ASSERT_FALSE(cache.lookup(0, 0));
    ASSERT_TRUE(cache.hit(0));
    ASSERT_FALSE(cache.lookup(1, 1));
    ASSERT_TRUE(cache.hit(1));

    ASSERT_FALSE(cache.lookup(4, 4));
    ASSERT_TRUE(cache.hit(4));

    ASSERT_TRUE(cache.lookup(0, 4));
    ASSERT_TRUE(cache.hit(0));

    ASSERT_TRUE(cache.lookup(1, 1));
    ASSERT_TRUE(cache.hit(1));
    ASSERT_FALSE(cache.lookup(2, 2));
        
}

TEST(Cache2Q, toMain)
{
    Cache2Q<size_t, size_t> cache(CACHE_SIZE);
    ASSERT_FALSE(cache.full());

    size_t hits = 0;

    for(size_t i = 0; i < CACHE_SIZE; i++)
        if(cache.lookup(i, i))
            hits++;
    ASSERT_EQ(hits, static_cast<size_t>(0));

    for(int r = 0; r < 2; r++)
    {
        for(size_t i = 0; i < CACHE_SIZE - CACHE_SIZE / 4; i++)
            if(cache.lookup(i, i))
                hits++;
    }
    ASSERT_EQ(hits, CACHE_SIZE - CACHE_SIZE / 4);
    ASSERT_TRUE(cache.full());

    hits = 0;
    for(int i = static_cast<int>(CACHE_SIZE - 1); i >= 0; i--)
        if(cache.lookup(i, i))
            hits++;
    ASSERT_EQ(hits, CACHE_SIZE);

}

TEST(Cache2Q, inner)
{
    Cache2Q<size_t, size_t> cache(CACHE_SIZE);
    size_t hits = 0;
    for(int r = 0; r < 2; r++)
    {
        for(size_t i = 0; i < CACHE_SIZE / 4; i++)
            if(cache.lookup(i, i))
                hits++;
    }
    ASSERT_EQ(hits, CACHE_SIZE / 4);
}

TEST(Cache2Q, mainOveflow)
{
    Cache2Q<size_t, size_t> cache(CACHE_SIZE);
    for(size_t i = 0; i < CACHE_SIZE; i++)
        cache.lookup(i, i);
    
    for(int r = 0; r < 2; r++)
    {
        for(size_t i = 0; i < CACHE_SIZE - CACHE_SIZE / 4; i++)
            cache.lookup(i, i);
    }

    for(size_t i = CACHE_SIZE; i < 2 * CACHE_SIZE; i++)
        cache.lookup(i, i);

    size_t hits = 0;
    for(int r = 0; r < 2; r++)
    {
        for(size_t i = CACHE_SIZE; i < 2 * CACHE_SIZE - CACHE_SIZE / 4; i++)
            cache.lookup(i, i);
    }
    
    for(size_t i = 0; i < CACHE_SIZE; i++)
    {
        if(cache.lookup(i, i))
            hits++;
    }
    ASSERT_EQ(hits, static_cast<size_t>(0));
}


