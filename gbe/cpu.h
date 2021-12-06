#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "register.h"

class Bus;

class CPU {
public:
	CPU();
	void connect(Bus* b);
	uint8_t& read(uint16_t address);
	void write(uint16_t address, uint8_t data);
	void fetch();
	void execute();

private:
	Register AF, BC, DE, HL, SP, PC;
	Flags flag;
	Bus* bus = nullptr;
	uint64_t clock = 0;
	uint8_t opcode = 0;

	//disassembly tables
	std::vector<uint8_t*> r = { &BC.high, &BC.low, &DE.high, &DE.low, &HL.high, &HL.low, &read(HL.get()), &AF.high };
	std::vector<Register*> rp = { &BC, &DE, &HL, &SP};
	std::vector<Register*> rp2 = { &BC, &DE, &HL, &AF };
	std::vector<bool> cc = { !flag._zero, flag._zero, !flag._carry, flag._carry };
	std::vector<void (CPU::*)(uint8_t)> alu{};
	std::vector<void (CPU::*)(uint8_t)> rot{};

	//instruction set
	//from https://rgbds.gbdev.io/docs/v0.5.2/gbz80.7

};