#pragma once
#include <string>

class DeadfishInterpreter {
public:
	bool mathFix = false; // Fixes deadfish's infamous bug
	bool wrapMode = false; // Variable overflows/underflows like on the 6502.

	std::string process(std::string code); // Returns values in a formatted string.

	inline int getAccumulator() { return acc; }

	void reset();

protected:
	inline void opI() { acc += 1; }
	inline void opD() { acc -= 1; }
	inline void opS() { acc *= acc; }
	inline int opO() { return acc; }
	inline void opR() { acc = sqrt(acc); }
	inline void opx2() { acc *= 2; }
	void opH();

	std::string haltOp = "h";
	std::string rootOp = "r";
	std::string charOp = "c"; // Makes sure the value is valid first.
	std::string worldOp = "w";

	int acc = 0; // Accumulator
};