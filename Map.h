//
// Created by olle on 2018-10-19.
//

#ifndef ROBOTS_MAP_H
#define ROBOTS_MAP_H


class Map {
private:
    int width;
    int height;
    //block[] mapContent;
public:
    Map(int width, int height); // Constructor, create the map
    void bake(); // Bake map, calculate all light intensities for all parts of the map.
    void putItem(int id, int x, int y); // Place an item in the map
    //block[] getMap(); // Returns map
    // block getItem(int x, int y); // Get item from x,y
    // block getItem(int index); // Get item from array index;
};


#endif //ROBOTS_MAP_H
