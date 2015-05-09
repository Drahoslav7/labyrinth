#pragma once
class Player;

#include <vector>
#include <string>
#include <boost/thread.hpp>
#include "server.h"
#include "../shared/connection.h"
#include "../shared/tools.h"
#include "../shared/components.h"
#include "server.h"
#include "game.h"

using namespace std;

class Player{
public:
	string nickname;
	Connection *connection;


	enum {
		NONE,
		STARTED,
		WAITING,
		INVITED,
		READY,
		INVITING, 
		CREATING, 
		PLAYING,
		DEAD,
		GODMODE,
		CREATING_NEW,
		CREATING_LOAD,
	};


	Player(Connection *con);
	~Player();

	bool setNickname(string nickname);
	bool invitePlayer(string nickname);
	int acceptInvite();
	int declineInvice();
	void leaveGame();

	int getState(){	return state; }
	void setState(int state){ this->state = state; }

	void tell(std::string msg);
	Figure * figure;

private:
	int state;
	int id;
	boost::thread thread;
	Game *game = NULL;


	void work();
	std::string handleUserRequest(std::string, std::string);

	static vector<Player *> players;
	static std::string getPlayers(int state);

public:
	static void killPlayer(std::string who);
	static std::string getPlayersInfo();
	static std::string getReadyPlayers(Game *);
	static void wipeall();
	static void pokeAll(){
		sendToAll("POKE");
	};
	static void sendToAll(std::string msg);
	static void sendToNext(std::vector<Player *>::iterator pit, std::string msg);
	// static int remove(Player * player);

};