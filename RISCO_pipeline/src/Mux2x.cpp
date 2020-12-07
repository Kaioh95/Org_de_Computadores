#include "Mux2x.h"

void Mux2x::mux2Process(){
	if(x2Sel.read())
		outData = data1;
	else
		outData = data0;
}