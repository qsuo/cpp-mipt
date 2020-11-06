
#ifndef RBTREE_H
#define RBTREE_H

#include <vector>
#include <iostream>

namespace tree
{

template <typename KeyT>
class RBTree
{

public:
    enum Color { RED, BLACK };

private:
    
    struct Node
    {
        Node *parent;
        Node *left;
        Node *right;
        Color color = BLACK;

        KeyT key;

        Node():
            parent(nullptr),
            left(nullptr),
            right(nullptr)
        {}
        
        Node(const KeyT &ckey): 
            parent(nullptr),
            left(nullptr),
            right(nullptr),
            color(RED),
            key(ckey)       
        {}

        Node(Node *cparent, Node *cleft, Node *cright, Color ccolor, const KeyT &ckey):
            parent(cparent),
            left(cleft),
            right(cright),
            color(ccolor),
            key(ckey)
        {}
        

        void dumpDot() const
        {
            std::string colors = (color == RED) ? 
                                "fillcolor=red, fontcolor=black, style=filled" :
                                "fillcolor=black, fontcolor=white, style=filled";
            std::cout << key << "[label=\"" << key << "\", " << colors << "]" << std::endl;
        }
    };

public:
    
    RBTree(): NodeNIL(), NIL(&NodeNIL), root_(NIL) {}
    RBTree(const RBTree &tree);
    RBTree &operator=(const RBTree &tree);
    ~RBTree();
    
    const Node* insert(const KeyT &key);
    const Node* find(const KeyT &key) const;
    void remove(const KeyT &key);
    
    Node* lowerBound(const KeyT &key) const;
    size_t rangeQuery(const KeyT &low, const KeyT &high) const;

    std::vector<KeyT> getSorted() const;
    
    const Node* root() const { return root_; }

    void dumpDot() const;

private:

    void rotateLeft(Node *node);
    void rotateRight(Node *node);

    Node* next(Node *node) const;

    void fixInsert(Node *node);
    void fixRemove(Node *x);

