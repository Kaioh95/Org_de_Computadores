#include <systemc.h>

SC_MODULE(testB){
	sc_out< sc_bv<4> > sel;
	sc_out< sc_bv<4> > rdin;
	sc_in< bool > rdout;

	sc_in< bool > clk;

	void source(){
		sel.write(0);
		rdin.write(0);
		wait();

		sc_bv<4> tsel = 0;
		sc_bv<4> trdin = 0;

		for(int i = 0; i<32; i++){
			if(i>=4 && i<8){
				tsel = 0;
				tsel[i%4] = 1;
				trdin = "0101";
			}
			if(i>=20){
				tsel = 0;
				tsel[i%4] = 1;
				trdin = "0010";
			}

			sel.write(tsel);
			rdin.write(trdin);
			wait();
		}
	}

	void sink(){
		bool trdout;

		for(int i = 0; i<32; i++){
			trdout = rdout.read();
			wait();
			
			cout << i << ":\t" << trdout << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};