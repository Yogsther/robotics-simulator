#include "Move.h"

Move::Move(int x, int y, int value, int direction) {
	this->x = x;
	this->y = y;
	this->value = value;
	this->direction = direction;
}
int Move::getX() {
	return this->x;
}
int Move::getY() {
	return this->y;
}
int Move::getValue() {
	return this->value;
}
int Move::getDirection() {
	return this->direction;
}