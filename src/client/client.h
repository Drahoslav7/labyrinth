#include <boost/asio.hpp>
#include <string>
#include "../shared/connection.h"

using namespace std;

struct address{
	string hostname;
	string port;
};

class Client {

public:

private:
	boost::asio::io_service io_service;
	Connection * connection;

public:
	Client(address serveraddr);
	void sendMessage(string message);

};