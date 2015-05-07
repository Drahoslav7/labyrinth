#include "connection.h"

using namespace std;

Connection::Connection(boost::asio::io_service & io_service): socket(io_service){

}

Connection::~Connection(){
	socket.close();
}

void Connection::receive(std::string * target){
	boost::asio::read_until(
		socket,
		rbuffer,
		'\n'
	);

	std::istream readStream(&rbuffer);
	std::getline(readStream, *target);
	// target->erase(target->end()-1, target->end());
	rbuffer.consume(rbuffer.size());
	// std::cout << "Recv:" << *target << std::endl;
}

void Connection::send(std::string * message){
	std::cout << *message << std::endl;
	*message += '\n';
	boost::asio::write(
		socket,
		boost::asio::buffer(*message),
		boost::asio::transfer_all()
	);
}

