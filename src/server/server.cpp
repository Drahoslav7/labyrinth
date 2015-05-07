#include "server.h"

using namespace std;

/////////////////////////////////
///

boost::asio::io_service * Server::io_service;
int Server::port;


Server::Server(boost::asio::io_service & io_service):
	acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
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

	Connection * connection = new Connection(acceptor.get_io_service());

	listenningConnection = connection;

	acceptor.async_accept(
		connection->socket,
		boost::bind(&Server::acceptClient, this, connection, boost::asio::placeholders::error)
	);

}

void Server::stop(){
	Server::io_service->stop();
	acceptor.close();

	games.clear();
	// for(auto &player : waitingPlayers){
	// 	delete player;
	// }
	// waitingPlayers.clear();
	Player::wipeall();

	delete listenningConnection;

}

void Server::acceptClient(Connection * connection, const boost::system::error_code& e){ // handler
	PRD("client accept 1"); 

	if(!e){
		Player * player = new Player(connection); // todo předat connection
		// waitingPlayers.push_back(player);
		listen();
	}else{
		Server::kill(0);
	}

	PRD("client accept 2");
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

// std::string Server::getPlayers(){
// 	std::string players = "";
// 	for(auto &player : waitingPlayers){
// 		players += player->nickname;
// 		players += ' ';
// 	}
// 	return players;
// }


// void Server::removePlayer(Player player){
// 	int pos = 0;

// 	for(auto &p : waitingPlayers){
// 		if(p == player){
// 			waitingPlayers.erase(waitingPlayers.begin() + pos);
// 			return 0;
// 		}
// 		pos++;
// 	}

// 	return 1;
// }