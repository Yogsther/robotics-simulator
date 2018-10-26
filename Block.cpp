//
// Created by moau16 on 26-10-2018.
//
#include "Block.h"

void Block::setLight(int intensity) {
    if (intensity >= 0 && intensity <= 10) this->light = intensity;
}

void Block::setItem(int item) {
    this->item = item;
}

int Block::getLight() {
    return light;
}

int Block::getItem() {
    return item;
}