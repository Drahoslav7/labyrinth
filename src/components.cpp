#include <ctime>
#include <boost/random.hpp>
#include "components.h"

/////////////////////////////////////////////////////////////////////////
/// ostatni

std::time_t now = std::time(0);
boost::random::mt19937 gen{static_cast<std::uint32_t>(now)};

int randomInt(int max){
	return gen() % max; // <0;max)
}

Shape randomShape(){
	int i = randomInt(3);
	switch(i){
		case 0:
			return Shape::I;
			break;
		case 1:
			return Shape::L;
			break;
		case 2:
			return Shape::T;
			break;
	}
	return Shape::O;
}


/////////////////////////////////////////////////////////////
//  metody tridy block:

//konstruktor

// random
Block::Block() : Block(randomShape(), randomInt(4)) {};
// nerandom
Block::Block(Shape shape, int rotation){
	this->item = NONE;
	this->shape = shape;
	this->orientation = 0;
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
	this->orientation += rotation;
	this->orientation %= 4;
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
	str += isTop() ? "# #" : "###" ;
	str += "\n";
	str += isLeft() ? " " : "#";
	str += item ? item + '@' : ' ';
	str += isRight() ? " " : "#";
	str += "\n";
	str += isBottom() ? "# #" : "###";
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
			board[i][j] = new Block;

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
				str += board[i][j]->isTop() ? "# #|" : "###|";
		str += "\n";
		for (int j = 0; j < size; ++j){
			str += board[i][j]->isLeft() ? " " : "#";
			str += board[i][j]->item?(board[i][j]->item + '@'):' ';
			str += board[i][j]->isRight() ? " |" : "#|";
		}
		str += "\n";
		for (int j = 0; j < size; ++j)
				str += board[i][j]->isBottom() ? "# #|" : "###|";
		str += "\n";
		for (int j = 0; j < size; ++j)
				str += "---+";
		str += "\n";
	}
	return str;
}


// rozmistit predmety po hracim poli
bool Board::placeItems(std::vector<Item> * items){
	Coords pos;
	for(Item item : *items){
		do {
			pos.x = randomInt(size);
			pos.y = randomInt(size);
		} while(board[pos.x][pos.y]->item != NONE);

		board[pos.x][pos.y]->item  = item;
	}

}


// umisti figurku na hraci pole
bool Board::placeFigure(Figure * figure){
	int size = figurestack.size();
	if(size <= 4){
		return false;
	}
	figurestack.push_back(figure);
	switch(size){
		case 0:
			figure->pos.x = 0;
			figure->pos.y = 0;
			break;
		case 1:
			figure->pos.x = size-1;
			figure->pos.y = size-1;
			break;
		case 2:
			figure->pos.x = 0;
			figure->pos.y = size-1;
			break;
		case 3:
			figure->pos.x = size-1;
			figure->pos.y = 0;
			break;
	}
	return true;

};


Block * Board::shift(Direction to, unsigned i, Block * pushedBlock){
	Block * poppedBlock = pushedBlock;
	if(i >= size || i%2 == 0){ // nejde shiftovat
		return poppedBlock;
	}
	if(to == Direction::RIGHT){
		poppedBlock = board[i][size-1];
		for (int j = size-1; j > 0 ; --j){
			board[i][j] = board[i][j-1];
		}
		board[i][0] = pushedBlock;
	}
	if(to == Direction::LEFT){
		poppedBlock = board[i][0];
		for (int j = 0; j < size-1; ++j){
			board[i][j] = board[i][j+1];
		}
		board[i][size-1] = pushedBlock;
	}
	if(to == Direction::DOWN){
		poppedBlock = board[size-1][i];
		for (int j = size-1; j > 0 ; --j){
			board[j][i] = board[j-1][i];
		}
		board[0][i] = pushedBlock;
	}
	if(to == Direction::UP){
		poppedBlock = board[0][i];
		for (int j = 0; j < size-1; ++j){
			board[j][i] = board[j+1][i];
		}
		board[size-1][i] = pushedBlock;
	}

	return poppedBlock;
}

