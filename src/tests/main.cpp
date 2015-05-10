/**
 * Projekt ICP 
 * Labyrint
 * 
 * Drahoslav Bednář - xbedna55
 * Jiří Kunčák -xkunca55
 * 
 * 2014/2015
 *
 * modul: test
 * 	modul pro rychlé testování funkčnosti jednotvlivých modulů
 */

#include <iostream>
#include "../shared/err.h"
#include "../shared/components.h"
#include "../server/game.h"
#include "../server/player.h"

using namespace std;

int main(int argc, char const *argv[]){	

	// test bordel na herni plochu
	#if 1


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
	Figure * gandalf = new Figure(Color::RED);
	Figure * saruman = new Figure(Color::GREEN);
	// Figure * frodo = new Figure(Color::INVISIBLE);
	// Figure * bilbo = new Figure(Color::INVISIBLE);
	// Figure * glum = new Figure(Color::GREEN);

	// a umistit na pocatecni lokace
	board->placeFigure(gandalf);
	board->placeFigure(saruman);
	// board->placeFigure(frodo);
	// board->placeFigure(bilbo);
	// board->placeFigure(glum);

	printColored(board->toString()); 

	#endif

	#if 0

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


	// bordel test na Game 
	#if 0

	Player player1;

	player1.setNickname("Prdelka");

	Player player2;

	player2.setNickname("zadecek");

	Player player3;

	player3.setNickname("prsicka");

	Player player4;

	player4.setNickname("pipinka");

	Game game(&player1);

	game.addPlayer(&player2);
	game.addPlayer(&player3);
	game.addPlayer(&player4);

	for(auto &player : game.players){
		cout << "Hraci tu jsou takovi: " << player->nickname << endl;
	}

	game.removePlayer(&player3);

	cout << "Pocet hracu je: " << game.players.size() << endl;
	for(auto &player : game.players){
		cout << "Hraci tu jsou takovi: " << player->nickname << endl;
	}

	#endif 

	#if 0

	string word = "zadek";
	string word2 = "prdelka";

	cout << word+word2 << endl;

	#endif

	#if 0

	int word = -1;
	int word2 = 5;

	cout << word%word2 << endl;

	#endif
}