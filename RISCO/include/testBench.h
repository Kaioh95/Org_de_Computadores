#ifndef _TESTBENCH_H_
#define _TESTBENCH_H_

#include <systemc.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
/**
* @file testBench.h
* @brief Módulo de Testes
* @author Kaio Henrique de Sousa
* @since 18/10/2020
*/

SC_MODULE(testBench){
	
	// in/out do Top Level
	sc_out<bool> reset, valid, mRead, mWrite;
	sc_out< sc_bv<32> > endDiretoMem, dadoDiretoMem;

	sc_in< sc_bv<32> > memOut;
	sc_in< sc_bv<32> > out2_Data_sig0, regBOut_sig;

	sc_in< sc_bv<6> > op;
	sc_in< sc_bv<16> > immediate;
	sc_in< sc_bv<32> > saidaUlaDireta, saidaRegUlaDireta;
	sc_in< bool > PCwCond, PCw, IorD, MemRead, MemWrite, IRWrite, RegDst, MemtoReg, RegWrite, SrcA;
	sc_in< sc_bv<2> > SrcB, PCSrc;
	sc_in< sc_bv<3> > ULAOp;

	sc_in<bool> clk;

	void source();
	void sink();

	ifstream inDataFile;
	//ofstream *outDataFile;
	sc_time start_time[64], end_time[64], clock_period;

	SC_CTOR(testBench){
		SC_CTHREAD(source, clk.pos());
		//sensitive << clk.pos();
		SC_CTHREAD(sink, clk.pos());
		//sensitive << clk.pos();
	}
};

#endif