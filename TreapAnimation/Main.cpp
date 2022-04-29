#include <SFML/Graphics.hpp>
#include "Treap.h"
#include "Node.h"
#include "Button.h"
#include "Tree.h"

//Colors
sf::Color white(255, 255, 255);
sf::Color maroon(134, 31, 65);
sf::Color orange(232, 119, 34);
sf::Color burntorange(198, 70, 0);
sf::Color stone(117, 120, 123);
sf::Color black(0, 0, 0);

struct removeAnimationVars
{
    bool removeAnimation = false;
    bool searchpart = true;
    float removedNodeX = 0.f;
    float removedNodeY = 0.f;
    float shiftX = 0.f;
    float shiftY = 0.f;
    bool nodeRemoved = false;
    Tree tree;
    bool needSpace = false;
    bool removeAgain = false;
};

struct spaceNodeVars
{
    bool varSet = false;
    int targetX = 0;
    int targetY = 0;
    int shiftX = 0;
    int shiftY = 0;
};

struct rotateRightVars
{
    bool goalsSet = false;
    float xGoalX = -1.f;
    float xGoalY = -1.f;
    float yGoalX = -1.f;
    float yGoalY = -1.f;
    float t1GoalX = -1.f;
    float t1GoalY = -1.f;
    float t2GoalX = -1.f;
    float t2GoalY = -1.f;
    float t3GoalX = -1.f;
    float t3GoalY = -1.f;
    float xShiftX = 0.f;
    float xShiftY = 0.f;
    float yShiftX = 0.f;
    float yShiftY = 0.f;
    float t1ShiftX = 0.f;
    float t1ShiftY = 0.f;
    float t2ShiftX = 0.f;
    float t2ShiftY = 0.f;
    float t3ShiftX = 0.f;
    float t3ShiftY = 0.f;
    Tree T3;
    Tree T2;
    Tree T1;
    bool xset = false;
    bool yset = false;
    bool t1set = false;
    bool t2set = false;
    bool t3set = false;
    bool t2xLineDeleted = false;
};

struct rotateLeftVars
{
    bool goalsSet = false;
    float xGoalX = -1.f;
    float xGoalY = -1.f;
    float yGoalX = -1.f;
    float yGoalY = -1.f;
    float t1GoalX = -1.f;
    float t1GoalY = -1.f;
    float t2GoalX = -1.f;
    float t2GoalY = -1.f;
    float t3GoalX = -1.f;
    float t3GoalY = -1.f;
    float xShiftX = 0.f;
    float xShiftY = 0.f;
    float yShiftX = 0.f;
    float yShiftY = 0.f;
    float t1ShiftX = 0.f;
    float t1ShiftY = 0.f;
    float t2ShiftX = 0.f;
    float t2ShiftY = 0.f;
    float t3ShiftX = 0.f;
    float t3ShiftY = 0.f;
    Tree T3;
    Tree T2;
    Tree T1;
    bool xset = false;
    bool yset = false;
    bool t1set = false;
    bool t2set = false;
    bool t3set = false;
    bool t2yLineDeleted = false;
};

//resets all variables in struct
void rRVReset(rotateRightVars& rRV) {
    rRV.goalsSet = false;
    rRV.xGoalX = -1.f;
    rRV.xGoalY = -1.f;
    rRV.yGoalX = -1.f;
    rRV.yGoalY = -1.f;
    rRV.t1GoalX = -1.f;
    rRV.t1GoalY = -1.f;
    rRV.t2GoalX = -1.f;
    rRV.t2GoalY = -1.f;
    rRV.t3GoalX = -1.f;
    rRV.t3GoalY = -1.f;
    rRV.xShiftX = 0.f;
    rRV.xShiftY = 0.f;
    rRV.yShiftX = 0.f;
    rRV.yShiftY = 0.f;
    rRV.t1ShiftX = 0.f;
    rRV.t1ShiftY = 0.f;
    rRV.t2ShiftX = 0.f;
    rRV.t2ShiftY = 0.f;
    rRV.t3ShiftX = 0.f;
    rRV.t3ShiftY = 0.f;
    rRV.T3.Reset();
    rRV.T2.Reset();
    rRV.T1.Reset();
    rRV.xset = false;
    rRV.yset = false;
    rRV.t1set = false;
    rRV.t2set = false;
    rRV.t3set = false;
    rRV.t2xLineDeleted = false;
}

//resets all variables in struct
void rLVReset(rotateLeftVars& rLV) {
    rLV.goalsSet = false;
    rLV.xGoalX = -1.f;
    rLV.xGoalY = -1.f;
    rLV.yGoalX = -1.f;
    rLV.yGoalY = -1.f;
    rLV.t1GoalX = -1.f;
    rLV.t1GoalY = -1.f;
    rLV.t2GoalX = -1.f;
    rLV.t2GoalY = -1.f;
    rLV.t3GoalX = -1.f;
    rLV.t3GoalY = -1.f;
    rLV.xShiftX = 0.f;
    rLV.xShiftY = 0.f;
    rLV.yShiftX = 0.f;
    rLV.yShiftY = 0.f;
    rLV.t1ShiftX = 0.f;
    rLV.t1ShiftY = 0.f;
    rLV.t2ShiftX = 0.f;
    rLV.t2ShiftY = 0.f;
    rLV.t3ShiftX = 0.f;
    rLV.t3ShiftY = 0.f;
    rLV.T3.Reset();
    rLV.T2.Reset();
    rLV.T1.Reset();
    rLV.xset = false;
    rLV.yset = false;
    rLV.t1set = false;
    rLV.t2set = false;
    rLV.t3set = false;
    rLV.t2yLineDeleted = false;
}

//returns the index of the line connecting two nodes
int LineFind(std::vector<sf::RectangleShape>& lines, Node root, Node child) {

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
        if (lines[i].getPosition() == line.getPosition()) {
            return i;
        }
        int x1 = lines[i].getPosition().x;
        int y1 = lines[i].getPosition().y;
        int x2 = line.getPosition().x;
        int y2 = line.getPosition().y;
        if ((x2 - 10 <= x1 && x1 <= x2 + 10) && y1 == y2) {
            return i;
        }
    }
    return -1;
}

//Draws the connecting line between two nodes
void LineDraw(std::vector<sf::RectangleShape>& lines, Node root, Node child) {
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

    lines.push_back(line);
}

