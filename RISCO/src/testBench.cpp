#include "testBench.h"

// Top Level teste
void testBench::source(){
	reset.write(1);
	valid.write(0);
	wait();

	// Lendo dados de arquivo externo e escrevendo na memória
	string linha1, linha2;

	inDataFile.open("inDataFile.txt");
	if(!inDataFile.is_open()){
		cout << "Falha ao abrir arquivo" << endl;
		return;
	}

	bool tmRead, tmWrite;
	sc_bv<32> tendDiretoMem, tdadoDiretoMem;

	while(getline(inDataFile, linha1) and getline(inDataFile, linha2)){
		tendDiretoMem = linha1.c_str();
		tdadoDiretoMem = linha2.c_str();
		tmRead = false;
		tmWrite = true;

		endDiretoMem.write(tendDiretoMem);
		dadoDiretoMem.write(tdadoDiretoMem);
		mRead.write(tmRead);
		mWrite.write(tmWrite);
		wait();
	}
	inDataFile.close();
	//**************************************
	//Executando o que foi escrito na Mem
	endDiretoMem.write(0);
	dadoDiretoMem.write(0);
	mRead.write(0);
	mWrite.write(0);

	bool treset = false;
	bool tvalid = false;

	for(int i = 0; i<64; i++){
		if(i>=4){
			tvalid = true;
			treset = false;
			tmRead = MemRead.read();
			tmWrite = MemWrite.read();
			tendDiretoMem = out2_Data_sig0.read();
			tdadoDiretoMem = regBOut_sig.read();
		}

		endDiretoMem.write(tendDiretoMem);
		dadoDiretoMem.write(tdadoDiretoMem);
		mRead.write(tmRead);
		mWrite.write(tmWrite);

		reset.write(treset);
		valid.write(tvalid);
		start_time[i] = sc_time_stamp();
		wait();
	}
}

void testBench::sink(){
	sc_bv<32> tsaidaUlaDireta, tsaidaRegUlaDireta, tmemOut;

	bool tPCwCond, tPCw, tIorD, tMemRead, tMemWrite, tIRWrite, tRegDst, tMemtoReg, tRegWrite, tSrcA;
	sc_bv<2> tSrcB, tPCSrc;
	sc_bv<3> tULAOp;
	sc_bv<6> top;
	sc_bv<16> timmediate;

	//Extract clock period
	sc_clock *clk_p = DCAST<sc_clock*>(clk.get_interface());
	clock_period = clk_p->period();

	double total_cycles = 0;

	for(int i = 0; i<64; i++){
		tsaidaUlaDireta = saidaUlaDireta.read();
		tsaidaRegUlaDireta = saidaRegUlaDireta.read();
		tmemOut = memOut.read();

		tPCwCond = PCwCond.read(); tPCw = PCw.read(); tIorD = IorD.read();
		tMemRead = MemRead.read(); tMemWrite = MemWrite.read(); tIRWrite = IRWrite.read();
		tRegDst = RegDst.read(); tMemtoReg = MemtoReg.read(); tRegWrite = RegWrite.read();
		tSrcA = SrcA.read(); tSrcB = SrcB.read(); tPCSrc = PCSrc.read();
		tULAOp = ULAOp.read();
		top = op.read();
		timmediate = immediate.read();
		end_time[i] = sc_time_stamp();
		total_cycles += (end_time[i] - start_time[i]) / clock_period;

		wait();

		cout << i << ":\t" << static_cast<sc_int<32>>(tsaidaUlaDireta).to_int() << " " << static_cast<sc_int<32>>(tsaidaRegUlaDireta).to_int() << " " << static_cast<sc_int<32>>(memOut).to_int() << endl;
		cout << " :\t" << tPCwCond << tPCw << tIorD << tMemRead << tMemWrite << tIRWrite << tRegDst << tMemtoReg << tRegWrite << tSrcA << " " << tSrcB << " " << tPCSrc << " " << ULAOp << endl;
		//cout << " " << ":\t" << op << " " << immediate << " " << tIRWrite << endl;
	}
	cout << "-------------Formato--------------" << endl;
	cout << "i-ésimo clock: Saídas da Ula, do registrador da Ula e da memória "<< endl;
	cout << "Sinais de controle"<< endl << endl;

	//print latency
	//double total_throughput = (start_time[63] - start_time[0]) / clock_period;
	//cout << "Average latency is "<< (double)(total_cycles/64) << " cycles." << endl;
	//cout << "Average throughput is "<< (double)(total_throughput/63) << " cycles per input." << endl;

	// Terminar simulação
	sc_stop();
}
