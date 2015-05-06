#include "../shared/err.h"
#include "server.h"
#include "player.h"


using namespace std;

/**
 * TOTO JE MAIN
 * @param  argc 
 * @param  argv 
 * @return      
 */
int main(int argc, char const *argv[])
{

	int port = Server::getPort(argc, argv);
	if(port == 0){
		err.stop(Err::INVALID_PORT);
	}



	// test bordel na herni plochu
	#if 0 

	// herni plocha
	Board * board = new Board(7);

	// balicek karet
	Pack cards(12);
	cout << cards.toString() << endl;
	//zamichat
	cards.shuffle();
	cout << cards.toString() << endl;

	//rozhazet po bludisti
	board->placeItems(cards.get());

	// vytvorit figurky
	Figure * gandalf = new Figure(Color::GREY);
	Figure * saruman = new Figure(Color::WHITE);
	// Figure * frodo = new Figure(Color::INVISIBLE);
	// Figure * bilbo = new Figure(Color::INVISIBLE);
	// Figure * glum = new Figure(Color::GREEN);

	// a umistit na pocatecni lokace
	board->placeFigure(gandalf);
	board->placeFigure(saruman);
	// board->placeFigure(frodo);
	// board->placeFigure(bilbo);
	// board->placeFigure(glum);

	cout << board->toString() << endl;

	// test hledani cesty
	Coords pos1(1,2);
	Coords pos2(12,12);

	bool result = board->isConnected(pos1, pos2);
	cout << "Cesta z [1,2] do [12,12] je:" << result << endl;

	Coords pos3(1,1);
	Coords pos4(2,2);

	result = board->isConnected(pos3, pos4);
	cout << "Cesta z [1,1] do [2,2] je:" << result << endl;

	Coords pos5(0,0);
	Coords pos6(0,1);

	result = board->isConnected(pos5, pos6);
	cout << "Cesta -> je:" << result << endl;

	Coords pos7(0,0);
	Coords pos8(1,0);

	result = board->isConnected(pos7, pos8);
	cout << "Cesta | je:" << result << endl;

	Coords pos9(1,1);
	Coords pos10(0,1);

	result = board->isConnected(pos9, pos10);
	cout << "Cesta ^ je:" << result << endl;

	Coords pos11(1,1);
	Coords pos12(1,0);

	result = board->isConnected(pos11, pos12);
	cout << "Cesta <- je:" << result << endl;
	
	#endif


	// test bordel na playera
	#if 0

	Player player1;

	player1.setNickname("Prdelka");

	Player player2;

	player2.setNickname("zadecek");

	Player player3;

	player3.setNickname("zadecek");

	Player player4;


	cout << "Nick je: " << player1.nickname << endl;
	cout << "Nick je: " << player2.nickname << endl;
	cout << "Nick je: " << player3.nickname << endl;
	cout << "Nick je: " << player4.nickname << endl;


	#endif 

	// try {
	// 	boost::asio::io_service io_service;
	// 	tcp_server server(io_service);
	// 	io_service.run();
		
	// } catch ( std::exception& e) {
	// 	std::cerr << e.what() << std::endl;
	// }




	return 0;
}


// format save souboru
// 
// T0 -- 
// L3 I1 T0 I0 T0 L2 L2
// I0 L2 L1 T3 I1 I0 T0
// T1 I0 T0 L2 T1 L1 T3
// 