//searches through node vector and return node index with key and priority
int NodeSearch(std::vector<Node>& nodes, int key, int priority) {
    for (size_t i = 0; i < nodes.size(); i++) {
        if (nodes[i].GetKey() == key && nodes[i].GetPriority() == priority) {
            return i;
        }
    }
    return -1; //node not found
}

//rotates treap right on given root
bool rotateRight(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, sf::VideoMode mode, rotateRightVars& rRV, Treap::Node* y) {
    if (!rRV.goalsSet) {    //variables need to be set

        float distance = nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().X - nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X; //x distance between y and x
        rRV.xGoalX = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X;
        rRV.xGoalY = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y;
        rRV.xShiftX = (rRV.xGoalX - nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().X) / 300.f;   //I choose 300 arbitrarily
        rRV.xShiftY = (rRV.xGoalY - nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().Y) / 300.f;
        rRV.yGoalX = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X - distance;
        rRV.yGoalY = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y + nodes[0].GetRadius() * 3;
        rRV.yShiftX = (rRV.yGoalX - nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X) / 300.f;
        rRV.yShiftY = (rRV.yGoalY - nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y) / 300.f;
        if (y->left->left != nullptr) {   //if T1 exists
            rRV.t1GoalX = nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().X;
            rRV.t1GoalY = nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().Y;
            rRV.t1ShiftX = (rRV.t1GoalX - nodes[NodeSearch(nodes, y->left->left->key, y->left->left->priority)].GetGlobalCenter().X) / 300.f;
            rRV.t1ShiftY = (rRV.t1GoalY - nodes[NodeSearch(nodes, y->left->left->key, y->left->left->priority)].GetGlobalCenter().Y) / 300.f;
            rRV.T1.Setup(treap1, nodes, lines, y->left->left);
        }
        if (y->left->right != nullptr) {   //if T2 exists
            rRV.t2GoalX = rRV.yGoalX + distance / 2;
            rRV.t2GoalY = rRV.yGoalY + nodes[0].GetRadius() * 3;
            rRV.t2ShiftX = (rRV.t2GoalX - nodes[NodeSearch(nodes, y->left->right->key, y->left->right->priority)].GetGlobalCenter().X) / 300.f;
            rRV.t2ShiftY = (rRV.t2GoalY - nodes[NodeSearch(nodes, y->left->right->key, y->left->right->priority)].GetGlobalCenter().Y) / 300.f;
            rRV.T2.Setup(treap1, nodes, lines, y->left->right);
        }
        if (y->right != nullptr) {   //if T3 exists
            rRV.t3GoalX = rRV.yGoalX - distance / 2;
            rRV.t3GoalY = rRV.yGoalY + nodes[0].GetRadius() * 3;
            rRV.t3ShiftX = (rRV.t3GoalX - nodes[NodeSearch(nodes, y->right->key, y->right->priority)].GetGlobalCenter().X) / 300.f;
            rRV.t3ShiftY = (rRV.t3GoalY - nodes[NodeSearch(nodes, y->right->key, y->right->priority)].GetGlobalCenter().Y) / 300.f;
            rRV.T3.Setup(treap1, nodes, lines, y->right);
        }
        rRV.goalsSet = true;
    }
    //moving stage

    //find lines first, move after nodes
    int lineindex_xy = LineFind(lines, nodes[NodeSearch(nodes, y->key, y->priority)], nodes[NodeSearch(nodes, y->left->key, y->left->priority)]);
    int lineindex_T1x = -1;
    int lineindex_T2x = -1;
    int lineindex_T2y = -1;
    int lineindex_T3y = -1;
    if (rRV.t1GoalX != -1.f) {   //exists
        lineindex_T1x = LineFind(lines, nodes[NodeSearch(nodes, y->left->key, y->left->priority)], nodes[rRV.T1.getTreeRootIndex()]);
    }
    if (rRV.t2GoalX != -1.f) {   //exists
        if (!rRV.t2xLineDeleted) {  //if T2 to x line exists still
            lineindex_T2x = LineFind(lines, nodes[NodeSearch(nodes, y->left->key, y->left->priority)], nodes[rRV.T2.getTreeRootIndex()]);
            lines.erase(lines.begin() + lineindex_T2x); //remove line
            LineDraw(lines, nodes[NodeSearch(nodes, y->key, y->priority)], nodes[rRV.T2.getTreeRootIndex()]);   //creates new line
            rRV.t2xLineDeleted = true;
        }
        lineindex_T2y = LineFind(lines, nodes[NodeSearch(nodes, y->key, y->priority)], nodes[rRV.T2.getTreeRootIndex()]);
    }
    if (rRV.t3GoalX != -1.f) {   //exists
        lineindex_T3y = LineFind(lines, nodes[NodeSearch(nodes, y->key, y->priority)], nodes[rRV.T3.getTreeRootIndex()]);
    }

    //x
    int x1x = rRV.xGoalX;
    int x2x = nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().X;
    int x1y = rRV.xGoalY;
    int x2y = nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().Y;
    if (x1x <= x2x && x1y >= x2y) {   //done moving
        rRV.xset = true;
    }
    else {
        //moves x
        nodes[NodeSearch(nodes, y->left->key, y->left->priority)].Move(nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().X + rRV.xShiftX, nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().Y + rRV.xShiftY);
    }

    //y
    int y1x = rRV.yGoalX;
    int y2x = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X;
    int y1y = rRV.yGoalY;
    int y2y = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y;
    if (y1x <= y2x && y1y <= y2y) {   //done moving
        rRV.yset = true;
    }
    else {
        //moves y
        nodes[NodeSearch(nodes, y->key, y->priority)].Move(nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X + rRV.yShiftX, nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y + rRV.yShiftY);
    }
    
    //T1
    if (rRV.t1GoalX != -1.f) {   //exists
        int t1x1 = rRV.t1GoalX;
        int t1x2 = rRV.T1.getPosition(nodes).x;
        int t1y1 = rRV.t1GoalY;
        int t1y2 = rRV.T1.getPosition(nodes).y;
        if (t1x1 <= t1x2 && t1y1 >= t1y2) {     //this not being == may cause sissues in the future
            rRV.t1set = true;
        }
        else {
            rRV.T1.Shift(nodes, lines, rRV.t1ShiftX, rRV.t1ShiftY);
        }
    }
    else {
        rRV.t1set = true;
    }
   
    //T2
    if (rRV.t2GoalX != -1.f) {
        int t2x1 = rRV.t2GoalX;
        int t2x2 = rRV.T2.getPosition(nodes).x;
        int t2y1 = rRV.t2GoalY;
        int t2y2 = rRV.T2.getPosition(nodes).y;
        if (t2x1 <= t2x2 && t2y1 == t2y2) {
            rRV.t2set = true;
        }
        else {
            rRV.T2.Shift(nodes, lines, rRV.t2ShiftX, rRV.t2ShiftY);
        }
    }
    else {
        rRV.t2set = true;
    }
    
    //T3
    if (rRV.t3GoalX != -1.f) {
        int t3x1 = rRV.t3GoalX;
        int t3x2 = rRV.T3.getPosition(nodes).x;
        int t3y1 = rRV.t3GoalY;
        int t3y2 = rRV.T3.getPosition(nodes).y;
        if (t3x1 <= t3x2 && t3y1 <= t3y2) {
            rRV.t3set = true;
        }
        else {
            rRV.T3.Shift(nodes, lines, rRV.t3ShiftX, rRV.t3ShiftY);
        }
    }
    else {
        rRV.t3set = true;
    }

    //move lines to new spots
    //xy
    float linexy_deltaX = nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().X - nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X;
    float linexy_deltaY = nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().Y - nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y;
    float linexy_angle = (atan2f(linexy_deltaY, linexy_deltaX) * 180) / 3.1415;
    float linexy_length = sqrtf((linexy_deltaX * linexy_deltaX) + (linexy_deltaY * linexy_deltaY));

    lines[lineindex_xy].setSize(sf::Vector2f(linexy_length - nodes[NodeSearch(nodes, y->key, y->priority)].GetRadius() * 2, nodes[NodeSearch(nodes, y->key, y->priority)].GetOutlineSize()));
    lines[lineindex_xy].setOrigin((linexy_length / 2) - nodes[NodeSearch(nodes, y->key, y->priority)].GetRadius(), nodes[NodeSearch(nodes, y->key, y->priority)].GetOutlineSize() / 2);

    float linexy_middleY = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y + linexy_deltaY / 2;
    float linexy_middleX = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X + linexy_deltaX / 2;

    lines[lineindex_xy].setPosition(sf::Vector2f(linexy_middleX, linexy_middleY));
    lines[lineindex_xy].setRotation(linexy_angle);

    //T1x
    if (lineindex_T1x != -1) {
        float lineT1x_deltaX = nodes[rRV.T1.getTreeRootIndex()].GetGlobalCenter().X - nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().X;
        float lineT1x_deltaY = nodes[rRV.T1.getTreeRootIndex()].GetGlobalCenter().Y - nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().Y;
        float lineT1x_angle = (atan2f(lineT1x_deltaY, lineT1x_deltaX) * 180) / 3.1415;
        float lineT1x_length = sqrtf((lineT1x_deltaX * lineT1x_deltaX) + (lineT1x_deltaY * lineT1x_deltaY));

        lines[lineindex_T1x].setSize(sf::Vector2f(lineT1x_length - nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetRadius() * 2, nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetOutlineSize()));
        lines[lineindex_T1x].setOrigin((lineT1x_length / 2) - nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetRadius(), nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetOutlineSize() / 2);

        float lineT1x_middleY = nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().Y + lineT1x_deltaY / 2;
        float lineT1x_middleX = nodes[NodeSearch(nodes, y->left->key, y->left->priority)].GetGlobalCenter().X + lineT1x_deltaX / 2;

        lines[lineindex_T1x].setPosition(sf::Vector2f(lineT1x_middleX, lineT1x_middleY));
        lines[lineindex_T1x].setRotation(lineT1x_angle);
    }

    //T2y
    if (lineindex_T2y != -1) {
        float lineT2y_deltaX = nodes[rRV.T2.getTreeRootIndex()].GetGlobalCenter().X - nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X;
        float lineT2y_deltaY = nodes[rRV.T2.getTreeRootIndex()].GetGlobalCenter().Y - nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y;
        float lineT2y_angle = (atan2f(lineT2y_deltaY, lineT2y_deltaX) * 180) / 3.1415;
        float lineT2y_length = sqrtf((lineT2y_deltaX * lineT2y_deltaX) + (lineT2y_deltaY * lineT2y_deltaY));

        lines[lineindex_T2y].setSize(sf::Vector2f(lineT2y_length - nodes[NodeSearch(nodes, y->key, y->priority)].GetRadius() * 2, nodes[NodeSearch(nodes, y->key, y->priority)].GetOutlineSize()));
        lines[lineindex_T2y].setOrigin((lineT2y_length / 2) - nodes[NodeSearch(nodes, y->key, y->priority)].GetRadius(), nodes[NodeSearch(nodes, y->key, y->priority)].GetOutlineSize() / 2);

        float lineT2y_middleY = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y + lineT2y_deltaY / 2;
        float lineT2y_middleX = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X + lineT2y_deltaX / 2;

        lines[lineindex_T2y].setPosition(sf::Vector2f(lineT2y_middleX, lineT2y_middleY));
        lines[lineindex_T2y].setRotation(lineT2y_angle);
    }

    //T3y
    if (lineindex_T3y != -1) {
        float lineT3y_deltaX = nodes[rRV.T3.getTreeRootIndex()].GetGlobalCenter().X - nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X;
        float lineT3y_deltaY = nodes[rRV.T3.getTreeRootIndex()].GetGlobalCenter().Y - nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y;
        float lineT3y_angle = (atan2f(lineT3y_deltaY, lineT3y_deltaX) * 180) / 3.1415;
        float lineT3y_length = sqrtf((lineT3y_deltaX * lineT3y_deltaX) + (lineT3y_deltaY * lineT3y_deltaY));

        lines[lineindex_T3y].setSize(sf::Vector2f(lineT3y_length - nodes[NodeSearch(nodes, y->key, y->priority)].GetRadius() * 2, nodes[NodeSearch(nodes, y->key, y->priority)].GetOutlineSize()));
        lines[lineindex_T3y].setOrigin((lineT3y_length / 2) - nodes[NodeSearch(nodes, y->key, y->priority)].GetRadius(), nodes[NodeSearch(nodes, y->key, y->priority)].GetOutlineSize() / 2);

        float lineT3y_middleY = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().Y + lineT3y_deltaY / 2;
        float lineT3y_middleX = nodes[NodeSearch(nodes, y->key, y->priority)].GetGlobalCenter().X + lineT3y_deltaX / 2;

        lines[lineindex_T3y].setPosition(sf::Vector2f(lineT3y_middleX, lineT3y_middleY));
        lines[lineindex_T3y].setRotation(lineT3y_angle);
    }
    
    if (rRV.t1set && rRV.t2set && rRV.t3set && rRV.xset && rRV.yset) {  //movement is complete
        return true;
    }
    else {
        return false;
    }
}

