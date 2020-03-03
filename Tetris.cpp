//	Tetris.cpp
#include "Tetromino.h"
#include "Board.h"
#include <ncurses.h>
#include <time.h>
#include <string>

using namespace std;

//	Functions
void update();
void render();
void manageInput();
void updateScore();
void generateTet();
void checkRows();
void moveRowDown(int);

//	Globla Variables
int WIDTH, HEIGHT;
Tetromino tet;
bool running;
bool quit = false;
int score = 0;
Board board;
int rowCount = 0;
double lastUpdate;
double updateTime = 10/60;

int main(){
	//	Setup
	srand(time(0));
	initscr();
	noecho();
	cbreak();
	nodelay(stdscr, TRUE);
	curs_set(0);
	getmaxyx(stdscr, HEIGHT, WIDTH);

	generateTet();

	//	Main loop
	lastUpdate = time(0) * 1000;
	running = TRUE;
	while(running){
		manageInput();
		double now = time(0) * 1000;
		if( now - lastUpdate >=  updateTime ) {
			update();
			render();
		}
	}

	move(15, 27);
	addstr("Game Over");
	move(16, 27);
	addstr("Press Q to exit");

	char ch = getch();
	while( ch != 'q' ){
		ch = getch();
	}

	endwin();	//	reset terminal to normal
	return 0;
}


void manageInput(){
	int ch = getch();
	if( ch == 27 || ch == 'q' ) running = false;
	else if ( ch == 'd' && tet.canMoveRight() ){
		tet.x++;
		if( tet.x >= WIDTH - 3 ) tet.x = WIDTH-3;
		clear();
		quit = true;
	}
	else if( ch == 'a' && tet.canMoveLeft() ){
		tet.x--;
		if( tet.x < 0 ) tet.x = 0;
		clear();
	}
	else if ( ch == 's' && tet.canMoveDown() ){
		tet.y++;
		if( tet.y >= HEIGHT - 3 ) tet. y = HEIGHT - 3;
		clear();
	}
	/*
	else if( ch == 'w' && tet.canMoveUp() ){
		tet.y--;
		if( tet.y < 0 ) tet.y = 0;
		clear();
	}
	*/
	else if ( ch == ' ' ){
		tet.rotateRight();
		clear();
	}
}

void update(){
	updateScore();
	if( (time(0) * 1000) - lastUpdate >= 1000 ){
		if(!tet.canMoveDown()){
			if(tet.y <= board.yPos+tet.size-1) running =  false;
			generateTet();
			score += 25;
			checkRows();
		}
		tet.y++;
		clear();
	}
	lastUpdate = time(0) * 1000;
}

void render(){
	board.draw();
	tet.draw();
}

void updateScore(){
	move(0,1);
	string str = "Score: ";
	str.append(to_string(score));
	addstr( str.c_str() );
}

void generateTet(){
	//	add current tetromino to list
	board.add(tet);
	//	Generate random number & pick shape based on number
	int num = rand() % 7;
	switch (num) {
		case 0:
			tet = L_Tetromino();
			break;
		case 1:
			tet = J_Tetromino();
			break;
		case 2:
			tet = O_Tetromino();
			break;
		case 3:
			tet = S_Tetromino();
			break;
		case 4:
			tet = Z_Tetromino();
			break;
		case 5:
			tet = I_Tetromino();
			break;
		case 6:
			tet = T_Tetromino();
			break;
	}
}

void checkRows(){
	int countPerRow = 0;
	for(int i=0;i<board.HEIGHT-1;i++){
		countPerRow = 0;
		for(int j=1;j<board.WIDTH-1;j++){
			move(board.yPos+i, board.xPos+j);
			char ch = inch();
			if(ch != ' ') countPerRow++;
		}
		if(countPerRow == board.WIDTH-2){
			rowCount++;
			score += 100;
			//	Delete rows
			board.deleteRow(i);
		}
	}
}
