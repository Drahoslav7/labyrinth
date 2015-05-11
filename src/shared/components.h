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

#include <string>
#include <deque>
#include <vector>
#include "debug.cpp"


int randomInt(int max);

typedef char Item;
// typedef char Card;

const Item NONE = 0;

const int LEFT = +1;
const int RIGHT = -1;

/**
 * Barva figurky
 */
enum class Color {
	INVISIBLE,
	
	RED,
	GREEN,
	BLUE,
	YELLOW,

	ORANGE,
	BLACK,
	WHITE,
	GREY,
	PURPLE,
};


inline Color operator++( Color& x ) { return x = (Color)(((int)(x) + 1)); }

inline char colortoc(Color color){
	switch(color){
			case Color::RED:
				return 'R';
			case Color::GREEN:
				return 'G';
			case Color::YELLOW:
				return 'Y';
			case Color::BLUE:
				return 'B';
			default:
				return '-';
	}
}

inline Color ctocolor(char color){
	switch(color){
			case 'R':
				return Color::RED;
			case 'G':
				return Color::GREEN;
			case 'Y':
				return Color::YELLOW;
			case 'B':
				return Color::BLUE;
			default:
				return Color::INVISIBLE;
	}
}

inline std::string colortos(Color color){
	std::string strcolor = "";
	strcolor += colortoc(color);
	return strcolor;
}


/**
 * Tvar políčka
 */
enum class Shape {
	I,
	L,
	T,
	O, // uzavreny block, nepouziva se
};

inline char shapetoc(Shape shape){
	switch(shape){
		case Shape::T:
			return 'T';
		case Shape::L:
			return 'L';
		case Shape::I:
			return 'I';
		default:
			return 'O';		
	}
}

// pro shiftovani
enum class Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
};


//souradnice policka bludiste
class Coords{

public:
	Coords(){
		this->x = 0;
		this->y = 0;
	};

	Coords(int x, int y){
		this->x = x;
		this->y = y;
	};
	unsigned int x;
	unsigned int y;

	bool operator==(Coords &pos2){
		return (this->x == pos2.x && this->y == pos2.y);
	} 
	bool operator!=(Coords &pos2){
		return !(*this == pos2);
	}
};

class Pack {

	std::vector<Item> cards;
	int originalSize = 0;
public:

	Pack() : Pack(12) {};

	/**
	 * Zkkonstruuje balíček seřazený o dané velikosti
	 */
	Pack(unsigned int count){
		for (Item i = 1; i <= count; ++i)
			cards.push_back(i);
		originalSize = count;
	}

	/**
	 * Zkonstruje balíček z řetězce získaného ze zouboru uložené hry
	 */
	Pack(std::string str, int origs){
		for(auto &i : str){
			cards.push_back(i - 'a' + 1);
		}
		this->originalSize = origs;
	}

	/**
	 * Provede sejmutí karty z vrchu balíčku
	 * @return karta
	 */
	Item draw(){
		Item item = cards.back();
		cards.pop_back();
		return item;
	}

	std::vector<Item> * get(){
		return &cards;
	}

	/**
	 * Náhodně zamíchá balíček
	 */
	void shuffle();

	int getOrigSize(){
		return originalSize;
	};

	std::string toString();

};


// figurka
class Figure {

	Color color;
public:
	Figure () {
		this->color = Color::INVISIBLE;
		pos = {-1,-1};
	}
	Figure (Color color){
		pos = {-1,-1};
		this->color = color;
	}
	Color getColor(){
		return color;
	}

	void changePos(Coords newpos){
		prevPos = pos;
		pos = newpos;
	}

	Coords pos;
	Coords prevPos;
};

// policko bludiste
class Block {

private:
	bool top;
	bool right;
	bool left;
	bool bottom;

	// pro ucely vykreslovani:
	Shape shape;
	unsigned int orientation;

	Item item;
	
public:
	// constructory
	Block();
	Block(Shape, int = 0);

	// dalsi metody
	void rotate(int);

	bool isTop(){
		return top;
	}
	bool isBottom(){
		return bottom;
	}
	bool isLeft(){
		return left;
	}
	bool isRight(){
		return right;
	}
	Shape getShape(){
		return shape;
	}
	int getRotation(){
		return orientation;
	}
	Item getItem(){
		return item;
	}
	void setItem(Item item){
		this->item = item;
	}

	/**
	 * Vrátí reprezentaci bloku v textové podobě
	 * @return řetězec
	 */
	std::string toString();

};

// hraci deska
class Board {

private:
	int size;
	Block*** board;
	Block* spareBlock;

	std::vector<Figure *> figurestack;

	bool canPass(Coords, Coords);

public:
	Board(int);
	Board(std::string);
	~Board();

	/**
	 * Vrátí textovou reprezentaci herní plochy
	 * pro učel vytištění na obrazovku
	 * @return řetězec
	 */
	std::string toString();

	/**
	 * Vrací textovou reprezentaci herní plochy
	 * do formátu pro použití v ukládaném souboru
	 * @return řetězec
	 */
	std::string toFormat();

	/**
	 * Provede rotaci volného bloku desky
	 * @param n počet čtvrtotoček doprava
	 */
	void rotate(int n = 1){
		spareBlock->rotate(n*RIGHT);
	}
	
	/**
	 * provede vsunutí volného bloku do herní desky
	 * @param  Direction směr vsunutí
	 * @param  unsigned  index sloupce nebo řady
	 * @return           true pokud se akce provedla
	 */
	bool shift(Direction, unsigned);
	bool shift(std::string);

	/**
	 * Testuje zda jsou dva bloky propojené
	 * @param  Coords souřeadnice počátečního bloku
	 * @param  Coords souřadnice cílového bloku
	 * @return        true pokud lze projít z počítečního do cílového
	 */
	bool isConnected(Coords, Coords); 

	/**
	 * Náhodně rozmístí pžedměty do hrací desky	
	 * @param  std::vector<Item> * ukazatel na vektor předmětů
	 * @return        true pokud se provede korektně
	 */
	bool placeItems(std::vector<Item> *);

	/**
	 * Umístí figurku do hrací desky v pevně daném pořadí
	 * @param  Figure *  ukazatel na vkládanou figurku
	 * @return        false pokud už jsou na desce 4 figurky
	 */
	bool placeFigure(Figure *);

	/**
	 * Odstraní z políčka na daných souřadnicích daný předmět, pokud tam je
	 * @param  Coords souřadnice políčka
	 * @param  Item   předmět
	 * @return        false pokud na daném místě není item
	 */
	bool pickUpItem(Coords, Item);
	/**
	 * Odstraní předmět z herní plochy, pokud na ní je
	 * @param  Item předmět
	 * @return      false pokud na herí desce předmět není
	 */
	bool pickUpItem(Item);

	/**
	 * kontrola zda se lze z dané pozice někam pohnout, kromě zakázané pozice (předchozí tah)
	 * @param  Coords aktuální pozice
	 * @param  Coords zakázaná pozice
	 * @return        true pokud lze provést tah
	 */
	bool canDoAnyMove(Coords, Coords);

};



