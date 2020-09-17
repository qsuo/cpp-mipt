
#include <iostream>

#include "cache/2q_cache.h"

int main()
{
    size_t size = 0;
    size_t nkeys = 0;
    std::cin >> size >> nkeys;

    Cache2Q<size_t, size_t> cache(size);

    size_t hits = 0;
    for(size_t i = 0; i < nkeys; i++)
    {
        size_t key = 0;
        std::cin >> key;
        if(cache.lookup(key, key))
            hits++;
    }
    std::cout << "Hits: " << hits << std::endl;
    
    return 0;
}
