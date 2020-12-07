#include "RegNeg.h"

void RegNeg::mainProcess(){
	if(reset.read())
		Dout = 0;
	else
		Dout = Din;
}