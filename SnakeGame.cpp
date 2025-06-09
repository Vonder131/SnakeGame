#include "SnakeGame.h"
#include <conio.h>
#include <iostream>
#include "Snake.h"
#include "Utils.h"
#include <windows.h>
#include <thread>
#include <chrono>

/*#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
//use this for arrow keys
*/

#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3


SnakeGame::SnakeGame() {
	//draw the game screen when instantiate the class
	for (int i = 0; i < 100; i++) {
		std::cout << "_";
	}
	std::cout << "\n";
	for (int i = 0; i < 50; i++) {
		std::cout << "|";
		for (int j = 0; j < 100; j++) {

			std::cout << " ";
		}
		std::cout << "|";
		std::cout << "\n";
	}
	for (int i = 0; i < 100; i++) {
		std::cout << "_";
	}
	score = 0;
	updateScore();
	setDifficulty();
	speed = difficulty;
	snake.nextFood();

}

void SnakeGame::updateScore() {
	Utils::setCursor(105, 1);
	std::cout << "Score: " << score;
}


void SnakeGame::getDirection() {
	if (_kbhit())
		switch (_getch()) {
		case 'w':
			snake.setDirection(UP);
			break;
		case 'a':
			snake.setDirection(LEFT);
			break;
		case 'd':
			snake.setDirection(RIGHT);
			break;
		case 's':
			snake.setDirection(DOWN);
			break;
		default:
			break;
		}

}



int SnakeGame::run() {

	int drawResult = 0;

	while (drawResult != 2) {
		std::this_thread::sleep_for(std::chrono::milliseconds(120 / speed));//the delay between every 'frame'

		getDirection();//every frame checks if wasd key was pressed
		drawResult = snake.draw();//2 - hit the snake, 1 - hit food, 0 - nothing 
		score += drawResult;
		updateScore();
	};
	score -= 2;
	updateScore();//removes the 2 points for hiting the snake
	replay = getReplay();
	if (replay == 1) {
		score = 0;
		snake.reset();
		run();
	}
	else return drawResult;

}


void SnakeGame::setDifficulty() {
	this->difficulty = getDifficulty();
	if (this->difficulty > 0 && this->difficulty < 3)
		return;
	else
		this->difficulty = 3;//max speed;
}

int SnakeGame::getDifficulty() {
	int difficulty;
	Utils::setCursor(45, 20);
	std::cout << "Difficulty: ";
	Utils::setCursor(45, 21);
	std::cout << "1 - Easy";
	Utils::setCursor(45, 22);
	std::cout << "2 - Normal";
	Utils::setCursor(45, 23);
	std::cout << "3 - Hard";
	Utils::setCursor(56, 20);
	std::cin >> difficulty;

	clearArea();//clean the text

	return difficulty;
}

void SnakeGame::clearArea() {
	Utils::setCursor(1, 1);
	for (int i = 2; i < 49; i++) {
		for (int j = 0; j < 99; j++)
			std::cout << " ";
		Utils::setCursor(1, i);
	}
	Utils::setCursor(113, 1);
	std::cout << "    ";
}

int SnakeGame::getReplay() {
	int n_replay;
	Utils::setCursor(45, 20);
	std::cout << "GAME OVER! ";
	Utils::setCursor(45, 21);
	std::cout << "REPLAY?";
	Utils::setCursor(45, 22);
	std::cout << "1 - YES";
	Utils::setCursor(45, 23);
	std::cout << "2 - NO";
	Utils::setCursor(45, 24);
	std::cin >> n_replay;

	//clean the text
	clearArea();
	return n_replay;
}