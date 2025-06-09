#pragma once

#include <iostream>
#include "Snake.h"
#include <windows.h>


class SnakeGame
{

public:


	SnakeGame();
	int run();

private:

	Snake snake;
	int score;
	int speed;
	int difficulty;
	int replay = 0;
	int getDifficulty();
	int getReplay();
	void getDirection();
	void updateScore();
	void setDifficulty();
	void clearArea();
};

