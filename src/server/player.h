#pragma once
class Player;

#include <vector>
#include <string>
#include <boost/thread.hpp>
#include "server.h"
#include "game.h"

using namespace std;

class Player{
public:
	string nickname;
	Connection *connection;

	enum {
		STARTED,
		WAITING,
		INVITED,
		READY,
		INVITING, 
		CREATING, 
		PLAYING
	};

	int state;

	Player(Connection *con){
		connection = con;
		nickname = "";
		state = STARTED;
		id = players.size();
		players.push_back(this);

		thread = boost::thread(&Player::work, this);
		PRD("Player thread");
	};

	~Player(){
		players[id] = NULL;
		thread.join();
		delete connection;
	};

	int setNickname(string nickname);
	int acceptInvite(Game *game);

private:

	void work();

	boost::thread thread;
	int id;
	static vector<Player *> players;


};