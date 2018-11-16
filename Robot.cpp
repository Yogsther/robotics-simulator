//
// Created by olle on 2018-10-19.
//

#include "Robot.h"
#include "Position.h"
#include "Block.h"
#include <vector>
#include <iostream>
#include <string>

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
	int final_x = x + pos.x;
	int final_y = y + pos.y;

	int width = map.getWidth();
	int height = map.getHeight();

	if (final_x >= width || final_x < 0 || final_y >= height || final_y < 0) possible = false;
		else if (map.getItem(final_x, final_y).getItem() != 0) possible = false;

	if (!possible) movePoints = 0;

	return Move(x, y, movePoints);
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
	//std::cout << "Moved > " << x << y << "Final x,y: " << this->position.x << ":" << this->position.y << std::endl;
}


Position Robot::getPosition() {
	return position;
}

char Robot::getIcon() {
	return this->icon;
}

Position Robot::logic(Map map) {

	this->direction = rand()%4;

	const int amountOfMoves = 4;
	Move moves[amountOfMoves]; // 4 possible moves
	moves[0] = evaluateMove(0, -1, this->position, map); 	// Up
	moves[1] = evaluateMove(1, 0, this->position, map);	 	// Left
	moves[2] = evaluateMove(0, 1, this->position, map); 	// Down
	moves[3] = evaluateMove(-1, 0, this->position, map);	// Right

	int bestMoveIndex;
	Move bestMove = Move(0, 0, 0);
	Move worstMove = Move(-1, 0, 0);

	for (int i = 0; i < amountOfMoves; i++) {
		if(moves[i].getValue() == bestMove.getValue() && i == this->direction){
			bestMove = moves[i];
			bestMoveIndex = i;
		}
		if (moves[i].getValue() > bestMove.getValue()){
			bestMove = moves[i];
			bestMoveIndex = i;
		}
		if (moves[i].getValue() < worstMove.getValue() || worstMove.getValue() == -1) worstMove = moves[i];
	}
	if (bestMove.getValue() != 0) {

		if (bestMove.getValue() == worstMove.getValue()) {
			this->move(moves[this->direction].getX(), moves[this->direction].getY()); // Continue in direction, all moves are equally good.
		}
		else {
			this->move(bestMove.getX(), bestMove.getY()); // Choose the best move.
			this->direction = bestMoveIndex;
		}
	}

	return this->position;
}

int Robot::getDirection() {
	return this->direction;
}
