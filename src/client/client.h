#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include <deque>
#include "../shared/connection.h"
#include "../shared/tools.h"
#include "../shared/debug.cpp"


using namespace std;

struct address{
	string hostname;
	string port;
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
	boost::asio::io_service * io_service;
	Connection * connection;

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
	string formatPlayers(string data);
public:
	void sendCommand(std::string, std::string);
	Client(boost::asio::io_service* io_service);
	start(address);
	~Client();

	bool isRunning();
	void quit();
	void write(std::string);
	string sendMessage(string);
	bool validCommand(string);

};