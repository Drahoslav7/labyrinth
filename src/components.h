#include <string>

const int LEFT = +1;
const int RIGHT = -1;

enum class Shape {
	I,
	L,
	T,
	O, // uzavreny block, nepouziva se
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



// hraci deska
class Board {

	Block*** board;
	int size;

public:
	Board(int);
	~Board();

	std::string toString();
};



