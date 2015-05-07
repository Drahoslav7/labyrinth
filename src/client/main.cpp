#include <iostream>
#include <stdlib.h>
// #include <QtGui/QApplication>
// #include <QApplication>

using namespace std;

struct address{
	string hostname;
	int port;
};

int main(int argc, char const *argv[])
{
	address serveraddr;
	
	if(argc != 3){
		cerr << "Usage: client <host> <port>\n" << endl;
		return 1;
	}else{
		serveraddr.hostname = argv[1];
		char * endPtr = NULL;
		long int port;
		port = strtol(argv[2], &endPtr, 0);
		if(*endPtr != '\0' || port < 1 || port > 65535){
			cerr << "Port must be a number\n" << endl;
			return 1;
		}

		serveraddr.port = (int) port;
	}

	


	return 0;
}