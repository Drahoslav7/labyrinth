#pragma once
class Game;

#include <vector>
#include <string>
#include "player.h"
#include "../shared/components.h"

using namespace std;

class Game{
public:
	vector<Player *> players;

	Game(Player *player){
		id = games.size();
		games.push_back(this);

		players.push_back(player);
	};

	~Game(){
    	games[id]=NULL;
   	};

   	int addPlayer(Player *player);
   	int removePlayer(Player *player);

private:

	int id;
	static vector<Game *> games;
};