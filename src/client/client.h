/**
 * Projekt ICP 
 * Labyrint
 * 
 * Drahoslav Bednář - xbedna55
 * Jiří Kunčák -xkunca55
 * 
 * 2014/2015
 *
 * 
 */

#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <thread>
#include <string>
#include <vector>
#include <deque>
#include "../shared/connection.h"
#include "../shared/components.h"
#include "../shared/tools.h"
#include "../shared/debug.cpp"

#ifdef WIN32
	#define thread boost::thread
#else
	#define thread std::thread
#endif

using namespace std;

struct Address{
	string hostname;
	string port;
};

struct Scoreline{
	char color;
	string nickname;
	int points;
	char card;
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
		ONTURN,
		GODMODE
	};

	int state;

private:
	Board * board = NULL;

	vector<Scoreline> scoreboard;
	vector<Figure*  > figures;

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
	string formatSavedGames(string);
	string formatScoreboard();
	void initScoreboard(string);
	void initFigure(char, char, char);

	void doRotate();
	void doShift(string);
	void doMove(string);
	void addPoint(char, char);

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
	string printCommands();

};