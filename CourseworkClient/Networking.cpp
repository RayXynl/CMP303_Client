#include "Networking.h"

Networking::Networking(sf::Clock& clck) :
	clock(clck)
{
	// Set sockets to nonblocking
	updateSocket.setBlocking(false);
	zombieUpdateSocket.setBlocking(false);

	// Insert entries into unordered map for each zombie
	for (int i = 0; i < 4; i++)
	{
		vector<ZombieMsg> initialisationVector;
		zombieMsgs.insert({ i, initialisationVector });
	}

	string serverIpAddressUser;
	cout << "Enter server IP address : ";
	cin >> serverIpAddressUser;

	serverIP = sf::IpAddress(serverIpAddressUser);
}

Networking::~Networking()
{
	playerMsgs.clear();
	zombieMsgs.clear();

	connectionSocket.disconnect();
}

bool Networking::connectToServer(Player* player, vector<Zombie*> zombies, float clientTime)
{
	// Attempt connection to server
	sf::Socket::Status connectionStatus = connectionSocket.connect(serverIP, connectionPort); 
	
	// If connection unsuccesful return false
	if (connectionStatus != sf::Socket::Done)
	{
		printf("Attempting Connection \n");
		return false;
	}
	// If connection successful return true
	else if (connectionStatus == sf::Socket::Done)
	{
		printf("Connected to server \n");
	}

	// Initialise zombie start message 
	ZombieMsg zStartMsg;

	// Loop for all zombies in game
	for (int i = 0; i < zombies.size(); i++)
	{
		if (connectionSocket.receive(zStartMsg.zombiePacket) == sf::Socket::Done)
		{
			if (zStartMsg.zombiePacket >> zStartMsg.zombieName >> zStartMsg.zombieXpos >> zStartMsg.zombieYpos >> zStartMsg.rotation)
			{
				// Set start variables for each zombie
				zombies[i]->setName(zStartMsg.zombieName);
				zombies[i]->setPosition(sf::Vector2f(zStartMsg.zombieXpos, zStartMsg.zombieYpos));
				zombies[i]->setRotation(zStartMsg.rotation);
			}
			else
			{
				return false; // Return false - data did not match set structure
			}
		}
		else
		{
			return false; // Return false - initial zombie data was not recieved
		}
	}

	// Initialise Player start message 
	PlayerMsg startMsg;

	// Recieve initial data from the server regarding the player
	if (connectionSocket.receive(startMsg.playerPacket) == sf::Socket::Done)
	{
		if (startMsg.playerPacket >> startMsg.playerName >> startMsg.playerXpos >> startMsg.playerYpos >> startMsg.playerRotation >> startMsg.playerVelocity)
		{
			// Set initial player data
			player->setName(startMsg.playerName);
			player->setPosition(startMsg.playerXpos, startMsg.playerYpos);
			player->setRotation(startMsg.playerRotation);
			player->setVelocity(startMsg.playerVelocity);
			connectionSocket.setBlocking(false); // Set connection socket blocking to false 
			return true;
		}
	}
	else
	{
		return false; // Return false - as initial player packet was not recieved
	}

	// Create packet to check if server time has been sent correctly
	sf::Packet timePacket;
	float serverTime;

	// Recieve start time from server
	if (connectionSocket.receive(timePacket) == sf::Socket::Done)
	{
		if (timePacket >> serverTime)
		{
			// If recieved server time greater than 0
			if (serverTime > 0)
			{
				clientTime -= serverTime; // Subtract server time fron the client's total time
			}
		}
	}
}

// Recieve the server time for the server to keep player client and server synchronised
float Networking::recvServerTime()
{
	sf::Packet timePacket;
	float serverTime;

	// Recieve server time packet
	if (connectionSocket.receive(timePacket) == sf::Socket::Done)
	{
		if (timePacket >> serverTime)
		{
			return serverTime; // Return server time 
		}
	}
}

//UPDATES
// Send player update to the server
void Networking::sendPlayerUpdate(Player* player)
{
	// Set Variables to be sent to server
	pSendMsg.identifier = true;
	pSendMsg.playerName = 0;
	pSendMsg.playerXpos = player->getPosition().x;
	pSendMsg.playerYpos = player->getPosition().y;
	pSendMsg.playerRotation = player->getRotation();
	pSendMsg.timeStamp = clock.getElapsedTime().asSeconds();

	// Pack the packet with the variables to be sent to the server
	pSendMsg.playerPacket << pSendMsg.identifier << pSendMsg.playerName << pSendMsg.playerXpos << pSendMsg.playerYpos << pSendMsg.playerRotation << pSendMsg.hasShot <<  pSendMsg.timeStamp;

	// Send player update to the server 
	updateSocket.send(pSendMsg.playerPacket, serverIP, updatePort);

	// Clear player packet for next use
	pSendMsg.playerPacket.clear();
}

// Recieve player update from the server
void Networking::recvPlayerUpdate()
{
	// Recieve player update from server
	if (updateSocket.receive(pRecvMsg.playerPacket, serverIP, updatePort) == sf::Socket::Done)
	{
		if (pRecvMsg.playerPacket >> pRecvMsg.identifier >> pRecvMsg.playerName >> pRecvMsg.playerXpos >> pRecvMsg.playerYpos >> pRecvMsg.playerRotation >> pRecvMsg.timeStamp)
		{
			if (pRecvMsg.identifier == true)
			{
				// Push the recieved message to the player message vector
				playerMsgs.push_back(pRecvMsg);
			}
		}
	}

	// Clear packet before next use
	pRecvMsg.playerPacket.clear();
}


// Bullet send to server - not implemented in time
void Networking::sendBullets(Bullet* bullet)
{
	bSendMsg.newShot = bullet->getNewShot();
	bSendMsg.bulletName = bullet->getName();
	bSendMsg.startXpos = bullet->getStartPos().x;
	bSendMsg.startYpos = bullet->getStartPos().y;
	bSendMsg.angle = bullet->getRotation();

	bSendMsg.bulletPacket << bSendMsg.newShot << bSendMsg.bulletName << bSendMsg.startXpos << bSendMsg.startYpos << bSendMsg.angle;

	updateSocket.send(bSendMsg.bulletPacket, serverIP, updatePort);
}


// Recieve zombie update from the server
void Networking::recvZombieUpdate()
{
	if (updateSocket.receive(zRecvMsg.zombiePacket, serverIP, updatePort) == sf::Socket::Done)
	{
		if (zRecvMsg.zombiePacket >> zRecvMsg.identifier >> zRecvMsg.zombieName >> zRecvMsg.zombieXpos >> zRecvMsg.zombieYpos >> zRecvMsg.rotation)
		{
			if (zRecvMsg.identifier == false)
			{
				// Push recieved message to appropiate zombie index in the map
				zombieMsgs[zRecvMsg.zombieName].push_back(zRecvMsg);
			}
		}
	}

	// Clear zombie packet for next use
	zRecvMsg.zombiePacket.clear();
}

// Clear old messages from messages vectors to free up resources
void Networking::clearOldData()
{
	// Clear player message vector to stop it slowing down the client
	if (playerMsgs.size() > 1000)
	{
		playerMsgs.clear();
	}

	// Clear zombie messages to stop the size of vector slowing down the client
	for (int i = 0; i < zombieMsgs.size(); i++)
	{
		if (zombieMsgs[i].size() > 1000)
		{
			zombieMsgs[i].clear();
		}
	}
}
