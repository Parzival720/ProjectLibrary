#pragma once

#include "Project.h"
#include "Snake.h"

/*
	Class: Menu
		A class containing the UI for a Menu and ability to react to events in order to switch between projects.

		Extends the Project abstract class.
*/

class Menu : public Project
{
public:
	Menu(float screenHeight, float screenWidth);

	Project* executeEvent(sf::Event event, sf::RenderWindow& window);

	std::string getName() const { return "Menu"; };
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::ConvexShape convexShape;
	sf::RectangleShape snakeButton;
	sf::Texture snakeTitle;
	float screenHeight; 
	float screenWidth;

};