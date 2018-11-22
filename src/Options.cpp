#include "Options.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Option {
public:
	std::string name;
	int value;
	Option::Option(std::string name, int value) {
		this->name = name;
		this->value = value;
	}
};

std::vector<Option> optionsList;

int Options::get(std::string name) {
	for (int i = 0; i < optionsList.size(); i++) {
		if (optionsList.at(i).name == name) return optionsList.at(i).value;
	}
	return -1;
}

Options::Options() {
	std::string text = "";
	std::string line;
	std::ifstream cfgFile("options.cfg");
	if (cfgFile.is_open()) {
		while (std::getline(cfgFile, line))
		{
			text = text + line + '?'; // ? are break lines
		}
		cfgFile.close();
	}

	// Status codes:
	// 0: reading name
	// 1: reading value
	// 3: reading comment, dismiss
	int status = 0;
	std::string tempName = "";
	std::string tempValue = "";
	for (int i = 0; i < text.length(); i++) {
		char character = text[i];
		// Skip spaces
		if (character == '#') {
			status = 3;
			continue;
		}
		if (character == ' ') continue;
		if (character == '?' /* Break line */) {
			status = 0; // End of value
			// Create and add the option - process is done
			if (tempName != "") optionsList.push_back(Option::Option(tempName, std::stoi(tempValue)));
			tempName = "";
			tempValue = "";
			continue;
		}
		if (character == ':') {
			status++;
			continue;
		}
		if (status == 0) tempName = tempName + character;
		if (status == 1) tempValue = tempValue + character;
	}
}