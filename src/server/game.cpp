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
		// rozdat figurku
		p->figure = new Figure(++color);
		board->placeFigure(p->figure);
		// liznout
		p->card = pack->get()->back();
		pack->get()->pop_back();
		// 
		p->score = 0;
	}
	return true;
}

void Game::sendInit(){
	std::string initCmd = "INIT ";
	for(auto &p : players){
		initCmd += colortoc(p->figure->getColor());
		initCmd += (p->card + 'a' - 1);
		initCmd += p->nickname;
		if(p != players.back()){
			initCmd += ';';
		}
	}

	initCmd += " " + board->toFormat();

	sendUpdate(initCmd);

};

void Game::sendUpdate(std::string data){
	for(auto &p : players){
		p->tell(data);
	}

	std::cout << board->toString() << endl;

}

void Game::nextTurn(){
	int max = players.size();
	if(onTurnIndex == -1){
		onTurnIndex = randomInt(max);
	}
	else{
		onTurnIndex += 1;
		onTurnIndex %= max;		
	}
	players[onTurnIndex]->tell("YOURTURN");
}


bool Game::doRotate(){
	board->rotate();
	sendUpdate("ROTATED");
	return true;
}

bool Game::doShift(std::string data){
	if(!board->shift(data)){
		return false;
	}

	char fig = '-';
	char c = '0';
	for(auto &p : players){
		if(board->pickUpItem(p->figure->pos, p->card)){
			p->card = pack->draw();
			c = (p->card + 'a' - 1);
			fig = colortoc(p->figure->getColor());
		}
	}

	std::string msg = "SHIFTED ";
	msg += fig;
	msg += data;
	msg += c;
	sendUpdate(msg);
	return true; 
}

bool Game::doMove(std::string data){
	if(data.size() != 2){
		return false;
	}

	Player * me = players[onTurnIndex];

	Coords dest(data[0] - 'A', data[1] - 'A');
	Coords orig = me->figure->pos;

	if(!board->isConnected(orig, dest)){
		return false;
	}

	me->figure->pos = dest;
	// sebrat a liznout novou;
	char c = '0';
	if(board->pickUpItem(dest, me->card)){
		me->card = pack->draw();
		c = (me->card + 'a' - 1);
	}

	std::string msg = "MOVED ";
	msg += colortoc(me->figure->getColor());
	msg += data;
	msg += c;
	sendUpdate(msg);
	return true;
}



void Game::cancel(){
	for(auto &p : players){
		p->leaveGame();
	}
	delete this;
}
