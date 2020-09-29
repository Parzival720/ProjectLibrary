//******************************************************************************
//	ProjectLibrary (09/28/20)
//
//       Author:  Ethan Walch, Brigham Young University
//  Description:  A Simple Project Library created to help me learn SFML and have a UI 
//				  to manage my projects coded in C++ and C(refactored to C++). 
//
//				  This is a work in progress and will no doubt have many revisions to it in the future 
//				  as I continue to learn and experiment with the SFML Library.
//
//   Disclaimer:  This code is the work of Ethan Walch.  I certify this to be my
//                source code and not obtained from anyone else.

#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Image.hpp"
#include"SFML/Graphics/Sprite.hpp"
#include "SFML/Window.hpp"
#include <iostream>
#include "Menu.h"
#include "Project.h"

const int HEIGHT = 800;
const int WIDTH = 500;

int main()
{
    std::cout << "Opening menu...\n";
	sf::RenderWindow renderWindow(sf::VideoMode(HEIGHT, WIDTH), "Project Library");

	sf::Color backgroundColor(125, 125, 125);
	sf::Event event;
	sf::Clock timer;

	float delay = 100.0f;

	Project* project = new Menu(WIDTH, HEIGHT);

	while (renderWindow.isOpen()) {
		timer.restart();
		while (renderWindow.pollEvent(event)) {
			switch (event.type)
			{
			case sf::Event::EventType::Closed:
				renderWindow.close();
				break;
			case sf::Event::MouseButtonPressed:
				project = (*project).executeEvent(event, renderWindow);
				break;
			case sf::Event::KeyPressed:
				project = (*project).executeEvent(event, renderWindow);
				break;
			default:
				break;
			}
		}

		// Perform Continuous Actions
		project->executeEvent(event, renderWindow);
	
		
		while (timer.getElapsedTime().asMilliseconds() < delay) {}

		renderWindow.clear(backgroundColor);
		renderWindow.draw(*project);
		//renderWindow.draw(sprite);
		renderWindow.display();
	}
}