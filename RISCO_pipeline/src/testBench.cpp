#include "testBench.h"

// Top Level teste
void testBench::source(){
	reset.write(1);
	valid.write(0);
	wait();

	// Lendo dados de arquivo externo e escrevendo na memória de instruções
	string Ilinha1, Ilinha2;

	IinDataFile.open("IinDataFile.txt");
	if(!IinDataFile.is_open()){
		cout << "Falha ao abrir arquivo" << endl;
		return;
	}

	bool tImemWDireto;
	sc_bv<32> tIaddressDireto, tIdataDireto;

	while(getline(IinDataFile, Ilinha1) and getline(IinDataFile, Ilinha2)){
		tIaddressDireto = Ilinha1.c_str();
		tIdataDireto = Ilinha2.c_str();
		tImemWDireto = true;

		IaddressDireto.write(tIaddressDireto);
		IdataDireto.write(tIdataDireto);
		ImemWDireto.write(tImemWDireto);
		wait();
	}
	IinDataFile.close();
	//*********************************************************************

	// Lendo dados de arquivo externo e escrevendo na memória de dados
	string Dlinha1, Dlinha2;

	DinDataFile.open("DinDataFile.txt");
	if(!DinDataFile.is_open()){
		cout << "Falha ao abrir arquivo" << endl;
		return;
	}

	bool tDmemWDireto;
	sc_bv<32> tDaddressDireto, tDdataDireto;

	while(getline(DinDataFile, Dlinha1) and getline(DinDataFile, Dlinha2)){
		tDaddressDireto = Dlinha1.c_str();
		tDdataDireto = Dlinha2.c_str();
		tDmemWDireto = true;

		DaddressDireto.write(tDaddressDireto);
		DdataDireto.write(tDdataDireto);
		DmemWDireto.write(tDmemWDireto);
		wait();
	}
	DinDataFile.close();
	//*********************************************************************

	//Executando o que foi escrito na Mem de instruções
	IaddressDireto.write(0);
	IdataDireto.write(0);
	ImemWDireto.write(0);

	DaddressDireto.write(0);
	DdataDireto.write(0);
	DmemWDireto.write(0);

	bool treset = true;
	bool tvalid = false;

	for(int i = 0; i<64; i++){

		//if(i>=4){
			tvalid = true;
			treset = false;

			tIaddressDireto = Dout_sig.read();
			tIdataDireto = 0;
			tImemWDireto = 0;

			tDaddressDireto = ulaResultO_sig.read();
			tDdataDireto = dataBO_sig1.read();
			tDmemWDireto = M1O_sig1.read();

		//}

		IaddressDireto.write(tIaddressDireto);
		IdataDireto.write(tIdataDireto);
		ImemWDireto.write(tImemWDireto);

		DaddressDireto.write(tDaddressDireto);
		DdataDireto.write(tDdataDireto);
		DmemWDireto.write(tDmemWDireto);

		reset.write(treset);
		valid.write(tvalid);
		start_time[i] = sc_time_stamp();
		wait();
	}
}

void testBench::sink(){
	// Sinais para testes
	sc_int<32> tdatawBReg, tendBReg, tendJump, tin0mux, tentradaA, tentradaB;
	bool twbRegs, tsaidaAnd, tselMux, twwb0, twwb1;
	
	// Sinais de controle
	bool tWB0, tWB1, tEX0, tEX1, tM0, tM1, tM2;
	sc_bv<3> tulaOp;
	sc_int<32> tulaResultO_sig, tDout_sig;
	
	// Sinais de saída do buffer IF/ID
	sc_bv<6> tIop;
	sc_bv<5> tIaddressA, tIaddressB0, tIaddressB1;
	sc_bv<16> tIimmediate;
	sc_bv<32> tjAddressOut;

	//Extract clock period
	sc_clock *clk_p = DCAST<sc_clock*>(clk.get_interface());
	clock_period = clk_p->period();

	double total_cycles = 0;

	for(int i = 0; i<64; i++){
		// Testes
		tselMux = selMux.read(), twwb0 = wwb0.read(), twwb0 = wwb0.read();
		tentradaA = static_cast<sc_int<32>>(entradaA.read());
		tentradaB = static_cast<sc_int<32>>(entradaB.read());
		tin0mux = static_cast<sc_int<32>>(in0mux.read());
		tdatawBReg = static_cast<sc_int<32>>(datawBReg.read());
		tendBReg = static_cast<sc_int<32>>(endBReg.read());
		tendJump = static_cast<sc_int<32>>(endJump.read());
		twbRegs = wbRegs.read(); tsaidaAnd = saidaAnd.read();

		// Controle
		tulaResultO_sig = static_cast<sc_int<32>>(ulaResultO_sig.read());
		tDout_sig = static_cast<sc_uint<32>>(Dout_sig.read());
		tWB0 = WB0.read(); tWB1 = WB1.read(); tEX0 = EX0.read(); tEX1 = EX1.read(); tM0 = M0.read(); tM1 = M1.read(); tM2 = M2.read();
		
		// Buffer Out
		tulaOp = ulaOp.read();
		tIop = Iop.read(); tIaddressA = IaddressA.read(); tIaddressB0 = IaddressB0.read();
		tIaddressB1 = IaddressB1.read(); tIimmediate = Iimmediate.read();

		end_time[i] = sc_time_stamp();
		total_cycles += (end_time[i] - start_time[i]) / clock_period;
		wait();

		cout << i << ":\t" << tDout_sig << " " << static_cast<sc_int<32>>(ulaResultO_sig) << endl;
		cout << " \t" << tWB0 << tWB1 << " " << tM0 << tM1 << tM2 << " " << tEX0 << tEX1 << " " << tulaOp << endl;
		cout << " \t" << wwb0 << wwb1 << " " << tentradaA << " " << tentradaB << endl;
		cout << " \t" << tsaidaAnd << " " << tendJump << " " << wbRegs << " " << tendBReg << " " << tdatawBReg << " " << selMux << " " << tin0mux << endl;
		cout << " \t" << tIop << " " << tIaddressA << " " << tIaddressB0 << " " << tIaddressB1 << " "  << tIimmediate << endl;
	}
	cout << "-------------Formato--------------" << endl;
	//cout << "i-ésimo clock: Saídas da Ula, do registrado da Ula e da memória "<< endl;WB0O_sig1

	//print latency
	//double total_throughput = (start_time[63] - start_time[0]) / clock_period;
	//cout << "Average latency is "<< (double)(total_cycles/64) << " cycles." << endl;
	//cout << "Average throughput is "<< (double)(total_throughput/63) << " cycles per input." << endl;

	// Terminar simulação
	sc_stop();
}
