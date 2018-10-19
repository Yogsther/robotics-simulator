//
// Created by olle on 2018-10-19.
//

#ifndef ROBOTS_ROBOT_H
#define ROBOTS_ROBOT_H


#include "Position.h"

class Robot {
public:
    Robot(int x, int y, bool lightLover);
    void move(int x, int y);
    Position getPosition();
    void refuel();
private:
    int fuel = 25; // Starts with 25 fuel, max amount is 50.
    bool lightLover;
    Position position = Position(0, 0);
};

#endif //ROBOTS_ROBOT_H
