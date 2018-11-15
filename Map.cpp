//
// Created by olle on 2018-10-19.
//

#include "Map.h"
#include <vector>
#include <string>

/*
	Item ID's:
	0 - Empty
	1 - Fuel station
	2 - Light source

*/

Map::Map(int width, int height) {
	this->width = width;
	this->height = height;

	for (int i = 0; i < (width*height); i++) {
		Block block = Block();
		this->contents.push_back(block);
	}
}

void bake() {
}

void Map::putItem(int id, int index) {
	this->contents.at(index).setItem(id);
}

void Map::putItem(int id, int x, int y) {
	this->contents.at(x + (y*this->width)).setItem(id);
}

std::vector<Block> Map::getMap() {
	return this->contents;
}

Block Map::getItem(int index) {
	return this->contents.at(index);
}

Block Map::getItem(int x, int y) {
	return this->contents.at(x + (y*this->width));
}

int Map::getWidth() {
	return this->width;
}
int Map::getHeight() {
	return this->height;
}