//
// Created by moau16 on 26-10-2018.
//

#ifndef ROBOTS_BLOCK_H
#define ROBOTS_BLOCK_H

class Block {
private:
	int light = 0;
	int item = 0;
	int distanceToFuel = -1;
public:
	Block();
	void setLight(int intensity);
	void setItem(int item);
	void setDistanceToFuel(int distance);
	int getLight();
	int getItem();
	int getDistanceToFuel();

};

#endif //ROBOTS_BLOCK_H
