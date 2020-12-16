#include <systemc.h>
#include "ofc.cpp"
#include "ows.cpp"
#include "ods.cpp"
#include "oc.cpp"
#include "Fifoo.cpp"

#define USE_THIS 1
#define DATA_WIDTH 8
#define FC_TYPE "HANDSHAKE"
#define FC_CREDIT 4 
#define FIFO_TYPE "SHIFT"
#define FIFO_DEPTH 4
#define FIFO_LOG2_DEPTH 4
#define ARBITER_TYPE "ROUND_ROBIN"
#define SWITCH_TYPE "LOGIC"

/**
* @file Xout.cpp
* @details Módulo do canal de output
* @author Kaio Henrique de Sousa
* @since 03/12/2020
*/

SC_MODULE(Xout){
	sc_in< bool > clk, rst;
	// Sinais do link
	sc_out< sc_bv<DATA_WIDTH+2> > out_data;	// Canal de output
	sc_out< bool > out_val;					// Validação de dados
	sc_in< bool > out_ret;					//ack
	// Sinais de interconexão dos canais de input e output
	sc_in< sc_bv<4> > x_req;	// Request dos inputs
	sc_in< sc_bv<4> > x_rok;	// rok dos inputs
	sc_out< bool > x_rd;		// read
	sc_out< sc_bv<4> > x_gnt;	// Concessão dos inputs
	sc_out< bool > x_idle;		
	// Dados dos 4 canais de input
	sc_in< sc_bv<DATA_WIDTH+2> > x_din0;
	sc_in< sc_bv<DATA_WIDTH+2> > x_din1;
	sc_in< sc_bv<DATA_WIDTH+2> > x_din2;
	sc_in< sc_bv<DATA_WIDTH+2> > x_din3;

	sc_signal< sc_bv<4> > gnt;
	sc_signal< bool > val;
	sc_signal< bool > ret;
	sc_signal< bool > rd;
	sc_signal< bool > rok;
	sc_signal< bool > idle;
	sc_signal< sc_bv<DATA_WIDTH+2> > din;
	sc_signal< sc_bv<DATA_WIDTH+2> > dout;
	sc_signal< bool > wr;
	sc_signal< bool > wok;

	oc *oc0;
	ods *ods0;
	ows *ows0;
	Fifoo *ff0;
	ofc *ofc0;

	void outputs(){
		out_data.write(din);
		x_rd.write(wok);
		x_gnt.write(gnt);
		x_idle.write(idle);
	}

	SC_CTOR(Xout){
		oc0 = new oc("oc0");
		oc0->rst(rst);
		oc0->R(x_req);
		oc0->G(gnt);
		oc0->idle(idle);
		oc0->clk(clk);

		ods0 = new ods("ods0");
		ods0->sel(gnt);
		ods0->din0(x_din0);
		ods0->din1(x_din1);
		ods0->din2(x_din2);
		ods0->din3(x_din3);
		ods0->dout(din);

		ows0 = new ows("ows0");
		ows0->sel(gnt);
		ows0->wrin(x_rok);
		ows0->wrout(wr);

		ff0 = new Fifoo("ff0");
		ff0->rst(rst);
		ff0->wr(wr);
		ff0->rd(rd);
		ff0->din(din);
		ff0->dout(dout);
		ff0->wok(wok);
		ff0->rok(rok);
		ff0->clk(clk);

		ofc0 = new ofc("ofc0");
		ofc0->rst(rst);
		ofc0->val(out_val);
		ofc0->ret(out_ret);
		ofc0->rd(rd);
		ofc0->rok(rok);
		ofc0->clk(clk);

		SC_METHOD(outputs);
		sensitive << dout << wok << gnt << idle;
	}

	~Xout(){
		delete oc0;
		delete ods0;
		delete ows0;
		delete ff0;
		delete ofc0;
	}

};
