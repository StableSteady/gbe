#include "cpu.h"
#include "bus.h"

CPU::CPU() {
}

void CPU::connect(Bus* b) {
	bus = b;
}

uint8_t CPU::read(uint16_t address) {
	return bus->read(address);
}

void CPU::write(uint16_t address, uint8_t data) {
	bus->write(address, data);
}
