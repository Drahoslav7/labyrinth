#pragma once
class Player;

#include <vector>
#include <string>
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
	};

	~Player(){
    	players[id]=NULL;
   	};

	int setNickname(string nickname);
	int acceptInvite(Game *game);

private:

	int id;
	static vector<Player *> players;


};