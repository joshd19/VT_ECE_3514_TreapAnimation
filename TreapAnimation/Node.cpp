#include "Node.h"

//Constructor
Node::Node(sf::Font& font) {

	//Circle
	x.circle.setFillColor(white);
	x.circle.setOutlineThickness(5.f);
	x.circle.setOutlineColor(maroon);
	x.circle.setPointCount(500);

	//Line
	x.line.setSize(sf::Vector2f((x.circle.getRadius() * 2) + x.circle.getOutlineThickness() * 2, x.circle.getOutlineThickness()));
	x.line.setPosition(x.circle.getGlobalBounds().left, (x.circle.getGlobalBounds().top + x.circle.getRadius() + x.circle.getOutlineThickness()));
	x.line.setFillColor(maroon);

	//Key
	x.key.setFont(font);
	x.key.setString("key");
	x.key.setCharacterSize(30);
	x.key.setFillColor(black);
	float keyposy = (x.circle.getLocalBounds().top + (x.circle.getRadius() * 0.6)) - (x.key.getLocalBounds().height / 2);
	float keyposx = (x.circle.getLocalBounds().left + (x.circle.getRadius() * 1.10)) - (x.key.getLocalBounds().width / 2);
	x.key.setPosition(keyposx, keyposy);	

	//Priority
	x.priority.setFont(font);
	x.priority.setString("prio");
	x.priority.setCharacterSize(30);
	x.priority.setFillColor(black);
	float priposy = (x.circle.getLocalBounds().top + (x.circle.getRadius() * 1.40)) - (x.priority.getLocalBounds().height / 2);
	float priposx = (x.circle.getLocalBounds().left + (x.circle.getRadius() * 1.10)) - (x.priority.getLocalBounds().width / 2);
	x.priority.setPosition(priposx, priposy);

}

//Destructor
Node::~Node() {
	
}

//draws the node on renderwindow
void Node::Draw(sf::RenderWindow& window, sf::Font& font) {
	window.draw(x.circle);
	window.draw(x.line);
	window.draw(x.key);
	window.draw(x.priority);
}

//moves the node center to x,y
void Node::Move(float xcord, float ycord) {
	x.circle.setPosition(sf::Vector2f(xcord - x.circle.getRadius(), ycord - x.circle.getRadius()));
	x.line.setPosition(x.circle.getGlobalBounds().left, (x.circle.getGlobalBounds().top + x.circle.getRadius() + x.circle.getOutlineThickness()));
	float keyposy = (x.circle.getGlobalBounds().top + (x.circle.getRadius() * 0.60)) - (x.key.getLocalBounds().height / 2);
	float keyposx = (x.circle.getGlobalBounds().left + (x.circle.getRadius() * 1.10)) - (x.key.getLocalBounds().width / 2);
	x.key.setPosition(keyposx, keyposy);
	float priposy = (x.circle.getGlobalBounds().top + (x.circle.getRadius() * 1.40)) - (x.priority.getLocalBounds().height / 2);
	float priposx = (x.circle.getGlobalBounds().left + (x.circle.getRadius() * 1.10)) - (x.priority.getLocalBounds().width / 2);
	x.priority.setPosition(priposx, priposy);
}

//set the key and priority
void Node::setvalues(int key, int priority) {
	std::string skey = std::to_string(key);
	std::string spriority = std::to_string(priority);

	x.key.setString(skey);
	x.priority.setString(spriority);
	std::string test = x.key.getString();
	std::string test2 = x.priority.getString();
	
}

//set the key
void Node::setkeystring(std::string key) {
	x.key.setString(key);
}

//returns key
int Node::GetKey() {
	std::string temp = x.key.getString();
	int temp2 = std::stoi(temp);
	return temp2;
}

//return priority
int Node::GetPriority() {
	std::string temp = x.priority.getString();
	int temp2 = std::stoi(temp);
	return temp2;
}

//return global bounds of node
Node::globalcenter Node::GetGlobalCenter() {
	globalcenter gc;
	gc.X = x.circle.getGlobalBounds().left + x.circle.getRadius() + x.circle.getOutlineThickness();
	gc.Y = x.circle.getGlobalBounds().top + x.circle.getRadius() + x.circle.getOutlineThickness();
	return gc;
}

//return radius
float Node::GetRadius() {
	return x.circle.getRadius();
}

//returns outline pixel size
float Node::GetOutlineSize() {
	return x.circle.getOutlineThickness();
}

//grows or shinks the node visually
void Node::ChangeSize(float radius) {
	//Circle
	x.circle.setRadius(radius);

	//Line
	x.line.setSize(sf::Vector2f((x.circle.getRadius() * 2) + x.circle.getOutlineThickness() * 2, x.circle.getOutlineThickness()));
	x.line.setPosition(x.circle.getGlobalBounds().left, (x.circle.getGlobalBounds().top + x.circle.getRadius() + x.circle.getOutlineThickness()));

	//Key
	x.key.setCharacterSize(radius / x.circle.getRadius());
	float keyposy = (x.circle.getLocalBounds().top + (x.circle.getRadius() * 0.6)) - (x.key.getLocalBounds().height / 2);
	float keyposx = (x.circle.getLocalBounds().left + (x.circle.getRadius() * 1.10)) - (x.key.getLocalBounds().width / 2);
	x.key.setPosition(keyposx, keyposy);

	//Priority
	x.priority.setCharacterSize(radius / x.circle.getRadius());
	float priposy = (x.circle.getLocalBounds().top + (x.circle.getRadius() * 1.40)) - (x.priority.getLocalBounds().height / 2);
	float priposx = (x.circle.getLocalBounds().left + (x.circle.getRadius() * 1.10)) - (x.priority.getLocalBounds().width / 2);
	x.priority.setPosition(priposx, priposy);
}

//change fill color
void Node::setFill(sf::Color color) {
	x.circle.setFillColor(color);
}

//change outline color
void Node::setOutline(sf::Color color, float size) {
	x.circle.setOutlineThickness(size);
	x.circle.setOutlineColor(color);
	x.line.setFillColor(color);
}