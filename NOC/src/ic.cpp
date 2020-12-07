#include <systemc.h>
#include "req_reg.cpp"
#include "routing_xy.cpp"

#define XID 3
#define YID 3
#define MODULE_ID "L"
#define RIB_WIDTH 8
#define ROUTING_TYPE "XY"
#define WF_TYPE "Y_BEFORE_E"

/**
* @file ic.cpp
* @details Controle responsável por detectar
* o cabeçalho de pacote de entrada, reserva um
* canal de output para ser requisitado, liberando
* apenas quando o pacote for entregue.
* @author Kaio Henrique de Sousa
* @since 27/11/2020
*/

SC_MODULE(ic){
	sc_in< bool > clk, rst;

	// coordenadas do nó destino
	sc_in< sc_bv<RIB_WIDTH/2> > Xdest;
	sc_in< sc_bv<RIB_WIDTH/2> > Ydest;

	// FIFO interface
	sc_in< bool > rok;
	sc_in< bool > rd;

	sc_in< bool > bop;	// bit que indica início de pacote
	sc_in< bool > eop;	// bit que indica fim de pacote

	// Status dos canais de saída
	sc_in< bool > Lidle; //Lout está ocioso
	sc_in< bool > Nidle;
	sc_in< bool > Eidle;
	sc_in< bool > Sidle;
	sc_in< bool > Widle;

	// requests
	sc_out< bool > reqL; //Loopback
	sc_out< bool > reqN;
	sc_out< bool > reqE;
	sc_out< bool > reqS;
	sc_out< bool > reqW;

//------------Variáveis Internas-----------------
	sc_signal< bool > s_reqL;
	sc_signal< bool > s_reqN;
	sc_signal< bool > s_reqE;
	sc_signal< bool > s_reqS;
	sc_signal< bool > s_reqW;

	routing_xy *r_xy;
	req_reg *req_r;

	SC_CTOR(ic){
		r_xy = new routing_xy("r_xy");
		r_xy->Xdest(Xdest);
		r_xy->Ydest(Ydest);
		r_xy->bop(bop);
		r_xy->rok(rok);
		r_xy->reqL(s_reqL);
		r_xy->reqN(s_reqN);
		r_xy->reqE(s_reqE);
		r_xy->reqS(s_reqS);
		r_xy->reqW(s_reqW);

		req_r = new req_reg("req_r");
		req_r->clk(clk);
		req_r->rst(rst);
		req_r->rok(rok);
		req_r->rd(rd);
		req_r->bop(bop);
		req_r->eop(eop);
		req_r->in_reqL(s_reqL);
		req_r->in_reqN(s_reqN);
		req_r->in_reqE(s_reqE);
		req_r->in_reqS(s_reqS);
		req_r->in_reqW(s_reqW);
		req_r->out_reqL(reqL);
		req_r->out_reqN(reqN);
		req_r->out_reqE(reqE);
		req_r->out_reqS(reqS);
		req_r->out_reqW(reqW);

	}

	~ic(){
		delete r_xy;
		delete req_r;
	}

};