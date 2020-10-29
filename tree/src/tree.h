
#ifndef TREE_H
#define TREE_H

#include <iostream>

template <typename KeyT>
class Tree
{

public:
    enum Color { RED, BLACK };
    
    struct Node
    {
        Node *parent;
        Node *left;
        Node *right;
        Color color = BLACK;

        KeyT key;

        explicit Node(): parent(nullptr), left(nullptr), right(nullptr) {}
        Node(const KeyT &ckey): key(ckey) {}
        Node(Node *cparent, Node *cleft, Node *cright, Color ccolor, const KeyT &ckey):
            parent(cparent), left(cleft), right(cright), color(ccolor), key(ckey) {}

        void dump() const
        {
            std::string colors = (color == RED) ? 
                                "fillcolor=red, fontcolor=black, style=filled" :
                                "fillcolor=black, fontcolor=white, style=filled";
            std::cout << key << "[label=\"" << key << "\", " << colors << "]" << std::endl;
        }
    };

public:

    ~Tree();
    
    const Node* insert(const KeyT &key);
    const Node* find(const KeyT &key) const;
    void remove(const KeyT &key);
    
    void dump() const;
       
    Node* lowerBound(const KeyT &key) const;

    size_t rangeQuery(const KeyT &low, const KeyT &high) const;

private:

    void rotateLeft(Node *node);
    void rotateRight(Node *node);

    Node* next(Node *node) const;

    void fixInsert(Node *node);
    void fixRemove(Node *x);

    void deleteTree(Node *root);
    
    void dumpTree(Node *root) const;

    Node NodeNIL;
    Node * const NIL = &NodeNIL;
    Node *root_ = NIL;
};

