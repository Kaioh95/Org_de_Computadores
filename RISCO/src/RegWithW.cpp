#include "RegWithW.h"

void RegWithW::mainProcess(){
	if(w.read())
		Iout = Iin;
	else if(reset.read())
		Iout = 0;
}