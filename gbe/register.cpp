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

uint16_t Register::operator--() {
	this->set(--reg);
	return reg;
}

uint16_t Register::operator--(int) {
	uint16_t oldReg = reg;
	--* this;
	return oldReg;
}

Flags::Flags() {

}

void Flags::set(Register* AF) {
	reg = AF;
	Z = (AF->low & 0x80);
	N = (AF->low & 0x40);
	H = (AF->low & 0x20);
	C = (AF->low & 0x10);
}

void Flags::z(int state) {
	Z = state;
	reg->low |= 0x80;
	reg->low &= state << 7;
	reg->set();
}

void Flags::n(int state) {
	N = state;
	reg->low |= 0x40;
	reg->low &= state << 6;
	reg->set();
}

void Flags::h(int state) {
	H = state;
	reg->low |= 0x20;
	reg->low &= state << 5;
	reg->set();
}

void Flags::c(int state) {
	C = state;
	reg->low |= 0x10;
	reg->low &= state << 4;
	reg->set();
}

int Flags::z() {
	return Z;
}

int Flags::n() {
	return N;
}

int Flags::h() {
	return H;
}

int Flags::c() {
	return C;
}