/* T1, T2 and T3 are subtrees of the tree rooted with y
  (on left side) or x (on right side)
                y                               x
               / \     Right Rotation          /  \
              x   T3   – – – – – – – >        T1   y
             / \       < - - - - - - -            / \
            T1  T2     Left Rotation            T2  T3 */

//rotates treap left on given root
bool rotateLeft(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, sf::VideoMode mode, rotateLeftVars& rLV, Treap::Node* x) {
    if (!rLV.goalsSet) {    //variables need to be set

        float distance = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().X; //x distance between y and x
        rLV.xGoalX = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X + distance;
        rLV.xGoalY = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y + nodes[0].GetRadius() * 3;
        rLV.xShiftX = (rLV.xGoalX - nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X) / 300.f;   //I choose 300 arbitrarily
        rLV.xShiftY = (rLV.xGoalY - nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y) / 300.f;
        rLV.yGoalX = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X;
        rLV.yGoalY = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y;
        rLV.yShiftX = (rLV.yGoalX - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().X) / 300.f;
        rLV.yShiftY = (rLV.yGoalY - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().Y) / 300.f;
        if (x->right->right != nullptr) {   //if T3 exists    
            rLV.t3GoalX = nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().X;
            rLV.t3GoalY = nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().Y;
            rLV.t3ShiftX = (rLV.t3GoalX - nodes[NodeSearch(nodes, x->right->right->key, x->right->right->priority)].GetGlobalCenter().X) / 300.f;
            rLV.t3ShiftY = (rLV.t3GoalY - nodes[NodeSearch(nodes, x->right->right->key, x->right->right->priority)].GetGlobalCenter().Y) / 300.f;
            rLV.T3.Setup(treap1, nodes, lines, x->right->right);
        }
        if (x->right->left != nullptr) {   //if T2 exists   --currently updating
            rLV.t2GoalX = rLV.xGoalX - distance / 2;
            rLV.t2GoalY = rLV.xGoalY + nodes[0].GetRadius() * 3;
            rLV.t2ShiftX = (rLV.t2GoalX - nodes[NodeSearch(nodes, x->right->left->key, x->right->left->priority)].GetGlobalCenter().X) / 300.f;
            rLV.t2ShiftY = (rLV.t2GoalY - nodes[NodeSearch(nodes, x->right->left->key, x->right->left->priority)].GetGlobalCenter().Y) / 300.f;
            rLV.T2.Setup(treap1, nodes, lines, x->right->left);
        }
        if (x->left != nullptr) {   //if T1 exists
            rLV.t1GoalX = rLV.xGoalX + distance / 2;
            rLV.t1GoalY = rLV.xGoalY + nodes[0].GetRadius() * 3;
            rLV.t1ShiftX = (rLV.t1GoalX - nodes[NodeSearch(nodes, x->left->key, x->left->priority)].GetGlobalCenter().X) / 300.f;
            rLV.t1ShiftY = (rLV.t1GoalY - nodes[NodeSearch(nodes, x->left->key, x->left->priority)].GetGlobalCenter().Y) / 300.f;
            rLV.T1.Setup(treap1, nodes, lines, x->left);
        }
        rLV.goalsSet = true;
    }
    //moving stage

    //find lines first, move after nodes
    int lineindex_xy = LineFind(lines, nodes[NodeSearch(nodes, x->right->key, x->right->priority)], nodes[NodeSearch(nodes, x->key, x->priority)]);
    int lineindex_T1x = -1;
    int lineindex_T2x = -1;
    int lineindex_T2y = -1;
    int lineindex_T3y = -1;
    if (rLV.t3GoalX != -1.f) {   //exists
        lineindex_T3y = LineFind(lines, nodes[NodeSearch(nodes, x->right->key, x->right->priority)], nodes[rLV.T3.getTreeRootIndex()]);
    }
    if (rLV.t2GoalX != -1.f) {   //exists
        if (!rLV.t2yLineDeleted) {  //if T2 to y line exists still
            lineindex_T2y = LineFind(lines, nodes[NodeSearch(nodes, x->right->key, x->right->priority)], nodes[rLV.T2.getTreeRootIndex()]);
            lines.erase(lines.begin() + lineindex_T2y); //remove line
            LineDraw(lines, nodes[NodeSearch(nodes, x->key, x->priority)], nodes[rLV.T2.getTreeRootIndex()]);   //creates new line
            rLV.t2yLineDeleted = true;
        }
        lineindex_T2x = LineFind(lines, nodes[NodeSearch(nodes, x->key, x->priority)], nodes[rLV.T2.getTreeRootIndex()]);
    }
    if (rLV.t1GoalX != -1.f) {   //exists
        lineindex_T1x = LineFind(lines, nodes[NodeSearch(nodes, x->key, x->priority)], nodes[rLV.T1.getTreeRootIndex()]);
    }

    //x
    int x1x = rLV.xGoalX;
    int x2x = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X;
    int x1y = rLV.xGoalY;
    int x2y = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y;
    if (x1x >= x2x && x1y <= x2y) {   //done moving
        rLV.xset = true;
    }
    else {
        //moves x
        nodes[NodeSearch(nodes, x->key, x->priority)].Move(nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X + rLV.xShiftX, nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y + rLV.xShiftY);
    }

    //y
    int y1x = rLV.yGoalX;
    int y2x = nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().X;
    int y1y = rLV.yGoalY;
    int y2y = nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().Y;
    if (y1x >= y2x && y1y >= y2y) {   //done moving
        rLV.yset = true;
    }
    else {
        //moves y
        nodes[NodeSearch(nodes, x->right->key, x->right->priority)].Move(nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().X + rLV.yShiftX, nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().Y + rLV.yShiftY);
    }

    //T3
    if (rLV.t3GoalX != -1.f) {   //exists
        int t3x1 = rLV.t3GoalX;
        int t3x2 = rLV.T3.getPosition(nodes).x;
        int t3y1 = rLV.t3GoalY;
        int t3y2 = rLV.T3.getPosition(nodes).y;
        if (t3x1 <= t3x2 && t3y1 >= t3y2) {     //this not being == may cause sissues in the future
            rLV.t3set = true;
        }
        else {
            rLV.T3.Shift(nodes, lines, rLV.t3ShiftX, rLV.t3ShiftY);
        }
    }
    else {
        rLV.t3set = true;
    }

    //T2
    if (rLV.t2GoalX != -1.f) {
        int t2x1 = rLV.t2GoalX;
        int t2x2 = rLV.T2.getPosition(nodes).x;
        int t2y1 = rLV.t2GoalY;
        int t2y2 = rLV.T2.getPosition(nodes).y;
        if (t2x1 >= t2x2 && t2y1 == t2y2) {
            rLV.t2set = true;
        }
        else {
            rLV.T2.Shift(nodes, lines, rLV.t2ShiftX, rLV.t2ShiftY);
        }
    }
    else {
        rLV.t2set = true;
    }

    //T1
    if (rLV.t1GoalX != -1.f) {
        int t1x1 = rLV.t1GoalX;
        int t1x2 = rLV.T1.getPosition(nodes).x;
        int t1y1 = rLV.t1GoalY;
        int t1y2 = rLV.T1.getPosition(nodes).y;
        if (t1x1 <= t1x2 && t1y1 <= t1y2) {
            rLV.t1set = true;
        }
        else {
            rLV.T1.Shift(nodes, lines, rLV.t1ShiftX, rLV.t1ShiftY);
        }
    }
    else {
        rLV.t1set = true;
    }

    //move lines to new spots
    //xy
    float linexy_deltaX = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().X;
    float linexy_deltaY = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().Y;
    float linexy_angle = (atan2f(linexy_deltaY, linexy_deltaX) * 180) / 3.1415;
    float linexy_length = sqrtf((linexy_deltaX * linexy_deltaX) + (linexy_deltaY * linexy_deltaY));

    lines[lineindex_xy].setSize(sf::Vector2f(linexy_length - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetRadius() * 2, nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetOutlineSize()));
    lines[lineindex_xy].setOrigin((linexy_length / 2) - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetRadius(), nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetOutlineSize() / 2);

    float linexy_middleY = nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().Y + linexy_deltaY / 2;
    float linexy_middleX = nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().X + linexy_deltaX / 2;

    lines[lineindex_xy].setPosition(sf::Vector2f(linexy_middleX, linexy_middleY));
    lines[lineindex_xy].setRotation(linexy_angle);

    //t3y
    if (lineindex_T3y != -1) {
        float linet3y_deltaX = nodes[rLV.T3.getTreeRootIndex()].GetGlobalCenter().X - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().X;
        float linet3y_deltaY = nodes[rLV.T3.getTreeRootIndex()].GetGlobalCenter().Y - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().Y;
        float linet3y_angle = (atan2f(linet3y_deltaY, linet3y_deltaX) * 180) / 3.1415;
        float linet3y_length = sqrtf((linet3y_deltaX * linet3y_deltaX) + (linet3y_deltaY * linet3y_deltaY));

        lines[lineindex_T3y].setSize(sf::Vector2f(linet3y_length - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetRadius() * 2, nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetOutlineSize()));
        lines[lineindex_T3y].setOrigin((linet3y_length / 2) - nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetRadius(), nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetOutlineSize() / 2);

        float linet3y_middleY = nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().Y + linet3y_deltaY / 2;
        float linet3y_middleX = nodes[NodeSearch(nodes, x->right->key, x->right->priority)].GetGlobalCenter().X + linet3y_deltaX / 2;

        lines[lineindex_T3y].setPosition(sf::Vector2f(linet3y_middleX, linet3y_middleY));
        lines[lineindex_T3y].setRotation(linet3y_angle);
    }

    //T2x
    if (lineindex_T2x != -1) {
        float lineT2x_deltaX = nodes[rLV.T2.getTreeRootIndex()].GetGlobalCenter().X - nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X;
        float lineT2x_deltaY = nodes[rLV.T2.getTreeRootIndex()].GetGlobalCenter().Y - nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y;
        float lineT2x_angle = (atan2f(lineT2x_deltaY, lineT2x_deltaX) * 180) / 3.1415;
        float lineT2x_length = sqrtf((lineT2x_deltaX * lineT2x_deltaX) + (lineT2x_deltaY * lineT2x_deltaY));

        lines[lineindex_T2x].setSize(sf::Vector2f(lineT2x_length - nodes[NodeSearch(nodes, x->key, x->priority)].GetRadius() * 2, nodes[NodeSearch(nodes, x->key, x->priority)].GetOutlineSize()));
        lines[lineindex_T2x].setOrigin((lineT2x_length / 2) - nodes[NodeSearch(nodes, x->key, x->priority)].GetRadius(), nodes[NodeSearch(nodes, x->key, x->priority)].GetOutlineSize() / 2);

        float lineT2x_middleY = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y + lineT2x_deltaY / 2;
        float lineT2x_middleX = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X + lineT2x_deltaX / 2;

        lines[lineindex_T2x].setPosition(sf::Vector2f(lineT2x_middleX, lineT2x_middleY));
        lines[lineindex_T2x].setRotation(lineT2x_angle);
    }

    //T1x
    if (lineindex_T1x != -1) {
        float lineT1x_deltaX = nodes[rLV.T1.getTreeRootIndex()].GetGlobalCenter().X - nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X;
        float lineT1x_deltaY = nodes[rLV.T1.getTreeRootIndex()].GetGlobalCenter().Y - nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y;
        float lineT1x_angle = (atan2f(lineT1x_deltaY, lineT1x_deltaX) * 180) / 3.1415;
        float lineT1x_length = sqrtf((lineT1x_deltaX * lineT1x_deltaX) + (lineT1x_deltaY * lineT1x_deltaY));

        lines[lineindex_T1x].setSize(sf::Vector2f(lineT1x_length - nodes[NodeSearch(nodes, x->key, x->priority)].GetRadius() * 2, nodes[NodeSearch(nodes, x->key, x->priority)].GetOutlineSize()));
        lines[lineindex_T1x].setOrigin((lineT1x_length / 2) - nodes[NodeSearch(nodes, x->key, x->priority)].GetRadius(), nodes[NodeSearch(nodes, x->key, x->priority)].GetOutlineSize() / 2);

        float lineT1x_middleY = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().Y + lineT1x_deltaY / 2;
        float lineT1x_middleX = nodes[NodeSearch(nodes, x->key, x->priority)].GetGlobalCenter().X + lineT1x_deltaX / 2;

        lines[lineindex_T1x].setPosition(sf::Vector2f(lineT1x_middleX, lineT1x_middleY));
        lines[lineindex_T1x].setRotation(lineT1x_angle);
    }

    if (rLV.t1set && rLV.t2set && rLV.t3set && rLV.xset && rLV.yset) {  //movement is complete
        return true;
    }
    else {
        return false;
    }
}

