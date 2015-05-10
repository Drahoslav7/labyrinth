/**
 * Projekt ICP 
 * Labyrint
 * 
 * Drahoslav Bednář - xbedna55
 * Jiří Kunčák -xkunca55
 * 
 * 2014/2015
 *
 * modul: debug
 * 	pomocný modul pro testovací výpisy
 */

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