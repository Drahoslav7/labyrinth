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

// std::string strbuftos(boost::asio::streambuf * strbuf){
// 	std::ostringstream ss;
// 	ss << *strbuf;
// 	std::string s = ss.str();
// 	return s;
// }

// std::string strbuftos(boost::asio::streambuf& streambuf)
// {
//  return {buffers_begin(streambuf.data()), 
//          buffers_end(streambuf.data())};
// }