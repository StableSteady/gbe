#pragma once

#include <cstdint>
#include <string>
#include <vector>

class Bus;

class CPU {
public:
	CPU();
	void connect(Bus* b);
	uint8_t& read(uint16_t address);
	void write(uint16_t address, uint8_t data);
	void fetch();
	void decode();
	void execute();

private:
	uint8_t A = 0, B = 0, C = 0, D = 0,
			E = 0, F = 0, H = 0, L = 0;
	uint16_t AF = 0, BC = 0, DE = 0, HL = 0, SP = 0, PC = 0;
	bool z = false, c = false;
	Bus* bus = nullptr;
	uint64_t clock = 0;
	uint8_t opcode = 0;

	//disassembly tables
	std::vector<uint8_t*> r = { &B, &C, &D, &E, &H, &L, &read(HL), &A };
	std::vector<uint16_t*> rp{ &BC, &DE, &HL, &SP};
	std::vector<uint16_t*> rp2{ &BC, &DE, &HL, &AF };
	std::vector<bool> cc{ !z, z, !c, c };
	std::vector<void (CPU::*)(uint8_t)> alu{};
	std::vector<void (CPU::*)(uint8_t)> rot{};

	//instruction set
	//8-bit arithmetic and logic
};