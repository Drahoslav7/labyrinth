#include <string>
#include <deque>

const int LEFT = +1;
const int RIGHT = -1;

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


// hraci deska
class Board {

	Block*** board;
	int size;

	bool blocksConnection(Coords, Coords);

public:
	Board(int);
	~Board();

	std::string toString();

	// push pop
	Block * shift(Direction, unsigned, Block*);

	bool isConnected(Coords, Coords); 
};



