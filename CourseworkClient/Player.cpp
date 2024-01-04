#include "Player.h"

Player::Player(sf::RenderWindow& wndow) :
	window(wndow), hasShot(false), shootCooldown(0.0f)
{
	playerTexture.loadFromFile("Assests/Player/player.png"); // Load player Texture
	setTexture(playerTexture); // Set player texture
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2); // set the sprite origin
	setScale(sf::Vector2f(0.25f, 0.25f)); // Scale player appropiately
}

Player::~Player()
{

}

void Player::handleInput(float dt)
{
	shootCooldown += dt;
	// Call the appropiate movement function dependant upon the user input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		moveForward(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		moveBackward(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveRight(dt);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveLeft(dt);
	}


	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shootCooldown >= 0.2f)
	{
		hasShot = true;
		shootCooldown = 0.0f;
	}

	// Adapted from	https://en.sfml-dev.org/forums/index.php?topic=10167.0
	// Rotate player sprite to look towards the mouse position
	sf::Vector2i mousePos = sf::Mouse::getPosition(window); // Get the mouse position relative to the window
	float mouseAngle = -atan2(mousePos.x - getPosition().x, mousePos.y - getPosition().y) * 180 / 3.1415 + 90; // Calculate the angle 
	setRotation(mouseAngle);// Apply the rotation to the player sprite
}

void Player::update(float dt)
{

}

void Player::interpolatePosition(vector<PlayerMsg>* playerMsgs)
{
	// If player message vector has data to process
	if (playerMsgs->size() > 0)
	{
		// Retrieve most recent message in the message vector
		const PlayerMsg msg0 = playerMsgs->at(playerMsgs->size() - 1); 
		
		// Alpha variable using as blending factor for interpolation 
		float alpha = 0.05f;

		// Interpolate between the server player position and the client's player position
		sf::Vector2f recvPos = sf::Vector2f(msg0.playerXpos, msg0.playerYpos);
		sf::Vector2f interpolatedPos = getPosition() + alpha * (recvPos - getPosition());
		setPosition(interpolatedPos);
	}
}