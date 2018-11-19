//
// Created by olle on 2018-10-19.
//

#ifndef ROBOTS_ROBOT_H
#define ROBOTS_ROBOT_H

#include "Position.h"
#include <vector>
#include "Block.h"
#include "Map.h"
#include "Move.h"

class Robot {
public:
	Robot();
	Robot(int x, int y, bool lightLover);
	Position logic(Map map); // Run the bot (one frame)
	void move(int x, int y);
	Position getPosition();
	void refuel();
	char getIcon();
	int getDirection();
private:
	Move evaluateMove(int x, int y, int direction, Map map); // Calculate how good a potential move is
	int fuel = 25; // Starts with 25 fuel, max amount is 50.
	bool lightLover;
	char icon = 'L';
	int direction; // Facing direction, 0-3, up, right, down, left
	Position position = Position(0, 0);
};

#endif //ROBOTS_ROBOT_H
