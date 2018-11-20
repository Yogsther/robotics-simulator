//
// Created by olle on 2018-11-20.
//

#ifndef ROBOTS_MOVE_H
#define ROBOTS_MOVE_H

class Move
{
private:
    int x, y, value, direction;
public:
    Move() {}
    Move(int x, int y, int value, int direction);
    int getX();
    int getY();
    int getValue();
    int getDirection();
};


#endif //ROBOTS_MOVE_H
