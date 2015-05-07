#include "client.h"

Client::Client(address serveraddr){	
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(serveraddr.hostname, serveraddr.port);
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

	connection = new Connection(io_service);

	boost::asio::connect(connection->socket, endpoint_iterator);
};

std::string Client::sendMessage(string message){
	connection->send(&message);
	connection->receive(&message);
	return message;
};

