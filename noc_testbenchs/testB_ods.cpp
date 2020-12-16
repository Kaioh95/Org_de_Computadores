#include <systemc.h>

SC_MODULE(testB){
	sc_out< sc_bv<4> > sel;
	sc_out< sc_bv<10> > din0;
	sc_out< sc_bv<10> > din1;
	sc_out< sc_bv<10> > din2;
	sc_out< sc_bv<10> > din3;
	sc_in< sc_bv<10> > dout;

	sc_in< bool > clk;

	void source(){
		sel.write(0);
		din0.write(0);
		din1.write(0);
		din2.write(0);
		din3.write(0);
		wait();

		sc_bv<4> tsel;
		sc_bv<10> tdin0;
		sc_bv<10> tdin1;
		sc_bv<10> tdin2;
		sc_bv<10> tdin3;

		for(int i = 0; i<32; i++){
			if(i>=4 && i<6){
				tsel = "0000";
				tdin0 = "0000011111";
				tdin1 = "1111100000";
				tdin2 = "1010101010";
				tdin3 = "0101010101";
			}
			else if(i>=8 && i<10){
				tsel = "0001";
				tdin0 = "0000011111";
				tdin1 = "1111100000";
				tdin2 = "1010101010";
				tdin3 = "0101010101";
			}
			else if(i>=12 && i<14){
				tsel = "0010";
				tdin0 = "0000011111";
				tdin1 = "1111100000";
				tdin2 = "1010101010";
				tdin3 = "0101010101";
			}
			else if(i>=16 && i<18){
				tsel = "0100";
				tdin0 = "0000011111";
				tdin1 = "1111100000";
				tdin2 = "1010101010";
				tdin3 = "0101010101";
			}
			else if(i>=20 && i<23){
				tsel = "1000";
				tdin0 = "0000011111";
				tdin1 = "1111100000";
				tdin2 = "1010101010";
				tdin3 = "0101010101";
			}
			else if(i>=25 && i<27){
				tsel = "1111";
				tdin0 = "0000011111";
				tdin1 = "1111100000";
				tdin2 = "1010101010";
				tdin3 = "0101010101";
			}

			sel.write(tsel);
			din0.write(tdin0);
			din1.write(tdin1);
			din2.write(tdin2);
			din3.write(tdin3);
			wait();
		}
	}

	void sink(){
		sc_bv<10> tdout;

		for(int i = 0; i<32; i++){
			tdout = dout.read();
			wait();
			
			cout << i << ":\t" << tdout << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};