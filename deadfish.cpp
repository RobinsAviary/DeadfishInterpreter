#include "deadfish.h"
#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>
#include <fstream>

std::string version = "1.0.1";

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

std::vector<std::string> dictionary = { incrementOp, decrementOp, squareOp, outputOp };

void DeadfishInterpreter::reset() {
	acc = 0;
}

std::string DeadfishInterpreter::process(std::string code) {
	std::string result = "";

	std::string_view codeView = code;

	bool halt = false;

	while (codeView.length() > 0) {
		std::string op = "";

		unsigned int dictionarySize = dictionary.size();
		for (unsigned int i = 0; i < dictionarySize; i++) {
			std::string currentOp = dictionary[i];
			
			if (codeView.starts_with(currentOp)) {
				codeView = codeView.substr(currentOp.length());
				op = currentOp;

				break;
			}
		}

		if (op != "") {
			if (op == incrementOp) {
				opI();
			}
			else if (op == decrementOp) {
				opD();
			}
			else if (op == squareOp) {
				opS();
			}
			else if (op == outputOp) {
				std::string toAdd = std::to_string(opO()) + " ";
				result += toAdd;
			}
		}
	}

	return result;
}