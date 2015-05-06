#include <vector>
#include <string>
#include "player.h"
#include "../shared/components.h"

using namespace std;

class Game{
public:

	vector<Player *> players;

	Game(Player *player){
		id = games.size();
		games.push_back(this);

		players.push_back(player);
	};

	~Game(){
    	games[id]=NULL;
   	};

private:

	int id;
	static vector<Game *> games;
};