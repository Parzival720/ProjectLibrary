#include "Menu.h"

/*
   Constructor
   Sets up the Menu Screen and creates buttons for each project.
   parameters:
	  screenHeight - the current Height of the Screen
	  screenWidth - the current Width of the Screen
*/
Menu::Menu(float screenHeight, float screenWidth)
{
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;

	convexShape.setPointCount(5);
	convexShape.setFillColor(sf::Color(147, 112, 227));
	convexShape.setOutlineThickness(3.0f);
	convexShape.setOutlineColor(sf::Color::White);

	convexShape.setPoint(0, sf::Vector2f(0.0f, 0.0f));
	convexShape.setPoint(1, sf::Vector2f(screenWidth, 0.0f));
	convexShape.setPoint(2, sf::Vector2f(screenWidth, screenHeight));
	convexShape.setPoint(3, sf::Vector2f(screenWidth / 2.0f, screenHeight / 2.0f));
	convexShape.setPoint(4, sf::Vector2f(0.0f, screenHeight));

	if (!snakeTitle.loadFromFile("./res/images/snake-title.png"))
		std::cout << "Error loading snake title file" << std::endl;

	snakeButton.setSize(sf::Vector2f(screenWidth / 3.0f, 100));
	snakeButton.setPosition(screenWidth / 3.0f, 50);
	snakeButton.setFillColor(sf::Color::White);
	snakeButton.setOutlineThickness(3.0f);
	snakeButton.setOutlineColor(sf::Color::White);
	snakeButton.setTexture(&snakeTitle);
}

/*
   Function: executeEvent
		Responds to events received from the Main Loop such as Mouse Clicks.
   parameters:
	  event - SFML Event object
	  window - reference to current RenderWindow
   return:
	  Project* - returns a reference to the selected project object(can stay the same or change)
*/
Project* Menu::executeEvent(sf::Event event, sf::RenderWindow& window) {
	if (event.type == sf::Event::MouseButtonPressed) {
		sf::Vector2i mousePos = sf::Mouse::getPosition(window);
		sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
		if (snakeButton.getGlobalBounds().contains(mousePosF))
		{
			return new Snake(screenHeight, screenWidth);
		}
	}
	return this;
}

/*
   Function: draw
		Overridden method from sf::Drawable allowing the Menu Window to be drawn normally.
   parameters:
	  event - SFML Event object
	  window - reference to current RenderWindow
*/
void Menu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(convexShape);
	target.draw(snakeButton);
}