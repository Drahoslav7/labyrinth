#pragma once

#include <boost/asio.hpp>
#include <string>
#include "../shared/connection.h"

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

	int sayHi();
	int setNickname();

public:
	// Client(address serveraddr);
	Client(boost::asio::io_service* io_service);
	start(address);
	~Client();
	string sendMessage(string message);
	int doAction();

};