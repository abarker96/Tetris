#ifndef TETROMINO_H
#define TETROMINO_H

#include <cstdint>

class Tetromino {
public:
	uint8_t **shape;
	int size=3;

	int x = 10;
	int y = 3;

	char letter = 'T';

	virtual void draw();

	virtual bool topRowEmpty();
	virtual bool rightColEmpty();
	virtual bool leftColEmpty();

	virtual void rotateLeft();
	virtual void rotateRight();

	virtual bool canMoveDown();
	virtual bool canMoveUp();
	virtual bool canMoveRight();
	virtual bool canMoveLeft();

	virtual void deleteAt(int x, int y);
	virtual bool isAt(int x, int y);
	bool isInRow(int y);
	void deleteRow(int y);
	void redrawAt(int x, int y);
	void update();

	Tetromino();
	~Tetromino();
};

class L_Tetromino: public Tetromino{
public:
	L_Tetromino();
	~L_Tetromino();
};

class Z_Tetromino: public Tetromino{
public:
	Z_Tetromino();
	~Z_Tetromino();
};

class O_Tetromino: public Tetromino{
public:
	O_Tetromino();
	~O_Tetromino();
};

class S_Tetromino: public Tetromino{
public:
	S_Tetromino();
	~S_Tetromino();
};

class J_Tetromino: public Tetromino{
public:
	J_Tetromino();
	~J_Tetromino();
};

class I_Tetromino: public Tetromino{
public:
	I_Tetromino();
	~I_Tetromino();
};

class T_Tetromino: public Tetromino{
public:
	T_Tetromino();
	~T_Tetromino();
};


#endif
