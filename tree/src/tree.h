
#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <string>
#include <stack>
#include <cassert>

#define DEBUG

enum Color { RED, BLACK };

struct NodeNIL
{
    Color color = BLACK;
};

template <typename T, typename KeyT>
struct Node
{
    Node *parent = nullptr;
    Node *left = nullptr;
    Node *right = nullptr;
    Color color = BLACK;

    T data;
    KeyT key;

    Node(T &cdata, KeyT &ckey): data(cdata), key(ckey) {}

#ifdef DEBUG
    void dump() const
    {
        //std::cout << key << "[label=\"data=" << data << "\\n" << "key=" << key << "\"]" << std::endl;
        std::cout << key << "[label=\"" << key << "\"]" << std::endl;
    }
#endif
};

//const Node<int, int> NIL = { nullptr, nullptr, nullptr };

template <typename T, typename KeyT>
class Tree
{

public:

    using NodeT = Node<T, KeyT>;

    ~Tree();
    
    NodeT* insert(T, KeyT);
    Node<T, KeyT>* find(KeyT key) const;
    void remove(KeyT key);


#ifdef DEBUG
    void dump() const;
#endif


private:
    Node<T, KeyT> * const NIL = nullptr;
    Node<T, KeyT> *root_ = NIL;

    void deleteTree(NodeT *root);
#ifdef DEBUG    
    void dumpTree(Node<T, KeyT> *root) const;
#endif

};

template <typename T, typename KeyT>
void Tree<T, KeyT>::deleteTree(NodeT *root)
{
    if(root == NIL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    
    //std::cerr << "Delete node:" << root->key << std::endl;
    delete root;
}

template <typename T, typename KeyT>
Tree<T, KeyT>::~Tree()
{
    deleteTree(root_); 
}

template <typename T, typename KeyT>
Node<T, KeyT>* Tree<T, KeyT>::insert(T data, KeyT key)
{
    NodeT *current = root_;
    NodeT *parent = nullptr;
    while(current != NIL)
    {
        if(key == current->key)
            return current;
        parent = current;
        current = (key < current->key) ? current->left : current->right;
    }

    NodeT *node = new NodeT(data, key);
    node->parent = parent;
    node->left = NIL;
    node->right = NIL;
    node->color = RED;

    if(parent != nullptr)
    {
        if(key < parent->key)
            parent->left = node;
        else
            parent->right = node;
    }
    else
        root_ = node;
    return node;
}

template <typename T, typename KeyT>
Node<T, KeyT>* Tree<T, KeyT>::find(KeyT key) const
{
    NodeT *current = root_;
    while(current != NIL)
    {
        if(key == current->key)
            return current;
        else
            current = (key < current->key) ? current->left : current->right;
    }
    return nullptr;
}

template <typename T, typename KeyT>
void Tree<T, KeyT>::remove(KeyT key)
{
    auto node = find(key); 
    if(node == NIL)
        return;

    NodeT *x = nullptr;
    NodeT *y = nullptr;

    if(node->left == NIL || node->right == NIL)
    {
        y = node;
    }
    else
    {
        y = node->right;
        while(y->left != NIL)
            y = y->left;
    }

    if(y->left == NIL && y->right == NIL)
    {
        if(y->parent->left == y)
            y->parent->left = NIL;

        if(y->parent->right == y)
            y->parent->right = NIL;
        delete y;
        return;
    }

    if(y->left != NIL)
        x = y->left;
    else
        x = y->right;

    x->parent = y->parent;
    if(y->parent)
    {
        if(y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }
    else
        root_ = x;

    if(y != node)
    {
        node->data = y->data;
        node->key = y->key;
    }

    delete y;

}


#ifdef DEBUG
template <typename T, typename KeyT>
void Tree<T, KeyT>::dumpTree(NodeT *root) const
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

    if(root->left == NIL)
    {
        std::cout << root->key << " -> " << "nil" << std::endl;
        return;
    }
    if(root->right == NIL)
    {
        std::cout << root->key << " -> " << "nil" << std::endl;
        return;
    }

}

template <typename T, typename KeyT>
void Tree<T, KeyT>::dump() const
{
    std::cout << "digraph tree\n{" << std::endl; 
    if(root_ == NIL)
        std::cout << "nil" << std::endl;
    dumpTree(root_);
    std::cout << "}" << std::endl;
}
#endif



#endif
