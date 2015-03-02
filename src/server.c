#include <iostream>
#include "components.h"

using namespace std;

int main(int argc, char const *argv[])
{
	// prilad volani

	// staticky
	Block blockA (Shape::T);

	// cout << blockA.toString() << endl;

	// cout << "doprava"<< endl;
	// blockA.rotate(RIGHT);
	// cout << blockA.toString() << endl;
	// blockA.rotate(RIGHT);
	// cout << blockA.toString() << endl;
	// blockA.rotate(RIGHT);
	// cout << blockA.toString() << endl;

	// cout << "doleva"<< endl;
	// blockA.rotate(LEFT);
	// cout << blockA.toString() << endl;
	// blockA.rotate(LEFT);
	// cout << blockA.toString() << endl;
	// blockA.rotate(LEFT);
	// cout << blockA.toString() << endl;


	// dynamicky
	Block * blockB = new Block(Shape::T, LEFT);
	blockB->rotate(3*LEFT);


	Board board(9);
	cout << board.toString();

	return 0;
}


// format save souboru
// 
// T0 -- 
// L3 I1 T0 I0 T0 L2 L2
// I0 L2 L1 T3 I1 I0 T0
// T1 I0 T0 L2 T1 L1 T3
// 


