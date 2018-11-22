//
// Created by olle on 2018-10-19.
//

#ifndef ROBOTS_MAP_H
#define ROBOTS_MAP_H

#include "Block.h"
#include <vector>
#include "Position.h"

class Map {
private:
	int width;
	int height;
	std::vector<Block> contents;
public:
	Map(int width, int height); // Constructor, create the map
	void bake(); // Bake map, calculate all light intensities for all parts of the map.
	Position summon(int item);
	void putItem(int id, int x, int y); // Place an item in the map
	void putItem(int id, int index); // Place an item in the map
	std::vector<Block> getMap(); // Returns map
	Block getItem(int x, int y); // Get item from x,y
	Block getItem(int index); // Get item from array index;
	int getWidth();
	int getHeight();
};

#endif //ROBOTS_MAP_H
