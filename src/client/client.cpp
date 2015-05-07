#include "client.h"

#define getNewCmd(data); getline(cin, data); if(data == "KILL"){return 2;};

Client::Client(address serveraddr){	
	boost::asio::ip::tcp::resolver resolver(io_service);
	boost::asio::ip::tcp::resolver::query query(serveraddr.hostname, serveraddr.port);
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

	connection = new Connection(io_service);

	boost::asio::connect(connection->socket, endpoint_iterator);

	state = NONE;
};

Client::~Client(){
	delete connection;
}

std::string Client::sendMessage(string message){
	connection->send(&message);
	connection->receive(&message);
	return message;
};

int Client::doAction(){
	string command;

	switch(state){
		case NONE:
			if(sayHi()){
				return 1;
			}else{
				state = STARTED;
			}
			break;
		case STARTED:
			getNewCmd(command);
			if(command == "IAM"){
				if(setNickname()){
					return 1;
				}else{
					state = WAITING;
					break;
				}
			}
			if(command == "GODMODE"){
				state = GODMODE;
				break;
			}
			cout << "Zadej spravny prikaz. Nabidka: IAM" << endl;
			break;
		case WAITING:
			// getNewCmd(command);
			// if(command == "RESTART"){
			// 	state = STARTED;
			// 	break;
			// }
			// if(command == "WHOISTHERE"){
			// 	showPlayers();
			// 	break;
			// }
			// if(command == "CREATE"){
			// 	state = INVITING;
			// 	break;
			// }
			// cout << "Zadej spravny prikaz. Nabidka: RESTART" << endl;
			// break;
		case INVITED:
		case READY:
		case INVITING:
			// if(command == "WHOISTHERE"){
			// 	break;
			// }
		case CREATING:
		case PLAYING:
		case GODMODE:
			getNewCmd(command);
			string msg = sendMessage(command);
			if(msg == "DIE"){
				return 1;
			}
			cout << msg << endl;
			break;
	}

	return 0;
}

int Client::sayHi(){
	string command = "HI";	
	string msg = sendMessage(command);
	
	return (msg == "DIE") ? 1 : 0;
}

int Client::setNickname(){
	string data;
	cout << "Zadejte nick: " << endl;
	getline(cin, data);

	string msg = sendMessage("IAM "+data);
	
	while(msg != "OK"){
		if(msg == "DIE"){
			return 1;
		}
		cout << "Zadejte novy nick: " << endl;
		getline(cin, data);

		msg = sendMessage("IAM "+data);
	}

	return 0;
}

// int Client::showPlayers(){

// }