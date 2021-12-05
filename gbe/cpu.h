#pragma once

#include <cstdint>
#include <string>

class Bus;

class CPU {
public:
	CPU();
	void connect(Bus* b);
	uint8_t read(uint16_t address);
	void write(uint16_t address, uint8_t data);

private:
	uint8_t A = 0, B = 0, C = 0, D = 0,
			E = 0, F = 0, H = 0, L = 0;
	uint16_t SP = 0, PC = 0;
	Bus* bus = nullptr;
	uint64_t clock = 0;
	uint8_t opcode = 0;

};