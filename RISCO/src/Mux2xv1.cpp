#include "Mux2xv1.h"

void Mux2xv1::mux2Process(){
	if(x2Sel.read())
		outData = data1;
	else
		outData = data0;
}