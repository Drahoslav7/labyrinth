#include "player.h"

using namespace std;
vector<Player *> Player::players = vector<Player *>();

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

		if(player->nickname == nickname){
			return 1;
		}
	}

	this->nickname = nickname;
	this->state = WAITING;

	return 0;
};

int Player::acceptInvite(Game *game){
	if(game->addPlayer(this)){
		return 1;
	}

	this->state = READY;

	return 0;
};

void Player::work(){

	std::string msg;

	PRD("player work");

	bool ok = true;
	while(ok){
		try{
			connection->receive(&msg);
		} catch (boost::system::system_error & e) {
			ok = false;
			// game->remove_player(this); // todo vykopnout neposlušneho hrače?
		}
		std::cout << "msg: " << msg << endl;
		
		string response = "OK";

		connection->send(&response);

		if(msg == "DIE"){
			break;
		}
	}

	PRD("player work2");
}