#include <iostream>
#include <boost/asio.hpp>
#include "components.h"

using namespace std;

/**
 * Trida pro zpracovani chyb
 */
class Err {
private:
	/**
	 * Chybove hlasky
	 */
	string ERR_MSG[2] = {
		"",
		"invalid port",
	};

public:
	/**
	 * Navratov kody (index do ERR_MSG)
	 */
	enum ecode {
		OK,
		INVALID_PORT,
	};

	/**
	 * Vypise chybovou hlasku na stderr a ukonci program
	 * @param  ecode Navratov kod
	 * @return       vraci Navratov kod
	 */
	ecode stop(ecode ecode){
		cerr << ERR_MSG[ecode] << endl;
		exit (ecode);
	}

	/**
	 * Vypise chybovou hlasku na stderr
	 * @param  ecode Navratov kod programu
	 * @return       Navratov kod programu
	 */
	ecode print(ecode ecode){
		cerr << ERR_MSG[ecode] << endl;
		return ecode;
	}
	
} err; // rovnou vytvorit globalni instanci tridy


/**
 * Vraci port zadany jako prvni argument programu
 * nebo nulu pokud je neco spatne
 * @param  argc 
 * @param  argv 
 * @return      port
 */
int getPort(int argc, char const *argv[]){
	int port = 0;
	if(argc > 1)
		port = atoi(argv[1]);
	return port;
}


/**
 * TOTO JE MAIN
 * @param  argc 
 * @param  argv 
 * @return      
 */
int main(int argc, char const *argv[])
{

	int port = getPort(argc, argv);
	if(port == 0){
		err.stop(Err::INVALID_PORT);
	}



	// herni plocha
	Board * board = new Board(7);

	std::vector<Item> items;
	for (Item i = 1; i <= 12; ++i){
		items.push_back(i);
	}

	board->placeItems(&items);
	Figure * gandalf = new Figure(Color::GREY);
	Figure * saruman = new Figure(Color::WHITE);
	// Figure * frodo = new Figure(Color::INVISIBLE);
	// Figure * bilbo = new Figure(Color::INVISIBLE);
	// Figure * glum = new Figure(Color::GREEN);

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




	return 0;
}


// format save souboru
// 
// T0 -- 
// L3 I1 T0 I0 T0 L2 L2
// I0 L2 L1 T3 I1 I0 T0
// T1 I0 T0 L2 T1 L1 T3
// 


