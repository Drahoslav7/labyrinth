#include <iostream>
#include <stdlib.h>
#include "client.h"

// #include <QtGui/QApplication>
// #include <QApplication>

using namespace std;

int main(int argc, char const *argv[])
{
	address serveraddr;
	
	if(argc != 3){
		cerr << "Usage: client <host> <port>\n" << endl;
		return 1;
	}else{
		serveraddr.hostname = argv[1];
		serveraddr.port = argv[2];
	}

	Client client(serveraddr);

	client.sendMessage("HELLODOLLY\n");


	return 0;
}