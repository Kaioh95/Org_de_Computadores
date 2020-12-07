#include "RegIR.h"

void RegIR::mainProcess(){
	if(w.read()){
		Iop = Iin.read().range(31, 26);
		IaddressA = Iin.read().range(25, 21);
		IaddressB0 = Iin.read().range(20, 16);
		IaddressB1 = Iin.read().range(15, 11);
		Iimmediate = Iin.read().range(15, 0);
		Ipcmux = Iin.read().range(25, 0);
	}
	else if(reset.read()){
		Iop = 0;
		IaddressA = 0;
		IaddressB0 = 0;
		IaddressB1 = 0;
		Iimmediate = 0;
		Ipcmux = 0;
	}

}