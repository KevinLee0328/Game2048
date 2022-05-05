#include "Game2048.h" 
#include <string>

Game2048::Game2048() {
	board = new Board;
	settime();
}

Game2048::~Game2048() {
	delete board;
}

int Game2048::getscore() {
	return board->getscore();
}

std::ostream& Game2048::print(std::ostream& out) const {
	return board->print(out);
}

Direction Game2048::askdirection(std::ostream& out, std::istream& in) {
	bool check = false;
	std::string str;
	while (!check) {
		out << "(¡ü:u) (¡ý:d) (¡û:l) (¡ú:r) (quit:q): ";
		in >> str;
		if (str == "u" || str == "d" || str == "l" || str == "r" || str == "q")
			check = true;
	}
	if (str == "u") return UP;
	if (str == "d") return DOWN;
	if (str == "r") return RIGHT;
	if (str == "l") return LEFT;
	if (str == "q") return QUIT;
}

void Game2048::move(Direction dir) {
	board->merge(dir);
	board->move(dir);
}

bool Game2048::init() {
	return board->init();
}

bool Game2048::over() {
	return board->is2048() || board->isfail();
}

void Game2048::settime() {
	begin = time(NULL);
	end = time(NULL);
}

time_t Game2048::gettime() {
	end = time(NULL);
	return end - begin;
}

std::string Game2048::getstarttime() {
	struct tm* recordTime;
	recordTime = std::localtime(&begin);
	std::string str(std::asctime(recordTime));
	str = str.substr(0, str.length() - 1);
	return str;
}
