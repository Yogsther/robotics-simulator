#include <iostream>
#include <string>
#include <vector>
#include "Robot.h"
#include "Position.h"
#include "Block.h"

using namespace std;

int main() {
    cout << "Creating new robot..." << endl;
    Robot *robot = new Robot(0, 5, true);

    Block *block = new Block();
    block->setItem(2);
    block->setLight(5);

    cout << "Block => item: " << block->getItem() << " light: " << block->getLight() << endl;

    while(true){

        robot->move(1, 0);
        //cout << "x:" << robot->getPosition().x << " y: " << robot->getPosition().y << endl;

        //sleep(1);
    }
}
