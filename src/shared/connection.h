#define BOOST_ASIO_ENABLE_BUFFER_DEBUGGING 1

#pragma once

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>
#include "tools.h"
#include "debug.cpp"

class Connection {

public:
	boost::asio::ip::tcp::socket socket;
	boost::asio::streambuf rbuffer;
	std::string * target;

public:
	Connection(boost::asio::io_service & bbbb);
	~Connection();

	void recv(std::string * target);
	void send(std::string * message);
	void recv_async(std::string * target, boost::function<void()> );
	void send_async(std::string * message, boost::function<void()> );

private:
	void handle_recv(boost::function<void()>);

};

