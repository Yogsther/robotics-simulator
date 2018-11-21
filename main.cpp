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
#include "main.h"

using namespace std;

// settings
int const AMOUNT_OF_ROBOTS = 500;
int const AMOUNT_OF_STATIONS = 5;
int const AMOUNT_OF_LIGHT = 5;
int const DELAY = 10; // ms
int const WIDTH = 60;
int const HEIGHT = 20;
bool const SEEDED = true;
// debug tools
bool const  RENDER_LIGHT_DATA = false;
bool const RENDER_ONLY_FOOTPRINTS = false;

int lightlovers, lighthaters, frames;

Robot robots[AMOUNT_OF_ROBOTS];

string generateGUI() {
	string gui = "amount:" + to_string(AMOUNT_OF_ROBOTS) + " seeded:" + to_string(SEEDED);
	int aliveRobots = 0;
	for (int i = 0; i < AMOUNT_OF_ROBOTS; i++) {
		Robot robot = robots[i];
		if (robot.isAlive()) aliveRobots++;
		//gui = gui + "\n robot " + to_string(i) + ", dir: " + to_string(robot.getDirection()) + " fuel: " + to_string(robot.getFuelLevel()) + " refueling: " + to_string(robot.isRefueling()) + " alive: " + to_string(robot.isAlive());
	}

	gui = gui + " alive:" + to_string(aliveRobots) + " dead:" + to_string(AMOUNT_OF_ROBOTS - aliveRobots) + " frames:" + to_string(frames);

	return gui;
}

int main() {
	if (SEEDED) srand(time(NULL)); // Seed rand()

	lightlovers = 0;
	lighthaters = 0;
	frames = 0;

	//Robot robot = new Robot(0, 5, true);
	Screen* screen = new Screen(WIDTH, HEIGHT); // Create a new screen to display the simulation onto
	Map* map = new Map(WIDTH, HEIGHT);

	// Summon the robots
	for (int i = 0; i < AMOUNT_OF_ROBOTS; i++) {
		int x = rand() % WIDTH;
		int y = rand() % HEIGHT;
		bool lightlover = false;
		if (rand() % 2) lightlover = true;

		if (lightlover) lightlovers++;
		else lighthaters++;
		robots[i] = Robot(x, y, lightlover);
	}

	// TODO: Create a better summoner for light and station, the can currently overlap.

	// Summon light sources
	for (int i = 0; i < AMOUNT_OF_LIGHT; i++) {
		map->putItem(2, rand() % (WIDTH*HEIGHT));
	}
	// Summon stations
	for (int i = 0; i < AMOUNT_OF_STATIONS; i++) {
		map->putItem(1, rand() % (WIDTH*HEIGHT));
	}

	map->bake(); // Bake the map

	screen->clear(); // Start of with a clean screen

	while (true) {
		screen->clear(); // Clear screen

		// Render out the map
		for (int i = 0; i < (WIDTH * HEIGHT); i++) {
			if (map->getItem(i).getItem() == 1) screen->draw('B', i);
			if (map->getItem(i).getItem() == 2) screen->draw('L', i);

			if (map->getItem(i).getLight() < 10 && RENDER_LIGHT_DATA) {
				screen->draw(to_string(map->getItem(i).getLight()).c_str()[0], i);
			}
			if(RENDER_ONLY_FOOTPRINTS && map->getItem(i).getItem() == 3) screen->draw(to_string(map->getItem(i).getItem()).c_str()[0], i);
		}

		// Add all robot footprints
		for (Robot rob : robots) {
			Position pos = rob.getPosition();
			map->putItem(3, pos.x, pos.y);
		}

		// Render out the robots and place footprints
		for (int i = 0; i < AMOUNT_OF_ROBOTS; i++) {
			if (robots[i].isAlive()) {
				Position pos = robots[i].getPosition(); // Get position from robot
				map->putItem(0, pos.x, pos.y); // Remove footprint
				pos = robots[i].logic(*map); // Run logic, and save new position
				map->putItem(3, pos.x, pos.y); // Re-apply footprint
				if (!RENDER_LIGHT_DATA && !RENDER_ONLY_FOOTPRINTS) screen->draw(robots[i].getIcon(), pos.x, pos.y); // Render out robot
			} else if(map->getItem(robots[i].getPosition().x, robots[i].getPosition().y).getItem() == 3) map->putItem(0, robots[i].getPosition().x, robots[i].getPosition().y);
		}

		string gui = "Robotics Simulator 2019 (R:Robot, H:Light-Hate-Robot, L: Light, B: Station)\n";// Compile GUI Text
		gui = gui + generateGUI();

		screen->render(gui); // Render screen with GUI
		frames++;
		this_thread::sleep_for(std::chrono::milliseconds(DELAY)); // Sleep for some millis
	}
}