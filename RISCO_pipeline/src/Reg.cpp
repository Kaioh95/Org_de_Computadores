#include "Reg.h"

void Reg::mainProcess(){
	if(valid.read())
		Dout = Din;
	if(reset.read())
		Dout = 0;
}