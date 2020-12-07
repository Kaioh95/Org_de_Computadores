#include <systemc.h>

#define RIB_WIDTH 8	// largura do campo RIB no header 
#define XID 3		// coordenada x
#define YID 3		// coordenada y
/**
* @file routing_xy.cpp
* @details Implementação do algoritmo XY
* @author Kaio Henrique de Sousa
* @since 26/11/2020
*/

SC_MODULE(routing_xy){
	// Coorderadas do nó destino
	sc_in< sc_bv<RIB_WIDTH/2> > Xdest;
	sc_in< sc_bv<RIB_WIDTH/2> > Ydest;

	sc_in< bool > bop;	//bit que indica início de pacote
	sc_in< bool > rok;	//bit que indica que o FIFO não está vazio

	// Requests
	sc_out< bool > reqL;
	sc_out< bool > reqN;
	sc_out< bool > reqE;
	sc_out< bool > reqS;
	sc_out< bool > reqW;

	// as contantes a seguir definem códigos
	// para as possíveis requests. Só é permitido
	// fazer request de um canal (Lout, Nout, Eout, Wout), ou nenhum.
	const sc_bv<5> REQ_L = "10000";
	const sc_bv<5> REQ_N = "01000";
	const sc_bv<5> REQ_E = "00100";
	const sc_bv<5> REQ_S = "00010";
	const sc_bv<5> REQ_W = "00001";
	const sc_bv<5> REQ_NONE = "00000";

	// o seguinte sinal recebe o resultado do roteamento.
	sc_signal< sc_bv<5> > request;

	void p_req(){
		bool header_present;
		int X;
		int Y;

		header_present = bop.read() & rok.read();

		if(header_present){
			X = Xdest.read().to_int() - XID;
			Y = Ydest.read().to_int() - YID;
		
			if(X != 0){
				if(X > 0)
					request = REQ_E;
				else
					request = REQ_W;
			}
			else if(Y != 0){
				if(Y > 0)
					request = REQ_N;
				else
					request = REQ_S;
			}
			else{
				request = REQ_L;
			}
		}
		else{
			request = REQ_NONE;
		}
	}

	void outputs(){
		reqL = request.read()[4];
		reqN = request.read()[3];
		reqE = request.read()[2];
		reqS = request.read()[1];
		reqW = request.read()[0];
	}

	SC_CTOR(routing_xy){
		SC_METHOD(p_req);
		sensitive << bop << rok << Xdest << Ydest;
		SC_METHOD(outputs);
		sensitive << request;
	}

};