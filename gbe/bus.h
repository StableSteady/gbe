#pragma once

#include <array>
#include <cstdint>

#include "cpu.h"

class Bus {
public:
	Bus();
	~Bus();
	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t data);

private:
	std::array<uint8_t, 65536> mem{0};
	CPU cpu;
};