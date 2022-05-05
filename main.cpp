#include "Game2048.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <string>

using std::cout;
using std::cin;
using std::endl;

int main()
{
	Game2048 game;
	game.init();
	game.init();
	cout << "Welcome to the game of 2048!" << endl;
	while (1) {
		game.print(cout);
		cout << "Your score: " << game.getscore() << endl;
		if (game.over()) break;
		Direction dir = game.askdirection(cout, cin);
		if (dir == QUIT) break;
		game.move(dir);
		game.init();
	}
	std::ofstream file("game2048.csv", std::ofstream::app);
	file << game.getstarttime() << "," << game.gettime() << "," << game.getscore() << endl;
	return 0;
}