#include "systemc.h"
#include "ifc.cpp"
#include "irs.cpp"
#include "ic.cpp"
#include "Fifo.cpp"
#include "dout_slice.cpp"

#define XID 2
#define YID 2
#define USE_THIS 1
//#define MODULE_ID "L"
#define DATA_WIDTH 8
#define RIB_WIDTH 8
#define ROUTING_TYPE "XY"
#define FC_TYPE "HANDSHAKE"
#define FIFO_TYPE "SHIFT"
#define FIFO_DEPTH 4
#define FIFO_LOG2_DEPTH 2
#define SWITCH_TYPE "LOGIC"

/**
* @file Xin.cpp
* @details Modulo do canal de input
* @author Kaio Henrique de Sousa
* @since 30/11/2020
*/

SC_MODULE(Xin){
	sc_in< int > MODULE_ID;
	sc_in< bool > clk, rst;
	sc_in< sc_bv<DATA_WIDTH+2> > in_data;
	sc_in< bool > in_val;
	sc_out< bool > in_ret;	//ack

	// comandos e sinais de status interconectando os canais de entrada e saída
	sc_out< bool > x_reqL;
	sc_out< bool > x_reqN;
	sc_out< bool > x_reqE;
	sc_out< bool > x_reqS;
	sc_out< bool > x_reqW;
	sc_out< bool > x_rok;

	sc_in< sc_bv<4> > x_rd;		// comando rd
	sc_in< sc_bv<4> > x_gnt;	// permissão para outputs

	// Status dos canais
	sc_in< bool > x_Lidle;
	sc_in< bool > x_Nidle;
	sc_in< bool > x_Eidle;
	sc_in< bool > x_Sidle;
	sc_in< bool > x_Widle;

	sc_out< sc_bv<DATA_WIDTH+2> > x_dout;

	// Sinais para conexões
	sc_signal< bool > wr;
	sc_signal< bool > wok;
	sc_signal< bool > rd;
	sc_signal< bool > rok;
	sc_signal< sc_bv<4> > sel;
	sc_signal< sc_bv<DATA_WIDTH+2> > dout;

	// Sinais do slice
	sc_signal< sc_bv<4> > sXdest, sYdest;
	sc_signal< bool > sbop, seop;

	ifc *ifc0;
	Fifo *fifo0;
	ic *ic0;
	irs *irs0;
	dout_slice *d_slice0;

	void outputs(){
		x_rok.write(rok);
		x_dout.write(dout);
	}

	SC_CTOR(Xin){
		ifc0 = new ifc("ifc0");
		ifc0->rst(rst);
		ifc0->val(in_val);
		ifc0->ret(in_ret);
		ifc0->wr(wr);
		ifc0->wok(wok);
		ifc0->rd(rd);
		ifc0->rok(rok);
		ifc0->clk(clk);

		fifo0 = new Fifo("fifo0");
		fifo0->rst(rst);
		fifo0->wok(wok);
		fifo0->rok(rok);
		fifo0->rd(rd);
		fifo0->wr(wr);
		fifo0->din(in_data);
		fifo0->dout(dout);
		fifo0->clk(clk);

		d_slice0 = new dout_slice("d_slice0");
		d_slice0->dout(dout);
		d_slice0->Xdest(sXdest);
		d_slice0->Ydest(sYdest);
		d_slice0->bop(sbop);
		d_slice0->eop(seop);

		ic0 = new ic("ic0");
		ic0->MODULE_ID(MODULE_ID);
		ic0->rst(rst);
		ic0->Xdest(sXdest);
		ic0->Ydest(sYdest);
		ic0->rok(rok);
		ic0->rd(rd);
		ic0->bop(sbop);
		ic0->eop(seop);
		ic0->Lidle(x_Lidle);
		ic0->Nidle(x_Nidle);
		ic0->Eidle(x_Eidle);
		ic0->Sidle(x_Sidle);
		ic0->Widle(x_Widle);
		ic0->reqL(x_reqL);
		ic0->reqN(x_reqN);
		ic0->reqE(x_reqE);
		ic0->reqS(x_reqS);
		ic0->reqW(x_reqW);
		ic0->clk(clk);

		irs0 = new irs("irs0");
		irs0->sel(x_gnt);
		irs0->rdin(x_rd);
		irs0->rdout(rd);

		SC_METHOD(outputs);
		sensitive << rok << dout;
	}

	~Xin(){
		delete ifc0;
		delete fifo0;
		delete ic0;
		delete irs0;
	}
};