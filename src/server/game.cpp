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


bool Game::createGame(std::string sets){
	if(sets.size() != 2){
		return false;
	}
	if(!(sets[0] >= 'A' && sets[0] <= 'E')){
		return false;
	}
	if(sets[1] != '0' && sets[1] != '1'){
		return false;
	}

	int boardSize = (sets[0] - 'A' + 2)*2 + 1;
	int packSize = (sets[1] - '0') * 12 + 12;

	board = new Board(boardSize);

	pack = new Pack(packSize);

	board->placeItems(pack->get());

	Color color = Color::INVISIBLE;
	for(auto &p : players ){
		p->figure = new Figure(++color);
		board->placeFigure(p->figure);
	}
	return true;
}

void Game::cancel(){
	for(auto &p : players){
		p->leaveGame();
	}
	delete this;
}