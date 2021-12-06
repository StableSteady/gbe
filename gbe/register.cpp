#include "register.h"

Register::Register() {

}

void Register::set() {
	reg = (high << 8) & low;
}

void Register::set(uint16_t r16) {
	reg = r16;
	low = r16 & 0xFF;
	high = (r16 >> 8);
}

uint16_t Register::get() {
	this->set();
	return reg;
}

uint16_t Register::operator++() {
	this->set(++reg);
	return reg;
}

uint16_t Register::operator++(int) {
	uint16_t oldReg = reg;
	++*this;
	return oldReg;
}

Register& Register::operator+=(const uint16_t& rhs) {
	this->set(reg+rhs);
	return *this;
}

Flags::Flags() {

}

void Flags::set(Register* AF) {
	reg = AF;
	_zero = (bool)(AF->low & 0x80);
	_BCD_sub = (bool)(AF->low & 0x40);
	_BCD_half_carry = (bool)(AF->low & 0x20);
	_carry = (bool)(AF->low & 0x10);
}

void Flags::zero(bool state) {
	_zero = state;
	reg->low |= 0x80;
	reg->low &= (int)state << 7;
	reg->set();
}

void Flags::BCD_sub(bool state) {
	_BCD_sub = state;
	reg->low |= 0x40;
	reg->low &= (int)state << 6;
	reg->set();
}

void Flags::BCD_half_carry(bool state) {
	_BCD_half_carry = state;
	reg->low |= 0x20;
	reg->low &= (int)state << 5;
	reg->set();
}

void Flags::carry(bool state) {
	_carry = state;
	reg->low |= 0x10;
	reg->low &= (int)state << 4;
	reg->set();
}

