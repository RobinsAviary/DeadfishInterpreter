#pragma once
#include <string>

class DeadfishInterpreter {
public:
	bool mathFix = false; // Fixes deadfish's infamous bug
	bool wrapMode = false; // Variable overflows/underflows like on the 6502.

	std::string process(std::string code); // Returns values in a formatted string.

	inline int getAccumulator() { return acc; }

protected:
	inline void opI() { acc += 1; }
	inline void opD() { acc -= 1; }
	inline void opS() { acc *= acc; }
	inline int opO() { return acc; }
	inline void opR() { acc = sqrt(acc); }
	//void opC();
	inline void op0() { acc = 0; }

	void reset();

	int acc = 0; // Accumulator
};