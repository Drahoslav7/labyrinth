#include "player.h"

using namespace std;

vector<Player *> Player::players = vector<Player *>();

// Player::STATES[] = {
// 	Player::NONE : "NONE",
// }

Player::Player(Connection *con){
	connection = con;
	nickname = "";
	state = NONE;
	id = players.size();
	players.push_back(this);

	game = NULL;
	figure = NULL;

	thread = boost::thread(&Player::work, this);
	PRD("Player thread");
};


Player::~Player(){
	thread.join();
	tell("DIE");
	// remove(this);
	delete connection;
};


bool Player::setNickname(string nickname){
	if(nickname.length() < 3 || nickname.length() > 17){
		return false;
	}

	for(auto &player : players){
		for(auto &c : nickname){
			if(!isalnum(c)){
				return false;
			}
		}

		if(player->state != DEAD && player->nickname == nickname){
			return false;
		}
	}

	this->nickname = nickname;
	this->state = WAITING;

	return true;
};

bool Player::invitePlayer(string nickname){
	std::string msg = "INVITATION " + this->nickname; 
	for(auto & p : players){
		if(p->nickname == nickname && p->state == WAITING){
			p->game = this->game;
			p->setState(INVITED);
			p->tell(msg);
			return true;
		}
	}
	return false;
};

void Player::leaveGame(){
	this->state = WAITING;
	delete this->figure;
	this->game = NULL;
	try{
		this->tell("GAMECANCELED");
	} catch (boost::system::system_error & e) {
		
	}
}


void Player::work(){

	std::string req;
	std::string res;

	PRD("player work");

	bool ok = true;
	while(ok){
		try{
			connection->recv(&req);
		} catch (boost::system::system_error & e) {
			ok = false;
		}

		string cmd;
		string data;
		
		split(req, ' ', &cmd, &data);


		res = handleUserRequest(cmd, data);
		
		if(res == "DIE" && state != GODMODE)
			ok = false;
		try{
			connection->send(&res);
		} catch (boost::system::system_error & e) {
			ok = false;
		}

	}

	if(game && game->getLeader() == this){
		for(auto &p : players){
			if(p != this && p->getGame() == game){
				p->leaveGame();
			}
		}
		game->cancel();
	}
	state = DEAD;

	PRD("player work end");
}


