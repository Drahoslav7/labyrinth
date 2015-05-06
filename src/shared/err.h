#include <iostream>


/**
 * Trida pro zpracovani chyb
 */

using namespace std;

class Err {
private:
	/**
	 * Chybove hlasky
	 */
	const string ERR_MSG[2] = {
		"",
		"invalid port",
	};

public:
	/**
	 * Navratov kody (index do ERR_MSG)
	 */
	enum ecode {
		OK,
		INVALID_PORT,
	};

	/**
	 * Vypise chybovou hlasku na stderr a ukonci program
	 * @param  ecode Navratov kod
	 * @return       vraci Navratov kod
	 */
	ecode stop(ecode ecode){
		cerr << ERR_MSG[ecode] << endl;
		exit (ecode);
	}

	/**
	 * Vypise chybovou hlasku na stderr
	 * @param  ecode Navratov kod programu
	 * @return       Navratov kod programu
	 */
	ecode print(ecode ecode){
		cerr << ERR_MSG[ecode] << endl;
		return ecode;
	}
	
} err; // rovnou vytvorit globalni instanci tridy
