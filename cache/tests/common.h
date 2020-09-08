
#ifndef COMMON_TEST_H
#define COMMON_TEST_H

#include <vector>

#include "../page.h"

#define TEST(expr) do\
{\
    if(!(expr))\
    {\
        std::cerr << "Test failed: in " << __FILE__ << " at line "  << __LINE__ << std::endl; \
        exit(1); \
    }\
} while(0)

std::vector<Page> generatePages(unsigned n);


#endif
