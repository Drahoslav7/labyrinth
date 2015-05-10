/**
 * Projekt ICP 
 * Labyrint
 * 
 * Drahoslav Bednář - xbedna55
 * Jiří Kunčák -xkunca55
 * 
 * 2014/2015
 *
 * modul: main
 * Vstupní bod programu Serveru 
 */


#include <iostream>
#include "../shared/err.h"
#include "server.h"
#include "game.h"
#include "player.h"

using namespace std;

/**
 * TOTO JE MAIN
 * @param  argc 
 * @param  argv 
 * @return      
 */
int main(int argc, char const *argv[])
{

	
	int port = Server::getPort(argc, argv);
	if(port == 0){
		err.stop(Err::INVALID_PORT);
	}

	signal(SIGINT, Server::kill);
	
	try {
		boost::shared_ptr<boost::asio::io_service> io_service(new boost::asio::io_service());

		Server::create(io_service.get(), port);

		Server::getInstance()->listen();
		io_service.get()->run();
		
	} catch (std::exception & e) {
		std::cerr << e.what() << std::endl;
	}
	return 0;
}

