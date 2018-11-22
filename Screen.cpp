//
// Created by olle on 2018-10-29.
//

#include <iostream>
#include "Screen.h"
#include <string>
using namespace std;

string borderString = "";
string frameSpace = "";
int frameSpacing = 100; // Lines

Screen::Screen(int width, int height) {
	this->width = width;
	this->height = height;

	for (int i = 0; i < width*height; i++) {
		data.push_back('E');
	}

	for (int j = 0; j < width + 2; ++j) {
		borderString += "*";
	}

	// Draw blank space to reset view
	for (int k = 0; k < frameSpacing; k++) {
		frameSpace += '\n';
	}
}

void Screen::clear() {
	for (int i = 0; i < data.size(); i++) {
		data.at(i) = 'E';
	}
}

void Screen::draw(char character, int index) {
	if (index >= data.size() || index < 0) {
		//cout << "Out of range! index: " << index << endl;
		return;
	}
	data.at(index) = character;
}

void Screen::draw(char character, int x, int y) {
	this->draw(character, x + (y*width));
}

string printStr = "";

void Screen::print(string str) {
	printStr = printStr + str;
}
void Screen::print(char str) {
	printStr = printStr + str;
}

void displayPrint() {
	//printf("%s\n", printStr.c_str());
	cout << printStr;
	printStr = "";
}

void Screen::render(string gui) {
	// Reset view
	print(frameSpace);

	printStr = printStr + gui + "\n";

	// Top frame border
	print(borderString + "\n");

	for (int i = 0; i < width*height; i++) {
		if (i % width == 0 && i != 0) print("\n"); // End of line, break line

		// Border top and left
		if (i % width == 0) print("*");

		if (data.at(i) != 'E') print(data.at(i)); // Draw out character for this pixel
		else print(" "); // Draw empty if slot is empty, i.e 'E'

	// Right side border
		if (i % width == width - 1) print("*");
	}

	// Bottom frame border
	print('\n' + borderString + '\n');

	displayPrint();
}

/**
 * Cleans screen data from all robot footprints.
 */
void Screen::clean() {
	for (int i = 0; i < data.size(); i++) {
		if (data.at(i) == 3) data.at(i) = 0;
	}
}