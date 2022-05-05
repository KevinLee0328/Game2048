#ifndef GUARD_BOARD_H_ 
#define GUARD_BOARD_H_ 

#include <iostream>

enum Direction { UP, DOWN, LEFT, RIGHT, QUIT = -1 };

class Board{
public:
	Board() : tile(), score(0) { }
	int getscore() const { return score;}
	void merge(Direction dir);
	void move(Direction dir);
	bool init();
    std::ostream& print(std::ostream&) const;
	bool isfail();
	bool is2048();
private:
	int tile[4][4]; 
	int score;
	Board(const Board& other);
	bool isfull();
};

#endif
