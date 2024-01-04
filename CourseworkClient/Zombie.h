#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

#include "ZombieMessage.h"

using namespace std;

class Zombie : public sf::Sprite
{
public:
	Zombie();
	~Zombie();

	// Update zombie position based on recieved server information
	void updatePosition(vector<ZombieMsg>* zombieMsgs);
public:
	// Set and Get zombie name
	void setName(int name) { zombieName = name; };
	int  getName()		   { return zombieName; };
private:
	sf::Vector2f moveTo;			// Position for zombie to move to over time
	sf::Texture  zombieTexture;		// Zombie texture
	float        recvRotation;		// Rotation recieved from server
	int			 zombieName;		// Zombie name used for indentity in network recieve


};

