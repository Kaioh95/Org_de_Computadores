#include <systemc.h>

SC_MODULE(testB){
	sc_out< sc_bv<8> > din;
	sc_out< bool > rd;	//Comando para ler do FIFO
	sc_out< bool > wr;	//Comando para escrever do FIFO
	sc_out< bool > rst;

	sc_in< sc_bv<8> > dout;
	sc_in< bool > rok;	//FIFO tem dado para ler (não vazio)
	sc_in< bool > wok;

	sc_in< bool > clk;

	void source(){
		rst.write(1);
		rd.write(0);
		wr.write(0);
		din.write(0);
		wait();

		bool trst = false;
		bool trd = false;
		bool twr = false;
		sc_bv<8> tdin = 0;

		for(int i = 0; i<32; i++){
			if(i>=4 && i<15){
				trst = 0;
				trd = 0;
				twr = 1;
				tdin = static_cast<sc_bv<8>>(71+i);
			}
			else if(i>=15 && i<22){
				trst = 0;
				trd = 1;
				twr = 0;
				tdin = static_cast<sc_bv<8>>(42);
			}
			else if(i>=22 && i<26){
				trst = 0;
				trd = 0;
				twr = 1;
				tdin = static_cast<sc_bv<8>>(42+i);
			}
			else if(i>=26){
				trst = 0;
				trd = 1;
				twr = 0;
				tdin = static_cast<sc_bv<8>>(42+i);
			}

			rst.write(trst);
			rd.write(trd);
			wr.write(twr);
			din.write(tdin);
			wait();
		}
	}

	void sink(){
		sc_bv<8> tdout;
		bool trok;
		bool twok;

		for(int i = 0; i<32; i++){
			tdout = dout.read();
			trok = rok.read();
			twok = wok.read();
			wait();
			
			cout << i << ":\t" << trok << " " << twok << " " << static_cast<sc_uint<8>>(tdout) << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};