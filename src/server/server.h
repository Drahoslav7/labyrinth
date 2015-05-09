#pragma once

class Server;

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <vector>
#include "player.h"
#include "game.h"
#include "../shared/connection.h"
#include "../shared/components.h"
#include "../shared/debug.cpp"

/////////////////////////////////////////////

class Server {

public:
	static boost::asio::io_service * io_service;
	static int port;
	static boost::asio::deadline_timer * timer;

	std::vector<Game *> games;

private:
	Connection * listenningConnection = NULL;
	boost::asio::ip::tcp::acceptor acceptor;
	// std::vector<Player *> waitingPlayers;

	Server(boost::asio::io_service & io_service);
	void acceptClient(Connection * conn, const boost::system::error_code& e);

	static void maintenance();

public:
	static Server * getInstance();
	static void create(boost::asio::io_service * io_service, int port);
	static void kill(int sig);

	~Server();
	void stop();
	void listen();

	static int getPort(int, char const *[]);

};

