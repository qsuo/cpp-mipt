
#include <iostream>

#include "common.h"
#include "../2q_cache.h"
#include "page.h"

const size_t MAIN_SIZE = 3;
const size_t IN_SIZE = 2;
const size_t OUT_SIZE = 2;


#define LOOKUP(idx, expr) do\
{\
    TEST(cache.lookup(pages[idx], pages[idx].id) == expr);\
}while(0)

#define HIT(idx, expr) do\
{\
    TEST(cache.hit(pages[idx].id) == expr);\
}while(0)


int main()
{
    std::vector<Page> pages;
    for(size_t i = 0; i < 8; i++)
        pages.push_back({(Page::Id)i, 0, NULL});

    Cache2Q<Page, Page::Id> cache(MAIN_SIZE, IN_SIZE, OUT_SIZE);
    
    LOOKUP(0, false);
    HIT(0, true);
    LOOKUP(1, false);
    HIT(1, true);

    LOOKUP(2, false);
    HIT(2, true);
    HIT(1, true);
    HIT(0, false);

    LOOKUP(3, false);
    HIT(3, true);

    LOOKUP(0, false);
    HIT(0, true);
    LOOKUP(1, false);
    HIT(1, true);

    LOOKUP(4, false);
    HIT(4, true);

    LOOKUP(0, true);
    HIT(0, true);

    LOOKUP(1, true);
    HIT(1, true);
    LOOKUP(2, false);
        
    return 0;
}

#undef LOOKUP
#undef HIT
