#include "game.h"

using namespace std;
vector<Game *> Game::games = vector<Game *>();

bool Game::addPlayer(Player *player){
	if(players.size() == 4 && players[0]->getState() != Player::INVITING){
		return false;
	}

	players.push_back(player);
	player->setState(Player::READY);

	return true;
};

int Game::removePlayer(Player *player){
	int pos = 0;

	for(auto &eachplayer : players){
		if(eachplayer->nickname == player->nickname){
			players.erase(players.begin() + pos);
			return 0;
		}

		pos++;
	}

	return 1;
};

bool Game::isSomeoneReady(){
	for(auto &p : players){
		if(p->getState() == Player::READY && p != getLeader()){
			return true;
		}
	}
	return false;
}

Player * Game::getLeader(){
	return players[0];
}


bool Game::save(std::string filename){
	if(!filename.size())
		return false;
	for(auto &c : filename){
		if(!isalnum(c)){
			return false;
		}
	}

	filename = "saves/" + itos(this->players.size()) + filename + ".lab.txt";

	// poskladat obsah
	std::string content = "";
	for(auto &p : players ){
		content += colortoc(p->figure->getColor());
		content += p->figure->pos.x + 'A';
		content += p->figure->pos.y + 'A';
		content += (p->card + 'a' - 1);
		content += p->score + '0';
		if(p != players.back()){
			content += ';';
		}
	}
	content += " " + board->toFormat() + " " + pack->toString();

	//ulozit
	fstream file;
	file.open(filename.c_str(), ios::in);
	if(file.is_open()){
		file.close();
		return false;
	}
	file.open(filename.c_str(), ios::out);
	file << content;
	file.close();
	return true;
}

std::string Game::getGameList(){
	std::string gamelist = "";
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("saves")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir (dir)) != NULL) {
			// cout << "file:" << ent->d_name << endl;
			if(ent->d_name[0] == this->players.size() + '0'){ // spravny pocet hracu
				for(int i = 1; ent->d_name[i] != '.' && ent->d_name[i] != '\0'; i++){
					gamelist += ent->d_name[i]; 
				}
				gamelist += ' ';
			}
			// cout << "gamelist:" << gamelist << endl;
		}
		closedir (dir);
	} else {
		cout << "can't open saves dir" << endl;
	}
	return gamelist;
}


bool Game::loadGame(std::string filename){ // akce LOAD
	filename = "saves/" + itos(this->players.size()) + filename + ".lab.txt";
	// nacist
	std::cout << "filetoload:" << filename << endl;
	
	fstream file;
	file.open(filename.c_str());
	if(!file.is_open()){
		return false;
	}
	PP;
	std::string content((std::istreambuf_iterator<char>(file)),
		std::istreambuf_iterator<char>());
	PP;

	cout << "content:" << content << endl;
	std::string boardFormat;
	std::string usersInfo;
	std::string packString;
	split(content, ' ', &usersInfo, &boardFormat);
	split(boardFormat, ' ', &boardFormat, &packString);
	PP;

	board = new Board(boardFormat); // umisti i itemy
	PP;


	int origPackSize = packString.size();
	Color color = Color::INVISIBLE;
	int cnt=0;
	for(auto &p : players ){
		// rozdat figurku
		p->figure = new Figure(++color);
		board->placeFigure(p->figure);
		p->figure->pos.x = usersInfo[1 + cnt] - 'A';
		p->figure->pos.y = usersInfo[2 + cnt] - 'A';
		p->card = usersInfo[3 + cnt] - 'a' + 1;
		p->score = usersInfo[4 + cnt] - '0';
		origPackSize += p->score;
 		origPackSize++;
		cnt += 6;
	}
	PP;

	pack = new Pack(packString, origPackSize);
	PP;

	std::cout << "fileloaded:" << filename << endl;

	return true;
}


bool Game::createGame(std::string sets){ // akce NEW
	if(sets.size() != 2){
		return false;
	}
	if(!(sets[0] >= 'A' && sets[0] <= 'E')){
		return false;
	}
	if(sets[1] != '0' && sets[1] != '1'){
		return false;
	}

	int boardSize = (sets[0] - 'A' + 2)*2 + 1;
	int packSize = (sets[1] - '0') * 12 + 12;

	board = new Board(boardSize);

	pack = new Pack(packSize);

	pack->shuffle();

	board->placeItems(pack->get());

	Color color = Color::INVISIBLE;
	for(auto &p : players ){
		// rozdat figurku
		p->figure = new Figure(++color);
		board->placeFigure(p->figure);
		// liznout
		p->card = pack->get()->back();
		pack->get()->pop_back();
		// 
		p->score = 0;
	}
	return true;
}

void Game::sendInit(){
	std::string initCmd = "INIT ";
	for(auto &p : players){
		initCmd += colortoc(p->figure->getColor());
		initCmd += p->figure->pos.x + 'A';
		initCmd += p->figure->pos.y + 'A';
		initCmd += p->card + 'a' - 1;
		initCmd += p->score + '0';
		initCmd += p->nickname;
		if(p != players.back()){
			initCmd += ';';
		}
		p->setState(Player::PLAYING);
	}

	initCmd += " " + board->toFormat();

	sendUpdate(initCmd);

};

void Game::sendUpdate(std::string data){
	for(auto &p : players){
		p->tell(data);
	}

	std::cout << board->toString() << endl;

}

void Game::nextTurn(){
	int max = players.size();
	if(onTurnIndex == -1){
		onTurnIndex = randomInt(max);
	}
	else{
		onTurnIndex += 1;
		onTurnIndex %= max;		
	}
	players[onTurnIndex]->tell("YOURTURN");
}


bool Game::doRotate(){
	board->rotate();
	sendUpdate("ROTATED");
	return true;
}

bool Game::doShift(std::string data){
	if(!board->shift(data)){
		return false;
	}

	char fig = '-';
	char c = '0';
	for(auto &p : players){
		if(board->pickUpItem(p->figure->pos, p->card)){
			p->card = pack->draw();
			c = (p->card + 'a' - 1);
			fig = colortoc(p->figure->getColor());
			p->score++;
		}
	}

	std::string msg = "SHIFTED ";
	msg += fig;
	msg += data;
	msg += c;
	sendUpdate(msg);
	return true; 
}

bool Game::doMove(std::string data){
	if(data.size() != 2){
		return false;
	}

	Player * me = players[onTurnIndex];

	Coords dest(data[0] - 'A', data[1] - 'A');
	Coords orig = me->figure->pos;

	if(!board->isConnected(orig, dest)){
		return false;
	}

	me->figure->pos = dest;
	// sebrat a liznout novou;
	char c = '0';
	if(board->pickUpItem(dest, me->card)){
		me->card = pack->draw();
		c = (me->card + 'a' - 1);
		me->score++;
	}

	std::string msg = "MOVED ";
	msg += colortoc(me->figure->getColor());
	msg += data;
	msg += c;
	sendUpdate(msg);
	return true;
}


bool Game::isWin(){
	bool win;
	for(auto &winner : players){
		if(winner->score == (pack->getOrigSize()/players.size()) ){ // win
			for(auto &p : players){
				p->endGame(winner->nickname, p == players.back());
			}
			return true;
		}
	}
	return false;
}


// void Game::cancel(){
// 	for(auto &p : players){
// 		p->leaveGame();
// 	}
// 	delete this;
// }
