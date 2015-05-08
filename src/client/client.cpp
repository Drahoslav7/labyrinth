#include "client.h"

Client::Client(boost::asio::io_service* io_service){
	Client::io_service = io_service;
}

Client::start(address serveraddr){	
	boost::asio::ip::tcp::resolver resolver(*io_service);
	boost::asio::ip::tcp::resolver::query query(serveraddr.hostname, serveraddr.port);
	boost::asio::ip::tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

	connection = new Connection(*io_service);

	// boost::asio::async_connect(connection->socket, endpoint_iterator,
	// 	boost::bind(&Client::handleConnect,this,
	// 	  boost::asio::placeholders::error
	// 	)
	// );

	boost::asio::connect(connection->socket, endpoint_iterator);
	connection->recv_async(&readMsg, boost::bind(&Client::handleRead, this));

	state = NONE;
	running = true;
};

Client::~Client(){
	delete connection;
}

bool Client::isRunning(){
	return running;
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

	string rcvCmd, rcvData, msg, cmd;
	split(readMsg, ' ', &rcvCmd, &rcvData);
	if(rcvCmd != "OK" && rcvCmd != "NOPE"){
		msg = doActionServer(rcvCmd, rcvData);
	}else{
		cmd = sendedCmds.front();
		msg = doActionClient(cmd, rcvCmd, rcvData);
		sendedCmds.pop_front();
	}

	cout << msg << endl;

	if(isRunning()){
		connection->recv_async(&readMsg, boost::bind(&Client::handleRead, this));
	}
}


void Client::sendCommand(std::string command, std::string data=""){
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

string Client::doActionClient(string cmd, string response, string data){
	string msg = "";

	switch(state){
		case NONE:
			if(cmd == "HI" && response == "OK"){
				state = STARTED;
				msg = "Zadejte svuj nick:";
			}
			break;
		case STARTED:
			if(cmd == "IAM"){
				if(response == "OK"){
					if(state == GODMODE){
						state = GODMODE;					
					}else{
						state = WAITING;
					}
				}else{
					msg = "Nick je spatny. Zadejte novy:";					
				}
			}
			if(cmd == "GODMODE" && response == "OK"){
				msg = "A ted jsi buh";
				state = GODMODE;
				break;
			}
			break;
		case WAITING:		
			if(cmd == "WHOISTHERE" && response == "OK"){
				msg = formatPlayers(data);
				break;
			}
			
			if(cmd == "CREATE" && response == "OK"){
				state = INVITING;
				break;
			}
			cout << "Zadej spravny prikaz. Nabidka: RESTART" << endl;
			break;
		case INVITED:
		case READY:
		case INVITING:
			break;
		case CREATING:
		case PLAYING:
		case GODMODE:
			break;
	}

	return msg;
}

string Client::doActionServer(string recvCmd, string data){
	string msg;

	if(recvCmd == "DIE"){
		running = false;
		msg = "Server se nastval!";
	}else{
		msg = "Server po mě něco chce";
	}

	return msg;
}

string Client::formatPlayers(string data){
	ostringstream oss;
	string first, msg, position;
	split(msg, ' ', &first, &data);
	msg += "Zacatek vypisu\n";
	int pos = 1;
	while(data != ""){
		split(data, ' ', &first, &data);
		oss << pos;
		msg = msg + "\t" + oss.str() + ". " + first + "\n";
		pos++;
	}
	msg += "Konec vypisu";

	return msg;
}

bool Client::validCommand(string cmd){

	switch(state){
		case STARTED:
			if (cmd == "IAM"){
				return true;
			}
			if (cmd == "GODMODE"){
				return true;
			}
			break;
		case WAITING:		
			if(cmd == "WHOISTHERE"){
				return true;
			}
			if(cmd == "CREATE"){
				return true;
			}
		case INVITED:
		case READY:
		case INVITING:
			break;
		case CREATING:
		case PLAYING:
		case GODMODE:
			if (cmd == "IAM"){
				return true;
			}
			if(cmd == "WHOISTHERE"){
				return true;
			}
			break;
	}

	return false;
} 
