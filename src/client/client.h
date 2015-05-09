#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include <vector>
#include <deque>
#include "../shared/connection.h"
#include "../shared/components.h"
#include "../shared/tools.h"
#include "../shared/debug.cpp"


using namespace std;

struct Address{
	string hostname;
	string port;
};

struct Scoreline{
	char color;
	string nickname;
	int points;
};

class Client {

public:

	enum {
		NONE,
		STARTED,
		WAITING,
		INVITED,
		READY,
		INVITING, 
		CREATING_NEW,
		CREATING_LOAD, 
		PLAYING,
		GODMODE
	};

	int state;

private:
	Board * board = NULL;

	vector<Scoreline> scoreboard;

	boost::asio::io_service * io_service = NULL;
	Connection * connection = NULL;

	deque<std::string> sendedCmds;

	string readMsg;
	bool running;

	int sayHi();
	int setNickname();
	int showPlayers();

	void handleConnect(const boost::system::error_code& error);
	void handleRead();

	void doSendCommand(std::string);
	string doActionClient(string, string, string);
	string doActionServer(string, string);
	string formatPlayers(string);
	string formatScoreboard();
	void initScoreboard(string);

public:
	void sendCommand(std::string, std::string);
	Client(boost::asio::io_service* io_service);
	void start(Address);
	~Client();

	bool isRunning();
	void quit();
	void write(std::string);
	string sendMessage(string);
	bool validCommand(string);

};