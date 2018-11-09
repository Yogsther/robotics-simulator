#include <iostream>
#include <string>
#include <vector>
#include <zconf.h>
#include "Robot.h"
#include "Position.h"
#include "Block.h"
#include "Screen.h"

using namespace std;

void sleepcp(int milliseconds);

void sleepcp(int milliseconds)
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}


int main() {
    Robot *robot = new Robot(0, 5, true);
    Screen *screen = new Screen(50, 20);

    screen->clear();
    int position = 0;
    char alpha[] = {'A', 'B', 'C', 'D', 'E'};

    while(true){
        screen->clear();
        screen->draw('O', position%1000);
        position++;
        screen->render();
        sleepcp(32);
    }
}



