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
	int getX() {
		return this->x;
	}
	int getY() {
		return this->y;
	}
	int getValue() {
		return this->value;
	}
};

Move evaluateMove(int x, int y, Position pos, Map map) {
	int movePoints = 1;
	bool possible = true;
	x += pos.x;
	y += pos.y;

	int width = map.getWidth();
	int height = map.getHeight();

	if (x > width || x < 0 || y > height || y < 0) possible = false;
	if (map.getItem(x, y).getItem() != 0) possible = false;

	if (!possible) movePoints = 0;

	return Move::Move(x, y, movePoints);
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

	Move bestMove = Move::Move(0, 0, 0);
	Move worstMove = Move::Move(-1, 0, 0);
	for (Move move : moves) {
		if (move.getValue() > bestMove.getValue()) bestMove = move;
		if (move.getValue() < worstMove.getValue() || worstMove.getValue() == -1) worstMove = move;
	}
	if (bestMove.getValue() != 0) {
		if (bestMove.getValue() == worstMove.getValue()) {
			this->move(moves[this->direction].getX(), moves[this->direction].getY()); // Continue in direction, all moves are equally good.
		}
		else {
			this->move(bestMove.getX(), bestMove.getY()); // Choose the best move.
		}
	}
}