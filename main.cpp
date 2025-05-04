#include "deadfish.h"
#include <iostream>
#include <filesystem>
#include <fstream>

DeadfishInterpreter interpreter;

std::string version = "1.0.1";

int main(int argc, char** argv) {
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

	std::cout << "Deadfish Interpreter v" << version << std::endl;

	bool looping = true;
	while (looping) {
		std::cout << ">> ";
		std::string input;
		std::cin >> input;
		if (input == "cls") {
			std::cout << "\033[2J\033[1;1H"; // Clear screen
		}
		else if (input == "reset") {
			interpreter.reset();
		}
		else std::cout << interpreter.process(input) << std::endl;
	}

	return 0;
}