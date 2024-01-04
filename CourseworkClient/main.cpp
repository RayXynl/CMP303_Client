#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Coursework Client");
	window.setFramerateLimit(60); // Set framerate limit of window to 60 fps
	window.requestFocus();

	float deltaTime; // Delta time variable
	sf::Clock clock; // Clock for keeping track of delta time

	Game game(window, clock); // Game engine intialisation

	sf::Event event;

	// While window is open
	while (window.isOpen())
	{
		window.pollEvent(event);
		deltaTime = clock.restart().asSeconds(); // Set delta time to the time since the last clock restart
		game.update(deltaTime); // Game engines update call
		game.handleInput(deltaTime); // Game engines handle input call
		game.render(); // Game engine render call
	}

	return 0;
}