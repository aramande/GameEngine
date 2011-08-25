#ifndef HIGHSCORE_H
#define HIGHSCORE_H

#include <gameengine.h>
#include <vector>

class Highscore{
	std::ifstream* file;
	std::vector<engine::Label*> scoreList;
	engine::Label* header;
public:
	Highscore(){}
	Highscore(engine::GameEngine* game);
	~Highscore();
	static void addScore(std::string name, long score);
};

#endif
