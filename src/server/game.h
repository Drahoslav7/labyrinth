#include <vector>
#include <string>

using namespace std;

class Game{
public:
	Game(){
		id = games.size();
		games.push_back(this);
	};

	~Game(){
    	games[id]=NULL;
   	};


private:

	int id;
	static std::vector<Game *> games;
};