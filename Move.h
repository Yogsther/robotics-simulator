#pragma once
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
