#include "deadfish.h"
#include <iostream>
#include <filesystem>
#include <fstream>

RobinfishInterpreter interpreter;

std::string version = "1.0.2";

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
						code += line;
					}
					std::string result = interpreter.process(code);
					std::fstream log("log.txt");
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