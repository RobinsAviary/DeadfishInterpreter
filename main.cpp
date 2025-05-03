#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>
#include <fstream>

std::string code;
bool terminalActive = true;

std::string incrementOp = "i";
std::string decrementOp = "d";
std::string squareOp = "s";
std::string outputOp = "o";
// Custom operators
std::string haltOp = "h";
std::string rootOp = "r";
std::string charOp = "c"; // Makes sure the value is valid first.

void processOp(std::string op) {

}

int acc = 0;

char argPrefix = '-';
bool verboseOutput = false;
bool mathFix = false;

void accCheck() {
	if (!mathFix) {
		if (acc == -1 || acc == 256) acc = 0;
	}
	else {
		// A fix for deadfish's odd implementation that better matches specifications / typical behavior.
		while (acc < 0) {
			acc += 256;
		}
		while (acc > 255) {
			acc -= 256;
		}
	}
}

void opI() {
	acc++;
}

void opD() {
	acc--;
}

void opS() {
	acc *= acc;
}

void opO() {
	std::cout << acc << std::endl;
}

int main(int argc, char *argv[]) {
	bool fileFound = false;

	for (int i = 0; i < argc; i++) {
		std::string_view currentArg = argv[i];

		if (currentArg.starts_with(argPrefix)) {
			if (currentArg == argPrefix + "v" || currentArg == argPrefix + "verbose") {
				verboseOutput = true;
			}
			else if (currentArg == argPrefix + "f" || currentArg == argPrefix + "fix") {
				mathFix = true;
			}
		}

		if (verboseOutput) std::cout << currentArg << std::endl;
		
		if (currentArg.ends_with(".df")) {
			if (std::filesystem::exists(currentArg)) {
				std::fstream file(static_cast<std::string>(currentArg));

				std::string line;

				while (std::getline(file, line)) {
					code += line;
					if (verboseOutput) std::cout << line << std::endl;
				}

				fileFound = true;
				terminalActive = false;
				i = argc;
			};

			//std::cout << argv[i] << std::endl;
		}
	}

	// File-based interpreter. Slightly faster.
	if (fileFound) {
		std::ofstream log("log.txt");

		for (char op : code) {
			if (op == incrementOp) opI();
			else if (op == decrementOp) opD();
			else if (op == 's') opS();
			else if (op == 'o') {
				opO();
				log << acc << " ";
			}
			else if (op == 'h') return 0;

			accCheck();
		}

		log.close();
	}

	// Terminal interpreter.
	while (terminalActive) {
		std::cout << ">> ";
		std::string typedCode;
		std::cin >> typedCode;

		for (int i = 0; i < typedCode.size(); i++) {
			char op = typedCode[i];

			if (op == 'i') opI();
			else if (op == 'd') opD();
			else if (op == 's') opS();
			else if (op == 'o') opO();
			else if (op == 'h') return 0;

			accCheck();
		}
	}
	
	return 0;
}