    void deleteTree(Node *root);
    Node* copyTree(const Node *_NIL, Node *root);
    void dumpTreeDot(Node *root) const;
   
    
    Node NodeNIL;
    Node *NIL;
    Node *root_;
};

template <typename KeyT>
void RBTree<KeyT>::deleteTree(Node *root)
{
    if(root == NIL)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

template <typename KeyT>
RBTree<KeyT>::~RBTree()
{
    deleteTree(root_);
}


template <typename KeyT>
typename RBTree<KeyT>::Node* RBTree<KeyT>::copyTree(const Node *_NIL, Node *root)
{
    Node *newNode = NIL;
    if(root != _NIL)
    {
        newNode = new Node(root->key);
        newNode->color = root->color;
        newNode->left = copyTree(_NIL, root->left);
        newNode->right = copyTree(_NIL, root->right);
    }
    return newNode;
}

template <typename KeyT>
RBTree<KeyT>::RBTree(const RBTree &tree)
{
    root_ = copyTree(tree.NIL, tree.root_);
}

template <typename KeyT>
RBTree<KeyT> &RBTree<KeyT>::operator=(const RBTree &tree)
{
    if(this == &tree)
        return *this;

    deleteTree(root_);
    root_ = copyTree(tree.NIL, tree.root_);
    return *this;
}

template <typename KeyT>
void RBTree<KeyT>::rotateLeft(Node *node)
{
    auto rightChild = node->right;
    auto parent = node->parent;
    node->right = rightChild->left;

    if(rightChild->left != NIL)
        rightChild->left->parent = node;

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
void RBTree<KeyT>::rotateRight(Node *node)
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
void RBTree<KeyT>::fixInsert(Node *node)
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
const typename RBTree<KeyT>::Node* RBTree<KeyT>::insert(const KeyT &key)
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
const typename RBTree<KeyT>::Node* RBTree<KeyT>::find(const KeyT &key) const
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
typename RBTree<KeyT>::Node* RBTree<KeyT>::lowerBound(const KeyT &key) const
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
size_t RBTree<KeyT>::rangeQuery(const KeyT &low, const KeyT &high) const
{
    size_t count = 0;
    auto lower = lowerBound(low);
    auto higher = lowerBound(high);
    
    for(auto it = lower, end = next(higher); it != end; it = next(it))
        count++;
     
    if(lower == nullptr || higher == nullptr)
        return count;
    if(high < higher->key) 
        count--;
    return count;
}

template <typename KeyT>
typename RBTree<KeyT>::Node* RBTree<KeyT>::next(Node *node) const
{
    if(node == nullptr || node == NIL)
        return  nullptr;
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
void RBTree<KeyT>::fixRemove(Node *node)
{
    while(node != root_ && node->color == BLACK)
    {
        if(node == node->parent->left)
        {
            auto *uncle = node->parent->right;
            if(uncle->color == RED)
            {
                uncle->color = BLACK;
                node->parent->color = RED;
                rotateLeft(node->parent);
                uncle = node->parent->right;
            }

            if(uncle->left->color == BLACK && uncle->right->color == BLACK)
            {
                uncle->color = RED;
                node = node->parent;
            }
            else
            {
                if(uncle->right->color == BLACK)
                {
                    uncle->left->color = BLACK;
                    uncle->color = RED;
                    rotateRight(uncle);
                    uncle = node->parent->right;
                }
                uncle->color = node->parent->color;
                node->parent->color = BLACK;
                uncle->right->color = BLACK;
                rotateLeft (node->parent);
                node = root_;
            }
        }

        else
        {
            Node *uncle = node->parent->left;
            if(uncle->color == RED)
            {
                uncle->color = BLACK;
                node->parent->color = RED;
                rotateRight (node->parent);
                uncle = node->parent->left;
            }
            if(uncle->right->color == BLACK && uncle->left->color == BLACK) 
            {
                uncle->color = RED;
                node = node->parent;
            } 
            else
            {
                if(uncle->left->color == BLACK)
                {
                    uncle->right->color = BLACK;
                    uncle->color = RED;
                    rotateLeft (uncle);
                    uncle = node->parent->left;
                }
                uncle->color = node->parent->color;
                node->parent->color = BLACK;
                uncle->left->color = BLACK;
                rotateRight (node->parent);
                node = root_;
            }
        }
    }
    node->color = BLACK;
}

template <typename KeyT>
void RBTree<KeyT>::remove(const KeyT &key)
{
    Node *pivot, *dnode;
    auto node = const_cast<Node*>(find(key)); 
    if(node == NIL)
        return;

    if(node == nullptr || node == NIL)
        return;

    if(node->left == NIL || node->right == NIL)
    {
        dnode = node;
    }
    else
    {
        dnode = node->right;
        while(dnode->left != NIL)
            dnode = dnode->left;
    }
    
    if(dnode->left != NIL)
        pivot = dnode->left;
    else
        pivot = dnode->right;

    pivot->parent = dnode->parent;
    if(dnode->parent != nullptr)
    {
        if(dnode == dnode->parent->left)
            dnode->parent->left = pivot;
        else
            dnode->parent->right = pivot;
    }
    else
    {
        root_ = pivot;
    }

    if(dnode != node)
        node->key = dnode->key;
    if(dnode->color == BLACK)
        fixRemove(pivot);

    delete dnode;
}


template <typename KeyT>
std::vector<KeyT> RBTree<KeyT>::getSorted() const
{
    std::vector<KeyT> sorted;

    auto min = root_;
    while(min->left != NIL)
        min = min->left;

    for(auto i = min; i != nullptr; i = next(i))
        sorted.push_back(i->key);
    return sorted;
}

template <typename KeyT>
void RBTree<KeyT>::dumpTreeDot(Node *root) const
{
    if(root == NIL)
        return;
    
    root->dumpDot();
    if(root->left != NIL)
    {
        std::cout << root->key << " -> " << root->left->key << std::endl;
        dumpTreeDot(root->left);
    }
    if(root->right != NIL)
    {
        std::cout << root->key << " -> " << root->right->key << std::endl;
        dumpTreeDot(root->right);
    }

    if(root->left == NIL || root->right == NIL) 
    {
        std::cout << root->key << " -> " << "nil" << std::endl;
        return;
    }

}

template <typename KeyT>
void RBTree<KeyT>::dumpDot() const
{
    std::cout << "digraph tree\n{" << std::endl; 

    std::cout << "nil[fillcolor=black, fontcolor=white, style=filled]" ;
    if(root_ == NIL)
        std::cout << "nil" << std::endl;
    dumpTreeDot(root_);
    std::cout << "}" << std::endl;
}

}// namespace tree


#endif
