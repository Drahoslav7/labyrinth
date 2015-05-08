#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <string>
#include <deque>
#include "../shared/connection.h"
#include "../shared/tools.h"

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
		CREATING, 
		PLAYING,
		GODMODE
	};

	int state;

private:
	boost::asio::io_service * io_service;
	Connection * connection;

	deque<std::string> sendedCmds;

	string readMsg;

	int sayHi();
	int setNickname();
	int showPlayers();


	void doSendCommand(std::string);
public:

	void sendCommand(std::string, std::string);
	// Client(address serveraddr);
	Client(boost::asio::io_service* io_service);
	start(address);
	~Client();

	void handleConnect(const boost::system::error_code& error);
	void handleRead();

	void write(std::string);
	string sendMessage(string message);
	int doAction();

};