#pragma once
#include <SFML/Network.hpp>
#include <unordered_map>
#include <vector>
#include <iostream>

#include "PlayerMessage.h"
#include "ZombieMessage.h"
#include "BulletMessage.h"
#include "Player.h"
#include "Zombie.h"
#include "Bullet.h"

using namespace std;

class Networking
{
public:
	// Networking Constructor
	Networking(sf::Clock& clock);
	// Networking Destructor
	~Networking();

	// Function to clear any old data regarding the player and zombies 
	void clearOldData();

	// PLAYER
	// Connect to server
	bool connectToServer(Player* player, vector<Zombie*> zombies, float clientTime);
	// Recieve server time
	float recvServerTime();
	// Send player update to the server
	void sendPlayerUpdate(Player* player);
	// Recieve player update from the server
	void recvPlayerUpdate();

	void sendBullets(Bullet* bullet);

	// ZOMBIE
	// Recieve Zombie update
	void recvZombieUpdate();
private:
	// Map containing vector of messages identified by the zombie names
	unordered_map<int, vector<ZombieMsg>> zombieMsgs;
	// Store recieved player messages
	vector<PlayerMsg> playerMsgs;
public:
	// Return zombie message vector based on the name passed
	vector<ZombieMsg>* getZombieMsgs(int zombieName) { return &zombieMsgs[zombieName]; };
	// Get player message vector
	vector<PlayerMsg>* getPlayerMsgs()				 { return &playerMsgs; };
private:
	// UPDATES
	// Player Updates
	sf::UdpSocket  updateSocket;			   // Socket to send and recieving player updates
	unsigned short updatePort = 5400;		   // Port used for recieving and sending player updates
	PlayerMsg	   pRecvMsg;				   // Struct containing all variables that will be recieved from the server regarding the player
	PlayerMsg	   pSendMsg;				   // Struct containing all variables that will be sent to the server regarding the player

	BulletMsg	   bSendMsg;

	// Zombie Updates
	sf::UdpSocket	   zombieUpdateSocket;     // Socket for sending and zombie updates
	unsigned short     zombiePort = 5401;	   // Port used to send zombie updates
	ZombieMsg		   zRecvMsg;			   // Struct containing all variables that will be recieved from the server regarding the zombies

	// SERVER	   
	sf::IpAddress  serverIP;				   // Server IP Address
	unsigned short connectionPort = 5400; 	   // Port used for connecting to server
	sf::TcpSocket  connectionSocket;		   // Socket to connect to server

	sf::Clock&	   clock;					   // Reference to game's clock
};

