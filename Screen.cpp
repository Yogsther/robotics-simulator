//
// Created by olle on 2018-10-29.
//

#include <iostream>
#include "Screen.h"
using namespace std;

string borderString = "";

Screen::Screen(int width, int height) {
    this->width = width;
    this->height = height;

    for (int i = 0; i < width*height; i++) {
        data.push_back('E');
    }

    for (int j = 0; j < width+2; ++j) {
        borderString+="*";
    }
}

void Screen::clear() {
    for(int i = 0; i < data.size(); i++){
        data.at(i) = 'E';
    }
}

void Screen::draw(char character, int index) {
    if(index >= data.size() || index < 0) return;
    data.at(index) = character;
}

void Screen::draw(char character, int x, int y) {
    draw(character, x + (y*width));
}




void Screen::render() {

    int frameSpacing = 50; // Lines

    // Draw blank space to reset view
    for (int j = 0; j < frameSpacing; j++) {
        cout << endl;
    }


    // Top frame border
    cout << borderString << endl;

    for (int i = 0; i < width*height; i++) {
        if(i % width == 0 && i != 0) cout << endl; // End of line, break line

        // Border top and left
        if(i % width == 0) cout << "*";

        if(data.at(i) != 'E') cout << data.at(i); // Draw out character for this pixel
            else cout << ' '; // Draw empty if slot is empty, i.e 'E'

        // Right side border
        if(i % width == width-1) cout << "*";
    }

    // Bottom frame border
    cout << endl << borderString << endl;
}

