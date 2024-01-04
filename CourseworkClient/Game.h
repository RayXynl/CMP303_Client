#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "Networking.h" 

#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

using namespace std;

class Game
{
public:
	Game(sf::RenderWindow& window, sf::Clock& clock);
	~Game();

	// Handle player input
	void handleInput(float dt);
	// Update game 
	void update(float dt);
	// Render game
	void render();
private:
	sf::RenderWindow& window;			// Reference to game window
	sf::Clock&		  clock;			// Reference to game's clock
	vector<Zombie*>	  zombies;			// Zombie object vector 
	Networking*		  network;			// Networking class
	Player*			  player;			// Player object
	vector<Bullet*>   bullets;			// Bullet object vector - unused 
	sf::Sprite		  groundSprite;		// Ground Sprite
	sf::Texture		  groundTexture;	// Ground Texture
private:
	const float		  tickRate = 1.0f / 60.f; // Tick rate of client 
	float			  totalTime;			  // Delta time accumulator
	float			  timeDiff;				  // Time sent from server


};