template <typename KeyT>
void Tree<KeyT>::deleteTree(Node *root)
{
    if(root == NIL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    
    delete root;
}

template <typename KeyT>
Tree<KeyT>::~Tree()
{
    deleteTree(root_); 
}

template <typename KeyT>
void Tree<KeyT>::rotateLeft(Node *node)
{
    auto rightChild = node->right;
    auto parent = node->parent;
    node->right = rightChild->left;

    if(rightChild->left != NIL)
    {
        rightChild->left->parent = node;
    }
    if(rightChild != NIL)
        rightChild->parent = parent;

    if(node != root_)
    {
        if(parent->left == node)
            parent->left = rightChild;
        else
            parent->right = rightChild;
    }
    else
    {
        root_ = rightChild;
    }

    rightChild->left = node;
    if(node != NIL)
        node->parent = rightChild;
}

template <typename KeyT>
void Tree<KeyT>::rotateRight(Node *node)
{
    auto leftChild = node->left;
    auto parent = node->parent;
    node->left = leftChild->right;

    if(leftChild->right != NIL)
        leftChild->right->parent = node;
    if(leftChild != NIL)
        leftChild->parent = parent;

    if(node != root_)
    {
        if(parent->right == node)
            parent->right = leftChild;
        else
            parent->left = leftChild;
    }
    else
    {
        root_ = leftChild;
    }

    leftChild->right = node;
    if(node != NIL)
        node->parent = leftChild;
}

template <typename KeyT>
void Tree<KeyT>::fixInsert(Node *node)
{
    if(node == root_)
    {
        node->color = BLACK;
        return;
    }
    while(node != root_ && node->parent->color == RED)
    {
        auto grand = node->parent->parent;
        auto parent = node->parent;

        if(grand->left == parent)
        {
            auto uncle = node->parent->parent->right;
            if(uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;
                node = grand;
            }
            else
            {
                if(parent->right == node)
                {
                    node = parent;
                    rotateLeft(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateRight(node->parent->parent);
            }
        }
        else
        {
            auto uncle = node->parent->parent->left;
            if(uncle->color == RED)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = RED;
                node = grand;
            }
            else
            {
                if(parent->left == node)
                {
                    node = parent;
                    rotateRight(node);
                }
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rotateLeft(node->parent->parent);

            }
        }
    }
    root_->color = BLACK;
}

template <typename KeyT>
const typename Tree<KeyT>::Node* Tree<KeyT>::insert(const KeyT &key)
{
    Node *current = root_;
    Node *parent = nullptr;
    while(current != NIL)
    {
        if(key == current->key)
            return current;
        parent = current;
        current = (key < current->key) ? current->left : current->right;
    }

    Node *node = new Node(parent, NIL, NIL, RED, key);

    if(parent != nullptr)
    {
        if(key < parent->key)
            parent->left = node;
        else
            parent->right = node;
    }
    else
    {
        root_ = node;
    }

    fixInsert(node);
    return node;
}


template <typename KeyT>
const typename Tree<KeyT>::Node* Tree<KeyT>::find(const KeyT &key) const
{
    Node *current = root_;
    while(current != NIL)
    {
        if(key == current->key)
            return current;
        else
            current = (key < current->key) ? current->left : current->right;
    }
    return nullptr;
}

template <typename KeyT>
typename Tree<KeyT>::Node* Tree<KeyT>::lowerBound(const KeyT &key) const
{
    Node *current = root_;
    Node *parent = nullptr;
    while(current != NIL)
    {
        if(current->key == key)
            return current;
        parent = current;
        current = (key < current->key) ? current->left : current->right;
    }
    if(parent->key > key)
        return parent;
    else
        return next(parent);
}

template <typename KeyT>
size_t Tree<KeyT>::rangeQuery(const KeyT &low, const KeyT &high) const
{
    size_t count = 0;
    auto lower = lowerBound(low);
    auto higher = lowerBound(high);
    
    for(auto it = lower; it != higher; it = next(it))
        count++;
    
    if(lower->key == low)
        count--;
    return count;
}

template <typename KeyT>
typename Tree<KeyT>::Node* Tree<KeyT>::next(Node *node) const
{
    if(node->right != NIL)
    {
        node = node->right;
        while(node->left != NIL)
            node = node->left;
        return node;
    }
    if(node == root_)
        return nullptr;

    while(node->parent->left != node)
    {
        node = node->parent;
        if(node == root_)
            return nullptr;
    }
    return node->parent;

}


template <typename KeyT>
void Tree<KeyT>::fixRemove(Node *x)
{
    while(x != root_ && x->color == BLACK)
    {
        if(x == x->parent->left)
        {
            Node *w = x->parent->right;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateLeft (x->parent);
                w = x->parent->right;
            }
            if(w->left->color == BLACK && w->right->color == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if(w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    rotateRight (w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                rotateLeft (x->parent);
                x = root_;
            }
        } 
        else
        {
            Node *w = x->parent->left;
            if(w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                rotateRight (x->parent);
                w = x->parent->left;
            }
            if(w->right->color == BLACK && w->left->color == BLACK) 
            {
                w->color = RED;
                x = x->parent;
            } 
            else
            {
                if(w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    rotateLeft (w);
                    w = x->parent->left;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                rotateRight (x->parent);
                x = root_;
            }
        }
    }
    x->color = BLACK;
}

template <typename KeyT>
void Tree<KeyT>::remove(const KeyT &key)
{
    if(root_ == NIL)
        return;
    
    auto node = const_cast<Node*>(find(key)); 
    if(node == NIL)
        return;

    auto parent = node->parent;

    if(node->left == NIL && node->right == NIL)
    {
        if(parent->left == node)
            parent->left = NIL;
        if(parent->right == node)
            parent->right = NIL;
    }

    if(node->left == NIL && node->right != NIL)
    {
        if(parent->left == node)
            parent->left = node->right;
        if(parent->right == node)
            parent->right = node->right;
        node->right->parent = parent;

    }
    
    if(node->left != NIL && node->right == NIL)
    {
        if(parent->left == node)
            parent->left = node->left;
        if(parent->right == node)
            parent->right = node->left;
        node->left->parent = parent;

    }
   
    Node *next = nullptr;
    if(node->left != NIL && node->right != NIL)
    {
        next = node->right;
        while(next->left != NIL) 
            next = next->left;
    
        if(next->parent->left == next)
        {
            next->parent->left = next->right;
            if(next->right != NIL)
                next->right->parent = next->parent;
        }
        else
        {
            next->parent->right = next->left;
            if(next->left != NIL)
                next->right->parent = next->parent;
        }
        next->parent = node->parent;
        next->left = node->left;
        next->right = node->right;
        if(node == root_)
            root_ = next;
        //if(next->color == BLACK)
        //    fixRemove(node);
    }
    
    delete node;
    
    /*    
    Node *x, *y;


    auto node = const_cast<Node*>(find(key)); 
    if(node == NIL)
        return;

    if(!node || node == NIL) return;


    if(node->left == NIL || node->right == NIL)
    {
        y = node;
    }
    else
    {
        y = node->right;
        while(y->left != NIL) y = y->left;
    }

    if (y->left != NIL)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;
    if (y->parent)
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    else
        root_ = x;

    if (y != node) node->key = y->key;


    if (y->color == BLACK)
        fixRemove(x);
    */
}

template <typename KeyT>
void Tree<KeyT>::dumpTree(Node *root) const
{
    if(root == NIL)
        return;
    
    root->dump();
    if(root->left != NIL)
    {
        std::cout << root->key << " -> " << root->left->key << std::endl;
        dumpTree(root->left);
    }
    if(root->right != NIL)
    {
        std::cout << root->key << " -> " << root->right->key << std::endl;
        dumpTree(root->right);
    }

    if(root->left == NIL || root->right == NIL) 
    {
        std::cout << root->key << " -> " << "nil" << std::endl;
        return;
    }

}

template <typename KeyT>
void Tree<KeyT>::dump() const
{
    std::cout << "digraph tree\n{" << std::endl; 

    std::cout << "nil[fillcolor=black, fontcolor=white, style=filled]" ;
    if(root_ == NIL)
        std::cout << "nil" << std::endl;
    dumpTree(root_);
    std::cout << "}" << std::endl;
}




#endif
