#include <systemc.h>
//#include "Xin.cpp"
#include "Fifo.cpp"
#include "testB.cpp"

SC_MODULE(TopLevel){
	testB *tb0;
	Fifo *ff0;

	//Sinais do Xin
	sc_signal< sc_bv<10> > dout;
	sc_signal< bool > rok;	//FIFO tem dado para ler (não vazio)
	sc_signal< bool > wok;

	//Sinais do teste Bench
	sc_signal< sc_bv<10> > din;
	sc_signal< bool > rd;	//Comando para ler do FIFO
	sc_signal< bool > wr;	//Comando para escrever do FIFO
	sc_signal< bool > rst;

	sc_clock clk_sig;

	SC_CTOR(TopLevel):clk_sig("clk_sig", 10, SC_NS){

		tb0 = new testB("tb0");
		tb0->din(din);
		tb0->rd(rd);
		tb0->wr(wr);
		tb0->rst(rst);
		tb0->dout(dout);
		tb0->rok(rok);
		tb0->wok(wok);		

		tb0->clk(clk_sig);

		ff0 = new Fifo("ff0");
		ff0->din(din);
		ff0->rd(rd);
		ff0->wr(wr);
		ff0->rst(rst);
		ff0->dout(dout);
		ff0->rok(rok);
		ff0->wok(wok);			

		ff0->clk(clk_sig);
	}

	~TopLevel(){
		delete tb0;
		delete ff0;
	}
};

TopLevel *tp0 = NULL;
int sc_main(int argc, char* argv[]){
	tp0 = new TopLevel("tp0");
	sc_start();

	return 0;
}