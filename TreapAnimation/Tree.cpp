#include "Tree.h"

//Constructor
Tree::Tree() {

}

//Destructor
Tree::~Tree() {

}

//setsup the tree
void Tree::Setup(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, Treap::Node* root) {
    treeroot.rootindex = nodeSearch(nodes, root->key, root->priority);
    //check if left child exists
    if (root->left != nullptr) {
        treeroot.leftindex = nodeSearch(nodes, root->left->key, root->left->priority);
        treeroot.lineleftindex = treeLineFind(lines, nodes[treeroot.rootindex], nodes[treeroot.leftindex]);
        createTreeREC(treap1, nodes, lines, root->left);
    }
    else {
        treeroot.leftindex = -1;
        treeroot.lineleftindex = -1;
    }
    if (root->right != nullptr) {
        treeroot.rightindex = nodeSearch(nodes, root->right->key, root->right->priority);
        treeroot.linerightindex = treeLineFind(lines, nodes[treeroot.rootindex], nodes[treeroot.rightindex]);
        createTreeREC(treap1, nodes, lines, root->right);
    }
    else {
        treeroot.rightindex = -1;
        treeroot.linerightindex = -1;
    }
}

//shifts the tree rooted at root by x, y
void Tree::Shift(std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, float x, float y) {
    shiftTreeNode(nodes, lines, treeroot, x, y);
    for (size_t i = 0; i < tn.size(); i++) {
        shiftTreeNode(nodes, lines, tn[i], x, y);
    }
}

//removes all tree nodes and resets treeroot
void Tree::Reset() {
    while (!tn.empty()) {
        tn.pop_back();
    }
    treeroot.rootindex = -1;
    treeroot.leftindex = -1;
    treeroot.rightindex = -1;
    treeroot.lineleftindex = -1;
    treeroot.linerightindex = -1;
}

//spaces nodes, returns true when all nodes are spaced correctly
bool Tree::Space(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, Treap::Node* root, sf::VideoMode mode) {
    int distance = 0;
    //find index of parent node to find distance
    if (root == treap1.root) {  //root is top node
        distance = mode.width / 2;
    }
    else {
        int parentindex = nodeSearch(nodes, treap1.parentSearch(treap1.root, root->key)->key, treap1.parentSearch(treap1.root, root->key)->priority);
        distance = abs(nodes[treeroot.rootindex].GetGlobalCenter().X - nodes[parentindex].GetGlobalCenter().X);
    }
    
    //check for children
    if (treeroot.leftindex != -1) { //left exists
        if (SpaceNode(nodes, lines, treeroot.rootindex, treeroot.leftindex, distance / 2, true) == false) {
            return false;
        }
    }
    if (treeroot.rightindex != -1) {
        if (SpaceNode(nodes, lines, treeroot.rootindex, treeroot.rightindex, distance / 2, false) == false) {
            return false;
        }
    }
    return true;
}

//get position
sf::Vector2f Tree::getPosition(std::vector<Node>& nodes) {
    return sf::Vector2f(nodes[treeroot.rootindex].GetGlobalCenter().X, nodes[treeroot.rootindex].GetGlobalCenter().Y);
}

//returns the index of the treeroot
int Tree::getTreeRootIndex() {
    return treeroot.rootindex;
}

///////////////////PRIVATE////////////////////////////////////////////////////////////////////////////////////////////

void Tree::createTreeREC(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, Treap::Node* root) {

    //create new treenode
    treenode A;
    A.rootindex = nodeSearch(nodes, root->key, root->priority);
    //check if left child exists
    if (root->left != nullptr) {
        A.leftindex = nodeSearch(nodes, root->left->key, root->left->priority);
        A.lineleftindex = treeLineFind(lines, nodes[A.rootindex], nodes[A.leftindex]);
        createTreeREC(treap1, nodes, lines, root->left);
    }
    else {
        A.leftindex = -1;
        A.lineleftindex = -1;
    }
    if (root->right != nullptr) {
        A.rightindex = nodeSearch(nodes, root->right->key, root->right->priority);
        A.linerightindex = treeLineFind(lines, nodes[A.rootindex], nodes[A.rightindex]);
        createTreeREC(treap1, nodes, lines, root->right);
    }
    else {
        A.rightindex = -1;
        A.linerightindex = -1;
    }
    tn.push_back(A);
}

//returns the index of Node that has the given key and priority
int Tree::nodeSearch(std::vector<Node>& nodes, int key, int priority) {
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].GetKey() == key && nodes[i].GetPriority() == priority) {
            return i;
        }
    }
    return -1; //node not found
}

//returns the index of the line connecting two nodes
int Tree::treeLineFind(std::vector<sf::RectangleShape>& lines, Node root, Node child) {
    sf::RectangleShape line;

    //finds the angle between two points
    float deltaX = child.GetGlobalCenter().X - root.GetGlobalCenter().X;
    float deltaY = child.GetGlobalCenter().Y - root.GetGlobalCenter().Y;
    float angle = (atan2f(deltaY, deltaX) * 180) / 3.1415;

    float length = sqrtf((deltaX * deltaX) + (deltaY * deltaY));

    line.setFillColor(sf::Color::Black);
    line.setSize(sf::Vector2f(length - root.GetRadius() * 2, root.GetOutlineSize()));
    line.setOrigin((length / 2) - root.GetRadius(), root.GetOutlineSize() / 2);

    float middleY = root.GetGlobalCenter().Y + deltaY / 2;
    float middleX = root.GetGlobalCenter().X + deltaX / 2;

    line.setPosition(sf::Vector2f(middleX, middleY));
    line.setRotation(angle);

    for (size_t i = 0; i < lines.size(); i++) {
        int l1x = lines[i].getPosition().x;
        int l1y = lines[i].getPosition().y;
        int l2x = line.getPosition().x;
        int l2y = line.getPosition().y;
        if ((l2x - 10 <= l1x && l1x <= l2x + 10) && l1y == l2y) {       //not checking x becuase it gets messed up a bit with the recursive functions, Y should just be good enough
            return i;
        }
    }
    return -1;
}

