
#ifndef PAGE_H
#define PAGE_H

struct Page 
{
    typedef unsigned Id;

    Id id;
    size_t size;
    char *data;

};

struct PageId
{
    typedef unsigned Id;
    Id id;
};



#endif
