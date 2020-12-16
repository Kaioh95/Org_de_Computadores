#include <systemc.h>

SC_MODULE(testB){
	sc_out< bool > rst;
	sc_in< bool > val;
	sc_out< bool > ret;
	sc_in< bool > rd;
	sc_out< bool > rok;

	sc_in< bool > clk;

	void source(){
		rst.write(1);
		ret.write(0);
		rok.write(0);
		wait();

		bool trst = 0;
		bool tret = 0;
		bool trok = 0;

		for(int i = 0; i<32; i++){
			if(i>=4 && i<6){
				trst = 0;
				tret = 0;
				trok = 0;
			}
			else if(i>=8 && i<10){
				trst = 0;
				tret = 0;
				trok = 1;
			}
			else if(i>=12 && i<14){
				trst = 0;
				tret = 1;
				trok = 1;
			}
			else if(i>=16 && i<18){
				trst = 0;
				tret = 0;
				trok = 1;
			}
			else if(i>=20 && i<23){
				trst = 0;
				tret = 0;
				trok = 1;
			}
			else if(i>=25 && i<27){
				trst = 0;
				tret = 0;
				trok = 1;
			}

			rst.write(trst);
			ret.write(tret);
			rok.write(trok);
			wait();
		}
	}

	void sink(){
		bool tval;
		bool trd;

		for(int i = 0; i<32; i++){
			tval = val.read();
			trd = rd.read();
			wait();
			
			cout << i << ":\t" << tval << " " << trd << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};