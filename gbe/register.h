#pragma once

#include <cstdint>

class Register {
public:
	Register();
	void set();
	void set(uint16_t r16);

	uint16_t reg = 0;
	uint8_t high = 0;
	uint8_t low = 0;
};

class Flags {
public:
	Flags();
	void set(Register* AF);
	void zero(bool state);
	void BCD_sub(bool state);
	void BCD_half_carry(bool state);
	void carry(bool state);

	Register* reg = nullptr;
	bool _zero = false;
	bool _BCD_sub = false;
	bool _BCD_half_carry = false;
	bool _carry = false;
};