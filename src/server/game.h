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
class Game;

#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <dirent.h>
#include "player.h"
#include "../shared/components.h"

using namespace std;

class Game{
public:

	/**
	 * Vytvoří novou instanci hry a rovnou do ní přidá hráče jako lídra
	 */
	Game(Player *player){
		id = games.size();
		games.push_back(this);

		players.push_back(player);
		onTurnIndex =-1;
	};

	~Game(){
		games[id]=NULL;
	};

	/**
	 * Přidá hráče do hry
	 * @param  player ukazatel na přidávaného hráče
	 * @return        vrací bool pokud už není hra plná
	 */
	bool addPlayer(Player *player);
	int removePlayer(Player *player);

	/**
	 * Vrací lídra hry 
	 * @return ukazatel na hráče která zakládal hru
	 */
	Player * getLeader();
	
	/**
	 * kontroluje zda je možné odstratrovat hry
	 * @return true pokud alespon jeden hráč přijal pozvánkuke hře
	 */
	bool isSomeoneReady();

	/**
	 * Uloží stav hry do souboru pro možnost pozdějšího načtení
	 * @param  filename název hry pod kterým bude přístupná pro nahrání
	 * @return          false pokud se nepovedo uložit do souboru
	 */
	bool save(std::string filename);

	/**
	 * Vrací textový seznam uložených her které je možné nahrát (závisí na počtu hráčů ve hře)
	 * @return názvy her oddělené mezerami
	 */
	std::string getGameList();

	/**
	 * Nahraje uloženou hru ze souboru a inicializuje hru (desku, figurky atd.)
	 * @param  filename název hry
	 * @return          false pokud se neodařilo načíst hru
	 */
	bool loadGame(std::string filename);
	
	/**
	 * Vytvoří novou hru - inicializuje desku, figurky atd.
	 * @param  settings dvouznakový řetězec, první znak A-F udává velikost hrací plochy, druhý 0/1 velikost balíku karet
	 * @return          false pokud byly předány čpatné data
	 */
	bool createGame(std::string settings);

	/**
	 * Pošle všem hráčům v dané hře iniciační informace (rozložení bloků, figurek, předmětů, skore atd..)
	 */
	void sendInit();

	/**
	 * Pošle všem hráčů dané hry informaci o akci (tahu) provedené hráčem (MOVE, SHIFT, ROTATE, ENDGAME...)
	 * @param std::string odesílané informace
	 */
	void sendUpdate(std::string);

	/**
	 * nastaví tah na dalšího hráče a pošle mu informaci YOURTURN
	 */
	void nextTurn();

	/**
	 * kontrola zda je dan hráč na tahu
	 * @param  p odkaz na hráče
	 * @return   true pokud je hráč na tahu
	 */
	bool isOnTurn(Player *p){ return p == players[onTurnIndex]; }

	/**
	 * Zpracuje požadavek od klienta na provedení akce rotace.
	 * @return true pokud byl tah proveden
	 */
	bool doRotate();

	/**
	 * Zpracuje požadavek od klienta na provedení akce posunu bloku
	 * @param  data parametry posunu - dvouznakový žetězec - směr a index sloupce/řady
	 * @return      true pokud bylo tah proveden
	 */
	bool doShift(std::string data);

	/**
	 * Zpracuje požadavek od klienta na provedení akce přesunu figurky
	 * @param  data souřadnice přesunu - dvouznakový řetězec - XY
	 * @return      [description]
	 */
	bool doMove(std::string data);

	/**
	 * Kontrola zda nedošlo ke splnění podmínek pro výhru
	 * pokud ano odešle informaci o vítězi hráčům 
	 * @return bool pokud je vyhráno
	 */
	bool isWin();

	/**
	 * Odešle všem hráčm informaci o násilném ukončení hry jiným hráčem a odstraní je z aktuální hry
	 */
	void cancel(); 

private:

	int onTurnIndex;
	vector<Player *> players;
	int id;
	Board * board;
	Pack * pack;


	static vector<Game *> games;
};