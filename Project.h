#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <string>

/*
	Class: Project
		An abstract class designed to be implemented as different screen windows that the Main Loop can easily switc between.

		
	Methods:
		Function: executeEvent
			Responds to events received from the Main Loop
			parameters:
				event - SFML Event object
				window - reference to current RenderWindow
			return:
				Project* - returns a reference to the selected project object(can stay the same or change)

		Function: draw
			Overridden method from sf::Drawable allowing the Snake Window to be drawn normally.
			parameters:
				event - SFML Event object
				window - reference to current RenderWindow

		Function getName
			Returns a string name of the child class
			return:
				std::string - name of child class
*/

class Project : public sf::Drawable, public sf::Transformable
{
public:
	virtual Project* executeEvent(sf::Event event, sf::RenderWindow& window) = 0;

	virtual std::string getName() const = 0;
private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};