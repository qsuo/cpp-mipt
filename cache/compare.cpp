
#include <iostream>
#include <vector>
#include <fstream>


#include "cache/2q_cache.h"
#include "cache/lru_cache.h"

std::vector<size_t> getKeys(const char *name)
{
    std::vector<size_t> keys;
    std::ifstream file(name);
    if(!file.is_open())
    {
        std::cerr << "Cannot open input file: " << name << std::endl;
        exit(1);
    }
    size_t key = 0;
    while(file >> key)
        keys.push_back(key);
    return keys;
}

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        std::cerr << "Give file with keys sequence" << std::endl;
        exit(1);
    }
    
    auto keys = getKeys(argv[1]);
    
    const size_t cache_size = 1000;
    
    LRU<size_t, size_t> lru(cache_size);
    Cache2Q<size_t, size_t> dq(cache_size);
    
    size_t lru_hits = 0;
    size_t dq_hits = 0;
    for(auto key : keys)
    {
        lru_hits += static_cast<size_t>(lru.lookup(key, key));
        dq_hits += static_cast<size_t>(dq.lookup(key, key));
    }

    std::cout << "2q: " << dq_hits * 100 / keys.size() << "%" << std::endl;
    std::cout << "lru: " << lru_hits * 100 / keys.size() << "%" << std::endl;
    
    return 0;
}
