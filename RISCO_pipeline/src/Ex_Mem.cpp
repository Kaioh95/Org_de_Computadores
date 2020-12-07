#include "Ex_Mem.h"

void Ex_Mem::write(){
	if(valid.read()){
		tWB0 = WB0.read();
		tWB1 = WB1.read();
		tM0 = M0.read();
		tM1 = M1.read();
		tM2 = M2.read();
		tjAddress = jAddress.read();
		tzero = zero.read();
		tulaResult = ulaResult.read();
		tdataB = dataB.read();
		taddressWriteReg = addressWriteReg.read();
	}
	if(reset.read()){
		tWB0 = 0;
		tWB1 = 0;
		tM0 = 0;
		tM1 = 0;
		tM2 = 0;
		tjAddress = 0;
		tzero = 0;
		tulaResult = 0;
		tdataB = 0;
		taddressWriteReg = 0;
	}
	tclk_out = clk.read();
}

void Ex_Mem::read(){
	if(valid.read()){
		WB0O = tWB0;
		WB1O = tWB1;
		M0O = tM0;
		M1O = tM1;
		M2O = tM2;
		jAddressO = tjAddress;
		zeroO = tzero;
		ulaResultO = tulaResult;
		dataBO = tdataB;
		addressWriteRegO = taddressWriteReg;
	}
	if(reset.read()){
		WB0O = 0;
		WB1O = 0;
		M0O = 0;
		M1O = 0;
		M2O = 0;
		jAddressO = 0;
		zeroO = 0;
		ulaResultO = 0;
		dataBO = 0;
		addressWriteRegO = 0;
	}
	clk_out = tclk_out;
}