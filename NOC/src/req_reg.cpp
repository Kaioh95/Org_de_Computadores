#include <systemc.h>

#define MODULE_ID "L"	//identificador da porta no roteador
#define ROUTING_TYPE "XY"
/**
* @file req_reg.cpp
* @details registrador que guarda o request depois que
* a função roteamento selecionar um canal output para ser
* usado por um pacote de entrada.
* Um request é guardada até que o pacote seja entegue.
* @author Kaio Henrique de Sousa
* @since 26/11/2020
*/

SC_MODULE(req_reg){
	sc_in< bool > clk, rst;

	// FIFO interface
	sc_in< bool > rok;
	sc_in< bool > rd;

	sc_in< bool > bop;	// bit que indica início de pacote
	sc_in< bool > eop;	// bit que indica fim de pacote

	// requests
	sc_in< bool > in_reqL; //Loopback
	sc_in< bool > in_reqN;
	sc_in< bool > in_reqE;
	sc_in< bool > in_reqS;
	sc_in< bool > in_reqW;
	sc_out< bool > out_reqL; //Loopback
	sc_out< bool > out_reqN;
	sc_out< bool > out_reqE;
	sc_out< bool > out_reqS;
	sc_out< bool > out_reqW;

//---------------variáveis internas---------------
	sc_signal< bool > reqL;
	sc_signal< bool > reqN;
	sc_signal< bool > reqE;
	sc_signal< bool > reqS;
	sc_signal< bool > reqW;
	sc_signal< bool > requesting;	//Quando há alguém fazendo request

	// Determina se há requests
	void rqting(){
		requesting = reqL.read() | reqN.read() | reqE.read() | reqS.read() | reqW.read();
	}

	// o seguinte processo implementa o registrador que determina um request
	void m_process(){
		if(rst.read()){
			reqL = 0;
			reqN = 0;
			reqE = 0;
			reqS = 0;
			reqW = 0;
		}
		else if(clk.event()){
			// se não há request e um cabeçalho é presente,
			// um novo request, determinado pela função de roteamento,
			// é registrado.
			if(rok.read() & bop.read() & !requesting.read()){
				// não é registrado pelo módulo L
				if(MODULE_ID == "L")
					reqL = 0;
				else
					reqL = in_reqL.read();
				// não é registrado pelo módulo N
				if(MODULE_ID == "N")
					reqN = 0;
				else
					reqN = in_reqN.read();
				// não é registrado pelo módulo E, N e S.
				if(MODULE_ID == "E")
					reqE = 0;
				else{
					if(ROUTING_TYPE == "XY"){
						if(MODULE_ID == "N" or MODULE_ID == "S")
							reqE = 0;
						else
							reqE = in_reqE;
					}
					else
						reqE = in_reqE;
				}
				// não é registrado pelo módulo S.
				if(MODULE_ID == "S")
					reqS = 0;
				else
					reqS = in_reqS.read();
				// não é registrado pelo módulo W, N e S.
				if(MODULE_ID == "W")
					reqW = 0;
				else{
					if(ROUTING_TYPE == "XY"){
						if(MODULE_ID == "N" or MODULE_ID == "S")
							reqW = 0;
						else
							reqW = in_reqW;
					}
					else
						reqW = in_reqW;
				}

			}

			// se um trailer está presente e está sendo lido pelo receptor
			// o registrador de request é resetado
			else if(rok.read() & eop.read() & rd.read()){
				reqL = 0;
				reqN = 0;
				reqE = 0;
				reqS = 0;
				reqW = 0;
			}
		}
	}

	void outputs(){
		out_reqL = reqL;
		out_reqN = reqN;
		out_reqE = reqE;
		out_reqS = reqS;
		out_reqW = reqW;
	}

	SC_CTOR(req_reg){
		SC_METHOD(rqting);
		sensitive << reqL << reqN << reqE << reqS << reqW;
	
		SC_METHOD(m_process);
		sensitive << clk.pos() << rst << rok << rd << eop << requesting;
	
		SC_METHOD(outputs);
		sensitive << reqL << reqN << reqE << reqS << reqW;
	}

};