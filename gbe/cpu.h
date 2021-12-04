#pragma once

#include <cstdint>
#include <string>

#include "memory.h"

class CPU {
public:
	CPU();
private:
	uint8_t A, B, C, D, E, F, H, L;
	uint16_t SP, PC;
};