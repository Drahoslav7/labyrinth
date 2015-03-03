#include "components.h"

/////////////////////////////////////////////////////////////
//  metody tridy block:

//konstruktor
Block::Block(Shape shape = Shape::I, int rotation = 0){ 
	this->shape = shape;
	this->oriantation = 0;
	top = left = right = bottom = false;
	switch(shape){
		case Shape::I:
			top = bottom = true;
			break;
		case Shape::L:
			top = right = true;
			break;
		case Shape::T:
			left = right = bottom = true;
			break;
	}
	rotate(rotation);
}

// destruktor
Block::rotate(int rotation){
	bool tmp;
	this->oriantation += rotation;
	this->oriantation %= 4;
	if(rotation > 0){ // to the left
		while(rotation--){
			tmp = left;
			left = top;
			top = right;
			right = bottom;
			bottom = tmp;
		}
	} else if(rotation < 0){ // to the right
		while(rotation++){
			tmp = right;
			right = top;
			top = left;
			left = bottom;
			bottom = tmp;
		}
	}
}


std::string Block::toString(){
	std::string str = "";
	str += isTop() ? "#.#" : "###" ;
	str += "\n";
	str += isLeft() ? "." : "#";
	str += ".";
	str += isRight() ? "." : "#";
	str += "\n";
	str += isBottom() ? "#.#" : "###";
	str += "\n";
	return str;
}



////////////////////////////////////////////////////////////////////
// metody tridy Board

/**
 * konstruktor
 * @param size velikost bludiste
 */
Board::Board(int size = 7){
	this->size = size;
	board = new Block** [size];

	for(int i = 0; i < size; ++i){			
		board[i] = new Block* [size];
		for (int j = 0; j < size; ++j){
			// rohy
			if(i == 0 && j == 0){ // levy horni
				board[i][j] = new Block(Shape::L, RIGHT);
				continue;
			}
			if(i == 0 && j == size-1){ // pravy horni
				board[i][j] = new Block(Shape::L, 2*RIGHT);
				continue;
			}
			if(i == size-1 && j == 0){ //levy dolni
				board[i][j] = new Block(Shape::L, 0);
				continue;
			}
			if(i == size-1 && j == size-1){ // pravy dolni
				board[i][j] = new Block(Shape::L, LEFT);
				continue;
			}
			// strany
			if(i == 0 && j%2 == 0){ // horni sude
				board[i][j] = new Block(Shape::T, 0);
				continue;
			}
			if(i == size-1 && j%2 == 0){ //dolni sude
				board[i][j] = new Block(Shape::T, 2*LEFT);
				continue;
			}
			if(j == 0 && i%2 == 0){ //leve sude
				board[i][j] = new Block(Shape::T, LEFT);
				continue;
			}
			if(j == size-1 && i%2 == 0){ // prave sude
				board[i][j] = new Block(Shape::T, RIGHT);
				continue;
			}
			// ostatni fixni
			if(i%2 == 0 && j%2 == 0){
				board[i][j] = new Block(Shape::T, (i+j)/2);
				continue;
			}
			//random
			board[i][j] = new Block(randomShape(), randomInt(3));

		}
	}

}

// destrucotr
Board::~Board(){
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j){
			delete board[i][j]; 
		}
		delete[] board[i];
	}
	delete[] board;
}

std::string Board::toString(){
	std::string str = "";
	for (int i = 0; i < size; ++i){
		for (int j = 0; j < size; ++j)
				str += board[i][j]->isTop() ? "#.#" : "###";
		str += "\n";
		for (int j = 0; j < size; ++j){
			str += board[i][j]->isLeft() ? "." : "#";
			str += ".";
			str += board[i][j]->isRight() ? "." : "#";
		}
		str += "\n";
		for (int j = 0; j < size; ++j)
				str += board[i][j]->isBottom() ? "#.#" : "###";
		str += "\n";
	}
	return str;
}


/////////////////////////////////////////////////////////////////////////
/// ostatni

int randomInt(int max){
	return 0;
}

Shape randomShape(){
	return Shape::O;

	// 5*5 = 25
	// 25/3 = 8.33
	// T 8 - (9-4) 	=> 3
	// L 8 - 4			=> 4
	// I 8 - 0 		=> 8
	// -> 3:4:8

	// 7*7 = 49
	// 49/3 = 16.33
	// T 16 - (16-4) 	=> 4
	// L 16 - 4 		=> 12
	// I 16 - 0 		=> 16
	// -> 4:12:16

	// 9*9 = 81
	// 81/3 = 27
	// T 27 - (25-4)	=> 6
	// L 27 - 4 		=> 23
	// I 27 - 0		=> 27
	// -> 6:23:27

	// 11*11 = 121
	// 121/3 = 40.33
	// T 40 - (36-4)	=> 8
	// L 40 - 4 		=> 32
	// I 40 - 0		=> 40

	// ((size/2)+1)*((size/2)+1) - 4

}



