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
	readMsg = "";

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

void Client::quit(){
	running = false;
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
		readMsg = "";
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
					state = WAITING;				
					msg = "Nick je v poradku. Pokracuj.";
				}else{
					msg = "Nick je spatny. Zadejte novy:";					
				}
			}
			if(cmd == "GODMODE" && response == "OK"){
				msg = "A ted jsi buh";
				state = GODMODE;
			}
			break;
		case WAITING:		
			if(cmd == "WHOISTHERE" && response == "OK"){
				msg = formatPlayers(data);
			}
			
			if(cmd == "CREATE" && response == "OK"){
				state = INVITING;
				msg = "Nyni muzes pozvat hrace";
			}
			break;
		case INVITED:
			if(cmd == "ACCEPT" && response == "OK"){
				state = READY;
				msg = "Prijmul si hru. Cekej nez hra zacne.";
			}
			if(cmd == "DECLINE" && response == "OK"){
				state = WAITING;
				msg = "Hru jsi neprijmul. Pockej nez te nekdo pozve nebo zaloz hru.";
			}
			break;
		case READY:
			break;
		case INVITING:
			if(cmd == "INVITE"){
				if(response == "OK"){
					msg = "Hrac " + data + " byl pozvan";
				}
				if(response == "NOPE"){
					msg = "Hrac " + data + " nemohl byt pozvan";
				}
			}

			if(cmd == "WHOISTHERE" && response == "OK"){
				msg = formatPlayers(data);
			}
			break;
		case CREATING:
			break;
		case PLAYING:
			break;
		case GODMODE:
			if(cmd == "IAM"){
				if(response == "OK"){
					msg = "Nick je v poradku. Pokracuj.";
				}else{
					msg = "Nick je spatny. Zadejte novy:";					
				}
			}
			if(cmd == "GODMODE" && response == "OK"){
				msg = "Uz jednou buh jsi tak neser!";
			}
			if(cmd == "WHOISTHERE" && response == "OK"){
				msg = formatPlayers(data);
			}
			if(cmd == "KILL" && response == "OK"){
				msg = "Mas dalsi zarez na pazbe";
			}
			break;
	}

	return msg;
}

string Client::doActionServer(string recvCmd, string data){
	string msg;

	cout << "prikaz od serveru: --->" << recvCmd << "<---" << endl;

	if(recvCmd == "DIE"){
		running = false;
		msg = "Server se nastval!";
	}else if(recvCmd == "POKE"){
		msg = "Server te stouchnul!";
	}else if(recvCmd == "INVITATION"){
		msg = "Byl jsi pozvan do hry hracem " + data + ". Prijimas vyzvu?";
		state = INVITED;
	}else if(recvCmd == "SHOOT"){
		running = false;
		msg = "Byl jsi sestrelen bozi rukou parchante!";
	}else{
		msg = "SERVER --- WTF?!";
	}

	return msg;
}

string Client::formatPlayers(string data){
	string first, msg, position;
	msg = "Zacatek vypisu\n";
	int pos = 1;
	while(data != ""){
		split(data, ' ', &first, &data);
		msg += "\t" + itos(pos) + ". " + first + "\n";
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
			break;
		case INVITED:
			if(cmd == "ACCEPT"){
				return true;
			}
			if(cmd == "DECLINE"){
				return true;
			}
			break;
		case READY:
			break;
		case INVITING:
			if(cmd == "INVITE"){
				return true;
			}

			if(cmd == "WHOISTHERE"){
				return true;
			}
			break;
		case CREATING:
			break;
		case PLAYING:
			break;
		case GODMODE:
			if (cmd == "IAM"){
				return true;
			}
			if(cmd == "WHOISTHERE"){
				return true;
			}
			if(cmd == "GODMODE"){
				return true;
			}
			if(cmd == "KILL"){
				return true;
			}
			break;
	}

	return false;
} 
