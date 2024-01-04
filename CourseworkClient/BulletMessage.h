#pragma once

struct BulletMsg
{
	sf::Packet bulletPacket;
	bool newShot;
	int bulletName;
	float startXpos;
	float startYpos;
	float angle;
};