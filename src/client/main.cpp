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

	boost::thread t(boost::bind(&boost::asio::io_service::run, io_service));

	string line;
	string cmd = "HI";
	string data = "";

	client.sendCommand(cmd, data);

	while(getline(cin, line) && client.isRunning()){
		split(line, ' ', &cmd, &data);

		if(cmd == "SUICIDE"){
			break;
		}

		if(client.validCommand(cmd)){
			client.sendCommand(cmd, data);
		}else{
			cout << "Neplatny prikaz zadajte novy:" << endl;
		}

	}

	cout << "Program se ukoncuje" << endl;

	client.quit();
	//t.join(); <--- to tu nikdy nemelo byt
	
	return 0;
}