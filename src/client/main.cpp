#include <iostream>
#include "client.h"

// #include <QtGui/QApplication>
// #include <QApplication>

// ///////////////////////////

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


	boost::shared_ptr<boost::asio::io_service> io_service(new boost::asio::io_service());

	Client client(io_service.get());
	client.start(serveraddr);


	while(1){
		int ecode = client.doAction();
		if(ecode == 1){
			cout << "Server se nastval!" << endl;
			break;
		}else if(ecode == 2){	
			cout << "Ukonceni aplikace!" << endl;
			break;
		}
	}

	return 0;
}