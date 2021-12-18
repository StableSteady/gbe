#include "cpu.h"
#include "bus.h"

CPU::CPU() {
	flag.set(&AF);
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

	}
	else {
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

void CPU::DI() {
	IME = false;
}

void CPU::EI() {
	EI_FLAG = false;
}

void CPU::LD_n16_SP(uint16_t n16) {
	write(n16, SP.get() & 0xFF);
	write(n16 + 1, SP.get() >> 8);
}

void CPU::LD_A_HLI() {
	AF.high = read(HL.get());
	++HL;
}

void CPU::LD_HL_SPe8() {
	uint16_t addend = SP.get() + (int8_t)read(PC++);
	flag.z(0);
	flag.n(0);
	flag.h((int)((HL.get() & 0xfff) + (addend & 0xfff) > 0xfff));
	flag.c((((uint32_t)HL.get() + addend) >> 16) & 1);
	HL += addend;
	++clock;
}

void CPU::NOP() {

}

void CPU::OR_A_r8(int z) {
	AF.high |= *r[z];
	flag.z((int)AF.high);
	flag.n(0);
	flag.h(0);
	flag.c(0);
}

void CPU::POP_r16(int p) {
	rp2[p]->low = read(SP++);
	rp2[p]->high = read(SP++);
}

void CPU::STOP() {

}

void CPU::SUB_A_r8(int z) {
	uint8_t subtrahend = *r[z];
	flag.n(1);
	flag.h((int)((subtrahend & 0xF) > (AF.high & 0xF)));
	flag.c((int)(AF.high < subtrahend));
	AF.high -= subtrahend;
	flag.z((int)(AF.high == 0));
}

void CPU::XOR_A_r8(int z) {
	AF.high ^= *r[z];
	flag.z((int)AF.high);
	flag.n(0);
	flag.h(0);
	flag.c(0);
}

void CPU::JP_cc_n16(int y) {
	uint16_t n16 = read(PC++);
	n16 |= (read(PC++) << 8);
	if (cc[y]) {
		++clock;
		PC.set(n16);
	}
}

void CPU::JP_n16() {
	uint16_t n16 = read(PC++);
	n16 |= (read(PC++) << 8);
	PC.set(n16);
}

void CPU::JP_HL() {
	PC.set(HL.get());
}

void CPU::JR_e8(uint8_t e8) {
	++clock;
	PC += e8;
}

void CPU::JR_cc_e8(int y) {
	int8_t e8 = read(PC++);
	if (cc[y - 4]) {
		++clock;
		PC += e8;
	}
}

void CPU::LD_r8_n8(uint8_t n8, int y) {
	*r[y] = n8;
}

void CPU::LD_r8_r8(int y, int z) {
	*r[y] = *r[z];
}

void CPU::LD_r16_n16(int p) {
	rp[p]->low = read(PC++);
	rp[p]->high = read(PC++);
}

void CPU::LD_r16_A(int p) {
	write(rp[p]->get(), AF.high);
}

void CPU::LDH_n16_A() {
	uint16_t n16 = 0xFF00 + read(PC++);
	write(n16, AF.high);
}

void CPU::LD_A_r16(int p) {
	AF.high = read(rp[p]->get());
}

void CPU::LD_SP_HL() {
	++clock;
	SP.set(HL.get());
}

void CPU::ADD_A_r8(int z) {
	uint8_t addend = *r[z];
	flag.n(0);
	flag.h((int)((addend & 0xF) + (AF.high & 0xF) > 0xF));
	flag.c((((uint16_t)AF.high + addend) >> 8) & 1);
	AF.high += addend;
	flag.z((int)(AF.high == 0));
}

void CPU::ADC_A_r8(int z) {
	uint8_t addend = *r[z] + flag.c();
	flag.n(0);
	flag.h((int)((addend & 0xF) + (AF.high & 0xF) > 0xF));
	flag.c((((uint16_t)AF.high + addend) >> 8) & 1);
	AF.high += addend;
	flag.z((int)(AF.high == 0));
}

void CPU::ADD_HL_r16(int p) {
	uint16_t addend = rp[p]->get();
	flag.n(0);
	flag.h((int)((HL.get() & 0xfff) + (addend & 0xfff) > 0xfff));
	flag.c((((uint32_t)HL.get() + addend) >> 16) & 1);
	HL += addend;
	++clock;
}

void CPU::ADD_SP_e8() {
	int addend = read(PC++);
	clock += 2;
	flag.z(0);
	flag.n(0);
	flag.h((int)((SP.get() & 0xfff) + (addend & 0xfff) > 0xfff));
	flag.c((((uint32_t)SP.get() + addend) >> 16) & 1);
	SP += addend;
}

void CPU::AND_A_r8(int z) {
	AF.high &= *r[z];
	flag.z((int)AF.high);
	flag.n(0);
	flag.h(1);
	flag.c(0);
}

void CPU::LD_A_n16() {
	uint16_t n16 = read(PC++);
	n16 |= (read(PC++) << 8);
	AF.high = read(n16);
}

void CPU::LD_n16_A() {
	uint16_t n16 = read(PC++);
	n16 |= (read(PC++) << 8);
	write(n16, AF.high);
}

void CPU::LD_HLI_A() {
	write(HL.get(), AF.high);
	++HL;
}

void CPU::LD_HLD_A() {
	write(HL.get(), AF.high);
}

void CPU::LDH_A_C() {
	AF.high = read(0xFF00 | BC.low);
}

void CPU::LDH_A_n16() {
	uint16_t n16 = 0xFF00 + read(PC++);
	AF.high = read(n16);
}

void CPU::LDH_C_A() {
	write(0xFF00 | BC.low, AF.high);
}

void CPU::LD_A_HLD() {
	AF.high = read(HL.get());
	--HL;
}

void CPU::INC_r16(int p) {
	++* rp[p];
}

void CPU::DEC_r16(int p) {
	--* rp[p];
}

void CPU::HALT() {

}

void CPU::INC_r8(int y) {
	++* r[y];
}

void CPU::CPL() {
	AF.high = ~AF.high;
	flag.n(1);
	flag.h(1);
}

void CPU::DAA() {
	uint8_t correction = 0;
	if (flag.c() || (AF.high > 0x99 && !flag.n())) {
		correction += 0x60;
		flag.c(1);
	}
	if (flag.h() || ((AF.high & 0x0F) > 0x09 && !flag.n())) {
		correction += 0x06;
		flag.c(1);
	}
	AF.high += flag.n() ? -correction : correction;
	flag.z((int)(AF.high == 0));
	flag.h(0);
}

void CPU::DEC_r8(int y) {
	--* r[y];
}

void CPU::RLA() {
	flag.z(0);
	flag.n(0);
	flag.h(0);
	uint8_t prev = AF.high;
	AF.high = (AF.high << 1) | flag.c();
	flag.c((prev >> 7) & 1);
}

void CPU::RLCA() {
	flag.z(0);
	flag.n(0);
	flag.h(0);
	flag.c((AF.high >> 7) & 1);
	AF.high = (AF.high << 1) | ((AF.high >> 7) & 1);
}

void CPU::RRA() {
	flag.z(0);
	flag.n(0);
	flag.h(0);
	uint8_t prev = AF.high;
	AF.high = (AF.high >> 1) | (flag.c() << 7);
	flag.c(prev & 1);
}

void CPU::RRCA() {
	flag.z(0);
	flag.n(0);
	flag.h(0);
	flag.c(AF.high & 1);
	AF.high = ((AF.high & 1) << 7) | (AF.high >> 1);
}

void CPU::SBC_A_r8(int z) {
	uint8_t subtrahend = *r[z] + flag.c();
	flag.n(1);
	flag.h((int)((subtrahend & 0xF) > (AF.high & 0xF)));
	flag.c((int)(AF.high < subtrahend));
	AF.high -= subtrahend;
	flag.z((int)(AF.high == 0));
}

void CPU::SCF() {
	flag.c(1);
}

void CPU::CCF() {
	flag.c(~flag.c());
}

void CPU::CP_A_r8(int z) {
	uint8_t subtrahend = *r[z];
	flag.n(1);
	flag.h((int)((subtrahend & 0xF) > (AF.high & 0xF)));
	flag.c((int)(AF.high < subtrahend));
	flag.z((int)(AF.high - subtrahend == 0));
}

void CPU::RET() {
	++clock;
	PC.low = read(SP++);
	PC.high = read(SP++);
}

void CPU::RETI() {
	++clock;
	PC.low = read(SP++);
	PC.high = read(SP++);
	IME = true;
}

void CPU::RET_cc(int y) {
	++clock;
	if (cc[y]) {
		++clock;
		PC.low = read(SP++);
		PC.high = read(SP++);
	}
}

void CPU::PUSH_r16(int p) {
	SP--;
	write(SP.get(), rp2[p]->high);
	SP--;
	write(SP.get(), rp2[p]->low);
	++clock;
}

void CPU::CALL_n16() {
	uint16_t n16 = read(PC++);
	n16 |= (read(PC++) << 8);
	SP--;
	write(SP.get(), PC.high);
	SP--;
	write(SP.get(), PC.low);
	PC.set(n16);
	++clock;
}

void CPU::CALL_cc_n16(int y) {
	uint16_t n16 = read(PC++);
	n16 |= (read(PC++) << 8);
	if (cc[y]) {
		SP--;
		write(SP.get(), PC.high);
		SP--;
		write(SP.get(), PC.low);
		PC.set(n16);
		++clock;
	}
}