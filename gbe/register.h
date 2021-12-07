#pragma once

#include <cstdint>

class Register {
public:
	Register();
	void set();
	void set(uint16_t r16);
	uint16_t get();
	uint16_t operator++(); //prefix
	uint16_t operator++(int); //postfix
	Register& operator+=(const uint16_t& rhs);
	uint16_t operator--(); 
	uint16_t operator--(int); 

	uint8_t high = 0;
	uint8_t low = 0;

private:
	uint16_t reg = 0;
};

class Flags {
public:
	Flags();
	void set(Register* AF);
	void z(int state);
	void n(int state);
	void h(int state);
	void c(int state);
	int z(); 
	int n();
	int h(); 
	int c();

private:
	Register* reg = nullptr;
	int Z = 0;
	int N = 0;
	int H = 0;
	int C = 0;
};