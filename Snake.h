#pragma once

#include <windows.h>
class Snake
{
public:
	//0-> down; 1->left; 2-> right; 3->up
	void nextFood();
	Snake();
	~Snake();
	int draw();
	void setDirection(int _direction);
	void reset();

private:
	int size;
	int position[1000];
	int direction;


	void updatePosition();
	void move();

	int drawAtPosition(int pos, char ch);



};

