#include <string>
#include <deque>

#include <vector>

typedef char Item;

const Item NONE = 0;
const Item XX = 4;

const int LEFT = +1;
const int RIGHT = -1;



enum class Color {
	INVISIBLE,
	BLACK,
	WHITE,
	GREY,
	RED,
	GREEN,
	BLUE,
	ORANGE,
	PURPLE,
	YELLOW,
};

enum class Shape {
	I,
	L,
	T,
	O, // uzavreny block, nepouziva se
};

enum class Direction {
	LEFT,
	RIGHT,
	UP,
	DOWN,
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
	int orientation;

	
public:
	Item item;
	// constructory
	Block();
	Block(Shape, int = 0);

	// dalsi metody
	rotate(int);

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

	std::string toString();

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
	int x;
	int y;

	bool operator==(Coords &pos2){
		return (this->x == pos2.x && this->y == pos2.y);
	} 
};

class Figure {

	Color color;
public:
	Figure () {
		this->color = Color::INVISIBLE;
	}
	Figure (Color color){
		this->color = color;
	}
	Color getColor(){
		return color;
	}

	Coords pos;
};


// hraci deska
class Board {

	Block*** board;
	Block* spareBlock;

	int size;

	bool blocksConnection(Coords, Coords);
	std::vector<Figure *> figurestack;

public:
	Board(int);
	~Board();

	std::string toString();

	// push pop
	bool shift(Direction, unsigned);

	bool isConnected(Coords, Coords); 

	// umistit itemy
	bool placeItems(std::vector<Item> *);
	// umisti figurku na hraci pole
	bool placeFigure(Figure *);

};



