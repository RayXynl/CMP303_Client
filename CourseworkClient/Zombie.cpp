#include "Zombie.h"

Zombie::Zombie()
{
	// Load zombies texture from file and assign it to the sprite
	zombieTexture.loadFromFile("Assests/Zombie/zombie.png");
	// Set zombie texture
	setTexture(zombieTexture);

	// Set origin of zombie sprite
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);
	// Set scale of zombie sprite
	setScale(sf::Vector2f(0.25f, 0.25f)); // Scale zombie appropiately
}

Zombie::~Zombie()
{

}

void Zombie::updatePosition(vector<ZombieMsg>* zombieMsgs)
{
	// If there is recieved data to process
	if (zombieMsgs->size() > 0)
	{
		// Retrieve most recent messsage from zombie message vector
		const ZombieMsg& msg0 = zombieMsgs->at(zombieMsgs->size() - 1);
		
		// Blending factor for interpolation
		float alpha = 0.1f;

		// Interpolate between current position and recieved position
		sf::Vector2f recvPos = sf::Vector2f(msg0.zombieXpos, msg0.zombieYpos);
		sf::Vector2f interpolatedPos = getPosition() + alpha * (recvPos - getPosition());
		setPosition(interpolatedPos);

		// Interpolate between current rotation and recieved rotation
		recvRotation = msg0.rotation;
		float interpolatedRotation = getRotation() + alpha * (recvRotation - getRotation());
		setRotation(interpolatedRotation);
	}
}

