#include "Board.h"
#include <ctime>
#include <cstdlib>
#include <string>

bool Board::init() {
	if (isfull()) return false;
	srand((unsigned)time(NULL));
	int x = rand() % 4;
	int y = rand() % 4;
	while (tile[x][y] != 0) {
		x = rand() % 4;
		y = rand() % 4;
	}
	int temp = rand() % 5;
	if (temp == 0) tile[x][y] = 4;
	else tile[x][y] = 2;
	return true;
}

bool Board::isfull() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if(tile[i][j] == 0) return false;
		}
	}
	return true;
}

bool Board::is2048() {
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (tile[i][j] == 2048) return true;
		}
	}
	return false;
}

bool Board::isfail() {
	if (!isfull()) return false;
	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 4; ++j) {
			if (tile[i][j] == tile[i + 1][j])
				return false;
		}
	}
	for (int j = 0; j < 3; ++j) {
		for (int i = 0; i < 4; ++i) {
			if (tile[i][j] == tile[i][j + 1])
				return false;
		}
	}
	return true;
}

std::string space(int num) {
	std::string str(num, ' ');
	return str;
}

std::ostream& Board::print(std::ostream& out) const {
	out << "|-----|-----|-----|-----|" << std::endl;
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			out << "|" << space(1);
			if (tile[i][j] == 0)
				out << space(4);
			else if (tile[i][j] >= 2 && tile[i][j] <= 8)
				out << tile[i][j] << space(3);
			else if (tile[i][j] >= 16 && tile[i][j] <= 64)
				out << tile[i][j] << space(2);
			else if (tile[i][j] >= 128 && tile[i][j] <= 512)
				out << tile[i][j] << space(1);
			else 
				out << tile[i][j];
		}
		out << "|" << std::endl << "|-----|-----|-----|-----|" << std::endl;
	}
	return out;
}

void Board::move(Direction dir) {
	switch (dir) {
	case UP:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (tile[i][j] == 0) {
					for (int k = i + 1; k < 4; ++k) {
						if (tile[k][j] != 0) {
							tile[i][j] = tile[k][j];
							tile[k][j] = 0;
							break;
						}
					}
				}
			}
		}
		break;
	case DOWN:
		for (int i = 3; i >= 0; --i) {
			for (int j = 0; j < 4; ++j) {
				if (tile[i][j] == 0) {
					for (int k = i - 1; k >= 0; --k) {
						if (tile[k][j] != 0) {
							tile[i][j] = tile[k][j];
							tile[k][j] = 0;
							break;
						}
					}
				}
			}
		}
		break;
	case LEFT:
		for (int j = 0; j < 4; ++j) {
			for (int i = 0; i < 4; ++i) {
				if (tile[i][j] == 0) {
					for (int k = j + 1; k < 4; ++k) {
						if (tile[i][k] != 0) {
							tile[i][j] = tile[i][k];
							tile[i][k] = 0;
							break;
						}
					}
				}
			}
		}
		break;
	case RIGHT:
		for (int j = 3; j >= 0; --j) {
			for (int i = 0; i < 4; ++i) {
				if (tile[i][j] == 0) {
					for (int k = j - 1; k >= 0; --k) {
						if (tile[i][k] != 0) {
							tile[i][j] = tile[i][k];
							tile[i][k] = 0;
							break;
						}
					}
				}
			}
		}
		break;
	}
}

void Board::merge(Direction dir) {
	switch (dir) {
	case UP:
		for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				if (tile[i][j] != 0) {
					for (int k = i + 1; k < 4; ++k) {
						if (tile[k][j] != 0) {
							if (tile[k][j] == tile[i][j]) {
								tile[i][j] *= 2;
								tile[k][j] = 0;
								score += tile[i][j];
							}
							break;
						}
					}
				}
			}
		}
		break;
	case DOWN:
		for (int i = 3; i >= 0; --i) {
			for (int j = 0; j < 4; ++j) {
				if (tile[i][j] != 0) {
					for (int k = i - 1; k >= 0; --k) {
						if (tile[k][j] != 0) {
							if (tile[k][j] == tile[i][j]) {
								tile[i][j] *= 2;
								tile[k][j] = 0;
								score += tile[i][j];
							}
							break;
						}
					}
				}
			}
		}
		break;
	case LEFT:
		for (int j = 0; j < 4; ++j) {
			for (int i = 0; i < 4; ++i) {
				if (tile[i][j] != 0) {
					for (int k = j + 1; k < 4; ++k) {
						if (tile[i][k] != 0) {
							if (tile[i][k] == tile[i][j]) {
								tile[i][j] *= 2;
								tile[i][k] = 0;
								score += tile[i][j];
							}
							break;
						}
					}
				}
			}
		}
		break;
	case RIGHT:
		for (int j = 3; j >= 0; --j) {
			for (int i = 0; i < 4; ++i) {
				if (tile[i][j] != 0) {
					for (int k = j - 1; k >= 0; --k) {
						if (tile[i][k] != 0) {
							if (tile[i][k] == tile[i][j]) {
								tile[i][j] *= 2;
								tile[i][k] = 0;
								score += tile[i][j];
							}
							break;
						}
					}
				}
			}
		}
		break;
	}
}
