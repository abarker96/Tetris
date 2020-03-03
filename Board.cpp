//	Board.cpp
#include <ncurses.h>
#include "Board.h"
#include "Tetromino.h"

void Board::draw(){
	for(int y=0;y<HEIGHT;y++){
		for(int x=0;x<WIDTH;x++){
			if( map[y][x] != ' ' ){
				move(y+yPos, x+xPos);
				addch(map[y][x]);
			}
		}
	}
}

void Board::add(Tetromino t){
	for(int i=0;i<t.size;i++){
		for(int j=0;j<t.size;j++){
			if(t.shape[i][j]) add(t.letter, t.x+j, t.y+i);
		}
	}
}

void Board::add(char c, int x, int y){
	x -= this->xPos;
	y -= this->yPos;
	if(x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) throw "Coordinates out of bounds.";
	map[y][x] = c;
}

void Board::deleteRow(int row){
	if(row < 0 || row >= HEIGHT) throw "Coordinates out of bounds.";
	for(int y=row;y>1;y--){
		for(int x=1;x<WIDTH-1;x++){
			map[y][x] = map[y-1][x];
		}
	}
	for(int x=1;x<WIDTH-1;x++){
		map[0][x] = ' ';
	}
}

Board::Board(){
	map = new char*[HEIGHT];
	for(int y=0;y<HEIGHT;y++){
		map[y] = new char[WIDTH];
		for(int x=0;x<WIDTH;x++){
			if(x == 0 || x == WIDTH-1){
				map[y][x] = '|';;
			}
			else if(y == HEIGHT-1){
				map[y][x] = (char)254;
			}
			else{
				map[y][x] = ' ';
			}
		}
	}
}
Board::~Board(){
}
