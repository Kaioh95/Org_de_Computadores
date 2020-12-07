#ifndef TOPLEVEL_H
#define TOPLEVEL_H

#include <systemc.h>
#include "ULA.h"
#include "RAM.h"
#include "B_Reg.h"
#include "Two_lshift.h"
#include "testBench.h"
#include "RegWithW.h"
#include "P_C.h"
#include "Reg.h"

/**
* @file TopLevel.h
* @brief Unificação dos componentes, que formam o processador
* @author Kaio Henrique de Sousa
* @since 26/10/2020
*/

SC_MODULE(TopLevel){

	sc_in< sc_bv<32> > instDireta;
	sc_in<bool> clk, reset, valid;
	sc_out< sc_bv<32> > saidaUlaDireta, saidaRegUlaDireta;

	sc_out< bool > PCwCond, PCw, IorD, MemRead, MemWrite, IRWrite, RegDst, MemtoReg, RegWrite, SrcA;
	sc_out< sc_bv<2> > SrcB, PCSrc;
	sc_out< sc_bv<3> > ULAOp;

	RegWithW *pc0;
	RAM *mem0;
	RegWithW *instReg0;
	Reg *regMemData0;
	B_Reg *regBank0;
	Reg *A0;
	Reg *B0;
	ULA *ula0;
	Reg *ulaResult0;
	P_C *controle0;

	// Sinais do PC
	sc_signal< sc_bv<32> > inPc_sig;
	sc_signal< bool > wPc_sig;
	sc_signal< sc_bv<32> > outPc_sig;

	//Sinais da memória
	sc_signal< sc_bv<32> > memAddress_sig;
	sc_signal< sc_bv<32> > memDataIn_sig;
	sc_signal< bool > memWrite_sig;
	sc_signal< bool > memRead_sig;
	sc_signal< sc_bv<32> > memDataOut_sig;

	//Sinais do registrador de instruções
	sc_signal< sc_bv<32> > instIn_sig;
	sc_signal< bool > IRWrite_sig;
	sc_signal< sc_bv<32> > instOut_sig;

	//Sinais do registrador de dados da MEM
	sc_signal< sc_bv<32> > regDataIn_sig;
	sc_signal< sc_bv<32> > regDataOut_sig;

	//Sinais do banco de registradores
	sc_signal< sc_bv<5> > regsAddressA_sig;
	sc_signal< sc_bv<5> > regsAddressB_sig;
	sc_signal< sc_bv<5> > regsAddressData_sig;
	sc_signal< sc_bv<32> > regsDataIn_sig;
	sc_signal< bool > regsWrite_sig;
	sc_signal< sc_bv<32> > regsDataA_sig;
	sc_signal< sc_bv<32> > regsDataB_sig;

	//Sinais do resgistrador da entrada A da ULA
	sc_signal< sc_bv<32> > regAIn_sig;
	sc_signal< sc_bv<32> > regAOut_sig;

	//Sinais do resgistrador da entrada B da ULA
	sc_signal< sc_bv<32> > regBIn_sig;
	sc_signal< sc_bv<32> > regBOut_sig;

	//Sinais da ULA
	sc_signal< sc_bv<32> > AulaIn_sig;
	sc_signal< sc_bv<32> > BulaIn_sig;
	sc_signal< sc_bv<3> > ULAOp_sig;
	sc_signal< bool > z_sig;
	sc_signal< sc_bv<32> > ulaResult_sig;

	//Sinais do registrador do resultador da ULA
	sc_signal< sc_bv<32> > ulaResultIn_sig;
	sc_signal< sc_bv<32> > ulaResultOut_sig;

	//Sinais da Parte de Controle
	sc_signal< sc_bv<6> > op_sig;
	sc_signal< bool > PCwCond_sig, PCw_sig, IorD_sig, RegDst_sig, MemtoReg_sig, RegWrite_sig, SrcA_sig;
	sc_signal< sc_bv<2> > SrcB_sig, PCSrc_sig;
		//sc_signal< bool > MemRead, MemWrite, IRWrite;
		//sc_signal< sc_bv<3> > ULAOp;

	sc_signal< bool > clk_sig, reset_sig, valid_sig;

	void tpProcess();

	SC_CTOR(TopLevel){

		//Conexões da Parte de Controle
		controle0 = new P_C("controle0");
		controle0->op(op_sig);
		controle0->PCwCond(PCwCond_sig);
		controle0->PCw(PCw_sig);
		controle0->IorD(IorD_sig);
		controle0->MemRead(memRead_sig);
		controle0->MemWrite(memWrite_sig);
		controle0->IRWrite(IRWrite_sig);
		controle0->RegDst(RegDst_sig);
		controle0->MemtoReg(MemtoReg_sig);
		controle0->RegWrite(RegWrite_sig);
		controle0->SrcA(SrcA_sig);
		controle0->SrcB(SrcB_sig);
		controle0->PCSrc(PCSrc_sig);
		controle0->ULAOp(ULAOp_sig);
		controle0->reset(reset_sig);
		controle0->valid(valid_sig);
		controle0->clk(clk_sig);

		//Conexões do Contador de Programa
		pc0 = new RegWithW("pc0");
		pc0->Iin(inPc_sig);
		pc0->w(wPc_sig);
		pc0->Iout(outPc_sig);
		pc0->reset(reset_sig);
		pc0->clk(clk_sig);

		//Conexões da Memória
		mem0 = new RAM("mem0");
		mem0->address(memAddress_sig);
		mem0->data_in(memDataIn_sig);
		mem0->data_out(memDataOut_sig);
		mem0->MemW(memWrite_sig);
		mem0->MemR(memRead_sig);
		mem0->clk(clk_sig);

		//Conexões do registrador de instruções
		instReg0 = new RegWithW("instReg0");
		instReg0->Iin(instIn_sig);
		instReg0->w(IRWrite_sig);
		instReg0->Iout(instOut_sig);
		instReg0->reset(reset_sig);
		instReg0->clk(clk_sig);

		//Conexões do registrador de dados da MEM
		regMemData0 = new Reg("regMemData0");
		regMemData0->Din(regDataIn_sig);
		regMemData0->Dout(regDataOut_sig);
		regMemData0->reset(reset_sig);
		regMemData0->clk(clk_sig);

		//Conexões do banco de registradores
		regBank0 = new B_Reg("regBank0");
		regBank0->address_A(regsAddressA_sig);
		regBank0->address_B(regsAddressB_sig);
		regBank0->address_data(regsAddressData_sig);
		regBank0->data_in(regsDataIn_sig);
		regBank0->wReg(regsWrite_sig);
		regBank0->data_A(regsDataA_sig);
		regBank0->data_B(regsDataB_sig);
		regBank0->clk(clk_sig);

		//Conexões do resgistrador da entrada A da ULA
		A0 = new Reg("A0");
		A0->Din(regAIn_sig);
		A0->Dout(regAOut_sig);
		A0->reset(reset_sig);
		A0->clk(clk_sig);

		//Conexões do resgistrador da entrada B da ULA
		B0 = new Reg("B0");
		B0->Din(regBIn_sig);
		B0->Dout(regBOut_sig);
		B0->reset(reset_sig);
		B0->clk(clk_sig);

		//Conexões da ULA
		ula0 = new ULA("ula0");
		ula0->A(AulaIn_sig);
		ula0->B(BulaIn_sig);
		ula0->opSel(ULAOp_sig);
		ula0->result(ulaResult_sig);
		ula0->z(z_sig);

		//Conexões do registrador do resultado da ULA
		ulaResult0 = new Reg("ulaResult0");
		ulaResult0->Din(ulaResultIn_sig);
		ulaResult0->Dout(ulaResultOut_sig);
		ulaResult0->reset(reset_sig);
		ulaResult0->clk(clk_sig);

		SC_CTHREAD(tpProcess, clk.pos());
		//sensitive << clk.pos();
	}

	~TopLevel();

};

#endif