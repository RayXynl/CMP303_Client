#include "Bullet.h"

Bullet::Bullet() :
	range(2000.f), distanceTravelled(0.0f)
{
	bulletTexture.loadFromFile("Assests/Player/bullet1.png");
	setTexture(bulletTexture);

	// Set scale
	setScale(sf::Vector2f(0.015f, 0.015f));

	// Set origin
	setOrigin(getTextureRect().width / 2, getTextureRect().height / 2);

	setPosition(sf::Vector2f(720, 360));
}

Bullet::~Bullet()
{

}

void Bullet::update(float dt)
{
	move(moveTo.x * dt * velocity, moveTo.y * dt * velocity);

    distanceTravelled += velocity * dt;
    printf("%f\n", distanceTravelled);
}

void Bullet::shoot(Player* player)
{
    // Set bullet position to player position
    startPos = sf::Vector2f(player->getPosition() + sf::Vector2f(10.f, 10.f));
    setPosition(startPos);

    // Calculate movement vector based on player's rotation
    float angle = player->getRotation() * (3.1415 / 180); // Convert degrees to radians
    float moveX = cos(angle);
    float moveY = sin(angle);

    // Set the movement vector with the desired range
    sf::Vector2f movementVector(moveX * range, moveY * range);

    // Normalize the movement vector
    float magnitude = sqrt(movementVector.x * movementVector.x + movementVector.y * movementVector.y);
    moveTo = sf::Vector2f(movementVector.x / magnitude, movementVector.y / magnitude);
}
