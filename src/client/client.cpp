#include "client.h"

#define getNewCmd(data); getline(cin, data); if(data == "SUICIDE"){return 2;};


Client::Client(boost::asio::io_service* io_service){
	Client::io_service = io_service;
}

Client::start(address serveraddr){	
	boost::asio::ip::tcp::resolver resolver(*io_service);
	boost::asio::ip::tcp::resolver::query query(serveraddr.hostname, serveraddr.port);
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

	connection = new Connection(*io_service);

	boost::asio::async_connect(connection->socket, endpoint_iterator,
		boost::bind(&Client::handleConnect,this,
		  boost::asio::placeholders::error
		)
	);

	state = NONE;
};

Client::~Client(){
	delete connection;
}

void Client::handleConnect(const boost::system::error_code& error){
	// if (!error) {
	// boost::asio::async_read(connection->socket,
	// 	boost::asio::buffer(readMsg, chat_message::header_length),
	// 	  boost::bind(&Client::handleRead, this,
	// 	    boost::asio::placeholders::error
	// 	  )
	// 	);
	// }
	if (!error){
		connection->recv_async(&readMsg, boost::bind(&Client::handleRead, this));
	}
}

void Client::handleRead(){

	std::cout << "msg:" << readMsg << endl;

	// readMsg;

	string cmd = sendedCmds.front();



	//sendedCmds.pop_front();
	
	connection->recv_async(&readMsg, boost::bind(&Client::handleRead, this));

}



void Client::sendCommand(std::string command, std::string data){
	sendedCmds.push_back(command);
	io_service->post(boost::bind(&Client::doSendCommand, this, command+" "+data));
}

void Client::doSendCommand(std::string command){
	connection->send(&command);
}

std::string Client::sendMessage(string message){
	connection->send(&message);
	connection->recv(&message);
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
			if(command == "IAMp"){
				sendMessage("IAM prdelka");
				state = WAITING;
				break;
			}
			cout << "Zadej spravny prikaz. Nabidka: IAM" << endl;
			break;
		case WAITING:
			getNewCmd(command);
			if(command == "RESTART"){
				state = STARTED;
				break;
			}
			if(command == "WHOISTHERE"){
				if(showPlayers()){
					return 1;
				}
				break;
			}
			if(command == "CREATE"){
				state = INVITING;
				break;
			}
			cout << "Zadej spravny prikaz. Nabidka: RESTART" << endl;
			break;
		case INVITED:
		case READY:
		case INVITING:
			getNewCmd(command);
			if(command == "WHOISTHERE"){
				if(showPlayers()){
					return 1;
				}
				break;
			}
			break;
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

int Client::showPlayers(){
	string msg = sendMessage("WHOISTHERE");
	if(msg == "DIE"){
		return 1;
	}

	string first, body;
	split(msg, ' ', &first, &body);
	if(first == "HERE"){
		cout << "Zacatek vypisu" << endl;
		int pos = 1;
		while(body != ""){
			split(body, ' ', &first, &body);
			cout << '\t' << pos << ". " << first << endl;
			pos++;
		}
		cout << "Konec vypisu" << endl;
	}else{
		return 1;
	}

	return 0;
}