bool Board::blocksConnection(Coords startcoords, Coords endcoords){
	Block* startBlock = board[startcoords.x][startcoords.y];
	Block* endBlock = board[endcoords.x][endcoords.y];

	// end je nad start blokem
	if(startcoords.y == endcoords.y && startcoords.x-endcoords.x == 1){
		if(startBlock->isTop() && endBlock->isBottom()){
			return true;
		}else{
			return false;
		}
	}
	// end je pod start blokem
	if(startcoords.y == endcoords.y && endcoords.x-startcoords.x == 1){
		if(startBlock->isBottom() && endBlock->isTop()){
			return true;
		}else{
			return false;
		}
	}

	// end je napravo od start bloku
	if(startcoords.x == endcoords.x && endcoords.y-startcoords.y == 1){
		if(startBlock->isRight() && endBlock->isLeft()){
			return true;
		}else{
			return false;
		}
	}

	// end je nalevo od start bloku
	if(startcoords.x == endcoords.x && startcoords.y-endcoords.y == 1){
		if(startBlock->isRight() && endBlock->isLeft()){
			return true;
		}else{
			return false;
		}
	}

	return false;
}

bool isInQueue(Coords coordinates, std::deque<Coords>* queue){
	for(auto pos : *queue){
		if(pos == coordinates){
			return true;
		}
	}

	return false;
}

bool Board::isConnected(Coords startcoords, Coords endcoords){
	std::deque<Coords> open_queue;
	std::deque<Coords> closed_queue;

	if(blocksConnection(startcoords, endcoords)){
		return true;
	}

	open_queue.push_back(startcoords);

	Coords actcoords;
	Coords topcoords;
	Coords rightcoords;
	Coords leftcoords;
	Coords bottomcoords;

	while(!open_queue.empty()){
		actcoords = open_queue.front();
		open_queue.pop_front();
		
		// kontrola vrchniho bloku
		topcoords.x = actcoords.x + 1;
		topcoords.y = actcoords.y; 
		
		if(topcoords.x < size){
			if(!isInQueue(topcoords, &open_queue) && !isInQueue(topcoords, &closed_queue) && blocksConnection(topcoords, actcoords)){
				if(topcoords == endcoords){
					return true;
				}
				open_queue.push_back(topcoords);
			}
		}

		// kontrola praveho bloku
		rightcoords.x = actcoords.x;
		rightcoords.y = actcoords.y + 1;

		if(rightcoords.y < size){
			if(!isInQueue(rightcoords, &open_queue) && !isInQueue(rightcoords, &closed_queue) && blocksConnection(rightcoords, actcoords)){
				if(rightcoords == endcoords){
					return true;
				}
				open_queue.push_back(rightcoords);
			}
		}

		// kontrola leveho bloku
		leftcoords.x = actcoords.x;
		leftcoords.y = actcoords.y - 1;

		if(leftcoords.y >= 0){
			if(!isInQueue(leftcoords, &open_queue) && !isInQueue(leftcoords, &closed_queue) && blocksConnection(leftcoords, actcoords)){
				if(leftcoords == endcoords){
					return true;
				}
				open_queue.push_back(leftcoords);
			}
		}

		// kontrola spodniho bloku
		bottomcoords.x = actcoords.x - 1;
		bottomcoords.y = actcoords.y;

		if(bottomcoords.x >= 0){
			if(!isInQueue(bottomcoords, &open_queue) && !isInQueue(bottomcoords, &closed_queue) && blocksConnection(bottomcoords, actcoords)){
				if(bottomcoords == endcoords){
					return true;
				}
				open_queue.push_back(bottomcoords);
			}
		}

		// nahrani do closed pole po rozvinutí uzlu
		closed_queue.push_back(actcoords);
	}

	return false;
}