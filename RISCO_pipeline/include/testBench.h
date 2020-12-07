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
* @since 13/11/2020
*/

SC_MODULE(testBench){
	
	sc_out<bool> reset, valid;

	sc_out< sc_bv<32> > IaddressDireto, IdataDireto, DaddressDireto, DdataDireto;
	sc_out< bool > ImemWDireto, DmemWDireto;

	sc_in < sc_bv<32> > ulaResultO_sig;	//endereço de MEM de Dados
	sc_in < sc_bv<32> > dataBO_sig1;	//WDados da MEM de Dados
	sc_in < bool > M1O_sig1;			//Sinais Write da MEM de Dados
	sc_in < sc_bv<32> > Dout_sig;		//endereço da memória de instruções


	sc_in< bool > selMux, wwb0, wwb1;
	sc_in< sc_bv<32> > in0mux, datawBReg, entradaA, entradaB;
	sc_in< sc_bv<5> > endBReg;
	sc_in< bool > wbRegs;
	sc_in< sc_bv<32> > endJump;
	sc_in< bool > saidaAnd;

	sc_in < bool > WB0, WB1, EX0, EX1, M0, M1, M2;
	sc_in < sc_bv<3> > ulaOp;
	sc_in < sc_bv<6> > Iop;
	sc_in < sc_bv<5> > IaddressA;
	sc_in < sc_bv<5> > IaddressB0;
	sc_in < sc_bv<5> > IaddressB1;
	sc_in < sc_bv<16> > Iimmediate; 

	sc_in<bool> clk;

	void source();
	void sink();

	ifstream IinDataFile;
	ifstream DinDataFile;
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