#include <string>
#include <sstream>
#include <iostream>
#include <boost/asio.hpp>

void split(std::string what, char delim, std::string * left, std::string *right);
std::string itos(int);
void printColored(std::string);

// std::string strbuftos(boost::asio::streambuf& strbuf);