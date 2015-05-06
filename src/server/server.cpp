#include "server.h"
#include "../shared/components.h"

using namespace std;


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




