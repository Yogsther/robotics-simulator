#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "Robot.h"
#include "Position.h"
#include "Block.h"
#include "Map.h"
#include "Screen.h"
#include <vector>

using namespace std;

int const amountOfRobots = 3;
int const WIDTH = 50;
int const HEIGHT = 20;

int main() {
	Robot robots[amountOfRobots];

	srand(time(NULL)); // Seed rand()

	for (int i = 0; i < amountOfRobots; i++) {
		robots[i] = Robot::Robot(rand() % WIDTH, rand() % HEIGHT, true);
	}
	//Robot robot = new Robot(0, 5, true);
	Screen *screen = new Screen(WIDTH, HEIGHT); // Create a new screen to display the simulation onto
	Map *map = new Map(WIDTH, HEIGHT);

	screen->clear(); // Start of with a clean screen

	while (true) {
		screen->clear(); // Clear screen

		// Render out the map
		for (int i = 0; i < (WIDTH * HEIGHT); i++) {
		}

		// Render out the robots
		for (Robot rob : robots) {
			rob.logic(*map);
			Position pos = rob.getPosition();
			screen->draw(rob.getIcon(), pos.x, pos.y);
		}

		screen->render(); // Render screen
		this_thread::sleep_for(std::chrono::milliseconds(16)); // Sleep for some millis
	}
}