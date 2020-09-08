
#include <iostream>
#include <cassert>
#include <cstddef>
#include <string>
#include <sstream>
#include <vector>

#include <stdio.h>

#include "common.h"
#include "../cache.h"
#include "../page.h"

const size_t CACHE_SIZE = 2;

/*
std::vector<Page> input(const std::string accesses)
{
    std::stringstream stream(accesses);
    std::vector<Page> pages;
    while(1)
    {
        Page::Id n;
        stream >> n;
        if(!stream)
            break;
        pages.push_back({n, 0, NULL});
    }
    return pages;
}
*/

int main()
{
    std::vector<Page> pages;
    for(size_t i = 0; i < CACHE_SIZE + 1; i++)
        pages.push_back({(Page::Id)i, 0, NULL});

    LRU<Page> lru(CACHE_SIZE);

    TEST(lru.full() == false);
    TEST(lru.hit(pages[0]) == false);
    TEST(lru.hit(pages[1]) == false);
    
    auto tmp = lru.insert(pages[0]);
    TEST(tmp.id == pages[0].id);
    TEST(lru.hit(pages[0]) == true);
    TEST(lru.hit(pages[1]) == false);
    TEST(lru.full() == false);

    tmp = lru.insert(pages[1]);
    TEST(tmp.id == pages[1].id);
    TEST(lru.hit(pages[0]) == true);
    TEST(lru.hit(pages[1]) == true);
    TEST(lru.full() == true);

    tmp = lru.insert(pages[0]);
    TEST(tmp.id == pages[0].id);
    TEST(lru.hit(pages[0]) == true);

    tmp = lru.insert(pages[2]);
    TEST(tmp.id == pages[1].id);
    TEST(lru.hit(pages[0]) == true);
    TEST(lru.hit(pages[1]) == false);
    TEST(lru.hit(pages[2]) == true);
    TEST(lru.full() == true);
    
    tmp = lru.insert(pages[2]);
    TEST(tmp.id == pages[2].id);
    TEST(lru.hit(pages[0]) == true);
    TEST(lru.hit(pages[2]) == true);
    TEST(lru.full() == true);

    lru.pull(pages[2]);
    TEST(lru.hit(pages[2]) == false);

    LRU<Page> lru2(CACHE_SIZE + 1);
    for(auto page : pages)
        lru2.insert(page);
    TEST(lru2.full() == true);
    lru2.pull(pages[1]);
    TEST(lru2.hit(pages[1]) == false);

    return 0;
}




