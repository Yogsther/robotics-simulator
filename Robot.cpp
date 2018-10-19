//
// Created by olle on 2018-10-19.
//

#include "Robot.h"
#include "Position.h"

Robot::Robot(int x, int y, bool lightLover){
    position = Position(x, y);
    this->lightLover = lightLover;
}

void Robot::move(int x, int y) {
    position.x += x;
    position.y += y;
}

Position Robot::getPosition() {
    return position;
}