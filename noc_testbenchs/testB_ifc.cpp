#include <systemc.h>

SC_MODULE(testB){
	sc_out< bool > rst;
	sc_out< bool > val;
	sc_in< bool > ret;
	sc_in< bool > wr;
	sc_out< bool > wok;
	sc_out< bool > rd;
	sc_out< bool > rok;

	sc_in< bool > clk;

	void source(){
		rst.write(1);
		val.write(0);
		wok.write(0);
		rd.write(0);
		rok.write(0);
		wait();

		bool trst = 0;
		bool tval = 0;
		bool twok = 0;
		bool trd = 0;
		bool trok = 0;

		for(int i = 0; i<32; i++){
			if(i>=4 && i<6){
				trst = 0;
				tval = 1;
				twok = 0;
				trd = 0;
				trok = 0;
			}
			if(i>=8 && i<10){
				trst = 0;
				tval = 1;
				twok = 1;
				trd = 0;
				trok = 0;
			}
			if(i>=12 && i<14){
				trst = 0;
				tval = 0;
				twok = 0;
				trd = 0;
				trok = 0;
			}
			if(i>=16 && i<18){
				trst = 0;
				tval = 1;
				twok = 0;
				trd = 0;
				trok = 0;
			}
			if(i>=20 && i<23){
				trst = 0;
				tval = 1;
				twok = 1;
				trd = 0;
				trok = 0;
			}
			if(i>=25 && i<27){
				trst = 0;
				tval = 1;
				twok = 1;
				trd = 0;
				trok = 0;
			}

			rst.write(trst);
			val.write(tval);
			wok.write(twok);
			rd.write(trd);
			rok.write(trok);
			wait();
		}
	}

	void sink(){
		bool tret;
		bool twr;

		for(int i = 0; i<32; i++){
			tret = ret.read();
			twr = wr.read();
			wait();
			
			cout << i << ":\t" << twr << " " << tret << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};