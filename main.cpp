#include "deadfish.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <windows.h>

std::string commentPrefix = "//";

RobinfishInterpreter interpreter;

std::string version = "1.0.3";

void printVersion() {
	std::cout << "Robinfish Interpreter v" << version << std::endl;
}

int main(int argc, char** argv) {
	// Search for the first file and process it.
	for (int i = 0; i < argc; i++) {
		std::string_view arg = argv[i];

		if (!arg.ends_with(".exe")) {
			if (arg.ends_with(".df") || arg.ends_with(".txt")) {
				if (std::filesystem::exists(arg)) {
					std::ifstream file(static_cast<std::string>(arg));
					std::string line;
					std::string code = "";
					while (std::getline(file, line)) {
						int pos = line.find(commentPrefix);
						if (pos != std::string::npos) { // If we find a comment
							// Remove the rest
							line = line.substr(0, pos);
						}
						code += line;
					}
					std::string result = interpreter.process(code);
					std::fstream log("log.txt", std::ofstream::out | std::ofstream::trunc);
					std::cout << result << std::endl;
					if (result != "") log << result << std::endl;
					log.close();
					file.close();
					return 0;
				}
			}
		}
	}

	// Actual interface for users.
	printVersion();
	std::vector<std::string> hints = { "Robinfish is based on Deadfish!", "Robinfish is considered a superset for Deadfish!", "You can type 'help' for a list of supported operators, as well as commands.", "Files can use // to have comments." };
	srand(GetTickCount64());
	std::string hint = hints[rand() % hints.size()];
	std::cout << "Did You Know: " << hint << std::endl;

	bool looping = true;
	while (looping) {
		std::cout << ">> ";
		std::string input;
		std::cin >> input;
		if (input == "cls" || input == "clear") {
			std::cout << "\033[2J\033[1;1H"; // Clear screen
		}
		else if (input == "reset") {
			interpreter.reset();
		}
		else if (input == "help") {
			auto dictionary = interpreter.getDictionary();
			std::cout << "Supported operators: ";
			unsigned int dictionarySize = dictionary.size();
			for (int i = 0; i < dictionarySize; i++) {
				std::string op = dictionary[i];
				std::cout << op;
				if (i == dictionarySize - 1) {
					std::cout << "." << std::endl;
				}
				else {
					std::cout << ", ";
				}
			}
		}
		else if (input == "version") {
			printVersion();
		}
		else if (input == "about") {
			std::cout << "Robinfish interpreter v" + version + "; Inspired by Deadfish; Written by Robin; robinsaviary.com" << std::endl;
		}
		else std::cout << interpreter.process(input) << std::endl;
	}

	return 0;
}