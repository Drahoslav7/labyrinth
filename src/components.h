#include <string>

const int LEFT = +1;
const int RIGHT = -1;

enum class Shape {
	I,
	L,
	T,
	O,
};

int randomInt(int);
Shape randomShape();

// policko bludiste
class Block {

	bool top;
	bool right;
	bool left;
	bool bottom;

	// pro ucely vykreslovani:
	Shape shape;
	int oriantation;
	
public:
	// constructory
	Block(){
		Block(Shape::I,0);
	}
	Block(Shape shape){
		Block(shape,0);
	}
	Block(Shape, int);

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



