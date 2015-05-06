#include <boost/asio.hpp>
// #include <QtGui/QApplication>
// #include <QApplication>

using namespace std;

struct address{
	string hostname;
	int port;
};

int main(int argc, char const *argv[])
{
	if(argc != 3){
		cerr << "Usage: client <host> <port>\n" << endl;
		return 1;
	}else{
		address serveraddrr;
		serveraddr.hostname = argv[1];
		serveraddr.port = argv[2];
	}


	return 0;
}