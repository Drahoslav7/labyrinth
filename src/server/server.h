#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <vector>
#include "player.h"
// #include "game.h"


class Server;
class Connection;

///////////////////////////////////////////////////////////////

class Connection {

public:
	boost::asio::ip::tcp::socket socket;


public:
	Connection(boost::asio::io_service & io_service);
	~Connection();

};

/////////////////////////////////////////////

class Server {

public:
	static boost::asio::io_service * io_service;
	static int port;

	// std::vector<Game *> games;

private:
	Connection * listenningConnection;
	boost::asio::ip::tcp::acceptor acceptor;
	std::vector<Player *> waitingPlayers;

	Server(boost::asio::io_service & io_service);
	void acceptClient(Connection * conn, const boost::system::error_code& e);


public:
	static Server * getInstance();
	static void create(boost::asio::io_service * io_service, int port);
	static void kill(int sig);

	~Server();
	void stop();
	void listen();

	static int getPort(int, char const *[]);

};

