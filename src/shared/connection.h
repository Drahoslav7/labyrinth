#pragma once

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include "debug.cpp"

class Connection {

public:
	boost::asio::ip::tcp::socket socket;
	boost::asio::streambuf rbuffer;
	std::string * target;

public:
	Connection(boost::asio::io_service & io_service);
	~Connection();

	void receive(std::string * target);
	void send(std::string * message);
};