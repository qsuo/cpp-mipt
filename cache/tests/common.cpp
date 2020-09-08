
#include "common.h"


std::vector<Page> generatePages(unsigned n)
{
    std::vector<Page> pages;
    for(unsigned i = 0; i < n + 1; i++)
        pages.push_back({(Page::Id)i, 0, NULL});
 
    return pages;
}
