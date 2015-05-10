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

void printColored(std::string text){
	#ifdef WIN32
	        int colors[5] = {FOREGROUND_INTENSITY, FOREGROUND_INTENSITY | FOREGROUND_RED, FOREGROUND_INTENSITY | FOREGROUND_GREEN, FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE, FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN};
	        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	        CONSOLE_SCREEN_BUFFER_INFO con_info;
	        GetConsoleScreenBufferInfo(hConsole, &con_info);
	        const int saved_colors = con_info.wAttributes;
	#else
	        const char *colors[5] = {"\033[1;30m", "\033[0;31m", "\033[0;32m", "\033[0;36m", "\033[0;33m"};
	#endif
	 
	for(auto &c : text){
		#ifdef WIN32
			if(islower(c)){
	        	std::cout << c;
				continue;
			}
			if(c == 'R'){				
			    SetConsoleTextAttribute(hConsole, colors[1]); 
	        	std::cout << c;
		        SetConsoleTextAttribute(hConsole, saved_colors);
				continue;
			}
			if(c == 'G'){				
			    SetConsoleTextAttribute(hConsole, colors[2]); 
	        	std::cout << c;
		        SetConsoleTextAttribute(hConsole, saved_colors);
				continue;
			}
			if(c == 'B'){				
			    SetConsoleTextAttribute(hConsole, colors[3]); 
	        	std::cout << c;
		        SetConsoleTextAttribute(hConsole, saved_colors);
				continue;
			}
			if(c == 'Y'){				
			    SetConsoleTextAttribute(hConsole, colors[4]); 
	        	std::cout << c;
		        SetConsoleTextAttribute(hConsole, saved_colors);
				continue;
			}

		    SetConsoleTextAttribute(hConsole, colors[0]); 
	    	std::cout << c;
	        SetConsoleTextAttribute(hConsole, saved_colors);
		#else
			if(islower(c)){
	        	std::cout << c;
				continue;
			}
			if(c == 'R'){				
		        std::cout << colors[1] + text + "\x1b[0m";
				continue;
			}
			if(c == 'G'){				
		        std::cout << colors[2] + text + "\x1b[0m";
				continue;
			}
			if(c == 'B'){				
		        std::cout << colors[3] + text + "\x1b[0m";
				continue;
			}
			if(c == 'Y'){				
		        std::cout << colors[4] + text + "\x1b[0m";
				continue;
			}
	        std::cout << colors[0] + text + "\x1b[0m";	
		#endif
	}
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

