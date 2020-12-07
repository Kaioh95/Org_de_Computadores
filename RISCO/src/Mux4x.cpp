#include "Mux4x.h"

void Mux4x::mux4Process(){
	if(x4Sel.read() == "00")
		outData = data0;
	else if(x4Sel.read() == "01")
		outData = data1;
	else
		outData = data2;
}