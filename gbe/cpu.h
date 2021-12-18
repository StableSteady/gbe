#pragma once

#include <cstdint>
#include <string>
#include <vector>

#include "register.h"

class Bus;

class CPU {
public:
	CPU();
	void connect(Bus* b);
	uint8_t& read(uint16_t address);
	void write(uint16_t address, uint8_t data);
	void fetch();
	void execute();

private:
	Register AF, BC, DE, HL, SP, PC;
	Flags flag;
	Bus* bus = nullptr;
	uint64_t clock = 0;
	uint8_t opcode = 0;
	bool IME = false;
	bool EI_FLAG = false;

	//disassembly tables
	std::vector<uint8_t*> r = { &BC.high, &BC.low, &DE.high, &DE.low, &HL.high, &HL.low, &read(HL.get()), &AF.high };
	std::vector<Register*> rp = { &BC, &DE, &HL, &SP};
	std::vector<Register*> rp2 = { &BC, &DE, &HL, &AF };
	std::vector<int> cc = { !flag.z(), flag.z(), !flag.c(), flag.c()};
	std::vector<void (CPU::*)(uint8_t)> alu{};
	std::vector<void (CPU::*)(uint8_t)> rot{};

	//instruction set
	//from https://rgbds.gbdev.io/docs/v0.5.2/gbz80.7
	void ADC_A_r8(int z); void ADC_r8_A(uint8_t r8); void ADC_A_HL(); void ADC_A_n8(uint8_t n8); void ADD_A_r8(int z); void ADD_A_HL(); void ADD_A_n8();
	void ADD_HL_r16(int p); void ADD_HL_SP(); void ADD_SP_e8(); void AND_A_r8(int z); void AND_A_HL(); void AND_A_n8(); 
	void BIT_u3_r8(); void BIT_u2_HL(); void CALL_n16(); void CALL_cc_n16(int y); void CCF(); void CP_A_r8(int z); 
	void CP_A_HL(); void CP_A_n8(); void CPL(); void DAA(); void DEC_r8(int y); void DEC_HL(); 
	void DEC_r16(int p); void DEC_SP(); void DI(); void EI(); void HALT(); void INC_r8(int y); 
	void INC_HL(); void INC_r16(int p); void INC_SP(); void JP_n16(); void JP_cc_n16(int y); void JP_HL();
	void JR_e8(uint8_t e8); void JR_cc_e8(int y); void LD_r8_r8(int y, int z); void LD_r8_n8(uint8_t n8, int y); void LD_r16_n16(int p);  void LD_HL_r8(); void LD_HL_n8();
	void LD_r8_HL(); void LD_r16_A(int p); void LD_n16_A(); void LDH_n16_A(); void LDH_C_A(); void LD_A_r16(int p); 
	void LD_A_n16(); void LDH_A_n16(); void LDH_A_C(); void LD_HLI_A(); void LD_HLD_A(); void LD_A_HLD();
	void LD_A_HLI(); void LD_SP_n16(); void LD_n16_SP(uint16_t n16); void LD_HL_SPe8(); void LD_SP_HL(); void NOP();
	void OR_A_r8(int z); void OR_A_HL(); void OR_A_n8(); void POP_AF(); void POP_r16(int p); void PUSH_AF(); 
	void PUSH_r16(int p); void RES_u3_r8(); void RES_u3_HL(); void RET(); void RET_cc(int y); void RETI(); 
	void RL_r8(); void RL_HL(); void RLA(); void RLC_r8(); void RLC_HL(); void RLCA(); 
	void RR_r8(); void RR_HL(); void RRA(); void RRC_r8(); void RRC_HL(); void RRCA(); 
	void RST_vec(); void SBC_A_r8(int z); void SBC_A_HL(); void SBC_A_n8(); void SCF(); void SET_u3_r8();
	void SET_u3_HL(); void SLA_r8(); void SLA_HL(); void SRA_r8(); void SRA_HL(); void SRL_r8(); 
	void SRL_HL(); void STOP(); void SUB_A_r8(int z); void SUB_A_HL(); void SUB_A_n8(); void SWAP_r8();
	void SWAP_HL(); void XOR_A_r8(int z); void XOR_A_HL(); void XOR_A_n8();
};