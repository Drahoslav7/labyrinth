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