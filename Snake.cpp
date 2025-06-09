#include "Snake.h"
#include <iostream>
#include <windows.h>
#include "Utils.h"
#define DOWN 0
#define LEFT 1
#define RIGHT 2
#define UP 3


Snake::Snake() {
	size = 4;
	direction = 2;
	//default position of the snake
	position[0] = 4;//HEAD
	position[1] = 3;
	position[2] = 2;
	position[3] = 1;
	position[4] = 0;

}

void Snake::reset() {
	nextFood();
	size = 4;

	direction = 2;
	//default position of the snake
	position[0] = 4;//HEAD
	position[1] = 3;
	position[2] = 2;
	position[3] = 1;
	position[4] = 0;
	Utils::setCursor(4, 1);

}

int Snake::draw() {

	int aux = drawAtPosition(0, 'O');
	for (int i = 1; i < size; i++) {
		drawAtPosition(i, 'o');//Body is lower case;
	};
	drawAtPosition(size, ' ');
	updatePosition();

	return aux;
}

void Snake::nextFood() {
	int x = Utils::randomNumberGenerator(1, 99);
	int y = Utils::randomNumberGenerator(1, 49);
	Utils::setCursor(x, y);
	if (Utils::cursorCharRead() == 'x' || Utils::cursorCharRead() == 'o' || Utils::cursorCharRead() == 'O')
		nextFood();
	else
		std::cout << "x";
}

int Snake::drawAtPosition(int pos, char ch) {
	int x = position[pos] % 100;
	int y = (int)(position[pos] / 100) + 1;
	Utils::setCursor(x, y);

	if (Utils::cursorCharRead() == 'x' && ch == 'O') {
		std::cout << ch;
		size++;
		nextFood();
		return 1;
	}
	else if (Utils::cursorCharRead() == 'o' && ch == 'O') {
		return 2;
	}
	else {
		std::cout << ch;
		return 0;
	}
}


void Snake::move() {

	int* auxPos;
	auxPos = new int[50];

	for (int i = 0; i < size; i++) {
		auxPos[i] = position[i];

	}

	for (int i = 1; i <= size; i++) {
		position[i] = auxPos[i - 1];

	}
}

void Snake::updatePosition() {
	switch (direction) {
	case DOWN:
		move();
		if (position[0] / 100 > 48)
			position[0] = position[0] % 100;
		else
			position[0] += 100;
		break;
	case LEFT:
		move();
		if (position[0] % 100 == 1)
			position[0] += 98;
		else
			position[0] -= 1;
		break;
	case RIGHT:
		move();
		if (position[0] % 100 == 99)
			position[0] -= 98;
		else
			position[0] += 1;
		break;
	case UP:
		move();
		if (position[0] < 100)
			position[0] += 4900;
		else
			position[0] -= 100;
		break;
	}
}



void Snake::setDirection(int _direction) {
	if (_direction >= 0 && _direction < 4) {
		//not allowing to move in the opposite direction (was simpler if would've mapped the keys in order, clock wise for instance)
		if (_direction == DOWN && this->direction != UP)
			this->direction = _direction;
		else if (_direction == UP && this->direction != DOWN)
			this->direction = _direction;
		else if (_direction == RIGHT && this->direction != LEFT)
			this->direction = _direction;
		else if (_direction == LEFT && this->direction != RIGHT)
			this->direction = _direction;
	}
}


Snake::~Snake() {
	delete[] position;
}


