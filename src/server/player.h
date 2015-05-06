#include <vector>
#include <string>

using namespace std;

class Player{
public:
	string nickname;

	enum {
		STARTED,
		WAITING,
		INVITED,
		READY,
		INVITING, 
		CREATING, 
		PLAYING
	};

	int state;

	Player(){
		nickname = "";
		state = STARTED;
		id = players.size();
		players.push_back(this);
	};

	~Player(){
    	players[id]=NULL;
   	};

	int setNickname(string nickname);

private:

	int id;
	static vector<Player *> players;


};