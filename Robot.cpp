//
// Created by olle on 2018-10-19.
//

#include "Robot.h"
#include "Position.h"
#include "Block.h"
#include <vector>

class Move {
	int x, y, value;
public:
	Move() {}
	Move(int x, int y, int value) {
		this->x = x;
		this->y = y;
		this->value = value;
	}
};

Move evaluateMove(int x, int y, Position pos, Map map) {
	int movePoints = 0;
	x += pos.x;
	y += pos.y;

	return Move::Move();
}

Robot::Robot(int x, int y, bool lightLover) {
	position = Position(x, y);
	this->lightLover = lightLover;
	if (!lightLover) icon = 'H';
}

Robot::Robot() {
}

void Robot::move(int x, int y) {
	this->position.x += x;
	this->position.y += y;
}

Position Robot::getPosition() {
	return position;
}

char Robot::getIcon() {
	return this->icon;
}

void Robot::logic(Map map) {
	Move moves[4]; // 4 possible moves
	moves[0] = evaluateMove(0, 1, this->position, map);
	moves[1] = evaluateMove(1, 0, this->position, map);
	moves[2] = evaluateMove(0, -1, this->position, map);
	moves[3] = evaluateMove(-1, 0, this->position, map);

	for (int i = 0; i < sizeof(moves); i++) {
	}
}