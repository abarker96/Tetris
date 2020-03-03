//	Tetromino.cpp
#include "Tetromino.h"
#include <ncurses.h>

Tetromino::Tetromino(){
	size = 3;
	uint8_t temp[size][size] = {
		{0, 0, 0},
		{0, 0, 0},
		{0, 0, 0}
	};
	shape = new uint8_t*[size];
	for(int i=0;i<size;i++){
		shape[i] = new uint8_t[size];
		for(int j=0;j<size;j++){
			shape[i][j] = temp[i][j];
		}
	}
}

Tetromino::~Tetromino(){
	//delete[] shape;
}

 void Tetromino::draw(){
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(shape[i][j] != 0){
				move(y+i, x+j);
				addch(letter);
			}
		}
	}
}

 bool Tetromino::topRowEmpty(){
	for(int i=0;i<size;i++){
		if(shape[0][i]) return false;
	}
	return true;
}

 bool Tetromino::rightColEmpty(){
	for(int i=0;i<size;i++){
		if(shape[i][size-1]) return false;
	}
	return true;
}

 bool Tetromino::leftColEmpty(){
	for(int i=0;i<size;i++){
		if(shape[i][0]) return false;
	}
	return true;
}

 void Tetromino::rotateLeft(){
	if(rightColEmpty() && !topRowEmpty() && !canMoveRight()) x--;
	else if(leftColEmpty() && !topRowEmpty() && !canMoveLeft()) x++;
	uint8_t **temp = new uint8_t*[size];
	for(int i=0;i<size;i++){
		temp[i] = new uint8_t[size];
	}
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			temp[i][j] = shape[j][size-1-i];
		}
	}
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			shape[i][j] = temp[i][j];
		}
	}
	delete[] temp;
}

 void Tetromino::rotateRight(){
	if(rightColEmpty() && !topRowEmpty() && !canMoveRight()) x--;
	else if(leftColEmpty() && !topRowEmpty() && !canMoveLeft()) x++;
	uint8_t **temp = new uint8_t*[size];
	for(int i=0;i<size;i++){
		temp[i] = new uint8_t[size];
	}
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			temp[i][j] = shape[size-1-j][i];
		}
	}
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			shape[i][j] = temp[i][j];
		}
	}
	delete[] temp;
}

 bool Tetromino::canMoveDown(){
	for(int i=0; i<size; i++){
		for(int j=0;j<size;j++){
			if( shape[i][j] ){
				if( i < size-1 ) if( shape[i+1][j] ) continue;
				move(y+i+1, x+j);
				char ch = inch();
				if( ch != ' ' ) return false;
			}
		}
	}
	return true;
}

 bool Tetromino::canMoveUp(){
	for(int i=0; i<size; i++){
		for(int j=0;j<size;j++){
			if( shape[i][j] ){
				if( i > 0 ) if( shape[i-1][j] ) continue;
				move(y+i-1, x+j);
				char ch = inch();
				if( ch != ' ' ) return false;
			}
		}
	}
	return true;
}

 bool Tetromino::canMoveRight(){
	for(int i=0; i<size; i++){
		for(int j=0;j<size;j++){
			if( shape[i][j] ){
				if( j < size-1 ) if ( shape[i][j+1] ) continue;
				move(y+i, x+j+1);
				char ch = inch();
				if( ch != ' ' ) return false;
			}
		}
	}
	return true;
}

 bool Tetromino::canMoveLeft(){
	for(int i=0; i<size; i++){
		for(int j=0;j<size;j++){
			if( shape[i][j] ){
				if( j > 0 ) if ( shape[i][j-1] ) continue;
				move(y+i, x+j-1);
				char ch = inch();
				if( ch != ' ' ) return false;
			}
		}
	}
	return true;
}

 void Tetromino::deleteAt(int x, int y){
	//	set the shape to zero at screen position (x,y)
	x -= this->x;
	y -= this->y;
	if(x < 0 || x >= size || y < 0 || y >= size) throw "Coordinates out of bounds.";
	this->shape[y][x] = 0;
}

 bool Tetromino::isAt(int x, int y){
	//	returns true if tetromino contains block at point (x,y)
	x -= this->x;
	y -= this->y;
	return !(x < 0 || x >= size || y < 0 || y >= size);
}

bool Tetromino::isInRow(int y){
	y -= this->y;
	return !(y < 0 || y >=size);
}

void Tetromino::deleteRow(int y){
	//	pass in overworld position y && delet all in that row
	for(int x=this->x;x<this->x+3;x++){
		//	delete the row
		if(isAt(x,y)) redrawAt(x, y);
	}
}

void Tetromino::redrawAt(int x, int y){
	x -= this->x;
	y -= this->y;
	if(x < 0 || x >= size || y < 0 || y >= size) throw "Coordinates out of bounds.";
	for(int i=y;i>0;i--){
		this->shape[y][x]=shape[y-1][x];
	}
}

void Tetromino::update(){
}

//	Child classes
L_Tetromino::L_Tetromino(){
	letter = 'L';
	uint8_t temp[3][3] = {
		{0, 1, 0},
		{0, 1, 0},
		{0, 1, 1}
	};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			shape[i][j] = temp[i][j];
		}
	}
}
L_Tetromino::~L_Tetromino(){
};

Z_Tetromino::Z_Tetromino(){
	letter = 'Z';
	uint8_t temp[3][3] = {
		{0, 0, 0},
		{1, 1, 0},
		{0, 1, 1}
	};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			shape[i][j] = temp[i][j];
		}
	}
}
Z_Tetromino::~Z_Tetromino(){
};

O_Tetromino::O_Tetromino(){
	letter = 'O';
	uint8_t temp[3][3] = {
		{0, 0, 0},
		{0, 1, 1},
		{0, 1, 1}
	};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			shape[i][j] = temp[i][j];
		}
	}
}
O_Tetromino::~O_Tetromino(){
};

S_Tetromino::S_Tetromino(){
	letter = 'S';
	uint8_t temp[3][3] = {
		{0, 0, 0},
		{0, 1, 1},
		{1, 1, 0}
	};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			shape[i][j] = temp[i][j];
		}
	}
}
S_Tetromino::~S_Tetromino(){
};

J_Tetromino::J_Tetromino(){
	letter = 'J';
	uint8_t temp[3][3] = {
		{0, 1, 0},
		{0, 1, 0},
		{1, 1, 0}
	};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			shape[i][j] = temp[i][j];
		}
	}
}
J_Tetromino::~J_Tetromino(){
}

I_Tetromino::I_Tetromino(){
	size = 4;
	letter = 'I';
	delete[] shape;
	shape = new uint8_t*[size];
	for(int i=0;i<size;i++){
		shape[i] = new uint8_t[size];
	}
	uint8_t temp[size][size] = {
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0},
		{0, 1, 0, 0}
	};
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			shape[i][j] = temp[i][j];
		}
	}
}
I_Tetromino::~I_Tetromino(){
}

T_Tetromino::T_Tetromino(){
	letter = 'T';
	uint8_t temp[3][3] = {
		{0, 0, 0},
		{1, 1, 1},
		{0, 1, 0}
	};
	for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			shape[i][j] = temp[i][j];
		}
	}
}
T_Tetromino::~T_Tetromino(){
}
