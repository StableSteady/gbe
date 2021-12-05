#pragma once

#include <array>
#include <cstdint>
#include <stack>

#include "cpu.h"

constexpr int MAX_ADDRESS = 0xFFFF;

class Bus {
public:
	Bus();
	~Bus();
	uint8_t& read(uint16_t address);
	void write(uint16_t address, uint8_t data);

private:
	std::array<uint8_t, MAX_ADDRESS> mem{0};
	std::stack<uint16_t> stack;
	CPU cpu;
};