#ifndef TREAP_HPP
#define TREAP_HPP

#include <cstddef>
#include <iostream>
#include <SFML/Graphics.hpp>

class Treap {
public:

    struct Node
    {
        int key;
        int priority;
        Node* left;
        Node* right;
    };

    //Default constructor for the treap
    Treap();

    // delete the treap
    ~Treap();

    //deletes all nodes from treap
    void clear();

    //searches through treap and returns node when found, if not found throw exception for now
    Node* search(Node* root, int key);

    //searches through treap and returns parent of node when found
    Node* parentSearch(Node* root, int key);

    //inserts new node into treap
    Node* insert(Node* root, int key);

    //removes node with key from treap
    Node* remove(Node* root, int key);

    //rotates the treap right at given root
    Node* rotateR(Node* root);

    //rotates the treap left at given root
    Node* rotateL(Node* root);

    //rotates the treap right, but finds the node to rotate based on key
    Treap::Node* justRotateR(Node* root, int key);

    //rotates the treap left, but finds the node to rotate based on key
    Treap::Node* justRotateL(Node* root, int key);

    //creates a new node with given key
    Node* newNode(int key);

    //prints treap to console for debugging
    void inOrder(Node* root);

    //initial root node
    Node* root = nullptr;

private:
    std::vector<int> keys;
    

};


#endif // TREAP_HPP