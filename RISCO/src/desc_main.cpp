#include <systemc.h>
/*#include "ULA.h"
#include "RAM.h"
#include "B_Reg.h"
#include "Two_lshift.h"
#include "testBench.h"
#include "RegWithW.h"
#include "P_C.h"
#include "Reg.h"*/
#include "TopLevel.h"
#include "testBench.h"

SC_MODULE(System){
	testBench *tb0;
	//ULA *ula0;
	//RAM *ram0;
	//B_Reg *regs0;
	//Two_lshift *lshift0;
	//Reg *RegWW0;
	//P_C *p_c0;
	TopLevel *tp0;

	/* sinais da ULA
	sc_signal< sc_bv<32> > A_sig;
	sc_signal< sc_bv<32> > B_sig;
	sc_signal< sc_bv<3> > opSel_sig;
	sc_signal< sc_bv<32> > result_sig;
	sc_signal< bool > z_sig;*/

	/* sinais do RAM
	sc_signal< sc_bv<32> > address_sig;
	sc_signal< sc_bv<32> > data_in_sig;
	sc_signal< bool > MemR_sig;
	sc_signal< bool > MemW_sig;
	sc_signal< sc_bv<32> > data_out_sig;*/

	/* sinais do BANK REG
	sc_signal< sc_bv<5> > address_A_sig;
	sc_signal< sc_bv<5> > address_B_sig;
	sc_signal< sc_bv<5> > address_data_sig;
	sc_signal< sc_bv<32> > data_in_sig;
	sc_signal< bool > wReg_sig;
	sc_signal< sc_bv<32> > data_A_sig;
	sc_signal< sc_bv<32> > data_B_sig;*/

	/* Sinais do deslocador
	sc_signal< sc_bv<32> > sdata_in_sig;
	sc_signal< sc_bv<32> > sdata_out_sig;*/

	/* Sinais do registrador com w
	sc_signal< sc_bv<32> > Iin_sig;
	sc_signal< sc_bv<32> > Iout_sig;
	sc_signal< bool > w_sig;
	sc_signal< bool > reset_sig;*/

	/* Sinais da PC
	sc_signal< sc_bv<6> > op_sig;
	sc_signal< bool > reset_sig, valid_sig;
	sc_signal< bool > PCwCond_sig, PCw_sig, IorD_sig, MemRead_sig, MemWrite_sig, IRWrite_sig, RegDst_sig, MemtoReg_sig, RegWrite_sig, SrcA_sig;
	sc_signal< sc_bv<2> > SrcB_sig, PCSrc_sig;
	sc_signal< sc_bv<3> > ULAOp_sig;*/

	// Sinais do Top Level
	sc_signal< sc_bv<32> > instDireta_sig;
	sc_signal<bool> reset_sig, valid_sig;
	sc_signal< sc_bv<32> > saidaUlaDireta_sig, saidaRegUlaDireta_sig;

	sc_signal< bool > PCwCond_sig, PCw_sig, IorD_sig, MemRead_sig, MemWrite_sig, IRWrite_sig, RegDst_sig, MemtoReg_sig, RegWrite_sig, SrcA_sig;
	sc_signal< sc_bv<2> > SrcB_sig, PCSrc_sig;
	sc_signal< sc_bv<3> > ULAOp_sig;


	sc_clock clk_sig;

	SC_CTOR(System):clk_sig("clk_sig", 10, SC_NS){

		// Conexões do Top Level

		tb0 = new testBench("tb0");
		tb0->instDireta(instDireta_sig);
		tb0->saidaUlaDireta(saidaUlaDireta_sig);
		tb0->saidaRegUlaDireta(saidaRegUlaDireta_sig);
		tb0->reset(reset_sig);
		tb0->valid(valid_sig);

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

		tp0 = new TopLevel("tp0");
		tp0->instDireta(instDireta_sig);
		tp0->saidaUlaDireta(saidaUlaDireta_sig);
		tp0->saidaRegUlaDireta(saidaRegUlaDireta_sig);
		tp0->reset(reset_sig);
		tp0->valid(valid_sig);

		tp0->PCwCond(PCwCond_sig);
		tp0->PCw(PCw_sig);
		tp0->IorD(IorD_sig);
		tp0->MemRead(MemRead_sig);
		tp0->MemWrite(MemWrite_sig);
		tp0->IRWrite(IRWrite_sig);
		tp0->RegDst(RegDst_sig);
		tp0->MemtoReg(MemtoReg_sig);
		tp0->RegWrite(RegWrite_sig);
		tp0->SrcA(SrcA_sig);
		tp0->SrcB(SrcB_sig);
		tp0->PCSrc(PCSrc_sig);
		tp0->ULAOp(ULAOp_sig);

		tp0->clk(clk_sig);

		/* Conexões da PC
		tb0 = new testBench("tb0");
		tb0->op(op_sig);
		tb0->reset(reset_sig);
		tb0->valid(valid_sig);
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

		p_c0 = new P_C("p_c0");
		p_c0->op(op_sig);
		p_c0->reset(reset_sig);
		p_c0->valid(valid_sig);
		p_c0->PCwCond(PCwCond_sig);
		p_c0->PCw(PCw_sig);
		p_c0->IorD(IorD_sig);
		p_c0->MemRead(MemRead_sig);
		p_c0->MemWrite(MemWrite_sig);
		p_c0->IRWrite(IRWrite_sig);
		p_c0->RegDst(RegDst_sig);
		p_c0->MemtoReg(MemtoReg_sig);
		p_c0->RegWrite(RegWrite_sig);
		p_c0->SrcA(SrcA_sig);
		p_c0->SrcB(SrcB_sig);
		p_c0->PCSrc(PCSrc_sig);
		p_c0->ULAOp(ULAOp_sig);

		p_c0->clk(clk_sig);*/

		/* Conexões do registrador com w
		tb0 = new testBench("tb0");
		tb0->Iin(Iin_sig);
		//tb0->w(w_sig);
		tb0->reset(reset_sig);
		tb0->Iout(Iout_sig);
		tb0->clk(clk_sig);

		RegWW0 = new Reg("RegWW0");
		RegWW0->Din(Iin_sig);
		//RegWW0->w(w_sig);
		RegWW0->reset(reset_sig);
		RegWW0->Dout(Iout_sig);
		RegWW0->clk(clk_sig);*/
		
		/* Conexões do deslocador
		tb0 = new testBench("tb0");
		tb0->sdata_in(sdata_in_sig);
		tb0->sdata_out(sdata_out_sig);
		tb0->clk(clk_sig);

		lshift0 = new Two_lshift("lshift0");
		lshift0->sdata_in(sdata_in_sig);
		lshift0->sdata_out(sdata_out_sig);*/


		/* Conexões do Banco de REGs
		tb0 = new testBench("tb0");
		tb0->address_A(address_A_sig);
		tb0->address_B(address_B_sig);
		tb0->address_data(address_data_sig);
		tb0->data_in(data_in_sig);
		tb0->wReg(wReg_sig);
		tb0->data_A(data_A_sig);
		tb0->data_B(data_B_sig);
		tb0->clk(clk_sig);

		regs0 = new B_Reg("regs0");
		regs0->address_A(address_A_sig);
		regs0->address_B(address_B_sig);
		regs0->address_data(address_data_sig);
		regs0->data_in(data_in_sig);
		regs0->wReg(wReg_sig);
		regs0->data_A(data_A_sig);
		regs0->data_B(data_B_sig);
		regs0->clk(clk_sig);*/
		

		/* Conexões da RAM
		tb0 = new testBench("tb0");
		tb0->address(address_sig);
		tb0->data_in(data_in_sig);
		tb0->MemW(MemW_sig);
		tb0->MemR(MemR_sig);
		tb0->data_out(data_out_sig);
		tb0->clk(clk_sig);

		ram0 = new RAM("ram0");
		ram0->address(address_sig);
		ram0->data_in(data_in_sig);
		ram0->MemW(MemW_sig);
		ram0->MemR(MemR_sig);
		ram0->data_out(data_out_sig);
		ram0->clk(clk_sig);*/

		/* conexões da ULA
		tb0 = new testBench("tb0");
		tb0->A(A_sig);
		tb0->B(B_sig);
		tb0->opSel(opSel_sig);
		tb0->result(result_sig);
		tb0->z(z_sig);
		tb0->clk(clk_sig);

		ula0 = new ULA("ula0");
		ula0->A(A_sig);
		ula0->B(B_sig);
		ula0->opSel(opSel_sig);
		ula0->result(result_sig);
		ula0->z(z_sig);*/

	}

	~System(){
		delete tb0;
		//delete ula0;
		//delete ram0;
		//delete regs0;
		//delete lshift0;
		//delete RegWW0;
		//delete p_c0;
		delete tp0;
	}

};

System *sys0 = NULL;
int sc_main(int argc, char* argv[]){
	sys0 = new System("sys0");
	sc_start();

	return 0;
}