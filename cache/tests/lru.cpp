
#include <iostream>
#include <vector>

#include "common.h"
#include "../lru_cache.h"
#include "page.h"

const size_t CACHE_SIZE = 2;


int main()
{
    std::vector<Page> pages;
    for(size_t i = 0; i < CACHE_SIZE + 1; i++)
        pages.push_back({(Page::Id)i, 0, NULL});

    LRU<Page, Page::Id> lru(CACHE_SIZE);

    TEST(lru.full() == false);
    TEST(lru.hit(pages[0].id) == false);
    TEST(lru.hit(pages[1].id) == false);
    
    auto tmp = lru.insert(pages[0], pages[0].id);
    TEST(tmp.id == pages[0].id);
    TEST(lru.hit(pages[0].id) == true);
    TEST(lru.hit(pages[1].id) == false);
    TEST(lru.full() == false);

    tmp = lru.insert(pages[1], pages[1].id);
    TEST(tmp.id == pages[1].id);
    TEST(lru.hit(pages[0].id) == true);
    TEST(lru.hit(pages[1].id) == true);
    TEST(lru.full() == true);

    tmp = lru.insert(pages[0], pages[0].id);
    TEST(tmp.id == pages[0].id);
    TEST(lru.hit(pages[0].id) == true);

    tmp = lru.insert(pages[2], pages[2].id);
    TEST(tmp.id == pages[1].id);
    TEST(lru.hit(pages[0].id) == true);
    TEST(lru.hit(pages[1].id) == false);
    TEST(lru.hit(pages[2].id) == true);
    TEST(lru.full() == true);
    
    tmp = lru.insert(pages[2], pages[2].id);
    TEST(tmp.id == pages[2].id);
    TEST(lru.hit(pages[0].id) == true);
    TEST(lru.hit(pages[2].id) == true);
    TEST(lru.full() == true);

    TEST(lru.pull(pages[2].id) == true);
    TEST(lru.hit(pages[2].id) == false);
    TEST(lru.pull(pages[2].id) == false);

    LRU<Page, Page::Id> lru2(CACHE_SIZE + 1);
    for(auto page : pages)
        lru2.insert(page, page.id);
    TEST(lru2.full() == true);
    lru2.pull(pages[1].id);
    TEST(lru2.hit(pages[1].id) == false);
    
    return 0;
}




