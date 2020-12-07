#include "If_Id.h"

void If_Id::write(){
	if(valid.read()){
		tIop = Iin.read().range(31, 26);
		tIaddressA = Iin.read().range(25, 21);
		tIaddressB0 = Iin.read().range(20, 16);
		tIaddressB1 = Iin.read().range(15, 11);
		tIimmediate = Iin.read().range(15, 0);
		tjAddressOut = jAddressIn.read();
	}
	if(reset.read()){
		tIop = 0;
		tIaddressA = 0;
		tIaddressB0 = 0;
		tIaddressB1 = 0;
		tIimmediate = 0;
		tjAddressOut = 0;
	}
	tclk_out = clk.read();
}

void If_Id::read(){
	if(valid.read()){
		Iop = tIop;
		IaddressA = tIaddressA;
		IaddressB0 = tIaddressB0;
		IaddressB1 = tIaddressB1;
		Iimmediate = tIimmediate;
		jAddressOut = tjAddressOut;
	}
	if(reset.read()){
		Iop = 0;
		IaddressA = 0;
		IaddressB0 = 0;
		IaddressB1 = 0;
		Iimmediate = 0;
		jAddressOut = 0;
	}
	clk_out = tclk_out;
}