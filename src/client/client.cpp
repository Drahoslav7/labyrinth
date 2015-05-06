#include <iostream>
#include <stdlib.h>
#include <boost/asio.hpp>
// #include <QtGui/QApplication>
// #include <QApplication>

using namespace std;

struct address{
	string hostname;
	long int port;
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
		serveraddr.port = strtol(argv[2], &endPtr, 0);
		if(*endPtr != '\0'){
			cerr << "Port must be a number\n" << endl;
			return 1;
		}
	}

	cout << "Port je: " << serveraddr.port << endl;


	return 0;
}