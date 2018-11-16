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

int const amountOfRobots = 100;
int const WIDTH = 90;
int const HEIGHT = 30;

int main() {
	Robot robots[amountOfRobots];

	srand(time(NULL)); // Seed rand()

	// Summon the robots
	for (int i = 0; i < amountOfRobots; i++) {
		int x = rand() % WIDTH;
		int y = rand() % HEIGHT;
		robots[i] = Robot(x, y, true);
	}
	//Robot robot = new Robot(0, 5, true);
	Screen* screen = new Screen(WIDTH, HEIGHT); // Create a new screen to display the simulation onto
	Map* map = new Map(WIDTH, HEIGHT);

	screen->clear(); // Start of with a clean screen

	while (true) {
		screen->clear(); // Clear screen

		// Render out the map
		for (int i = 0; i < (WIDTH * HEIGHT); i++) {
		}

		// Add all robot footprints
		for (Robot rob : robots) {
			Position pos = rob.getPosition();
			map->putItem(3, pos.x, pos.y);
		}

		// Render out the robots
		for (int j = 0; j < amountOfRobots; j++) {
			Position pos = robots[j].getPosition(); // Get position from robot
			map->putItem(0, pos.x, pos.y); // Remove footprint
			pos = robots[j].logic(*map); // Run logic, and save new position
			map->putItem(3, pos.x, pos.y); // Re-apply footprint
			//cout << "Position to draw " << pos.x << ":" << pos.y << " Robot index: " << j << " Robots[] size: " << amountOfRobots << endl;
			screen->draw(robots[j].getIcon(), pos.x, pos.y); // Render out robot
		}

		string gui = "Robot 0: " + to_string(robots[0].getPosition().x) + ":" + to_string(robots[0].getPosition().y) + " dir: " + to_string(robots[0].getDirection()); // Compile GUI Text

		screen->render(gui); // Render screen with GUI
		//this_thread::sleep_for(std::chrono::milliseconds(32)); // Sleep for some millis
	}
}