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
	int getFuelLevel();
	char getIcon();
	int getDirection();
	bool isRefueling();
	bool isAlive();
private:
	bool alive = true;
	int refueling = false;
	Move evaluateMove(int x, int y, int direction, Map map); // Calculate how good a potential move is
	int fuel;
	bool lightLover;
	char icon = 'R';
	int direction; // Facing direction, 0-7
	Position position = Position(0, 0);
};

#endif //ROBOTS_ROBOT_H
