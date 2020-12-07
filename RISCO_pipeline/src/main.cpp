#include <systemc.h>
#include "Adder.h"
#include "And.h"
#include "B_Reg.h"
#include "DataMem.h"
#include "Ex_Mem.h"
#include "Ext_16to32.h"
#include "Id_Ex.h"
#include "If_Id.h"
#include "InstMem.h"
#include "Mem_Wb.h"
#include "Mux2x.h"
#include "Mux2x5b.h"
#include "P_C.h"
#include "Reg.h"
#include "testBench.h"
#include "ULA.h"


SC_MODULE(System){
	testBench *tb0;
	Adder *add0;
	Adder *add1;
	And *and0;
	B_Reg *regBank0;
	DataMem *dataMem0;
	Ex_Mem *ex_mem0;
	Ext_16to32 *ext0;
	Id_Ex *id_ex0;
	If_Id *if_id0;
	InstMem *instMem0;
	Mem_Wb *mem_wb0;
	Mux2x *mux2x0;
	Mux2x *mux2x1;
	Mux2x5b *mux2x2;
	Mux2x *mux2x3;
	P_C *p_c0;
	Reg *p_counter0;
	ULA *ula0;

	// Sinais do contador de programa
	sc_signal< sc_bv<32> > Dout_sig;

	// Sinais do mux do contador de programa
	sc_signal< sc_bv<32> > outData0_sig;

	// Sinais do somador PC+1
	sc_signal< sc_bv<32> > Bdata_in_sig{"Bdata_in_sig", 1};
	sc_signal< sc_bv<32> > out_pcounter_sig;

	// Sinais da memória de instruções
	sc_signal< sc_bv<32> > data_out_sig;

	// Sinais do buffer IF/ID
	sc_signal< sc_bv<6> > Iop_sig;
	sc_signal< sc_bv<5> > IaddressA_sig, IaddressB0_sig, IaddressB1_sig;
	sc_signal< sc_bv<16> > Iimmediate_sig;
	sc_signal< sc_bv<32> > jAddressOut_sig;
	sc_signal< bool > clk_out_sig;

	// Sinais do banco de registradores
	sc_signal< sc_bv<32> > data_A_sig;
	sc_signal< sc_bv<32> > data_B_sig;

	// Sinais do extensor de sinais 16 bits para 32
	sc_signal< sc_bv<32> > extdata_out_sig;

	// Sinais do controlador
	sc_signal< bool > WB0_sig, WB1_sig, EX0_sig, EX1_sig;
	sc_signal< bool > M0_sig, M1_sig, M2_sig;
	sc_signal< sc_bv<3> > ulaOp_sig;

	// Sinais buffer ID/EX
	sc_signal< bool > WB0O_sig, WB1O_sig;
	sc_signal< bool > M0O_sig, M1O_sig, M2O_sig;
	sc_signal< bool > EX0O_sig, EX1O_sig;
	sc_signal< sc_bv<3> > ulaOpO_sig;
	sc_signal< sc_bv<32> > jAddressO_sig1;
	sc_signal< sc_bv<32> > dataAO_sig, dataBO_sig;
	sc_signal< sc_bv<32> > immediateO_sig;
	sc_signal< sc_bv<5> > addressAO_sig, addressBO_sig;
	sc_signal< bool > clk_out_sig1;

	// Sinais do somador para cálculo do desvio
	sc_signal< sc_bv<32> > outJ_sig;

	// Sinais mux da entada B da ULA
	sc_signal< sc_bv<32> > outData1_sig;

	// Sinais da ULA
	sc_signal< sc_bv<32> > ulaResult_sig;
	sc_signal< bool > z_sig;

	// Sinais do mux do endereço do registrador a ser escrito
	sc_signal< sc_bv<5> > outData2_sig;

	// Sinais do buffer EX/MEM
	sc_signal< bool > WB0O_sig1, WB1O_sig1;
	sc_signal< bool > M0O_sig1, M1O_sig1, M2O_sig1;
	sc_signal< sc_bv<32> > jAddressO_sig2;
	sc_signal< bool > zeroO_sig;
	sc_signal< sc_bv<32> > ulaResultO_sig, dataBO_sig1;
	sc_signal< sc_bv<5> > addressWriteRegO_sig;
	sc_signal< bool > clk_out_sig2;

	// Sinais do componente AND
	sc_signal< bool > result_sig;

	// Sinais da memória de dados
	sc_signal< sc_bv<32> > data_out_dsig;

	// Sinais buffer MEM/WB
	sc_signal< bool > WB0O_sig2, WB1O_sig2;
	sc_signal< sc_bv<32> > dataOutO_sig, ulaResultO_sig1;
	sc_signal< sc_bv<5> > addressWriteRegO_sig1;
	sc_signal< bool > clk_out_sig3;

	// Sinais do mux do estágio Write Back
	sc_signal< sc_bv<32> > outData3_sig;

	// Sinais do test bench
	sc_signal< sc_bv<32> > IaddressDireto, IdataDireto;
	sc_signal< bool > ImemWDireto;

	sc_signal< sc_bv<32> > DaddressDireto, DdataDireto;
	sc_signal< bool > DmemWDireto;

	sc_signal< bool > reset_sig, valid_sig;
	sc_clock clk_sig;

	SC_CTOR(System):clk_sig("clk_sig", 10, SC_NS){

		// Conexões do contador de programa
		p_counter0 = new Reg("p_counter0");
		p_counter0->Din(outData0_sig);
		p_counter0->Dout(Dout_sig);
		p_counter0->clk(clk_sig);
		p_counter0->reset(reset_sig);
		p_counter0->valid(valid_sig);

		// Conexões do mux do contador de programa
		mux2x0 = new Mux2x("mux2x0");
		mux2x0->data0(out_pcounter_sig);
		mux2x0->data1(jAddressO_sig2);
		mux2x0->x2Sel(result_sig);
		mux2x0->outData(outData0_sig);

		// Conexões do somador PC+1
		add0 = new Adder("add0");
		add0->Adata_in(Dout_sig);
		add0->Bdata_in(Bdata_in_sig);
		add0->data_out(out_pcounter_sig);

		// Conexões da memória de instruções
		instMem0 = new InstMem("instMem0");
		instMem0->address(IaddressDireto);
		instMem0->data_in(IdataDireto);
		instMem0->MemW(ImemWDireto);
		instMem0->data_out(data_out_sig);
		instMem0->clk(clk_sig);

		// Conexões do buffer IF/ID
		if_id0 = new If_Id("if_id0");
		if_id0->Iin(data_out_sig);
		if_id0->jAddressIn(out_pcounter_sig);
		if_id0->Iop(Iop_sig);
		if_id0->IaddressA(IaddressA_sig);
		if_id0->IaddressB0(IaddressB0_sig);
		if_id0->IaddressB1(IaddressB1_sig);
		if_id0->Iimmediate(Iimmediate_sig);
		if_id0->jAddressOut(jAddressOut_sig);
		if_id0->reset(reset_sig);
		if_id0->valid(valid_sig);
		if_id0->clk(clk_sig);
		if_id0->clk_out(clk_out_sig);

		// Conexões do banco de registradores
		regBank0 = new B_Reg("regBank0");
		regBank0->address_A(IaddressA_sig);
		regBank0->address_B(IaddressB0_sig);
		regBank0->address_data(addressWriteRegO_sig1);
		regBank0->data_in(outData3_sig);
		regBank0->wReg(WB0O_sig2);		//WB0O_sig2
		regBank0->data_A(data_A_sig);
		regBank0->data_B(data_B_sig);
		regBank0->clk(clk_out_sig);

		// Conexões do extensor de sinais 16 bits para 32
		ext0 = new Ext_16to32("ext0");
		ext0->extdata_in(Iimmediate_sig);
		ext0->extdata_out(extdata_out_sig);

		// Conexões do controlador
		p_c0 = new P_C("p_c0");
		p_c0->op(Iop_sig);
		p_c0->WB0(WB0_sig);
		p_c0->WB1(WB1_sig);
		p_c0->EX0(EX0_sig);
		p_c0->EX1(EX1_sig);
		p_c0->M0(M0_sig);
		p_c0->M1(M1_sig);
		p_c0->M2(M2_sig);
		p_c0->ulaOp(ulaOp_sig);
		p_c0->reset(reset_sig);
		p_c0->valid(valid_sig);
		p_c0->clk(clk_out_sig);

		// Conexões buffer ID/EX
		id_ex0 = new Id_Ex("id_ex0");
		id_ex0->WB0(WB0_sig);
		id_ex0->WB1(WB1_sig);
		id_ex0->M0(M0_sig);
		id_ex0->M1(M1_sig);
		id_ex0->M2(M2_sig);
		id_ex0->EX0(EX0_sig);
		id_ex0->EX1(EX1_sig);
		id_ex0->ulaOp(ulaOp_sig);
		id_ex0->jAddress(jAddressOut_sig);
		id_ex0->dataA(data_A_sig);
		id_ex0->dataB(data_B_sig);
		id_ex0->immediate(extdata_out_sig);
		id_ex0->addressA(IaddressB0_sig);
		id_ex0->addressB(IaddressB1_sig);

		id_ex0->WB0O(WB0O_sig);
		id_ex0->WB1O(WB1O_sig);
		id_ex0->M0O(M0O_sig);
		id_ex0->M1O(M1O_sig);
		id_ex0->M2O(M2O_sig);
		id_ex0->EX0O(EX0O_sig);
		id_ex0->EX1O(EX1O_sig);
		id_ex0->ulaOpO(ulaOpO_sig);
		id_ex0->jAddressO(jAddressO_sig1);
		id_ex0->dataAO(dataAO_sig);
		id_ex0->dataBO(dataBO_sig);
		id_ex0->immediateO(immediateO_sig);
		id_ex0->addressAO(addressAO_sig);
		id_ex0->addressBO(addressBO_sig);

		id_ex0->reset(reset_sig);
		id_ex0->valid(valid_sig);
		id_ex0->clk(clk_sig);
		id_ex0->clk_out(clk_out_sig1);

		// Conexões do somador para cálculo do desvio
		add1 = new Adder("add1");
		add1->Adata_in(jAddressO_sig1);
		add1->Bdata_in(immediateO_sig);
		add1->data_out(outJ_sig);

		// Conexões mux da entada B da ULA
		mux2x1 = new Mux2x("mux2x1");
		mux2x1->data0(dataBO_sig);
		mux2x1->data1(immediateO_sig);
		mux2x1->x2Sel(EX0O_sig);		//EX0O_sig
		mux2x1->outData(outData1_sig);

		// Conexões da ULA
		ula0 = new ULA("ula0");
		ula0->A(dataAO_sig);
		ula0->B(outData1_sig);
		ula0->opSel(ulaOpO_sig);
		ula0->result(ulaResult_sig);
		ula0->z(z_sig);

		// Conexões do mux do endereço do registrador a ser escrito
		mux2x2 = new Mux2x5b("mux2x2");
		mux2x2->data0(addressAO_sig);
		mux2x2->data1(addressBO_sig);
		mux2x2->x2Sel(EX1O_sig);		//EX1O_sig
		mux2x2->outData(outData2_sig);

		// Conexões do buffer EX/MEM
		ex_mem0 = new Ex_Mem("ex_mem0");
		ex_mem0->WB0(WB0O_sig);
		ex_mem0->WB1(WB1O_sig);
		ex_mem0->M0(M0O_sig);
		ex_mem0->M1(M1O_sig);
		ex_mem0->M2(M2O_sig);
		ex_mem0->jAddress(outJ_sig);
		ex_mem0->zero(z_sig);
		ex_mem0->ulaResult(ulaResult_sig);
		ex_mem0->dataB(dataBO_sig);
		ex_mem0->addressWriteReg(outData2_sig);

		ex_mem0->WB0O(WB0O_sig1);
		ex_mem0->WB1O(WB1O_sig1);
		ex_mem0->M0O(M0O_sig1);
		ex_mem0->M1O(M1O_sig1);
		ex_mem0->M2O(M2O_sig1);
		ex_mem0->jAddressO(jAddressO_sig2);
		ex_mem0->zeroO(zeroO_sig);
		ex_mem0->ulaResultO(ulaResultO_sig);
		ex_mem0->dataBO(dataBO_sig1);
		ex_mem0->addressWriteRegO(addressWriteRegO_sig);

		ex_mem0->reset(reset_sig);
		ex_mem0->valid(valid_sig);
		ex_mem0->clk(clk_sig);
		ex_mem0->clk_out(clk_out_sig2);

		// Conexões do componente AND
		and0 = new And("and0");
		and0->e1(M0O_sig1);
		and0->e2(zeroO_sig);
		and0->result(result_sig);

		// Conexões da memória de dados
		dataMem0 = new DataMem("dataMem0");
		dataMem0->address(DaddressDireto);
		dataMem0->data_in(DdataDireto);
		dataMem0->MemW(DmemWDireto);
		dataMem0->MemR(M2O_sig1);		//M2O_sig1
		dataMem0->data_out(data_out_dsig);
		dataMem0->clk(clk_sig);

		// Conexões buffer MEM/WB
		mem_wb0 = new Mem_Wb("mem_wb0");
		mem_wb0->WB0(WB0O_sig1);
		mem_wb0->WB1(WB1O_sig1);
		mem_wb0->dataOut(data_out_dsig);
		mem_wb0->ulaResult(ulaResultO_sig);
		mem_wb0->addressWriteReg(addressWriteRegO_sig);
		mem_wb0->WB0O(WB0O_sig2);
		mem_wb0->WB1O(WB1O_sig2);
		mem_wb0->dataOutO(dataOutO_sig);
		mem_wb0->ulaResultO(ulaResultO_sig1);
		mem_wb0->addressWriteRegO(addressWriteRegO_sig1);
		mem_wb0->reset(reset_sig);
		mem_wb0->valid(valid_sig);
		mem_wb0->clk(clk_sig);
		mem_wb0->clk_out(clk_out_sig3);

		// Conexões do mux do estágio Write Back
		mux2x3 = new Mux2x("mux2x3");
		mux2x3->data0(dataOutO_sig);
		mux2x3->data1(ulaResultO_sig1);
		mux2x3->x2Sel(WB1O_sig2);		//WB1O_sig2
		mux2x3->outData(outData3_sig);

		//Conexões do TestBench
		tb0 = new testBench("tb0");
		tb0->ulaResultO_sig(ulaResultO_sig);
		tb0->dataBO_sig1(dataBO_sig1);
		tb0->M1O_sig1(M1O_sig1);		//M1O_sig1
		tb0->Dout_sig(Dout_sig);

		tb0->IaddressDireto(IaddressDireto);
		tb0->IdataDireto(IdataDireto);
		tb0->ImemWDireto(ImemWDireto);

		tb0->DaddressDireto(DaddressDireto);
		tb0->DdataDireto(DdataDireto);
		tb0->DmemWDireto(DmemWDireto);

		tb0->entradaA(dataAO_sig);
		tb0->entradaB(outData1_sig);
		tb0->wwb0(M1O_sig1);
		tb0->wwb1(M2O_sig1);
		tb0->selMux(WB1O_sig2);
		tb0->in0mux(data_out_dsig);
		tb0->datawBReg(outData3_sig);
		tb0->endBReg(addressWriteRegO_sig1);
		tb0->wbRegs(WB0O_sig2);
		tb0->endJump(jAddressO_sig2);
		tb0->saidaAnd(result_sig);

		tb0->WB0(WB0_sig);
		tb0->WB1(WB1_sig);
		tb0->EX0(EX0_sig);
		tb0->EX1(EX1_sig);
		tb0->M0(M0_sig);
		tb0->M1(M1_sig);
		tb0->M2(M2_sig);
		tb0->ulaOp(ulaOp_sig);

		tb0->Iop(Iop_sig);
		tb0->IaddressA(IaddressA_sig);
		tb0->IaddressB0(IaddressB0_sig);
		tb0->IaddressB1(IaddressB1_sig);
		tb0->Iimmediate(Iimmediate_sig);

		tb0->reset(reset_sig);
		tb0->valid(valid_sig);
		tb0->clk(clk_sig);

	}

	~System(){
		delete tb0;
		delete add0;
		delete add1;
		delete and0;
		delete regBank0;
		delete dataMem0;
		delete ex_mem0;
		delete ext0;
		delete id_ex0;
		delete if_id0;
		delete instMem0;
		delete mem_wb0;
		delete mux2x0;
		delete mux2x1;
		delete mux2x2;
		delete mux2x3;
		delete p_c0;
		delete p_counter0;
		delete ula0;
	}

};

System *sys0 = NULL;
int sc_main(int argc, char* argv[]){
	sys0 = new System("sys0");
	sc_start();

	return 0;
}