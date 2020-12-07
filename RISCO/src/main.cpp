#include <systemc.h>
#include <fstream>
#include "ULA.h"
#include "RAM.h"
#include "B_Reg.h"
#include "testBench.h"
#include "RegWithW.h"
#include "RegIR.h"
#include "P_C.h"
#include "Reg.h"
#include "RegNeg.h"
#include "Mux2x.h"
#include "Mux2xv1.h"
#include "Mux4x.h"
#include "Ext_16to32.h"
#include "Ext_26to32.h"
#include "And_or.h"
#include "testBench.h"


SC_MODULE(System){
	testBench *tb0;
	RegWithW *pc0;
	RAM *mem0;
	RegIR *instReg0;
	RegNeg *regMemData0;
	B_Reg *regBank0;
	Reg *A0;
	Reg *B0;
	ULA *ula0;
	Reg *ulaResult0;
	P_C *controle0;
	Mux2x *mux2x0;
	Mux2xv1 *mux2x1;
	Mux2x *mux2x2;
	Mux2x *mux2x3;
	Ext_16to32 *ext0;
	Mux4x *mux4x0;
	Ext_26to32 *ext1;
	Mux4x *mux4x1;
	And_or *and_or0;

	// Sinais do PC
	sc_signal< sc_bv<32> > outPc_sig;

	//Sinais da memória
	sc_signal< sc_bv<32> > memDataOut_sig;

	//Sinais do registrador de instruções
	sc_signal< sc_bv<6> > Iop_sig;
	sc_signal< sc_bv<5> > IaddressA_sig;
	sc_signal< sc_bv<5> > IaddressB0_sig;
	sc_signal< sc_bv<5> > IaddressB1_sig;
	sc_signal< sc_bv<16> > Iimmediate_sig;
	sc_signal< sc_bv<26> > Ipcmux_sig;

	//Sinais do registrador de dados da MEM
	sc_signal< sc_bv<32> > regDataOut_sig;

	//Sinais do banco de registradores
	sc_signal< sc_bv<32> > regsDataA_sig;
	sc_signal< sc_bv<32> > regsDataB_sig;

	//Sinais do resgistrador da entrada A da ULA
	sc_signal< sc_bv<32> > regAOut_sig;

	//Sinais do resgistrador da entrada B da ULA
	sc_signal< sc_bv<32> > regBOut_sig;

	//Sinais da ULA
	sc_signal< bool > z_sig;
	sc_signal< sc_bv<32> > ulaResult_sig;

	//Sinais do registrador do resultador da ULA
	sc_signal< sc_bv<32> > ulaResultOut_sig;

	//Sinais da Parte de Controle
	sc_signal< sc_bv<6> > op_sig;
	sc_signal< bool > PCwCond_sig, PCw_sig, IorD_sig, MemRead_sig, MemWrite_sig, IRWrite_sig, RegDst_sig, MemtoReg_sig, RegWrite_sig, SrcA_sig;
	sc_signal< sc_bv<2> > SrcB_sig, PCSrc_sig;
	sc_signal< sc_bv<3> > ULAOp_sig;

	//Sinais dos Muxes de 2 entradas
	sc_signal< sc_bv<32> > out2_Data_sig0;

		//sc_signal< sc_bv<32> > data2_0_sig1, data2_1_sig1;
	sc_signal< sc_bv<5> > out2_Data_sig1;

	sc_signal< sc_bv<32> > out2_Data_sig2;

	sc_signal< sc_bv<32> > out2_Data_sig3;
	
	//Sinais do Extensor de sinal 16 para 32 bits
	sc_signal< sc_bv<32> > extdata_out_sig0;
	
	//Sinais do Extensor de sinal 26 para 32 bits
	sc_signal< sc_bv<32> > extdata_out_sig1;

	//Sinais do Muxes de 4 entradas
	sc_signal< sc_bv<32> > data4_1_sig0{"data4_1_sig0", 1};
		//sc_signal< sc_bv<32> > data4_2_sig0;
	sc_signal< sc_bv<32> > out4_Data_sig0;

		//sc_signal< sc_bv<32> > data4_2_sig1;
	sc_signal< sc_bv<32> > out4_Data_sig1;

	//Sinais do componente and or
	sc_signal< bool > logicResult_sig;

	// Sinais do Top Level
	sc_signal< bool > mRead, mWrite;
	sc_signal< sc_bv<32> > endDiretoMem, dadoDiretoMem;

	sc_signal< bool > reset_sig, valid_sig;
	sc_clock clk_sig;

	SC_CTOR(System):clk_sig("clk_sig", 10, SC_NS){

		//Conexões da Parte de Controle
			//op_sig = instOut_sig.read().range(31, 26);
		controle0 = new P_C("controle0");
		controle0->op(Iop_sig);
		controle0->PCwCond(PCwCond_sig);
		controle0->PCw(PCw_sig);
		controle0->IorD(IorD_sig);
		controle0->MemRead(MemRead_sig);
		controle0->MemWrite(MemWrite_sig);
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

		//Conexões componente lógico and or
		and_or0 = new And_or("and_or0");
		and_or0->pcwc(PCwCond_sig);
		and_or0->zero(z_sig);
		and_or0->pcw(PCw_sig);
		and_or0->condResult(logicResult_sig);

		//Conexões do Contador de Programa
		pc0 = new RegWithW("pc0");
		pc0->Iin(out4_Data_sig1);
		pc0->w(logicResult_sig);
		pc0->Iout(outPc_sig);
		pc0->reset(reset_sig);
		pc0->clk(clk_sig);

		//Conexões do mux da entrada a memória
		mux2x0 = new Mux2x("mux2x0");
		mux2x0->data0(outPc_sig);
		mux2x0->data1(ulaResultOut_sig);
		mux2x0->x2Sel(IorD_sig);
		mux2x0->outData(out2_Data_sig0);

		//Conexões da Memória
		mem0 = new RAM("mem0");
		mem0->address(endDiretoMem);
		mem0->data_in(dadoDiretoMem);
		mem0->data_out(memDataOut_sig);
		mem0->MemW(mWrite);
		mem0->MemR(mRead);
		mem0->clk(clk_sig);

		//Conexões do registrador de instruções
		instReg0 = new RegIR("instReg0");
		instReg0->w(IRWrite_sig);
		instReg0->Iin(memDataOut_sig);
		instReg0->Iop(Iop_sig);
		instReg0->IaddressA(IaddressA_sig);
		instReg0->IaddressB0(IaddressB0_sig);
		instReg0->IaddressB1(IaddressB1_sig);
		instReg0->Iimmediate(Iimmediate_sig);
		instReg0->Ipcmux(Ipcmux_sig);
		instReg0->reset(reset_sig);
		instReg0->clk(clk_sig);

		//Conexões do registrador de dados da MEM
		regMemData0 = new RegNeg("regMemData0");
		regMemData0->Din(memDataOut_sig);
		regMemData0->Dout(regDataOut_sig);
		regMemData0->reset(reset_sig);
		regMemData0->clk(clk_sig);

		//Conexões do mux da entrada de endereço do Banco de Registradores
			//data2_0_sig1 = static_cast< sc_bv<32> >(IaddressB0_sig);
			//data2_1_sig1 = static_cast< sc_bv<32> >(IaddressB1_sig);
		mux2x1 = new Mux2xv1("mux2x1");
		mux2x1->data0(IaddressB0_sig);
		mux2x1->data1(IaddressB1_sig);
		mux2x1->x2Sel(RegDst_sig);
		mux2x1->outData(out2_Data_sig1);

		//Conexões do mux da entrada de dados do Banco de Registradores
		mux2x2 = new Mux2x("mux2x2");
		mux2x2->data0(ulaResultOut_sig);
		mux2x2->data1(regDataOut_sig);
		mux2x2->x2Sel(MemtoReg_sig);
		mux2x2->outData(out2_Data_sig2);

		//Conexões do banco de registradores
		regBank0 = new B_Reg("regBank0");
		regBank0->address_A(IaddressA_sig);
		regBank0->address_B(IaddressB0_sig);
		regBank0->address_data(out2_Data_sig1);
		regBank0->data_in(out2_Data_sig2);
		regBank0->wReg(RegWrite_sig);
		regBank0->data_A(regsDataA_sig);
		regBank0->data_B(regsDataB_sig);
		regBank0->clk(clk_sig);

		//Conexões do resgistrador da entrada A da ULA
		A0 = new Reg("A0");
		A0->Din(regsDataA_sig);
		A0->Dout(regAOut_sig);
		A0->reset(reset_sig);
		A0->clk(clk_sig);

		//Conexões do resgistrador da entrada B da ULA
		B0 = new Reg("B0");
		B0->Din(regsDataB_sig);
		B0->Dout(regBOut_sig);
		B0->reset(reset_sig);
		B0->clk(clk_sig);

		//Conexões do mux da entrada A da ULA
		mux2x3 = new Mux2x("mux2x3");
		mux2x3->data0(outPc_sig);
		mux2x3->data1(regAOut_sig);
		mux2x3->x2Sel(SrcA_sig);
		mux2x3->outData(out2_Data_sig3);

		//Conexões do Extensor de sinal 16 para 32
		ext0 = new Ext_16to32("ext0");
		ext0->extdata_in(Iimmediate_sig);
		ext0->extdata_out(extdata_out_sig0);

		//Conexões do mux da entrada sc_out< sc_bv<26> > Ipcmux;B da ULA
			//data4_2_sig0 = static_cast< sc_bv<32> >(instOut_sig.read().range(15, 0)); 
		mux4x0 = new Mux4x("mux4x0");
		mux4x0->data0(regBOut_sig);
		mux4x0->data1(data4_1_sig0);
		mux4x0->data2(extdata_out_sig0);
		mux4x0->x4Sel(SrcB_sig);
		mux4x0->outData(out4_Data_sig0);

		//Conexões da ULA
		ula0 = new ULA("ula0");
		ula0->A(out2_Data_sig3);
		ula0->B(out4_Data_sig0);
		ula0->opSel(ULAOp_sig);
		ula0->result(ulaResult_sig);
		ula0->z(z_sig);

		//Conexões do registrador do resultado da ULA
		ulaResult0 = new Reg("ulaResult0");
		ulaResult0->Din(ulaResult_sig);
		ulaResult0->Dout(ulaResultOut_sig);
		ulaResult0->reset(reset_sig);
		ulaResult0->clk(clk_sig);

		//Conexões do Extensor de sinal 26 para 32
		ext1 = new Ext_26to32("ext1");
		ext1->extdata_in(Ipcmux_sig);
		ext1->extdata_out(extdata_out_sig1);

		//Conexões do mux da entrada do contador de programa
			//data4_2_sig1 = static_cast< sc_bv<32> >(instOut_sig.read().range(25, 0));
		mux4x1 = new Mux4x("mux4x1");
		mux4x1->data0(ulaResult_sig);
		mux4x1->data1(ulaResultOut_sig);
		mux4x1->data2(extdata_out_sig1);
		mux4x1->x4Sel(PCSrc_sig);
		mux4x1->outData(out4_Data_sig1);

		//Conexões do TestBench
		tb0 = new testBench("tb0");
			//tb0->instDireta(instDireta_sig);
		tb0->mRead(mRead);
		tb0->mWrite(mWrite);
		tb0->endDiretoMem(endDiretoMem);
		tb0->dadoDiretoMem(dadoDiretoMem);
		tb0->memOut(memDataOut_sig);
		tb0->out2_Data_sig0(out2_Data_sig0);
		tb0->regBOut_sig(regBOut_sig);
		tb0->reset(reset_sig);
		tb0->valid(valid_sig);

		tb0->op(Iop_sig);
		tb0->immediate(Iimmediate_sig);

		tb0->saidaUlaDireta(ulaResult_sig);
		tb0->saidaRegUlaDireta(ulaResultOut_sig);
		tb0->PCwCond(PCwCond_sig);
		tb0->PCw(PCw_sig);
		tb0->IorD(IorD_sig);
		tb0->MemRead(MemRead_sig);
		tb0->MemWrite(MemWrite_sig);
		tb0->IRWrite(IRWrite_sig);
		tb0->RegDst(RegDst_sig);
		tb0->MemtoReg(MemtoReg_sig);
		tb0->RegWrite(RegWrite_sig);
		tb0->SrcA(SrcA_sig);
		tb0->SrcB(SrcB_sig);
		tb0->PCSrc(PCSrc_sig);
		tb0->ULAOp(ULAOp_sig);

		tb0->clk(clk_sig);

	}

	~System(){
		delete tb0;
		delete pc0;
		delete mem0;
		delete instReg0;
		delete regMemData0;
		delete regBank0;
		delete A0;
		delete B0;
		delete ula0;
		delete ulaResult0;
		delete controle0;
		delete mux2x0;
		delete mux2x1;
		delete mux2x2;
		delete mux2x3;
		delete mux4x0;
		delete mux4x1;
		delete and_or0;
	}

};

System *sys0 = NULL;
int sc_main(int argc, char* argv[]){
	sys0 = new System("sys0");
	sc_start();

	return 0;
}