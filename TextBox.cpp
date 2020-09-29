#include "TextBox.h"

/*
   Constructor
   Initializes the TextBox with width and height and a coordinate.
   parameters:
	  width - int width in pixels
	  height - int height in pixels
	  x - int x-coordinate
	  y - int y-coordinate
*/
TextBox::TextBox(int width, int height, int x, int y) {
	this->x_pos = x;
	this->y_pos = y;
	box.setSize(sf::Vector2f(width, height));
	this->setPosition(x, y);
	box.setFillColor(sf::Color::Transparent);
}

/*
   Function: setSize
   Sets the width and height of the TextBox.
   parameters:
	  width - int width in pixels
	  height - int height in pixels
*/
void TextBox::setSize(int width, int height) {
	box.setSize(sf::Vector2f(width, height));
}


/*
   Function: setPosition
   Sets the position of the TextBox.
   parameters:
	  x - int x-coordinate
	  y - int y-coordinate
*/
void TextBox::setPosition(int x, int y) {
	box.setPosition(sf::Vector2f(x, y));
	text.setPosition(sf::Vector2f(x, y));
	const sf::FloatRect bounds(text.getLocalBounds());
	const sf::Vector2f sizes(box.getSize());
	text.setOrigin((bounds.width - sizes.x) / 2 + bounds.left + 40, (bounds.height - sizes.y) / 2 + bounds.top + 20);
}

/*
   Function: setFillColor
   Sets the color of the TextBox.
   parameters:
	  sf::Color fillColor - a SFML Color Object
*/
void TextBox::setFillColor(sf::Color fillColor) {
	box.setFillColor(fillColor);
}

/*
   Function: setOutline
   Sets the thickness and color of the Outline.
   parameters:
	  borderThickness - float thickness in pixels
	  borderColor - a SFML Color Object
*/
void TextBox::setOutline(float borderThickness, sf::Color borderColor) {
	box.setOutlineThickness(borderThickness);
	box.setOutlineColor(borderColor);
}

/*
   Function: setOutlineColor
   Sets the color of the Outline.
   parameters:
	  borderColor - a SFML Color Object
*/
void TextBox::setOutlineColor(sf::Color borderColor) {
	box.setOutlineColor(borderColor);
}

/*
   Function: setText
   Initializes the text with a string, font and font size.
   parameters:
	  textString - string of text to be put in TextBox
	  fontFileName - fileName of selected font
	  fontSize - int font size
*/
void TextBox::setText(std::string textString, std::string fontFileName, int fontSize) {
	if (!font.loadFromFile(fontFileName)) {
		std::cout << "Error loading font" << std::endl;
	}

	text.setFont(font);
	text.setCharacterSize(fontSize);
	text.setString(textString);
}

/*
   Function: setTextColor
   Sets the color of the Text.
   parameters:
	  color - a SFML Color Object
*/
void TextBox::setTextColor(sf::Color color) {
	text.setFillColor(color);
}

/*
   Function: getGlobalBounds
   Gets the global bounds of the TextBox.
   return:
	  sf::FloatRect containing bounds of TextBox
*/
sf::FloatRect TextBox::getGlobalBounds() const {
	return box.getGlobalBounds();
}