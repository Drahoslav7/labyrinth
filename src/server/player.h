#pragma once
class Player;

#include <vector>
#include <string>
#include <boost/thread.hpp>
#include "server.h"
#include "../shared/connection.h"
#include "../shared/tools.h"
#include "server.h"
#include "game.h"

using namespace std;

class Player{
public:
	string nickname;
	Connection *connection;

	int gameId = -1;

	enum {
		NONE,
		STARTED,
		WAITING,
		INVITED,
		READY,
		INVITING, 
		CREATING, 
		PLAYING,
		DEAD,
		GODMODE
	};

	int state;

	Player(Connection *con);
	~Player();

	int setNickname(string nickname);
	int acceptInvite();
	int declineInvice();

private:
	boost::thread thread;
	int id;
	static vector<Player *> players;

	void work();
	std::string handleUserRequest(std::string, std::string);

	static std::string getPlayers(int state);

public:
	static void wipeall();
	// static int remove(Player * player);

};