//moves an individual node
void Tree::shiftTreeNode(std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, treenode A, float x, float y) {
    nodes[A.rootindex].Move(nodes[A.rootindex].GetGlobalCenter().X + x, nodes[A.rootindex].GetGlobalCenter().Y + y);
    if (A.lineleftindex != -1) {
        lines[A.lineleftindex].setPosition(lines[A.lineleftindex].getPosition().x + x, lines[A.lineleftindex].getPosition().y + y);
    }
    if (A.linerightindex != -1) {
        lines[A.linerightindex].setPosition(lines[A.linerightindex].getPosition().x + x, lines[A.linerightindex].getPosition().y + y);
    }
}

//recursive function to help space nodes
bool Tree::SpaceNode(std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, int parentindex, int rootindex, int distance, bool leftnode) {
    treenode x = findTreeNode(rootindex);
    bool inposition = false;
    //see if root is left child
    if (leftnode) {
        int rootX = nodes[rootindex].GetGlobalCenter().X;
        int goalX = nodes[parentindex].GetGlobalCenter().X - distance;
        if (rootX != goalX) {   //needs to shift
            float shiftx = 0;
            if (rootX > goalX) {
                shiftx = nodes[rootindex].GetGlobalCenter().X - (distance / 2) / 100.f;
            }
            else {
                shiftx = nodes[rootindex].GetGlobalCenter().X + (distance / 2) / 100.f;
            }
            int lineindex = treeLineFind(lines, nodes[parentindex], nodes[rootindex]);  //this must happen before node is shifted or else the line wont be found
            nodes[rootindex].Move(shiftx, nodes[rootindex].GetGlobalCenter().Y);
            moveLine(nodes, lines, lineindex, rootindex, parentindex);
        }
        else {
            inposition = true;
        }
    }
    else {  //root is right child of parent
        int rootX = nodes[rootindex].GetGlobalCenter().X;
        int goalX = nodes[parentindex].GetGlobalCenter().X + distance;
        if (rootX != goalX) {   //needs to shift
            float shiftx = 0;
            if (rootX > goalX) {
                shiftx = nodes[rootindex].GetGlobalCenter().X - (distance / 2) / 100.f;
            }
            else {
                shiftx = nodes[rootindex].GetGlobalCenter().X + (distance / 2) / 100.f;
            }
            int lineindex = treeLineFind(lines, nodes[parentindex], nodes[rootindex]);  //this must happen before node is shifted or else the line wont be found
            nodes[rootindex].Move(shiftx, nodes[rootindex].GetGlobalCenter().Y);
            moveLine(nodes, lines, lineindex, rootindex, parentindex);
        }
        else {
            inposition = true;
        }
    }
    //check for children
    bool childrentrue = true;
    if (x.leftindex != -1) { //left exists
        if (!SpaceNode(nodes, lines, rootindex, x.leftindex, distance / 2, true)) {
            childrentrue = false;
        }
        
    }
    if (x.rightindex != -1) {
        if (!SpaceNode(nodes, lines, rootindex, x.rightindex, distance / 2, false)) {
            childrentrue = false;
        }
    }
    //node has no children
    if (inposition == true && childrentrue == true) {
        return true;
    }
    else {
        return false;
    }
}

//returns the treenode of the given index
Tree::treenode Tree::findTreeNode(int index) {
    for (size_t i = 0; i < tn.size(); i++) {
        if (tn[i].rootindex == index) {
            return tn[i];
        }
    }
    //gonna throw an error here, if not found
}

//moves the line between the two nodes
void Tree::moveLine(std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, int lineindex, int childindex, int rootindex) {
    float rx = nodes[rootindex].GetGlobalCenter().X;
    float ry = nodes[rootindex].GetGlobalCenter().Y;
    float cx = nodes[childindex].GetGlobalCenter().X;
    float cy = nodes[childindex].GetGlobalCenter().Y;

    float deltaX = cx - rx;
    float deltaY = cy - ry;
    float angle = (atan2f(deltaY, deltaX) * 180) / 3.1415;

    float length = sqrtf((deltaX * deltaX) + (deltaY * deltaY));

    lines[lineindex].setSize(sf::Vector2f(length - nodes[rootindex].GetRadius() * 2, nodes[rootindex].GetOutlineSize()));
    lines[lineindex].setOrigin((length / 2) - nodes[rootindex].GetRadius(), nodes[rootindex].GetOutlineSize() / 2);

    float middleY = nodes[rootindex].GetGlobalCenter().Y + deltaY / 2;
    float middleX = nodes[rootindex].GetGlobalCenter().X + deltaX / 2;

    lines[lineindex].setPosition(sf::Vector2f(middleX, middleY));
    lines[lineindex].setRotation(angle);

}
