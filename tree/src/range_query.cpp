
#include "rbtree.h"
#include "tree.h"
#include "range_query.h"

#include <fstream>
#include <streambuf>
#include <sstream>
#include <cassert>

#define CHECK(stream, what, input, _msg)            \
    if(stream.what())                               \
        do                                          \
        {                                           \
            input.msg = _msg;                       \
            return input;                           \
        }                                           \
        while(0)                                    \


namespace
{

struct Request
{
    int low;
    int high;
};

struct Input
{
    int nkeys;
    std::vector<int> keys;

    int nrequests;
    std::vector<Request> request;
    
    std::string msg;
};

Input parse(std::istream &in)
{
    Input input;
    std::string instr;
    
    while(instr.empty())
        std::getline(in, instr);

    std::stringstream raw(instr);

    raw >> input.nkeys;
    CHECK(raw, fail, input, "INVALID");
  
    if(input.nkeys < 0)
    {   
        input.msg = "INVALID NKEYS";
        return input;
    } 

    for(int i = 0; i < input.nkeys && !raw.eof(); i++)
    {
        int key = 0;
        raw >> key;
        CHECK(raw, fail, input, "INVALID");
        input.keys.push_back(key);
    }
    CHECK(raw, eof, input, "EOF");
    assert(static_cast<size_t>(input.nkeys) == input.keys.size());

    raw >> input.nrequests;
    CHECK(raw, fail, input, "INVALID");
    
    if(input.nrequests < 0)
    {   
        input.msg = "INVALID NREQUESTS";
        return input;
    }

    int i = 0;
    for(i = 0; i < input.nrequests && !raw.eof(); i++)
    {
        int low = 0;
        int high  = 0;
        
        raw >> low;
        CHECK(raw, fail, input, "INVALID");
        CHECK(raw, eof, input, "EOF");

        raw >> high;
        CHECK(raw, fail, input, "INVALID");
        if(low > high)
        {
            input.msg = "INVALID REQUEST";
            return input;
        }

        Request request = { low, high };
        input.request.push_back(request);
    }


    if(i != input.nrequests)
        input.msg = "EOF";
    
    return input;
}

}// namespace

namespace query
{

int range_query(std::istream &in, std::ostream &out)
{
    tree::RBTree<int> tree;
    auto input = parse(in);
    
    if(!input.msg.empty())
    {
        out << input.msg;
        return -1;
    }
    
    for(auto key : input.keys)
        tree.insert(key);

    for(auto request : input.request)
        out << tree.rangeQuery(request.low, request.high) << " ";
    return 0;
}

}//namespace query
