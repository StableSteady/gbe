#include "bus.h"

Bus::Bus() {
	cpu.connect(this);
}

Bus::~Bus() {
}

uint8_t& Bus::read(uint16_t address) {
	return mem[address];
}

void Bus::write(uint16_t address, uint8_t data) {
	mem[address] = data;
}
