#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>

/*
	Class: TextBox
		A Simple TextBox using primitive SFML objects that aligns text inside of it.

	Uses:
		Buttons, Banners, etc.
*/


class TextBox : public sf::Drawable, public sf::Transformable
{
public:
	// Default Constructor
	TextBox() {}

	TextBox(int width, int height, int x, int y);

	void setSize(int width, int height);

	void setPosition(int x, int y);

	void setFillColor(sf::Color fillColor);

	void setOutline(float borderThickness, sf::Color borderColor);

	void setOutlineColor(sf::Color borderColor);

	void setText(std::string textString, std::string fontFileName, int fontSize);

	void setTextColor(sf::Color color);

	sf::FloatRect getGlobalBounds() const;


private:
	/*
	   Function: draw
	   Overridden method from sf::Drawable allowing TextBox to be drawn normally.
	   parameters:
		  target - render target(e.g. an sf::RenderWindow object
		  states - render states of the render target
	*/
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(box);
		target.draw(text);
	}
	

	sf::RectangleShape box;
	sf::Font font;
	sf::Text text;

	int x_pos;
	int y_pos;
};
