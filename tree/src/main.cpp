
#include "tree.h"

int main()
{
    Tree<int, int> tree;
    
    tree.insert(2, 2);
    tree.insert(1, 1);
    tree.insert(3, 3);
    tree.insert(0, 0);
    tree.insert(4, 4);
    tree.remove(0);
    tree.dump();
    //tree.insert(3, 3);
    //tree.dump();
    return 0;
}