void InitialNodePlacementREC(Treap::Node* root, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, int rootindex, float offset) {
    if (root->left != nullptr) {
        int rlindex = NodeSearch(nodes, root->left->key, root->left->priority);
        nodes[rlindex].Move((nodes[rootindex].GetGlobalCenter().X - (offset / 2)), nodes[rootindex].GetGlobalCenter().Y + nodes[rootindex].GetRadius() * 3);
        LineDraw(lines, nodes[rootindex], nodes[rlindex]);
        InitialNodePlacementREC(root->left, nodes, lines, rlindex, offset / 2);
    }
    if (root->right != nullptr) {
        int rrindex = NodeSearch(nodes, root->right->key, root->right->priority);
        nodes[rrindex].Move((nodes[rootindex].GetGlobalCenter().X + (offset / 2)), nodes[rootindex].GetGlobalCenter().Y + nodes[rootindex].GetRadius() * 3);
        LineDraw(lines, nodes[rootindex], nodes[rrindex]);
        InitialNodePlacementREC(root->right, nodes, lines, rrindex, offset / 2);
    }
    return;
}

//sets up the treap with 4 nodes initially
void TreapSetUp(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, sf::VideoMode mode, sf::Font& font) {
    //delete nodes
    while (!nodes.empty()) {
        nodes.pop_back();
    }
    //deletes lines
    while (!lines.empty()) {
        lines.pop_back();
    }

    treap1.clear();
    treap1.root = treap1.insert(treap1.root, 10);
    treap1.root = treap1.insert(treap1.root, 20);
    treap1.root = treap1.insert(treap1.root, 30);
    treap1.root = treap1.insert(treap1.root, 40);

    Node n1 = Node(font);
    n1.setvalues(treap1.search(treap1.root, 10)->key, treap1.search(treap1.root, 10)->priority);
    nodes.push_back(n1);
    Node n2 = Node(font);
    n2.setvalues(treap1.search(treap1.root, 20)->key, treap1.search(treap1.root, 20)->priority);
    nodes.push_back(n2);
    Node n3 = Node(font);
    n3.setvalues(treap1.search(treap1.root, 30)->key, treap1.search(treap1.root, 30)->priority);
    nodes.push_back(n3);
    Node n4 = Node(font);
    n4.setvalues(treap1.search(treap1.root, 40)->key, treap1.search(treap1.root, 40)->priority);
    nodes.push_back(n4);
    

    //moves first node
    int rootindex = NodeSearch(nodes, treap1.root->key, treap1.root->priority);
    nodes[rootindex].Move(mode.width / 2, mode.height / 8);
    
    InitialNodePlacementREC(treap1.root, nodes, lines, rootindex, mode.width / 2);

}

