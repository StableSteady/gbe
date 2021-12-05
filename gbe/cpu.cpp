#include "cpu.h"
#include "bus.h"

CPU::CPU() {
}

void CPU::connect(Bus* b) {
	bus = b;
}

uint8_t& CPU::read(uint16_t address) {
	++clock;
	return bus->read(address);
}

void CPU::write(uint16_t address, uint8_t data) {
	++clock;
	bus->write(address, data);
}

void CPU::fetch() {
	opcode = read(PC++);
}

void CPU::decode() {
	int x = opcode >> 6;
	int y = (opcode >> 3) & 07;
	int z = opcode & 07;
	int p = y >> 1;
	int q = y & 2;


}


