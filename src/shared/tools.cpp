/**
 * Projekt ICP 
 * Labyrint
 * 
 * Drahoslav Bednář - xbedna55
 * Jiří Kunčák -xkunca55
 * 
 * 2014/2015
 *
 * modul: tools
 * 	obsahuje obecné pomocné funkce nesouvisející přímo s labyrintem
 */

#include "tools.h"

void split(std::string what, char delim, std::string * left, std::string *right){
	*left = "";
	*right = "";
	bool toRight = false;
	for(auto &c : what){
		if(c == delim && !toRight) {
			toRight = true;
			continue;
		}
		if(toRight)
			*right += c;
		else
			*left += c;
	}
}

std::string itos(int i){
	std::string str;
	std::ostringstream oss;
	oss << i;
	str = oss.str();
	return str;
}
