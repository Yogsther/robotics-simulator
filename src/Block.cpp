//
// Created by moau16 on 26-10-2018.
//
#include "Block.h"

Block::Block() {
}

void Block::setLight(int intensity) {
	if (intensity >= 0 && intensity <= 10) this->light = intensity;
}

void Block::setItem(int item) {
	this->item = item;
}

void Block::setDistanceToFuel(int distance) {
	this->distanceToFuel = distance;
}

int Block::getLight() {
	return light;
}

int Block::getItem() {
	return item;
}

int Block::getDistanceToFuel() {
	return this->distanceToFuel;
}