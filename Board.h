//	Board.h
#ifndef BOARD_H
#define BOARD_H

#include "Tetromino.h"

class Board{
public:
	const static int HEIGHT = 20;
	const static int WIDTH = 20;

	int xPos = 2;
	int yPos = 2;

	void draw();

	void add(Tetromino);
	void add(char, int, int);

	void deleteRow(int row);

	Board();
	~Board();

private:
	char **map;
};

#endif
