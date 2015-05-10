/**
 * Projekt ICP 
 * Labyrint
 * 
 * Drahoslav Bednář - xbedna55
 * Jiří Kunčák -xkunca55
 * 
 * 2014/2015
 *
 * 
 */

#pragma once

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <thread>
#include <string>
#include <vector>
#include <deque>
#include "../shared/connection.h"
#include "../shared/components.h"
#include "../shared/tools.h"
#include "../shared/debug.cpp"

#ifdef WIN32
	#define thread boost::thread
#else
	#define thread std::thread
#endif

using namespace std;

struct Address{
	string hostname;
	string port;
};

struct Scoreline{
	char color;
	string nickname;
	int points;
	char card;
};

class Client {

public:

	enum {
		NONE,
		STARTED,
		WAITING,
		INVITED,
		READY,
		INVITING, 
		CREATING_NEW,
		CREATING_LOAD, 
		PLAYING,
		ONTURN,
		GODMODE
	};

	int state;

private:
	Board * board = NULL;

	vector<Scoreline> scoreboard;
	vector<Figure*  > figures;

	boost::asio::io_service * io_service = NULL;
	Connection * connection = NULL;

	deque<std::string> sendedCmds;

	string readMsg;
	bool running;

	/**
	 * Callback funkce volana po navazani spojeni,
	 *  ktera dale vola funkci handleRead()
	 * @param error
	 */
	void handleConnect(const boost::system::error_code& error);
	
	/**
	 * Rekurzivne volana funkce pro asynchronni
	 *  cteni ze socketu a nasledne zpracovani
	 *  precteneho stringu
	 */
	void handleRead();

	/**
	 * Provede poslani zpravy serveru
	 * @param string zprava pro server
	 */
	void doSendCommand(std::string);

	/**
	 * Provede akci na zaklade odpovedi serveru na zadany prikazu
	 * @param string zadany prikaz
	 * @param string odpoved
	 * @param string data ktera server poslal
	 * @return
	 */
	string doActionClient(string, string, string);

	/**
	 * Provede akci na zaklade prikazu ktery prisel ze serveru
	 * @param string prikaz serveru
	 * @param string data poslana serverem
	 * @return
	 */
	string doActionServer(string, string);

	/**
	 * Zformatuje string hracu do tvaru pro vypis
	 * @param string nezformatovany retezec hracu
	 * @return string zformatovany retezec hracu
	 */
	string formatPlayers(string);

	/**
	 * Zformatuje string ulozenych her do tvaru pro vypis
	 * @param string nezformatovany retezec ulozenych her
	 * @return string zformatovany retezec ulozenych her
	 */
	string formatSavedGames(string);

	/**
	 * Vytiskne tabulku skore a hraci plochu na standartni vystup
	 */
	void printGamedesk();

	/**
	 * Zpracuje dodany string a naplni z nej tabulku skore
	 * @param string inicializacni retezec pro tabulku skore
	 */
	void initScoreboard(string);

	/**
	 * Vytvori figurku, nastavi ji barvu a umisti na pozici
	 * @param char x-ova souradnice
	 * @param char y-ova souradnice
	 * @param char barva figurky
	 */
	void initFigure(char, char, char);

	/**
	 * Provede rotaci volneho bloku
	 */
	void doRotate();

	/**
	 * Provede posun radku/sloupce popripade aktualizuje tabulku skore
	 * @param string formatovaci retezec obsahujici znak pro barvu,
	 *	souradnice posunu a znak pro pripadne nalezeni pokladu
	 */
	void doShift(string);

	/**
	 * Provede posun figurkou popripade aktualizuje tabulku skore
	 * @param string formatovaci retezec obsahujici znak pro barvu,
	 * 	souradnice posunu a znak pro pripadne nalezeni pokladu
	 */
	void doMove(string);

	/**
	 * Funkce pro aktualizaci tabulky a smazani pokladu z hraci plochy
	 * @param char znak pro novy poklad ktery hrac bude hledat
	 * @param char barva hrace ktery poklad nasel a kteremu bude pripsan bod
	 */
	void addPoint(char, char);

public:
	Client(boost::asio::io_service* io_service);
	~Client();

	/**
	 * Inicializuje TCP pripojeni k serveru
	 * @param Address hostname a port na ktery se ma pripojit
	 */
	void start(Address);

	/**
	 * Funkce pro poslani zpravy serveru pomoci funkce doSendCommand()
	 * @param string prvni cast zpravy
	 * @param string druha cast zpravy
	 */
	void sendCommand(std::string, std::string);
	
	/**
	 * Zjisti jestli klient ma stale bezet
	 * @return bool vraci promennou running
	 */
	bool isRunning();

	/**
	 * Nastavi promennou running na false
	 */
	void quit();

	/**
	 * Funkce pro kontrolu validity prikazu
	 * @param string kontrolovany prikaz
	 * @return bool vraci true/false podle toho
	 * 	jestli klient muze dany prikaz pouzit
	 */
	bool validCommand(string);

	/**
	 * Zformatuje do stringu pouzitelne prikazy
	 *  pro klienta v aktualnim stavu
	 * @return string zformatovane prikazy pro vypis
	 */
	string printCommands();

};