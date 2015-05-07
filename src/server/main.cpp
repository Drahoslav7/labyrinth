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


// format save souboru
// 
// T0 -- 
// L3 I1 T0 I0 T0 L2 L2
// I0 L2 L1 T3 I1 I0 T0
// T1 I0 T0 L2 T1 L1 T3
// 
