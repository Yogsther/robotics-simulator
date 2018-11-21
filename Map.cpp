//
// Created by olle on 2018-10-19.
//

#include "Map.h"
#include <vector>
#include <string>
#include <cmath>
#include <iostream>

/*
	Item ID's:
	0 - Empty
	1 - Fuel station
	2 - Light source
	3 - Robot footstep
*/

Map::Map(int width, int height) {
	this->width = width;
	this->height = height;

	for (int i = 0; i < (width*height); i++) {
		Block block = Block();
		this->contents.push_back(block);
	}
}

/* Calcualte all light intesinities over the map */
void Map::bake() {
	// Go through all items and calculate on each light.
	for (int i = 0; i < this->width * this->height; i++) {
		if (this->contents.at(i).getItem() == 2 /* Light source*/) {
			// Get original x and y
			int org_x = i % this->width;
			int org_y = (i - org_x) / this->width;
			for (int j = 0; j < this->contents.size(); j++) {
				// Find the distance of all other blocks
				int x = j % this->width;
				int y = (j - x) / this->width;
				// Calculate distance
				int d = 10 - sqrt(pow(org_x - x, 2) + pow(org_y - y, 2));
				// Save original light intensity so they can be added if that is the case.
				int org_d = this->contents.at(j).getLight();
				// Apply light value
				if (d > 0) this->contents.at(j).setLight(d + org_d);
			}
		}
	}

    // Go through all items and calculate on each station.
    for (int i = 0; i < this->width * this->height; i++) {
        if (this->contents.at(i).getItem() == 1 /* Fuel tank */) {
            // Get original x and y
            int org_x = i % this->width;
            int org_y = (i - org_x) / this->width;
            for (int j = 0; j < this->contents.size(); j++) {
                // Find the distance of all other blocks
                int x = j % this->width;
                int y = (j - x) / this->width;
                // Calculate distance
                int d = sqrt(pow(org_x - x, 2) + pow(org_y - y, 2));
                // Apply light value
                if (this->contents.at(j).getDistanceToFuel() > d || this->contents.at(j).getDistanceToFuel() == -1) this->contents.at(j).setDistanceToFuel(d);
            }
        }
    }
}

// Place an item in the map
void Map::putItem(int id, int index) {
	if (index > contents.size() || index < 0) return;
	this->contents.at(index).setItem(id);
}

// Place an item in the map with x,y
void Map::putItem(int id, int x, int y) {
	int index = x + (y*this->width);
	if (index > width*height|| index < 0) return;
	this->contents.at(index).setItem(id);
}

// Get entire map
std::vector<Block> Map::getMap() {
	return this->contents;
}

// Get item at index
Block Map::getItem(int index) {
	return this->contents.at(index);
}

// Get item at x,y
Block Map::getItem(int x, int y) {
	int index = x + (y*this->width);
	if (index > contents.size() || index < 0) {
		std::cout << "getItem(x, y) failed x:" << x << " y:" << y << std::endl;
	}
	return this->getItem(index);
}

int Map::getWidth() {
	return this->width;
}
int Map::getHeight() {
	return this->height;
}