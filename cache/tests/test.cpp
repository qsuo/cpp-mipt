
#include <iostream>
#include <vector>

#include <gtest/gtest.h>

#include "../cache/lru_cache.h"
#include "../cache/2q_cache.h"
#include "page.h"


const size_t CACHE_SIZE = 100;

TEST(CacheLRU, minimalFunctional)
{
    const size_t CACHE_SIZE = 2;
    std::vector<Page> pages;
    for(size_t i = 0; i < CACHE_SIZE + 1; i++)
        pages.push_back({(Page::Id)i, 0, NULL});

    LRU<Page, Page::Id> lru(CACHE_SIZE);

    ASSERT_FALSE(lru.full());
    ASSERT_FALSE(lru.hit(pages[0].id));
    ASSERT_FALSE(lru.hit(pages[1].id));
    
    auto tmp = lru.insert(pages[0], pages[0].id);
    ASSERT_EQ(tmp.id, pages[0].id);
    ASSERT_TRUE(lru.hit(pages[0].id));
    ASSERT_FALSE(lru.hit(pages[1].id));
    ASSERT_FALSE(lru.full());

    tmp = lru.insert(pages[1], pages[1].id);
    ASSERT_EQ(tmp.id, pages[1].id);
    ASSERT_TRUE(lru.hit(pages[0].id));
    ASSERT_TRUE(lru.hit(pages[1].id));
    ASSERT_TRUE(lru.full());

    tmp = lru.insert(pages[0], pages[0].id);
    ASSERT_EQ(tmp.id, pages[0].id);
    ASSERT_TRUE(lru.hit(pages[0].id));

    tmp = lru.insert(pages[2], pages[2].id);
    ASSERT_EQ(tmp.id, pages[1].id);
    ASSERT_TRUE(lru.hit(pages[0].id));
    ASSERT_FALSE(lru.hit(pages[1].id));
    ASSERT_TRUE(lru.hit(pages[2].id));
    ASSERT_TRUE(lru.full());
    
    tmp = lru.insert(pages[2], pages[2].id);
    ASSERT_EQ(tmp.id, pages[2].id);
    ASSERT_TRUE(lru.hit(pages[0].id));
    ASSERT_TRUE(lru.hit(pages[2].id));
    ASSERT_TRUE(lru.full());

    ASSERT_TRUE(lru.pull(pages[2].id));
    ASSERT_FALSE(lru.hit(pages[2].id));
    ASSERT_FALSE(lru.pull(pages[2].id));

    LRU<Page, Page::Id> lru2(CACHE_SIZE + 1);
    for(auto page : pages)
        lru2.insert(page, page.id);
    ASSERT_TRUE(lru2.full());
    lru2.pull(pages[1].id);
    ASSERT_FALSE(lru2.hit(pages[1].id));
}

TEST(CacheLRU, popFromTail)
{
    const size_t CACHE_SIZE = 100;
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
    const size_t CACHE_SIZE = 100;
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
    const size_t CACHE_SIZE = 100;
    LRU<size_t, size_t> lru(CACHE_SIZE);

    size_t hits = 0;
    for(size_t i = 0; i < CACHE_SIZE + 1; i++)
        if(lru.lookup(i, i))
            hits++;

    ASSERT_EQ(hits, static_cast<size_t>(0));
}

TEST(CacheLRU, hits)
{
    const size_t CACHE_SIZE = 100;

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


#define LOOKUP(idx) cache.lookup(pages[idx], pages[idx].id)
#define HIT(idx) cache.hit(pages[idx].id)

TEST(Cache2Q, minimalFunctional)
{
    std::vector<Page> pages;
    for(size_t i = 0; i < 8; i++)
        pages.push_back({(Page::Id)i, 0, NULL});
    
    const size_t MAIN_SIZE = 3;
    const size_t IN_SIZE = 2;
    const size_t OUT_SIZE = 2;

    Cache2Q<Page, Page::Id> cache(MAIN_SIZE, IN_SIZE, OUT_SIZE);
    
    

    ASSERT_FALSE(LOOKUP(0));
    ASSERT_TRUE(HIT(0));
    ASSERT_FALSE(LOOKUP(1));
    ASSERT_TRUE(HIT(1));

    ASSERT_FALSE(LOOKUP(2));
    ASSERT_TRUE(HIT(2));
    ASSERT_TRUE(HIT(1));
    ASSERT_FALSE(HIT(0));

    ASSERT_FALSE(LOOKUP(3));
    ASSERT_TRUE(HIT(3));

    ASSERT_FALSE(LOOKUP(0));
    ASSERT_TRUE(HIT(0));
    ASSERT_FALSE(LOOKUP(1));
    ASSERT_TRUE(HIT(1));

    ASSERT_FALSE(LOOKUP(4));
    ASSERT_TRUE(HIT(4));

    ASSERT_TRUE(LOOKUP(0));
    ASSERT_TRUE(HIT(0));

    ASSERT_TRUE(LOOKUP(1));
    ASSERT_TRUE(HIT(1));
    ASSERT_FALSE(LOOKUP(2));
        
}

#undef LOOKUP
#undef HIT

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


    /*
    for(size_t i = CACHE_SIZE / 4; i < CACHE_SIZE; i++)
        if(cache.lookup(i, i))
            hits++;
    ASSERT_EQ(hits, static_cast<size_t>(CACHE_SIZE / 4));
    */  
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



int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}




