#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "PlayerMessage.h"

using namespace std;

class Player : public sf::Sprite
{
public:
	Player(sf::RenderWindow& wndow);
	~Player();

	// Handle player input
	void handleInput(float dt);
	// Update player object
	void update(float dt);

	// Interpolate between client player position and server player position
	void interpolatePosition(vector<PlayerMsg>* msgVector);
private:
	sf::RenderWindow& window;			// Reference to game window
	sf::Texture		  playerTexture;	// Player texture
	int		          playerName;		// Player's name
	float			  velocity;			// Player's velocity
	float			  shootCooldown;	// Shot cooldown - unused
	bool			  hasShot;			// hasShot unused
private:
	// Player movement functions
	void moveForward(float dt)  { move(sf::Vector2f(0, -velocity * dt)); };
	void moveBackward(float dt) { move(sf::Vector2f(0, velocity * dt));  };
	void moveRight(float dt)	{ move(sf::Vector2f(velocity * dt, 0));  };
	void moveLeft(float dt)		{ move(sf::Vector2f(-velocity * dt, 0)); };
public:
	// Set and Get Player name
	void  setName(int name)				 { playerName = name; };
	int   getName()						 { return playerName; };
	// Set and Get player velocity
	void  setVelocity(float newVelocity) { velocity = newVelocity; };
	float getVelocity()					 { return velocity; };
	// Set and Get player has shot
	void  setHasShot(bool shotState)	 { hasShot = shotState; };
	bool  getHasShot()					 { return hasShot; };
};

