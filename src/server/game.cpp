#include "game.h"

using namespace std;
vector<Game *> Game::games = vector<Game *>();

bool Game::addPlayer(Player *player){
	if(players.size() == 4 && players[0]->getState() != Player::INVITING){
		return false;
	}

	players.push_back(player);
	player->setState(Player::READY);

	return true;
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

bool Game::isSomeoneReady(){
	for(auto &p : players){
		if(p->getState() == Player::READY && p != getLeader()){
			return true;
		}
	}
	return false;
}

Player * Game::getLeader(){
	return players[0];
}
