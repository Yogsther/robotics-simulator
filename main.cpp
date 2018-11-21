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
int const amountOfStations = 5;

int const amountOfRobots = 5;
int const amountOfLights = 5;
int const DELAY = 150; // ms
int const WIDTH = 60;
int const HEIGHT = 20;
const bool seeded = true;
const bool renderLightData = false;

int lightlovers, lighthaters;

Robot robots[amountOfRobots];

string generateGUI() {
	string gui = "amount:" + to_string(amountOfRobots) + " seeded:" + to_string(seeded);
	int aliveRobots = 0;
	for (int i = 0; i < amountOfRobots; i++) {
		Robot robot = robots[i];
		if (robot.isAlive()) aliveRobots++;
		//gui = gui + "\n robot " + to_string(i) + ", dir: " + to_string(robot.getDirection()) + " fuel: " + to_string(robot.getFuelLevel()) + " refueling: " + to_string(robot.isRefueling()) + " alive: " + to_string(robot.isAlive());
	}

	gui = gui + " alive:" + to_string(aliveRobots) + " dead:" + to_string(amountOfRobots - aliveRobots);

	return gui;
}

int main() {
	if (seeded) srand(time(NULL)); // Seed rand()

	lightlovers = 0;
	lighthaters = 0;

	//Robot robot = new Robot(0, 5, true);
	Screen* screen = new Screen(WIDTH, HEIGHT); // Create a new screen to display the simulation onto
	Map* map = new Map(WIDTH, HEIGHT);

	// Summon the robots
	for (int i = 0; i < amountOfRobots; i++) {
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
	for (int i = 0; i < amountOfLights; i++) {
		map->putItem(2, rand() % (WIDTH*HEIGHT));
	}
	// Summon stations
	for (int i = 0; i < amountOfStations; i++) {
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

			if (map->getItem(i).getLight() < 10 && renderLightData) {
				screen->draw(to_string(map->getItem(i).getLight()).c_str()[0], i);
			}
		}

		// Add all robot footprints
		for (Robot rob : robots) {
			Position pos = rob.getPosition();
			map->putItem(3, pos.x, pos.y);
		}

		// Render out the robots
		for (int j = 0; j < amountOfRobots; j++) {
			if (robots[j].isAlive()) {
				Position pos = robots[j].getPosition(); // Get position from robot
				map->putItem(0, pos.x, pos.y); // Remove footprint
				pos = robots[j].logic(*map); // Run logic, and save new position
				map->putItem(3, pos.x, pos.y); // Re-apply footprint
				//cout << "Position to draw " << pos.x << ":" << pos.y << " Robot index: " << j << " Robots[] size: " << amountOfRobots << endl;
				if (!renderLightData) screen->draw(robots[j].getIcon(), pos.x, pos.y); // Render out robot
			}
		}

		string gui = "Robotics Simulator 2019\n";// Compile GUI Text
		gui = gui + generateGUI();

		screen->render(gui); // Render screen with GUI
		this_thread::sleep_for(std::chrono::milliseconds(DELAY)); // Sleep for some millis
	}
}