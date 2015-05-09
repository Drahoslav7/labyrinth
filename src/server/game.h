#pragma once
class Game;

#include <vector>
#include <string>
#include "player.h"
#include "../shared/components.h"

using namespace std;

class Game{
public:

	Game(Player *player){
		id = games.size();
		games.push_back(this);

		players.push_back(player);
	};

	~Game(){
		games[id]=NULL;
	};

	bool addPlayer(Player *player);
	int removePlayer(Player *player);
	Player * getLeader();
	bool isSomeoneReady();

private:

	vector<Player *> players;
	int id;
	static vector<Game *> games;
};