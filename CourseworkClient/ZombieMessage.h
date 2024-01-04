#pragma once
#include <SFML/Network.hpp>

// Struct containing all variables that will be sent and recieved from client to server regarding the zombie enemys
struct ZombieMsg
{
	sf::Packet zombiePacket; // Packet to be sent to clients
	bool	   identifier;	 // Idenitifier to differientiate between zombie and player 
	int		   zombieName;   // Zombie's name for identification when sending and recieving
	double	   zombieXpos;   // Zombie's x co-ordinate
	double	   zombieYpos;   // Zombie's y co-ordinate
	float	   rotation;     // Zombie's rotation
	float	   velocity;	 // Zombie's velocity - only used in first send to store on client side
	float	   timeStamp;    // Time stamp for clarification when the packet was sent
};
