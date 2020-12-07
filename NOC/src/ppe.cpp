#include <systemc.h>

#define N 4
/**
* @file ppe.cpp
* @details Codifiador de prioridade que recebe um conjunto de request
* e prioridades, e baseado nas prioridades atuais reserva um dos pedidos
* pendentes dando a ele uma concesão. Composto por N árbitros. Este módulo
* inclui um registrador que guarda o último request concedido até que o request
* conceido retorne 0. Uma nova concessão só pode ser dada após o árbitro retornar
* ao estado ocioso.
* @author Kaio Henrique de Sousa
* @since 02/12/2020
*/

SC_MODULE(ppe){
	sc_in< bool > clk, rst;
	sc_in< sc_bv<N> > R;	// Requests
	sc_in< sc_bv<N> > P;	// Prioridades
	sc_out< sc_bv<N> > G;	// Concessões
	sc_out< bool > idle;	// Status

	sc_bv<N> Imed_in;		// Uma das células anteriores concedeu um request
	sc_bv<N> Imed_out;		// Concessão dada
	sc_bv<N> Grant;			// Sinais de concessão
	sc_bv<N> Grant_reg;		// Sinais de concessão registrados
	sc_signal< sc_bv<N> > sGrant_reg;
	bool s_idle;			// Sinais para outputs ociosas
	sc_signal< bool > sidle;

	void arb_cells(){
		for(int i = N-1; i>=0; i--){
			// Status da célula de arbitragem anterior
			Imed_in[i] = Imed_out[(i-1) % N];
			// Sinal de concessão envido para o bloco de request
			Grant[i] = R.read()[i] & (!(Imed_in[i] & (!P.read()[i])));
			// Status da próxima célula de arbitragem
			Imed_out[i] = R.read()[i] | (Imed_in[i] & (!P.read()[i]));
		}
	}

	void reg_grant(){
		for(int i = N-1; i>=0; i--){
			if(rst.read())
				Grant_reg[i] = 0;
			else if(clk.event()){
				// Um bit do registrador pode ser autalizado quando o árbitro está ocioso
				// ou quando não há request, especialmente quando uma request concedida é resetada.
				if(s_idle == 1)
					Grant_reg[i] = Grant[i];
				else if(!R.read()[i])
					Grant_reg[i] = 0;
			}
		}
		sGrant_reg = Grant_reg;
	}

	void iidle(){
		bool tmp = 0;

		for(int i = N-1; i>=0; i--){
			tmp = tmp | Grant_reg[i];
		}
		s_idle = not tmp;
		sidle = s_idle;
	}

	void outputs(){
		idle.write(sidle);
		G.write(sGrant_reg);
	}

	SC_CTOR(ppe){
		SC_METHOD(arb_cells);
		sensitive << R << P;

		SC_METHOD(reg_grant);
		sensitive << clk.pos() << rst;

		SC_METHOD(iidle);
		sensitive << sGrant_reg;

		SC_METHOD(outputs);
		sensitive << sGrant_reg << sidle;
	}

};