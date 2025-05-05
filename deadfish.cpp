#include "deadfish.h"
#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>
#include <fstream>
#include <vector>

std::string code;
bool terminalActive = true;

std::string divOp = "d2";
std::string twoOp = "x2";
std::string skipOp = "S";
std::string incrementOp = "i";
std::string decrementOp = "d";
std::string squareOp = "s";
std::string outputOp = "o";
// Custom operators
std::string haltOp = "h";
std::string rootOp = "sr";
std::string charOp = "c"; // Makes sure the value is valid first.
std::string worldOp = "w";
std::string resetOp = ";";
std::string resetAccOp = "#";
std::string resetStackOp = "$";
std::string quineOp = "q";
std::string putOp = ">";
std::string takeOp = "<";
std::string reverseOp = "r";
std::string robinmathOp = "R";
std::string spaceOp = " ";
std::string newlineOp = "\n";
std::string throwOp = "^";
std::string randOp = "D2";
std::string equalsOp = "=";

std::vector<std::string> dictionary = { resetAccOp, resetStackOp, quineOp, putOp, takeOp, reverseOp, robinmathOp, spaceOp, twoOp, divOp, skipOp, incrementOp, decrementOp, squareOp, outputOp, haltOp, rootOp, charOp, worldOp, resetOp};
// NOTE: Dictionary needs to be sorted from largest to smallest

std::vector<std::string> RobinfishInterpreter::getDictionary() {
	return dictionary;
}

template <typename T> int sgn(T val) {
	return (T(0) < val) - (val < T(0));
}

void RobinfishInterpreter::reset() {
	acc = 0;
}

std::string RobinfishInterpreter::process(std::string code) {
	std::string result = "";

	std::string_view codeView = code;

	bool halt = false;

	while (codeView.length() > 0) {
		if (!robinfishMode) {
			if (mathFix) {
				if (acc < 0 || acc > 255) {
					acc = 0;
				}
			}
			else if (acc == -1 || acc == 256) {
				acc = 0;
			}
		}

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
			if (op == spaceOp) {
				// ALWAYS ignored.
			}
			else if (op == twoOp) {
				opx2();
			}
			else if (op == divOp) {
				opd2();
			}
			else if (op == skipOp) {
				if (acc==0) codeView = codeView.substr(1);
			}
			else if (op == incrementOp) {
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
			else if (op == rootOp) {
				opR();
			}
			else if (op == worldOp) {
				result += "Hello, World!";
			}
			else if (op == haltOp) {
				return result;
			}
			else if (op == charOp) {
				if (acc >= 0 && acc <= 255) {
					result += static_cast<char>(acc);
				}
			}
			else if (op == resetOp) {
				acc = 0;
				stack.clear();
				robinfishMode = false;
			}
			else if (op == resetAccOp) {
				acc = 0;
			}
			else if (op == resetStackOp) {
				stack.clear();
			}
			else if (op == quineOp) {
				
			}
			else if (op == equalsOp) {
				if (acc >= 0 && acc < stack.size()) {
					acc = stack[acc];
				}
			}
			else if (op == randOp) {
				
			}
			else if (op == newlineOp) {
				// Do nothing.
			}
			else if (op == putOp) {
				stack.push_back(acc);
			}
			else if (op == throwOp) {
				stack.pop_back();
			}
			else if (op == takeOp) {
				acc = stack.back();
				stack.pop_back();
			}
			else if (op == reverseOp) {
				std::reverse(stack.begin(), stack.end());
			}
			else if (op == robinmathOp) {
				robinfishMode = !robinfishMode;
			}
		}
		else {
			codeView = codeView.substr(1);
		}
	}

	return result;
}

void RobinfishInterpreter::opH() {

}