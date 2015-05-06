#include "game.h"

using namespace std;
vector<Game *> Game::games = vector<Game *>();

int Game::addPlayer(Player *player){
	if(players.size() == 4){
		return 1;
	}

	players.push_back(player);
	player->state = Player::READY;

	return 0;
};

int Game::removePlayer(Player *player){
	int pos = 0;

	for(auto &eachplayer : players){
		if(eachplayer->nickname == player->nickname){
			players.erase(players.begin() + pos);
			return 0;
		}

		pos++;
	}

	return 1;
};

