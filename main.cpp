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
#include <fstream>
#include "Options.h"

using namespace std;

Options options = Options::Options();

// Set all settings
int const AMOUNT_OF_ROBOTS = options.get("AMOUNT_OF_ROBOTS");
int const AMOUNT_OF_STATIONS = options.get("AMOUNT_OF_STATIONS");
int const AMOUNT_OF_LIGHT = options.get("AMOUNT_OF_LIGHT_SOURCES");
int const DELAY = options.get("DELAY"); // ms
int const WIDTH = options.get("WIDTH");
int const HEIGHT = options.get("HEIGHT");
int SEEDED = options.get("SEEDED");
int SEED = options.get("SEED");
// debug tools
bool const RENDER_LIGHT_DATA = options.get("RENDER_LIGHT_DATA");
bool const RENDER_ONLY_FOOTPRINTS = options.get("RENDER_ONLY_FOOTPRINTS");
bool const RENDER_TRAIL = options.get("RENDER_TRAIL");

int lightlovers, lighthaters, frames, fuelSlots, emptyFuelSlots;

vector<Robot> robots; // Vector to house all robots

/* Generate an information GUI at the top of the screen */
string generateGUI() {
	string gui = "amount:" + to_string(AMOUNT_OF_ROBOTS) + " seed:" + to_string(SEED) + " seeded:" + to_string(SEEDED);
	int aliveRobots = 0;
	for (int i = 0; i < AMOUNT_OF_ROBOTS; i++) {
		Robot robot = robots.at(i);
		if (robot.isAlive()) aliveRobots++;
		//gui = gui + "\n robot " + to_string(i) + ", dir: " + to_string(robot.getDirection()) + " fuel: " + to_string(robot.getFuelLevel()) + " refueling: " + to_string(robot.isRefueling()) + " alive: " + to_string(robot.isAlive());
	}

	gui = gui + " alive:" + to_string(aliveRobots) + " dead:" + to_string(AMOUNT_OF_ROBOTS - aliveRobots) + " frames:" + to_string(frames) + "\nfuel_slots:" + to_string(fuelSlots) + " empty_fuel_slots : " + to_string(emptyFuelSlots);

	return gui;
}

int main() {
	if (SEEDED == 1) srand(time(NULL)); // Seed rand()
	if (SEEDED == 2) srand(SEED); // Seed rand()

	lightlovers = 0;
	lighthaters = 0;
	frames = 0;

	fuelSlots = AMOUNT_OF_STATIONS * 8;
	emptyFuelSlots = 0;
	if (options.get("ONLY_FUEL_DIRECT") == 1) fuelSlots /= 2;

	//Robot robot = new Robot(0, 5, true);
	Screen* screen = new Screen(WIDTH, HEIGHT); // Create a new screen to display the simulation onto
	Map* map = new Map(WIDTH, HEIGHT);

	// Summon the robots
	for (int i = 0; i < AMOUNT_OF_ROBOTS; i++) {
		bool lightlover = false;
		if (rand() % 2) lightlover = true;

		if (lightlover) lightlovers++;
		else lighthaters++;

		Position pos = map->summon(3); //Summon a footstep and save the new position for the robot.
		robots.push_back(Robot(pos.x, pos.y, lightlover, options));
		//map->putItem(3, x, y); // Add robot footprint
	}

	// Summon light sources
	for (int i = 0; i < AMOUNT_OF_LIGHT; i++) {
		map->summon(2);
	}
	// Summon stations
	for (int i = 0; i < AMOUNT_OF_STATIONS; i++) {
		map->summon(1);
	}

	map->bake(); // Bake the map

	screen->clear(); // Start of with a clean screen

	/* Heartbeat loop */
	while (true) {
		emptyFuelSlots = fuelSlots;
		screen->clear(); // Clear screen

		// Render out the map
		for (int i = 0; i < (WIDTH * HEIGHT); i++) {
			if (map->getItem(i).getItem() == 1) screen->draw('B', i);
			if (map->getItem(i).getItem() == 2) screen->draw('L', i);

			if (map->getItem(i).getLight() < 10 && RENDER_LIGHT_DATA) {
				screen->draw(to_string(map->getItem(i).getLight()).c_str()[0], i);
			}
			if (RENDER_ONLY_FOOTPRINTS && map->getItem(i).getItem() == 3) screen->draw(to_string(map->getItem(i).getItem()).c_str()[0], i);

			if (RENDER_TRAIL) {
				for (int i = 0; i < AMOUNT_OF_ROBOTS; i++) {
					Position pos = robots.at(i).getPosition();

					std::vector<Position> trail = robots.at(i).getTrail();
					for (int j = 0; j < trail.size(); j++) {
						//cout << trail.at(j).x << trail.at(j).y << endl;
						screen->draw('T', trail.at(j).x, trail.at(j).y);
					}
				}
			}
		}

		// Render out the robots and place footprints
		for (int i = 0; i < AMOUNT_OF_ROBOTS; i++) {
			if (robots.at(i).isAlive()) {
				Position pos = robots.at(i).getPosition(); // Get position from robot
				map->putItem(0, pos.x, pos.y); // Remove footprint
				pos = robots.at(i).logic(*map); // Run logic, and save new position
				map->putItem(3, pos.x, pos.y); // Re-apply footprint
				if (!RENDER_LIGHT_DATA && !RENDER_ONLY_FOOTPRINTS) screen->draw(robots.at(i).getIcon(), pos.x, pos.y); // Render out robot
				if (robots.at(i).isRefueling()) emptyFuelSlots--;
			}
			else if (!robots.at(i).isConfirmedDead()) {
				// Confirm the death to make sure it's footprint is erased.
				map->putItem(0, robots.at(i).getPosition().x, robots.at(i).getPosition().y);
				robots.at(i).confirmDeath();
			}
		}

		string gui = "Robotics Simulator 2019\n(R:Robot, H:Light_Hate_Robot, L: Light, B: Station)\n-----------------\n";// Compile GUI Text
		gui = gui + generateGUI();

		screen->render(gui); // Render screen with GUI
		frames++;
		this_thread::sleep_for(std::chrono::milliseconds(DELAY)); // Sleep for some millis
	}
}