bool RemoveNode_SearchREC(Treap::Node* root, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, sf::Font& font, int key, float duration, float totalDuration) {
    
    //check if node is found
    if (key == root->key) {
        int rootindex = NodeSearch(nodes, root->key, root->priority);   
        nodes[rootindex].setOutline(sf::Color::Red, 10.f);
        if (totalDuration > 2000) {
            int rootindex = NodeSearch(nodes, root->key, root->priority);
            nodes[rootindex].setOutline(maroon, 5.f);
            return true;
        }
    }
    else {
        //color node
        int rootindex = NodeSearch(nodes, root->key, root->priority);
        nodes[rootindex].setOutline(sf::Color::Magenta, 10.f);

        if (totalDuration > 1000) { //wait 1 sec
            //reset past node
            int rootindex = NodeSearch(nodes, root->key, root->priority);
            nodes[rootindex].setOutline(maroon, 5.f);

            //keep searching
            if (key > root->key) {
                return RemoveNode_SearchREC(root->right, nodes, lines, font, key, duration, totalDuration - 1000);
            }
            else {
                return RemoveNode_SearchREC(root->left, nodes, lines, font, key, duration, totalDuration - 1000);
            }
        }
    }
    return false;
}

//visually removes node of given key
bool RemoveNode(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, sf::RenderWindow& window, sf::VideoMode mode, sf::Font& font, int key, float duration, float totalDuration, removeAnimationVars& rAV, rotateRightVars& rRV, rotateLeftVars& rLV) {
    //search stage
    if (rAV.searchpart) {
        bool searchresult = RemoveNode_SearchREC(treap1.root, nodes, lines, font, key, duration, totalDuration);
        if (!searchresult) {
            return searchresult;
        }
        rAV.searchpart = false;
        return false;   //at this point, search is finished and will not run again, but still needs to return false so that the main loop knows this function inst done yet
    }
    else {  //delete stage
        if (treap1.search(treap1.root, key)->left == nullptr && treap1.search(treap1.root, key)->right == nullptr) {    //node is childless
            if (treap1.search(treap1.root, key) == treap1.root) {   //if node being removed is root node
                int index = NodeSearch(nodes, treap1.search(treap1.root, key)->key, treap1.search(treap1.root, key)->priority);
                //deletes node
                nodes[index].Move(mode.width * 2, mode.height * 2); //move node off screen
                nodes[index].Draw(window, font);    //draw the node off screen
                nodes.erase(nodes.begin() + index); //removes node from being redrawn

            }
            else {
                //delete node
                int index = NodeSearch(nodes, treap1.search(treap1.root, key)->key, treap1.search(treap1.root, key)->priority);
                int pindex = NodeSearch(nodes, treap1.parentSearch(treap1.root, key)->key, treap1.parentSearch(treap1.root, key)->priority);
                int lineindex = LineFind(lines, nodes[pindex], nodes[index]);

                //deletes line
                lines[lineindex].setPosition(mode.width * 2, mode.height * 2);
                window.draw(lines[lineindex]);
                lines.erase(lines.begin() + lineindex);

                //deletes node
                nodes[index].Move(mode.width * 2, mode.height * 2); //move node off screen
                nodes[index].Draw(window, font);    //draw the node off screen
                nodes.erase(nodes.begin() + index); //removes node from being redrawn


            }
            //removes node from actual treap
            treap1.root = treap1.remove(treap1.root, key);
            rAV.removeAnimation = false;
            rAV.searchpart = true;
            rAV.nodeRemoved = false;
            return true;
        }
        else if (treap1.search(treap1.root, key)->left == nullptr) {    //right child exists
            if (!rAV.nodeRemoved) {
                int index = NodeSearch(nodes, treap1.search(treap1.root, key)->key, treap1.search(treap1.root, key)->priority);
                int childindex = NodeSearch(nodes, treap1.search(treap1.root, key)->right->key, treap1.search(treap1.root, key)->right->priority);
                int lineindex = LineFind(lines, nodes[index], nodes[childindex]);

                rAV.removedNodeX = nodes[index].GetGlobalCenter().X;
                rAV.removedNodeY = nodes[index].GetGlobalCenter().Y;
                rAV.shiftX = (nodes[index].GetGlobalCenter().X - nodes[childindex].GetGlobalCenter().X) / (100.f);
                rAV.shiftY = (nodes[index].GetGlobalCenter().Y - nodes[childindex].GetGlobalCenter().Y) / (100.f);

                //deletes line
                lines[lineindex].setPosition(mode.width * 2, mode.height * 2);
                window.draw(lines[lineindex]);
                lines.erase(lines.begin() + lineindex);

                //deletes node
                nodes[index].Move(mode.width * 2, mode.height * 2); //move node off screen
                nodes[index].Draw(window, font);    //draw the node off screen
                nodes.erase(nodes.begin() + index); //removes node from being redrawn

                rAV.nodeRemoved = true;
                rAV.tree.Setup(treap1, nodes, lines, treap1.search(treap1.root, key)->right);
            }
            int xo = rAV.tree.getPosition(nodes).x;
            int yo = rAV.tree.getPosition(nodes).y;
            int x1 = rAV.removedNodeX;
            int y1 = rAV.removedNodeY;
            if (xo == x1 && yo == y1) {
                treap1.root = treap1.remove(treap1.root, key);  //this needs to happen before space
                rAV.needSpace = true;
                rAV.removeAnimation = false;
                rAV.searchpart = true;
                rAV.nodeRemoved = false;
                return true;
            }
            else {
                rAV.tree.Shift(nodes, lines, rAV.shiftX, rAV.shiftY);
                return false;
            }
        }
        else if (treap1.search(treap1.root, key)->right == nullptr) {   //left child exists
            if (!rAV.nodeRemoved) {
                int index = NodeSearch(nodes, treap1.search(treap1.root, key)->key, treap1.search(treap1.root, key)->priority);
                int childindex = NodeSearch(nodes, treap1.search(treap1.root, key)->left->key, treap1.search(treap1.root, key)->left->priority);
                int lineindex = LineFind(lines, nodes[index], nodes[childindex]);

                rAV.removedNodeX = nodes[index].GetGlobalCenter().X;
                rAV.removedNodeY = nodes[index].GetGlobalCenter().Y;
                rAV.shiftX = (nodes[index].GetGlobalCenter().X - nodes[childindex].GetGlobalCenter().X) / (100.f);
                rAV.shiftY = (nodes[index].GetGlobalCenter().Y - nodes[childindex].GetGlobalCenter().Y) / (100.f);

                //deletes line
                lines[lineindex].setPosition(mode.width * 2, mode.height * 2);
                window.draw(lines[lineindex]);
                lines.erase(lines.begin() + lineindex);

                //deletes node
                nodes[index].Move(mode.width * 2, mode.height * 2); //move node off screen
                nodes[index].Draw(window, font);    //draw the node off screen
                nodes.erase(nodes.begin() + index); //removes node from being redrawn

                rAV.nodeRemoved = true;
                rAV.tree.Setup(treap1, nodes, lines, treap1.search(treap1.root, key)->left);
            }
            int xo = rAV.tree.getPosition(nodes).x;
            int yo = rAV.tree.getPosition(nodes).y;
            int x1 = rAV.removedNodeX;
            int y1 = rAV.removedNodeY;
            if (xo == x1 && yo == y1) {
                treap1.root = treap1.remove(treap1.root, key);  //this needs to happen before space
                rAV.needSpace = true;
                rAV.removeAnimation = false;
                rAV.searchpart = true;
                rAV.nodeRemoved = false;
                return true;
            }
            else {
                rAV.tree.Shift(nodes, lines, rAV.shiftX, rAV.shiftY);
                return false;
            }
        }
        else {                                                          //both left and right child exist
            if (treap1.search(treap1.root, key)->right->priority > treap1.search(treap1.root, key)->left->priority) { //check if need right rotate or left
                if (rotateLeft(treap1, nodes, lines, mode, rLV, treap1.search(treap1.root, key))) {
                    //reset variables
                    rAV.needSpace = true;
                    rAV.removeAnimation = false;
                    rAV.removeAgain = true; //indicating remove will be called directly after space
                    rAV.searchpart = true;
                    rAV.nodeRemoved = false;
                    //rAV.tree.Setup(treap1, nodes, lines, treap1.search(treap1.root, key)->right);    //tree rooted at y
                    treap1.root = treap1.justRotateL(treap1.root, key);
                    rAV.tree.Setup(treap1, nodes, lines, treap1.parentSearch(treap1.root, key));    //tree rooted at y
                    rLVReset(rLV);
                    return true;
                }
                else {
                    return false;
                }
            }
            else {
                if (rotateRight(treap1, nodes, lines, mode, rRV, treap1.search(treap1.root, key))) {
                    //reset variables
                    rAV.needSpace = true;
                    rAV.removeAnimation = false;
                    rAV.removeAgain = true; //indicating remove will be called directly after space
                    rAV.searchpart = true;
                    rAV.nodeRemoved = false;
                    //rAV.tree.Setup(treap1, nodes, lines, treap1.search(treap1.root, key)->left);    //tree rooted at x
                    treap1.root = treap1.justRotateR(treap1.root, key);
                    rAV.tree.Setup(treap1, nodes, lines, treap1.parentSearch(treap1.root, key));    //tree rooted at x
                    rRVReset(rRV);
                    return true;
                }
                else {
                    return false;
                }
            }
        }
    }
}

