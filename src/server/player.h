#include <vector>
#include <string>

using namespace std;

class Player{
public:
	string nickname;
	enum {STARTED, WAITING, CREATING, CONNECTING, READY, PLAYING};

	int status;

	Player(){
		nickname = "";
		status = STARTED;
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