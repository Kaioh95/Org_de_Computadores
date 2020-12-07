#include "Reg.h"

void Reg::mainProcess(){
	if(reset.read())
		Dout = 0;
	else
		Dout = Din;
}