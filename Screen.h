//
// Created by olle on 2018-10-29.
//

#ifndef ROBOTS_SCREEN_H
#define ROBOTS_SCREEN_H

#include "vector"

using namespace std;

class Screen {
private:
	int width;
	int height;
	void print(string str);
	void print(char str);
	vector <char> data; // TODO: Maybe change this to an Array, when I have internet again.
public:
	Screen(int width, int height);
	void draw(char character, int x, int y);
	void draw(char character, int index);
	void render();
	void clear();
};

#endif //ROBOTS_SCREEN_H
