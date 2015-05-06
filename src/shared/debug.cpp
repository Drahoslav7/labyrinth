#ifdef DEBUG
	#include <iostream>
	#define PRD(X) std::cout << X << std::endl
	#define PP std::cout << "Prdel!" << std::endl
	#define PZ std::cout << "Zadek!" << std::endl
#else
	#define PRD
	#define PP
	#define PZ
#endif