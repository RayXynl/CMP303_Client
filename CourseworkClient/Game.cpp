#include "Game.h"

Game::Game(sf::RenderWindow& wndow, sf::Clock& clck) :
	window(wndow), clock(clck), totalTime(0.0f), timeDiff(0.0f)
{
	// Load ground texture
	groundTexture.loadFromFile("Assests/groundTexture.png");
	// Apply ground texture to ground sprite
	groundSprite.setTexture(groundTexture);

	// Create networking class
	network = new Networking(clck);

	// Create new player after connection
	player = new Player(window);

	// Create zombie vector
	for (int i = 0; i < 6; i++)
	{
		Zombie* zombie = new Zombie();
		zombies.push_back(zombie);
	}

	// If connection cannot be made to the server keep attempting
	while (!network->connectToServer(player, zombies, totalTime));
}

Game::~Game()
{

}

void Game::handleInput(float dt)
{
	// Handle input related to player object
	player->handleInput(dt);
}

void Game::update(float dt)
{
	// Accumulate delta time
	totalTime += dt;

	if (totalTime >= tickRate)
	{
		// Send player to server
		network->sendPlayerUpdate(player);

		// Recieve server time from server
		timeDiff = network->recvServerTime();

		// If recieved server time greater than 0
		if (timeDiff > 0)
		{
			totalTime -= timeDiff; // Subtract server time fron the client's total time
		}

		// Recieve player update from server 
		network->recvPlayerUpdate();

		// Interpolate between client player position and server player position
		player->interpolatePosition(network->getPlayerMsgs());

		// Loop for every zombie object
		for (int i = 0; i < zombies.size(); i++)
		{
			// For every zombie object recieve their updated data from server
			network->recvZombieUpdate();
		}

		// Clear old network messages
		network->clearOldData();

		// Subtract tick rate from total time
		totalTime -= tickRate;
	}

	// Loop for every zombie object in the vector
	for (int i = 0; i < zombies.size(); i++)
	{
		zombies[i]->updatePosition(network->getZombieMsgs(zombies[i]->getName()));	// Apply recieved data to each zombie
	}


}

void Game::render()
{
	window.clear(sf::Color::Blue);

	// Render ground sprite
	window.draw(groundSprite);

	// Render player
	window.draw(*player);

	// Render every zombie object in the vector
	for (int i = 0; i < zombies.size(); i++)
	{
		window.draw(*zombies[i]);
	}

	window.display();
}