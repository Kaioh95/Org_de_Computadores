#include <systemc.h>

SC_MODULE(testB){
	sc_out< int > MODULE_ID;
	sc_out< bool > rst;
	// coordenadas do nó destino
	sc_out< sc_bv<8/2> > Xdest;
	sc_out< sc_bv<8/2> > Ydest;
	// FIFO interface
	sc_out< bool > rok;
	sc_out< bool > rd;
	sc_out< bool > bop;
	sc_out< bool > eop;
	// requests
	sc_out< bool > Lidle;
	sc_out< bool > Nidle;
	sc_out< bool > Eidle;
	sc_out< bool > Sidle;
	sc_out< bool > Widle;
	// requests
	sc_in< bool > reqL;
	sc_in< bool > reqN;
	sc_in< bool > reqE;
	sc_in< bool > reqS;
	sc_in< bool > reqW;

	sc_in< bool > clk;

	void source(){
		MODULE_ID.write(0);
		rst.write(1);
		Xdest.write(0);
		Ydest.write(0);
		rok.write(0);
		rd.write(0);
		bop.write(0);
		eop.write(0);
		Lidle.write(0);
		Nidle.write(0);
		Eidle.write(0);
		Sidle.write(0);
		Widle.write(0);
		wait();

		int tMODULE_ID;
		bool trst = 0;
		sc_bv<4> tXdest = 0;
		sc_bv<4> tYdest = 0;
		bool trok = 0;
		bool trd = 0;
		bool tbop = 0;
		bool teop = 0;
		bool tLidle = 0;
		bool tNidle = 0;
		bool tEidle = 0;
		bool tSidle = 0;
		bool tWidle = 0;

		for(int i = 0; i<32; i++){
			if(i>=4 && i<15){
				tMODULE_ID = 0;
				trst = 0;
				tXdest = 2;
				tYdest = 4;
				trok = 1;
				trd = 1;
				tbop = 1;
				teop = 0;
				tLidle = 0;
				tNidle = 0;
				tEidle = 0;
				tSidle = 0;
				tWidle = 0;
			}
			else if(i>=15 && i<22){
				tMODULE_ID = 0;
				trst = 0;
				tXdest = 2;
				tYdest = 4;
				trok = 1;
				trd = 1;
				tbop = 0;
				teop = 0;
				tLidle = 0;
				tNidle = 0;
				tEidle = 0;
				tSidle = 0;
				tWidle = 0;
			}
			else if(i>=22 && i<26){
				tMODULE_ID = 0;
				trst = 0;
				tXdest = 2;
				tYdest = 4;
				trok = 1;
				trd = 1;
				tbop = 0;
				teop = 1;
				tLidle = 0;
				tNidle = 0;
				tEidle = 0;
				tSidle = 0;
				tWidle = 0;
			}
			else if(i>=26){
				tMODULE_ID = 0;
				trst = 0;
				tXdest = 2;
				tYdest = 4;
				trok = 1;
				trd = 1;
				tbop = 1;
				teop = 0;
				tLidle = 0;
				tNidle = 0;
				tEidle = 0;
				tSidle = 0;
				tWidle = 0;
			}

			MODULE_ID.write(tMODULE_ID);
			rst.write(trst);
			Xdest.write(tXdest);
			Ydest.write(tYdest);
			rok.write(trok);
			rd.write(trd);
			bop.write(tbop);
			eop.write(teop);
			Lidle.write(tLidle);
			Nidle.write(tNidle);
			Eidle.write(tEidle);
			Sidle.write(tSidle);
			Widle.write(tWidle);
			wait();
		}
	}

	void sink(){
		bool treqL; //Loopback
		bool treqN;
		bool treqE;
		bool treqS;
		bool treqW;

		for(int i = 0; i<32; i++){

			treqL = reqL.read();
			treqN = reqN.read();
			treqE = reqE.read();
			treqS = reqS.read();
			treqW = reqW.read();
			wait();
			
			cout << i << ":\t" << treqL << treqN << treqE << treqS << treqW << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};