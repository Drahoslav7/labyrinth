#include "connection.h"

using namespace std;

Connection::Connection(boost::asio::io_service & io_service): socket(io_service){

}

Connection::~Connection(){
	socket.close();
}

void Connection::recv(std::string * target){
	boost::asio::read_until(
		socket,
		rbuffer,
		'\n'
	);

	std::istream readStream(&rbuffer);
	std::getline(readStream, *target);
	// target->erase(target->end()-1, target->end());
	rbuffer.consume(rbuffer.size());
	std::cout << "Recv:" << *target << std::endl;
}

void Connection::send(std::string * message){
	std::cout <<  "Send:" << *message << std::endl;
	*message += '\n';
	boost::asio::write(
		socket,
		boost::asio::buffer(*message),
		boost::asio::transfer_all()
	);
}


// void foo(){
// 	cout << "foo" << endl;
// }

void Connection::send_async(std::string * message, boost::function<void()> handler )
{
	boost::asio::async_write(
		socket,
		boost::asio::buffer(*message),
		boost::bind(handler)
	);
}


void Connection::recv_async(std::string * target,  boost::function<void()> handler )
{
	this->target = target;
	boost::asio::async_read_until(
		socket,
		rbuffer,
		'\n',
		boost::bind(&Connection::handle_recv, this, handler)
	);
}

void Connection::handle_recv(boost::function<void()> handler)
{
	target->assign(boost::asio::buffer_cast<const char*>(rbuffer.data()));
	*target = target->substr(0, target->size()-1);
	cout << "-->" << *target << "<--" << endl;
	handler();
}

