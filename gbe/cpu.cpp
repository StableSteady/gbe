#include "cpu.h"

uint8_t CPU::read(uint16_t address) {
	return bus[address];
}
