#include <systemc.h>

SC_MODULE(testB){
	sc_out< sc_bv<4> > sel;
	sc_out< sc_bv<4> > wrin;
	sc_in< bool > wrout;

	sc_in< bool > clk;

	void source(){
		sel.write(0);
		wrin.write(0);
		wait();

		sc_bv<4> tsel;
		sc_bv<4> twrin;

		for(int i = 0; i<32; i++){
			if(i>=4 && i<6){
				tsel = "0000";
				twrin = "1010";
			}
			else if(i>=8 && i<10){
				tsel = "0001";
				twrin = "1010";
			}
			else if(i>=12 && i<14){
				tsel = "0010";
				twrin = "1010";
			}
			else if(i>=16 && i<18){
				tsel = "0100";
				twrin = "1010";
			}
			else if(i>=20 && i<22){
				tsel = "1000";
				twrin = "1010";
			}
			else if(i>=24 && i<26){
				tsel = "1111";
				twrin = "1010";
			}

			sel.write(tsel);
			wrin.write(twrin);
			wait();
		}
	}

	void sink(){
		bool twrout;

		for(int i = 0; i<32; i++){
			twrout = wrout.read();
			wait();
			
			cout << i << ":\t" << twrout << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};