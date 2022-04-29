#ifndef TREE_HPP
#define TREE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Node.h"
#include "Treap.h"

class Tree {
public:

    struct treenode
    {
        int rootindex;
        int leftindex;
        int rightindex;
        int linerightindex;
        int lineleftindex;
    };

    //Constructor
    Tree();

    //Destructor
    ~Tree();

    //setsup the tree
    void Setup(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, Treap::Node* root);

    //moves the tree centerd at root node to by x, y
    void Shift(std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, float x, float y);

    //removes all tree nodes and resets treeroot
    void Reset();

    //spaces nodes, returns true when all nodes are spaced correctly
    bool Space(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, Treap::Node* root, sf::VideoMode mode);

    //get position
    sf::Vector2f getPosition(std::vector<Node>& nodes);

    //returns the index of the treeroot
    int getTreeRootIndex();


private:
    treenode treeroot;
    std::vector<treenode> tn;

    //recursive function to help set up tree
    void createTreeREC(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, Treap::Node* root);

    //returns the index of Node that has the given key and priority
    int nodeSearch(std::vector<Node>& nodes, int key, int priority);

    //returns the index of the line connecting two nodes
    int treeLineFind(std::vector<sf::RectangleShape>& lines, Node root, Node child);

    //moves an individual node
    void shiftTreeNode(std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, treenode A, float x, float y);

    //recursive function to help space nodes
    bool SpaceNode(std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, int parentindex, int rootindex, int distance, bool leftnode);

    //returns the treenode of the given index
    treenode findTreeNode(int index);

    //moves the line between the two nodes
    void moveLine(std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, int lineindex, int childindex, int rootindex);
};


#endif // BUTTON_HPP