//visually inserts node of given key
void InsertNode(Treap& treap1, std::vector<Node>& nodes, std::vector<sf::RectangleShape>& lines, sf::VideoMode mode, sf::Font& font, int key, float totalDuration) {

}

int main()
{
    srand(time(NULL));
    sf::Clock clock;

    //timing stuff
    float duration = float();
    float totalDuration = float();

    //Fonts
    sf::Font font;
    font.loadFromFile("Arial.ttf");

    // Display the list of all the video modes available for fullscreen
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    sf::VideoMode mode = modes[0];  //gets largest screen size

    sf::RenderWindow window(sf::VideoMode(mode.width, mode.height), "Interactive Treap Animation", sf::Style::Fullscreen); //uses screen width and height retrieved in previous step

    std::vector<Node> nodes;
    std::vector<sf::RectangleShape> lines;
    std::vector<Button> buttons;
    Treap treap1;
    bool inTextBox = false;
    std::string userText = "";
    int userKey = -1;
    removeAnimationVars rAV;
    spaceNodeVars sNV;
    rotateRightVars rRV;
    rotateLeftVars rLV;

    //create buttons

    sf::RectangleShape bottomBorder;
    bottomBorder.setFillColor(stone);
    bottomBorder.setSize(sf::Vector2f(mode.width, mode.height * 0.2));
    bottomBorder.setPosition(sf::Vector2f(0, mode.height * 0.8));

    Button exit = Button(font, true);
    exit.SetColor(sf::Color::Red);
    exit.SetText("Exit");
    exit.SetSize(mode.width / 25, mode.width / 25);
    exit.Move(mode.width * 0.97, mode.height * 0.05);
    buttons.push_back(exit);

    Button createTreap = Button(font, false);
    createTreap.SetColor(orange);
    createTreap.SetText("Create", "Treap");
    createTreap.SetSize(bottomBorder.getSize().x * 0.1, bottomBorder.getSize().y * 0.6);
    createTreap.Move(bottomBorder.getLocalBounds().width * 0.1, bottomBorder.getGlobalBounds().top + bottomBorder.getLocalBounds().height / 2);
    buttons.push_back(createTreap);

    Button setKey = Button(font, true);
    setKey.SetColor(burntorange);
    setKey.SetText("Set Key");
    setKey.SetSize(bottomBorder.getSize().x * 0.1, bottomBorder.getSize().y * 0.3);
    setKey.Move(bottomBorder.getLocalBounds().width * 0.3, bottomBorder.getGlobalBounds().top + bottomBorder.getLocalBounds().height * 0.66);
    buttons.push_back(setKey);

    Button textBox = Button(font, true);
    textBox.SetColor(white);
    textBox.SetBorder(black, 5.f);
    textBox.SetText("Type Here");
    textBox.SetSize(bottomBorder.getSize().x * 0.1 - 5.f, bottomBorder.getSize().y * 0.3 - 5.f);
    textBox.Move(bottomBorder.getLocalBounds().width * 0.3 + 5.f, bottomBorder.getGlobalBounds().top + bottomBorder.getLocalBounds().height * 0.33);

    Button remove = Button(font, true);
    remove.SetColor(sf::Color::Red);
    remove.SetText("Remove");
    remove.SetSize(bottomBorder.getSize().x * 0.1, bottomBorder.getSize().y * 0.3);
    remove.Move(bottomBorder.getLocalBounds().width * 0.5, bottomBorder.getGlobalBounds().top + bottomBorder.getLocalBounds().height * 0.66);
    buttons.push_back(remove);

    Button insert = Button(font, true);
    insert.SetColor(sf::Color::Green);
    insert.SetText("Insert");
    insert.SetSize(bottomBorder.getSize().x * 0.1, bottomBorder.getSize().y * 0.3);
    insert.Move(bottomBorder.getLocalBounds().width * 0.5, bottomBorder.getGlobalBounds().top + bottomBorder.getLocalBounds().height * 0.33);
    //buttons.push_back(insert);


    //window loop
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        duration += dt.asMilliseconds();

        if (rAV.removeAnimation) {
            totalDuration += dt.asMilliseconds();
            if (duration > 10.f) {
                duration = 0;
                if (treap1.search(treap1.root, userKey) != nullptr) {
                    if (RemoveNode(treap1, nodes, lines, window, mode, font, userKey, duration, totalDuration, rAV, rRV, rLV)) {
                        totalDuration = 0;
                    }
                }
                else {
                    totalDuration = 0;
                    rAV.removeAnimation = false;
                    rAV.searchpart = true;
                }
            }
        }
        else if (rAV.needSpace) {
            if (rAV.tree.Space(treap1, nodes, lines, treap1.search(treap1.root, nodes[rAV.tree.getTreeRootIndex()].GetKey()), mode)) {
                if (rAV.removeAgain) {
                    rAV.removeAnimation = true;
                    rAV.removeAgain = false;
                }
                rAV.needSpace = false;
                rAV.tree.Reset();
            }
        }
        else {


            sf::Event event;
            while (window.pollEvent(event))
            {
                if (inTextBox) {
                    if (event.type == sf::Event::TextEntered) {
                        if (event.text.unicode >= 48 && event.text.unicode <= 57) { //0 - 9
                            if (userText.length() < 2) {
                                userText += event.text.unicode;
                                textBox.SetText(userText);
                                textBox.SetBorder(black, 5.f);
                            }
                        }
                        else if (event.text.unicode == 8) { //backspace
                            if (1 == userText.length()) {
                                userText.pop_back();
                                textBox.SetText("Type Here");
                                textBox.SetBorder(black, 5.f);
                            }
                            else if (2 == userText.length()) {
                                userText.pop_back();
                                textBox.SetText(userText);
                                textBox.SetBorder(black, 5.f);
                            }
                        }
                    }
                }
                if (event.type == sf::Event::Closed)
                    window.close();
                if (event.type == sf::Event::MouseButtonPressed) {
                    sf::Vector2i mouselocalpos = sf::Mouse::getPosition(window);
                    if (createTreap.IsClicked(mouselocalpos)) {
                        TreapSetUp(treap1, nodes, lines, mode, font);
                    }
                    if (textBox.IsClicked(mouselocalpos)) {
                        inTextBox = true;
                    }
                    else {
                        inTextBox = false;
                    }
                    if (setKey.IsClicked(mouselocalpos)) {
                        if (textBox.GetText().length() <= 2) {
                            userKey = std::stoi(textBox.GetText());
                            textBox.SetBorder(sf::Color::Green, 5.f);
                        }
                    }
                    if (remove.IsClicked(mouselocalpos)) {
                        rAV.removeAnimation = true;
                    }
                    if (exit.IsClicked(mouselocalpos)) {
                        window.close();
                    }
                }
            }
        }

        window.clear(white);
        window.draw(bottomBorder);
        for (size_t i = 0; i < nodes.size(); i++) {
            nodes[i].Draw(window, font);
        }
        for (size_t i = 0; i < lines.size(); i++) {
            window.draw(lines[i]);
        }
        for (size_t i = 0; i < buttons.size(); i++) {
            buttons[i].Draw(window, font);
        }
        textBox.Draw(window, font); //needs to be seperate from vector because it constantly changes

        window.display();
    }

    return 0;
}

