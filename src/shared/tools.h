#include <string>
#include <sstream>
#include <boost/asio.hpp>

void split(std::string what, char delim, std::string * left, std::string *right);
std::string itos(int);

// std::string strbuftos(boost::asio::streambuf strbuf);