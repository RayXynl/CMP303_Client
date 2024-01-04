#pragma once
#include <SFML/Graphics.hpp>

#include "Player.h"

class Bullet : public sf::Sprite
{
public:
	Bullet();
	~Bullet();

	void update(float dt);
	void shoot(Player* player);
private:
	sf::Texture bulletTexture;
	sf::Vector2f moveTo;
	sf::Vector2f startPos;
	int name;
	bool newShot;
	float magnitude;
	const float velocity = 300.f;
	float distanceTravelled;
	float range;
public:
	float getDistanceTravelled() { return distanceTravelled; };

	void setName(int newName) { name = newName; };
	int getName() { return name; };

	void setNewShot(bool newState) { newShot = newState; };
	bool getNewShot() { return newShot; };

	sf::Vector2f getStartPos() { return startPos; };
};

