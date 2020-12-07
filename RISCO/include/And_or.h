#ifndef AND_OR_H
#define AND_OR_H

#include <systemc.h>

/**
* @file And_or.h
* @brief Componente Lógico para determinar escrita no contador de programa
* @author Kaio Henrique de Sousa
* @since 03/11/2020
*/

SC_MODULE(And_or){
	sc_in< bool > pcwc, zero, pcw;
	sc_out< bool > condResult;

	void and_orProcess();

	SC_CTOR(And_or){
		SC_METHOD(and_orProcess);
		sensitive << pcwc << zero << pcw;
	}
};

#endif