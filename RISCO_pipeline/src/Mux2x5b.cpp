#include "Mux2x5b.h"

void Mux2x5b::mux2Process(){
	if(x2Sel.read())
		outData = data1;
	else
		outData = data0;
}