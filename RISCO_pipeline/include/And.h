#ifndef AND_H
#define AND_H

#include <systemc.h>

/**
* @file And.h
* @brief Componente Lógico para determinar escrita no contador de programa
* @author Kaio Henrique de Sousa
* @since 13/11/2020
*/

SC_MODULE(And){
	sc_in< bool > e1, e2;
	sc_out< bool > result;

	void and_orProcess();

	SC_CTOR(And){
		SC_METHOD(and_orProcess);
		sensitive << e1 << e2;
	}
};

#endif