//
// Created by moau16 on 26-10-2018.
//

#ifndef ROBOTS_BLOCK_H
#define ROBOTS_BLOCK_H

class Block {
private:
	int light = 0;
	int item = 0;
public:
	Block::Block();
	void setLight(int intensity);
	void setItem(int item);
	int getLight();
	int getItem();
};

#endif //ROBOTS_BLOCK_H