std::string Player::handleUserRequest(std::string cmd, std::string data){

	std::string res = "DIE";

	switch(state){
		case NONE:
			if(cmd == "HI") {
				state = STARTED;
				res = "OK";
			}
			break;

		case STARTED:
			if(cmd == "IAM"){ // nick
				if(setNickname(data)){
					state = WAITING;
					res = "OK";
				} else {
					res = "NOPE";
				}
			}
			if(cmd == "GODMODE"){
				state = GODMODE;
				res = "OK";
			}
			break;

		case WAITING:
			if(cmd == "CREATE"){
				state = INVITING;
				game = new Game(this);
				res = "OK";
			}
			if(cmd == "WHOISTHERE"){
				res = "OK " + Player::getPlayers(WAITING);
			}
			break;

		case INVITING:
			if(cmd == "INVITE"){ // koho
				if(invitePlayer(data)){
					res = "OK "+data;
				}else{
					res = "NOPE "+data;
				}
			}
			if(cmd == "WHOISWAITING" || cmd == "WHOISTHERE"){
				res = "OK " + Player::getPlayers(WAITING);
			}
			// if(cmd == "WHOISREADY"){
			// 	res = "OK " + Player::getPlayers(READY);
			// }
			if(cmd == "NEWGAME"){
				if(game->isSomeoneReady()){
					res = "OK";
					state = CREATING_NEW; // ??
				}
				else {
					res = "NOPE";
				}
			}
			if(cmd == "LOADGAME"){
				// TODO !
				res = "NOPE";
			}
			break;

		case CREATING_NEW:
			if(cmd == "NEW"){
				if(game->createGame(data)){
					res = "OK";
					state = READY;
					game->sendInit();
					game->nextTurn();
				} else {
					res = "NOPE";
				}
			}

			break;

		case INVITED:
			if(cmd == "ACCEPT"){
				if(game && game->addPlayer(this)){
					std::string msg = "READYLIST " + Player::getReadyPlayers(game);
					game->getLeader()->tell(msg);
					state = READY;
					res = "OK";
				} else {
					state = WAITING;
					res = "NOPE";
				}
			}
			if(cmd == "DECLINE"){
				game = NULL;
				state = WAITING;
				res = "OK";
			}
			break;


		case PLAYING:
			if(!game->isOnTurn(this)){
				res = "NOPE";
				break;
			}
			if(cmd == "ROTATE"){
				if(this->shifted){
					res = "NOPE";
					break;
				} 
				if(game->doRotate()){
					res = "OK";
				} else {
					res = "NOPE";
				}
				break;
			}
			if(cmd == "SHIFT"){
				if(this->shifted){
					res = "NOPE";
					break;
				} 
				if(game->doShift(data)){
					this->shifted = true;
					res = "OK";
				} else {
					res = "NOPE";
				}
				break;
			}
			if(cmd == "MOVE"){
				if(game->doMove(data)){
					this->shifted = false;
					res = "OK";
					game->nextTurn();
				} else {
					res = "NOPE";
					break;
				}
			}
			break;


		case GODMODE:
			if(cmd == "IAM"){ // nick
				if(setNickname(data)){
					state = WAITING;
					res = "OK";
				} else {
					res = "NOPE";
				}
			}
			if(cmd == "WHOISWAITING" || cmd == "WHOISTHERE"){
				res = "OK " + Player::getPlayers(WAITING);
			}
			if(cmd == "WHOISREADY"){
				res = "OK " + Player::getPlayers(READY);
			}
			if(cmd == "KILL"){
				Player::killPlayer(data);
				res = "OK";
			}
			break;

		default:
			break;
	}

	return res;

}


void Player::tell(std::string msg){
	connection->send(&msg);
}


////// STATICKÉ

void Player::killPlayer(std::string who){
	for(auto &p : players){
		if(p->nickname == who && p->getState() != DEAD){
			p->tell("SHOOT");
			p->setState(DEAD);
			break;
		}
	}
}

std::string Player::getReadyPlayers(Game * game){
	std::string str = "";
	for(auto &p : players){
		if(p->game == game && p->state == READY){
			str += p->nickname;
			str += ' ';
		}
	}
	return str;
}

std::string Player::getPlayers(int state){
 	std::string str = "";
	for(auto &player : players){
		if(player->state == state){
			str += player->nickname;
			str += ' ';
		}
	}
	return str;
}

std::string Player::getPlayersInfo(){
	std::string str = "";
	for(auto &p : players){
		str += p->nickname + " " + itos(p->getState()) + "\n";
	}
	return str;
}

// int Player::remove(Player * player){
// 	int pos = 0;

// 	for(auto &p : players){
// 		if(p == player){
// 			players.erase(players.begin() + pos);
// 			return 0;
// 		}
// 		pos++;
// 	}

// 	return 1;
// }


void Player::wipeall(){
	while(players.size()){
		delete players.back();
		players.pop_back();
	}
}


void Player::sendToAll(std::string msg){
	std::vector<Player *>::iterator nextpit;
	if(players.size()){
		nextpit = players.begin() + 1;
		players.front()->connection->send_async(&msg, boost::bind(&Player::sendToNext, nextpit, msg));
	}
}

void Player::sendToNext(std::vector<Player *>::iterator pit, std::string msg){
	std::vector<Player *>::iterator nextpit;

	if(pit != players.end()){
		nextpit = pit + 1;
		(*pit)->connection->send_async(&msg, boost::bind(&Player::sendToNext, nextpit, msg));
	}
	
}