#include <systemc.h>

SC_MODULE(testB){
	sc_out< bool > rst;
	sc_out< sc_bv<4> > R;
	sc_in< sc_bv<4> > G;
	sc_in< bool > idle;

	sc_in< bool > clk;

	void source(){
		rst.write(1);
		R.write(0);
		wait();

		bool trst = 0;
		sc_bv<4> tR = 0;

		for(int i = 0; i<32; i++){
			if(i>=4 && i<6){
				trst = 0;
				tR = "0001";
			}
			if(i>=8 && i<10){
				trst = 0;
				tR = "0010";
			}
			if(i>=12 && i<14){
				trst = 0;
				tR = "0100";
			}
			if(i>=16 && i<18){
				trst = 0;
				tR = "1011";
			}
			if(i>=20 && i<23){
				trst = 0;
				tR = "1011";
			}
			if(i>=25 && i<27){
				trst = 0;
				tR = "1011";
			}

			rst.write(trst);
			R.write(tR);
			wait();
		}
	}

	void sink(){
		bool tidle;
		sc_bv<4> tG;

		for(int i = 0; i<32; i++){
			tidle = idle.read();
			tG = G.read();
			wait();
			
			cout << i << ":\t" << tG << " " << tidle << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};