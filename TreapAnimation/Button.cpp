#include "Button.h"

//Constructor
Button::Button(sf::Font& font, bool textinmiddle) {
	//top text
	bs.top.setFillColor(black);
	bs.top.setCharacterSize(40);
	bs.top.setFont(font);

	//bottom text
	bs.bottom.setFillColor(black);
	bs.bottom.setCharacterSize(40);
	bs.bottom.setFont(font);

	//middle text
	bs.middle.setFillColor(black);
	bs.middle.setCharacterSize(40);
	bs.middle.setFont(font);

	Button::textinmiddle = textinmiddle;
}

//Destructor
Button::~Button() {

}

//changes size of button
void Button::SetSize(float width, float height) {
	bs.button.setSize(sf::Vector2f(width, height));
	if (textinmiddle) {
		bs.middle.setOrigin(sf::Vector2f(bs.middle.getLocalBounds().left + bs.middle.getLocalBounds().width / 2,
			bs.middle.getLocalBounds().top + bs.middle.getLocalBounds().height / 2));
		float middleY = (bs.button.getGlobalBounds().top + bs.button.getGlobalBounds().height * 0.5);
		float middleX = (bs.button.getGlobalBounds().left + bs.button.getGlobalBounds().width * 0.5);
		bs.middle.setPosition(sf::Vector2f(middleX, middleY));
	}
	else {
		bs.top.setOrigin(sf::Vector2f(bs.top.getLocalBounds().left + bs.top.getLocalBounds().width / 2,
			bs.top.getLocalBounds().top + bs.top.getLocalBounds().height / 2));
		float topY = (bs.button.getGlobalBounds().top + bs.button.getGlobalBounds().height * 0.25);
		float topX = (bs.button.getGlobalBounds().left + bs.button.getGlobalBounds().width * 0.5);
		bs.top.setPosition(sf::Vector2f(topX, topY));

		bs.bottom.setOrigin(sf::Vector2f(bs.bottom.getLocalBounds().left + bs.bottom.getLocalBounds().width / 2,
			bs.bottom.getLocalBounds().top + bs.bottom.getLocalBounds().height / 2));
		float bottomY = (bs.button.getGlobalBounds().top + bs.button.getGlobalBounds().height * 0.75);
		float bottomX = (bs.button.getGlobalBounds().left + bs.button.getGlobalBounds().width * 0.5);
		bs.bottom.setPosition(sf::Vector2f(bottomX, bottomY));
	}
}

//draws the button on renderwindow
void Button::Draw(sf::RenderWindow& window, sf::Font& font) {
	window.draw(bs.button);
	if (textinmiddle) {
		window.draw(bs.middle);
	}
	else {
		window.draw(bs.top);
		window.draw(bs.bottom);
	}
}

//moves the button from one x,y to another
void Button::Move(float x, float y) {
	bs.button.setPosition(x - bs.button.getGlobalBounds().width / 2, y - bs.button.getGlobalBounds().height / 2);

	if (textinmiddle) {
		bs.middle.setOrigin(sf::Vector2f(bs.middle.getLocalBounds().left + bs.middle.getLocalBounds().width / 2,
			bs.middle.getLocalBounds().top + bs.middle.getLocalBounds().height / 2));
		float middleY = (bs.button.getGlobalBounds().top + bs.button.getGlobalBounds().height * 0.5);
		float middleX = (bs.button.getGlobalBounds().left + bs.button.getGlobalBounds().width * 0.5);
		bs.middle.setPosition(sf::Vector2f(middleX, middleY));
	}
	else {
		bs.top.setOrigin(sf::Vector2f(bs.top.getLocalBounds().left + bs.top.getLocalBounds().width / 2,
			bs.top.getLocalBounds().top + bs.top.getLocalBounds().height / 2));
		float topY = (bs.button.getGlobalBounds().top + bs.button.getGlobalBounds().height * 0.25);
		float topX = (bs.button.getGlobalBounds().left + bs.button.getGlobalBounds().width * 0.5);
		bs.top.setPosition(sf::Vector2f(topX, topY));

		bs.bottom.setOrigin(sf::Vector2f(bs.bottom.getLocalBounds().left + bs.bottom.getLocalBounds().width / 2,
			bs.bottom.getLocalBounds().top + bs.bottom.getLocalBounds().height / 2));
		float bottomY = (bs.button.getGlobalBounds().top + bs.button.getGlobalBounds().height * 0.75);
		float bottomX = (bs.button.getGlobalBounds().left + bs.button.getGlobalBounds().width * 0.5);
		bs.bottom.setPosition(sf::Vector2f(bottomX, bottomY));
	}
}

//return the text as string
std::string Button::GetText() {
	return bs.middle.getString();
}

//set the text
void Button::SetText(std::string middle) {
	bs.middle.setString(middle);

}

//set the text
void Button::SetText(std::string top, std::string bottom) {
	bs.top.setString(top);
	bs.bottom.setString(bottom);
}


//set color of button
void Button::SetColor(sf::Color color) {
	bs.button.setFillColor(color);
}

//set border of button
void Button::SetBorder(sf::Color color, float outlinesize) {
	bs.button.setOutlineThickness(outlinesize);
	bs.button.setOutlineColor(color);
}

//return true if mouse is over button
bool Button::IsClicked(sf::Vector2i mouselocalpos) {
	if (textinmiddle) {
		if (((mouselocalpos.x >= bs.button.getGlobalBounds().left && mouselocalpos.x <= bs.button.getGlobalBounds().left + bs.button.getGlobalBounds().width)
			&& (mouselocalpos.y >= bs.button.getGlobalBounds().top && mouselocalpos.y <= bs.button.getGlobalBounds().top + bs.button.getGlobalBounds().height)) 
			|| ((mouselocalpos.x >= bs.middle.getGlobalBounds().left && mouselocalpos.x <= bs.middle.getGlobalBounds().left + bs.middle.getGlobalBounds().width) 
				&& (mouselocalpos.y >= bs.middle.getGlobalBounds().top && mouselocalpos.y <= bs.middle.getGlobalBounds().top + bs.middle.getGlobalBounds().height)))
		{
			return true;
		}
	}
	else {
		if (((mouselocalpos.x >= bs.button.getGlobalBounds().left && mouselocalpos.x <= bs.button.getGlobalBounds().left + bs.button.getGlobalBounds().width)
			&& (mouselocalpos.y >= bs.button.getGlobalBounds().top && mouselocalpos.y <= bs.button.getGlobalBounds().top + bs.button.getGlobalBounds().height))
			|| ((mouselocalpos.x >= bs.bottom.getGlobalBounds().left && mouselocalpos.x <= bs.bottom.getGlobalBounds().left + bs.bottom.getGlobalBounds().width)
				&& (mouselocalpos.y >= bs.bottom.getGlobalBounds().top && mouselocalpos.y <= bs.bottom.getGlobalBounds().top + bs.bottom.getGlobalBounds().height)))
				
		{
			return true;
		}
	}
	return false;
}

//return global bounds of node
Button::globalcenter Button::GetGlobalCenter() {
	globalcenter gc;
	gc.X = bs.button.getGlobalBounds().left + bs.button.getGlobalBounds().width / 2;
	gc.Y = bs.button.getGlobalBounds().top + bs.button.getGlobalBounds().height / 2;
	return gc;
}