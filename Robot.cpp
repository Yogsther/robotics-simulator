//
// Created by olle on 2018-10-19.
//

#include "Robot.h"
#include "Position.h"
#include "Block.h"
#include <vector>
#include <iostream>
#include <string>
#include "Move.h"

int const THRESHOLD_LEVEL = 25; // When they will become desperate for fuel and sometimes ignore lightlevels
int const START_FUEL = 50;
int const TRAIL_LENGTH = 100;
int trailIndex = 0;
Position trail[TRAIL_LENGTH]; // Trail of the robot, history of position

/* Creates a circular array */
void pushToTrail(Position pos) {
	trail[trailIndex % TRAIL_LENGTH] = pos;
	trailIndex++;
}

int indexOfTrail(Position pos) {
	for (int i = 0; i < TRAIL_LENGTH; i++) {
		if (trail[i].x == pos.x && trail[i].y == pos.y) return i;
	}
	return -1;
}

Move Robot::evaluateMove(int x, int y, int direction, Map map) {
	int movePoints = 10;
	bool possible = true;
	int final_x = x + this->position.x;
	int final_y = y + this->position.y;

	int width = map.getWidth();
	int height = map.getHeight();

	if (final_x >= width || final_x < 0 || final_y >= height || final_y < 0) possible = false;
	else if (map.getItem(final_x, final_y).getItem() != 0) possible = false;

	if (possible) {
		// Check trial. If it has not been here before, go there.
		if (indexOfTrail(Position(x, y)) == -1) movePoints++;

		if (this->fuel > THRESHOLD_LEVEL) {
			// Evaluate light conditions
			if (this->lightLover) {
				movePoints += map.getItem(final_x, final_y).getLight(); // The more light, the better
			}
			else {
				movePoints -= map.getItem(final_x, final_y).getLight(); // The less light, the better
			}
		}
		else {
			// Get to a fuel station immediately!
			movePoints += map.getWidth() - map.getItem(final_x, final_y).getDistanceToFuel();
		}

		if (map.getItem(final_x, final_y).getDistanceToFuel() == 1 && this->fuel < THRESHOLD_LEVEL) {
			movePoints += 10000;
			this->refueling = true;
		}
	}

	if (!possible) movePoints = 0;

	return Move(x, y, movePoints, direction);
}

Robot::Robot(int x, int y, bool lightLover) {
	position = Position(x, y);
	this->fuel = START_FUEL;
	this->lightLover = lightLover;
	if (!lightLover) icon = 'H';
}

Robot::Robot() {
}

void Robot::move(int x, int y) {
	this->position.x += x;
	this->position.y += y;
	pushToTrail(Position(x, y));
	this->fuel -= 1;
}

Position Robot::getPosition() {
	return position;
}

char Robot::getIcon() {
	return this->icon;
}

Position Robot::logic(Map map) {
	if (refueling) {
		fuel++;
		if (this->fuel == START_FUEL) refueling = false;
		return this->position;
	}

	if (this->fuel < 0) {
		this->alive = false;
		return this->position;
	}

	const int amountOfMoves = 8; // 8 for diagonal, otherwise 4.
	Move moves[amountOfMoves]; // 8 possible moves
	moves[0] = evaluateMove(0, -1, 0, map); 	// Up
	moves[1] = evaluateMove(1, 0, 1, map);	 	// Left
	moves[2] = evaluateMove(0, 1, 2, map); 	// Down
	moves[3] = evaluateMove(-1, 0, 3, map);	// Right

	// Diagonal move-set
	moves[4] = evaluateMove(1, -1, 4, map); 	// Up, Right
	moves[5] = evaluateMove(1, 1, 5, map);	 	// Down, Right
	moves[6] = evaluateMove(-1, 1, 6, map); 	// Down, Left
	moves[7] = evaluateMove(-1, -1, 7, map);	// Up, Left

	int bestMoveIndex; // Important for saving the direction (index = direction)
	Move bestMove = Move(0, 0, 0, 0);
	Move worstMove = Move(-1, 0, 0, 0);

	// Choose a move
	// Calcualte best and worst move
	for (int i = 0; i < amountOfMoves; i++) {
		if ((moves[i].getValue() == bestMove.getValue() && i == this->direction) || moves[i].getValue() > bestMove.getValue()) {
			bestMove = moves[i];
			bestMoveIndex = i;
		}
		if (moves[i].getValue() < worstMove.getValue() || worstMove.getValue() == -1) worstMove = moves[i];
	}
	if (bestMove.getValue() != 0) {
		if (bestMoveIndex == this->direction) {
			this->move(bestMove.getX(), bestMove.getY()); // Continue in direction, all moves are equally good.
		}
		else {
			std::vector<Move> equalMoves;
			for (int i = 0; i < amountOfMoves; i++) {
				if (moves[i].getValue() == bestMove.getValue()) equalMoves.push_back(moves[i]);
			}
			Move selectedMove = equalMoves.at(rand() % equalMoves.size());
			this->move(selectedMove.getX(), selectedMove.getY()); // Choose the best move.
			this->direction = selectedMove.getDirection();
		}
	}

	return this->position;
}

int Robot::getDirection() {
	return this->direction;
}

int Robot::getFuelLevel() {
	return this->fuel;
}

bool Robot::isRefueling() {
	return this->refueling;
}

bool Robot::isAlive() {
	return this->alive;
}