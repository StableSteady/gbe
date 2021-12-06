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

void CPU::execute() {
	if (opcode == 0xCB) {
		fetch();
		int x = opcode >> 6;
		int y = (opcode >> 3) & 07;
		int z = opcode & 07;

		switch (x) {
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		}

	} else {
		int x = opcode >> 6;
		int y = (opcode >> 3) & 07;
		int z = opcode & 07;
		int p = y >> 1;
		int q = y & 2;

		switch (x) {
		case 0:
			switch (z) {
			case 0:
				switch (y) {
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4: case 5: case 6: case 7:
					break;
				}
				break;
			case 1:
				switch (q) {
				case 0:
					break;
				case 1:
					break;
				}
				break;
			case 2:
				switch (q) {
				case 0:
					switch (p) {
					case 0:
						break;
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					}
					break;
				case 1:
					switch (p) {
					case 0:
						break;
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					}
					break;
				}
				break;
			case 3:
				switch (q) {
				case 0:
					break;
				case 1:
					break;
				}
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				switch (y) {
				case 0:
					break;
				case 1:
					break;
				case 2:
					break;
				case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				}
				break;
			}
			break;
		case 1:
			if (z == 6 && y == 6) {

			}
			else {

			}
			break;
		case 2:
			break;
		case 3:
			switch (z) {
			case 0:
				switch (y) {
				case 0: case 1: case 2: case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				}
				break;
			case 1:
				switch (q) {
				case 0:
					break;
				case 1:
					switch (p) {
					case 0:
						break;
					case 1:
						break;
					case 2:
						break;
					case 3:
						break;
					}
					break;
				}
				break;
			case 2:
				switch (y) {
				case 0: case 1: case 2: case 3:
					break;
				case 4:
					break;
				case 5:
					break;
				case 6:
					break;
				case 7:
					break;
				}
				break;
			case 3:
				switch (y) {
				case 0:
					break;
				case 6:
					break;
				case 7:
					break;
				}
				break;
			case 4:
				switch (y) {
				case 0: case 1: case 2: case 3:
					break;
				}
				break;
			case 5:
				switch (q) {
				case 0:
					break;
				case 1:
					if (p == 0) {

					}
					break;
				}
				break;
			case 6:
				break;
			case 7:
				break;
			}
			break;
		}
	}
}

void CPU::NOP() {

}

void CPU::LD_nn_SP() {
	uint8_t n = read(PC++);
	uint16_t nn = (read(PC++) << 8) & n;
	write(nn, SP & 0xFF);
	write(nn + 1, SP >> 8);
}

void CPU::STOP() {

}

void CPU::JR_d() {
	++clock;
	int8_t e = read(PC++);
	PC += e;
}

void CPU::JR_cc_d(int y) {
	int8_t e = read(PC++);
	if (cc[y - 4]) {
		++clock;
		PC += e;
	}
}

void CPU::LD_rp_nn(int p) {
	uint8_t n = read(PC++);
	uint16_t nn = (read(PC++) << 8) & n;
	*rp[p] = nn;
}


