#include "highscore.h"
#include <gameengine.h>

using namespace engine;
using namespace std;

void stripSpaces(string &str);

Highscore::Highscore(GameEngine* game){
	//Read file and show the list of scores on the screen
	scoreList = vector<Label*>();
	file = new std::ifstream("scores.txt");
	string name = "", score = "0";
	int i = 0;

	header = new Label(200, 90, "Highscores!");
	header->setFont(Resource::loadFont("FreeUniversal-Bold.ttf", 18));
	game->addComponent(header);

	if (file->is_open()) {
		while (!file->eof()) {
			(*file) >> name >> score;
			if(name != ""){
				if(i == 10)
					throw file_exception("Too many entries in the highscore, please don't edit the scores.txt, cheater.");
				Label* temp = new Label(200, i*20+120, Logger::toStr(i+1) + ": " + name + " " + score);
				game->addComponent(temp);
				scoreList.push_back(temp);
				++i;
			}
			name = "";
			score = "0";
		}
	}

	file->close();
}

Highscore::~Highscore(){
	//Close file here and remove scores from the screen
	delete file;
}

void Highscore::addScore(string name, long score){
	stripSpaces(name);
	ifstream in("scores.txt");
	int i = 0;
	std::string oldname[10];
	long oldscore[10];
	bool stored = false;
	if (in.is_open()) {
		while (!in.eof()) {
			if(i == 10)
				break;

			in >> oldname[i] >> oldscore[i];
			++i;
		}
	}
	in.close();

	ofstream out("scores.txt");
	for(int k = 0; k < i; k++){
		if(oldscore[k] < score && !stored){
			out << name << " " << score << endl;
			stored = true;
			// if it raises k, an old line is overwritten instead of pushed down
			--i; 
		}
		if(k == i)
			break;
			
		// if not last line, add a newline
		if(oldname[k] != ""){
			out << oldname[k] << " " << oldscore[k];
			if(k != i - 1) 
				out << endl;
		}
	}

	// had less than 10 entries and ended up last in the list
	if(i != 10 && !stored){ 
		out << name << " " << score;
	}
	out.close();
}

/**
 * Source: http://www.daniweb.com/software-development/cpp/threads/71960
 */
void stripSpaces(string &str) {
	for (unsigned int i = 0; i < str.length(); i++){
		if (str[i]==' ') {
			str.erase(i,1);
			i--;
		}
	}
}