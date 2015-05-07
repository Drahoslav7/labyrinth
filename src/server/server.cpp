#include "server.h"
#include "../shared/components.h"
#include "../shared/debug.cpp"

using namespace std;


//////////////////////////////////
///
Connection::Connection(boost::asio::io_service & io_service): socket(io_service){

}

Connection::~Connection(){
	socket.close();
}


/////////////////////////////////
///

boost::asio::io_service * Server::io_service;
int Server::port;


Server::Server(boost::asio::io_service & io_service): acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
{

}

Server::~Server(){

}


void Server::create(boost::asio::io_service * io_service, int port){
	Server::io_service = io_service; 
	Server::port = port;
}


Server * Server::getInstance(){
	static Server instance(*(Server::io_service));
	return &instance;
}


void Server::listen(){

	Connection * conn = new Connection(acceptor.get_io_service());

	listenningConnection = conn;

	acceptor.async_accept(
		conn->socket,
		boost::bind(&Server::acceptClient, this, conn, boost::asio::placeholders::error)
		
	);

}

void Server::stop(){
	Server::io_service->stop();
	acceptor.close();

	games.clear();
	waitingPlayers.clear();

	delete listenningConnection;

}

void Server::acceptClient(Connection * conn, const boost::system::error_code& e){
	if(!e){
		Player * player = new Player(); // todo předat conn
		waitingPlayers.push_back(player);
		listen();
	}else{
		Server::kill(0);
	}
}


void Server::kill(int sig){
	std::cout << "exiting" << endl;
	Server::getInstance()->stop();
}


/**
 * Vraci port zadany jako prvni argument programu
 * nebo nulu pokud je neco spatne
 * @param  argc 
 * @param  argv 
 * @return      port
 */
int Server::getPort(int argc, char const *argv[]){
	int port = 0;
	if(argc > 1)
		port = atoi(argv[1]);
	return port;
}


