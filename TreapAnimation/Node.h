#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Node {
public:

    //struct used to hold all shapes and text to repesent one node of Treap
    struct nodeshape
    {
        sf::CircleShape circle = sf::CircleShape(50.f);
        sf::RectangleShape line = sf::RectangleShape(sf::Vector2f(150.f, 5.f));
        sf::Text key;
        sf::Text priority;
    };

    struct globalcenter
    {
        float X;
        float Y;
    };
    
    //Constructor
    Node(sf::Font& font);

    //Destructor
    ~Node();

    //draws the node on renderwindow
    void Draw(sf::RenderWindow& window, sf::Font &font);

    //moves the node from one x,y to another
    void Move(float x, float y);

    //set the key and priority
    void setvalues(int key, int priority);

    //set the key
    void setkeystring(std::string key);

    //returns key
    int GetKey();

    //return priority
    int GetPriority();

    //return global bounds of node
    globalcenter GetGlobalCenter();

    //return radius
    float GetRadius();

    //returns outline pixel size
    float GetOutlineSize();

    //grows or shinks the node visually
    void ChangeSize(float radius);

    //change fill color
    void setFill(sf::Color color);

    //change fill color
    void setOutline(sf::Color color, float size);

private:
    nodeshape x;

    sf::Color white{ 255, 255, 255 };
    sf::Color maroon{ 134, 31, 65 };
    sf::Color orange{ 232, 119, 34 };
    sf::Color burntorange{ 198, 70, 0 };
    sf::Color stone{ 117, 120, 123 };
    sf::Color black{ 0, 0, 0 };

    
};


#endif // NODE_HPP
