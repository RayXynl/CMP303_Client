#pragma once
#include <SFML/Network.hpp>

// Struct containing all variables that will be sent and recieved from client to server
struct PlayerMsg
{
	sf::Packet playerPacket;   // Packet to be sent / recieved
	bool	   identifier;	   // Idenitifier to differientiate between zombie and player 
	int		   playerName;	   // Player's name for identification when sending and recieving 
	float	   playerXpos;	   // Player's x co-ordinate
	float      playerYpos;	   // Player's y co-ordinate
	float      playerRotation; // Player's rotation
	float      playerVelocity; // Player's velocity - only used in initial send to set client's velocity variable
	bool	   hasShot;		   // Player's has shot variable tells the server whether the player has shot or not
	float      timeStamp;	   // Timestamp for clarification as to when the packet was sent 
};