#ifndef GUARD_GAME2048_H_ 
#define GUARD_GAME2048_H_
#define _CRT_SECURE_NO_WARNINGS

#include "Board.h"
#include <iostream>
#include <ctime>
#include <string>

class Game2048{
public:
	Game2048();
	~Game2048();
	int getscore();
	void move(Direction dir);
	void settime();
	time_t gettime();
	std::string getstarttime();
	Direction askdirection(std::ostream&, std::istream&);
	bool init();
	bool over();
    std::ostream& print(std::ostream&) const;
private:
	Board* board;
	Game2048(const Game2048& other);
	time_t begin;
	time_t end;
};

#endif
