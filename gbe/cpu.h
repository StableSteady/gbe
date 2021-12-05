#pragma once

#include <cstdint>
#include <string>

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
	std::array<uint8_t&, 8> r{ B, C, D, E, H, L, read(HL), A };
	std::array<uint16_t&, 4> rp{BC, DE, HL, SP};
	std::array<uint16_t&, 4> rp2{ BC, DE, HL, AF };
	std::array<bool, 4> cc{ !z, z, !c, c };
	std::array<void (CPU::*)(uint8_t), 8> alu{};
	std::array<void (CPU::*)(uint8_t), 8> rot{};

	//instruction set
	//8-bit arithmetic and logic
};