#include "TopLevel.h"

/*
* @file TopLevel.cpp
* @brief Unificação dos componentes, que formam o processador
* @author Kaio Henrique de Sousa
* @since 26/10/2020
*/

void TopLevel::tpProcess(){

	instIn_sig = instDireta;
	reset_sig = reset;
	valid_sig = valid;
	saidaUlaDireta = ulaResult_sig;
	saidaRegUlaDireta = ulaResultOut_sig;

	PCwCond = PCwCond_sig ; PCw = PCw_sig; IorD = IorD_sig;
	MemRead = memRead_sig; MemWrite = memWrite_sig; IRWrite = IRWrite_sig;
	RegDst = RegDst_sig; MemtoReg = MemtoReg_sig; RegWrite = RegWrite_sig;
	SrcA = SrcA_sig; SrcB = SrcB_sig; PCSrc = PCSrc_sig;
	ULAOp = ULAOp_sig;

	clk_sig = clk;

	//Conexões da Parte de Controle
	op_sig = instOut_sig.read().range(31, 26);

	//Conexões do Contador de Programa
	if(PCSrc_sig.read() == "00")
		inPc_sig = ulaResult_sig;
	else if(PCSrc_sig.read() == "01")
		inPc_sig = ulaResultOut_sig;
	else
		inPc_sig = static_cast< sc_bv<32> >(instOut_sig.read().range(25, 0));

	wPc_sig = (PCwCond_sig & z_sig) | PCw_sig;

	//Conexões da Memória
	if(IorD_sig.read())
		memAddress_sig = outPc_sig;
	else
		memAddress_sig = ulaResultOut_sig;
	memDataIn_sig = regBOut_sig;

	//Conexões do registrador de instruções
	instIn_sig = memDataOut_sig;

	//Conexões do registrador de dados da MEM
	regDataIn_sig = memDataOut_sig;

	//Conexões do banco de registradores
	regsAddressA_sig = instOut_sig.read().range(25, 21);
	regsAddressB_sig = instOut_sig.read().range(20, 16);
		
	if(RegDst_sig.read())
		regsAddressData_sig = instOut_sig.read().range(15, 11);
	else
		regsAddressData_sig = instOut_sig.read().range(20, 16);

	if(MemtoReg_sig.read())
		regsDataIn_sig = regDataOut_sig;
	else
		regsDataIn_sig = ulaResultOut_sig;

	//Conexões do resgistrador da entrada A da ULA
	regAIn_sig = regsDataA_sig;

	//Conexões do resgistrador da entrada B da ULA
	regBIn_sig = regsDataB_sig;

	//Conexões da ULA
	if(SrcA_sig.read())
		AulaIn_sig = regAOut_sig;
	else
		AulaIn_sig = outPc_sig;

	if(SrcB_sig.read() == "00")
		BulaIn_sig = regBOut_sig;
	else if(SrcB_sig.read() == "01")
		BulaIn_sig = 1;
	else
		BulaIn_sig = static_cast< sc_bv<32> >(instOut_sig.read().range(15, 0));

	//Conexões do registrador do resultado da ULA
	ulaResultIn_sig = ulaResult_sig;

}

TopLevel::~TopLevel(){
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
}