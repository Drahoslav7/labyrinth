#include "player.h"

using namespace std;

vector<Player *> Player::players = vector<Player *>();

Player::Player(Connection *con){
	connection = con;
	nickname = "";
	state = NONE;
	id = players.size();
	players.push_back(this);

	thread = boost::thread(&Player::work, this);
	PRD("Player thread");
};


Player::~Player(){
	thread.join();
	// remove(this);
	delete connection;
};


int Player::setNickname(string nickname){
	if(nickname.length() < 3 || nickname.length() > 17){
		return 2;
	}

	for(auto &player : players){
		for(auto &c : nickname){
			if(!isalnum(c)){
				return 2;
			}
		}

		if(player->state != DEAD && player->nickname == nickname){
			return 1;
		}
	}

	this->nickname = nickname;
	this->state = WAITING;

	return 0;
};

// int Player::acceptInvite(Game *game){
// 	if(game->addPlayer(this)){
// 		return 1;
// 	}

// 	this->state = READY;

// 	return 0;
// };


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


	state = DEAD;

	PRD("player work2");
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
				if(!setNickname(data)){
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
				res = "OK";
			}
			if(cmd == "WHOISTHERE"){
				res = "HERE " + Player::getPlayers(WAITING);
			}
			break;

		case INVITING:
			if(cmd == "INVITE"){ // koho
				// invite(data);
				res = "OK";
			}
			if(cmd == "WHOISTHERE"){
				res = "HERE " + Player::getPlayers(WAITING);
			}
			break;

		case INVITED:
			if(cmd == "ACCEPT"){
				//acceptInvite()
				state = READY;
				res = "OK";
			}
			if(cmd == "REJECT"){
				state = WAITING;
				res = "OK";
			}
			break;

		case GODMODE:
			if(cmd == "IAM"){ // nick
				if(!setNickname(data)){
					state = WAITING;
					res = "OK";
				} else {
					res = "NOPE";
				}
			}
			if(cmd == "WHOISTHERE"){
				res = "HERE " + Player::getPlayers(WAITING);
			}
			break;

		default:
			break;
	}

	return res;

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