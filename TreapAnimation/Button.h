#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

class Button {
public:

    //struct used to hold all shapes and text to repesent one node of Treap
    struct buttonshape
    {
        sf::RectangleShape button = sf::RectangleShape(sf::Vector2f(150.f, 5.f));
        sf::Text top;
        sf::Text bottom;
        sf::Text middle;
    };

    struct globalcenter
    {
        float X;
        float Y;
    };

    //Constructor
    Button(sf::Font& font, bool textinmiddle);

    //Destructor
    ~Button();

    //changes size of button
    void SetSize(float width, float height);

    //draws the button on renderwindow
    void Draw(sf::RenderWindow& window, sf::Font& font);

    //moves the button from one x,y to another
    void Move(float x, float y);

    //return the text as string
    std::string GetText();

    //set the text
    void SetText(std::string middle);

    //set the text
    void SetText(std::string top, std::string bottom);

    //set color of button
    void SetColor(sf::Color color);

    //set border of button
    void SetBorder(sf::Color color, float outlinesize);
    
    //return true if mouse is over button
    bool IsClicked(sf::Vector2i mouselocalpos);

    //return global bounds of node
    globalcenter GetGlobalCenter();


private:
    buttonshape bs;

    //variable for if text will be in one line at middle or two lines
    bool textinmiddle;

    sf::Color white{ 255, 255, 255 };
    sf::Color maroon{ 134, 31, 65 };
    sf::Color orange{ 232, 119, 34 };
    sf::Color burntorange{ 198, 70, 0 };
    sf::Color stone{ 117, 120, 123 };
    sf::Color black{ 0, 0, 0 };


};


#endif // BUTTON_HPP
