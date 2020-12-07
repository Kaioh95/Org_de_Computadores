#include "Id_Ex.h"

void Id_Ex::write(){
	if(valid.read()){
		tWB0 = WB0.read();
		tWB1 = WB1.read();
		tM0 = M0.read();
		tM1 = M1.read();
		tM2 = M2.read();
		tEX0 = EX0.read();
		tEX1 = EX1.read();
		tulaOp = ulaOp.read();
		tjAddress = jAddress.read();
		tdataA = dataA.read();
		tdataB = dataB.read();
		timmediate = immediate.read();
		taddressA = addressA.read();
		taddressB = addressB.read();
	}
	if(reset.read()){
		tWB0 = 0;
		tWB1 = 0;
		tM0 = 0;
		tM1 = 0;
		tM2 = 0;
		tEX0 = 0;
		tEX1 = 0;
		tulaOp = 0;
		tjAddress = 0;
		tdataA = 0;
		tdataB = 0;
		timmediate = 0;
		taddressA = 0;
		taddressB = 0;
	}
	tclk_out = clk.read();
}

void Id_Ex::read(){
	if(valid.read()){
		WB0O = tWB0;
		WB1O = tWB1;
		M0O = tM0;
		M1O = tM1;
		M2O = tM2;
		EX0O = tEX0;
		EX1O = tEX1;
		ulaOpO = tulaOp;
		jAddressO = tjAddress;
		dataAO = tdataA;
		dataBO = tdataB;
		immediateO = timmediate;
		addressAO = taddressA;
		addressBO = taddressB;
	}
	if(reset.read()){
		WB0O = 0;
		WB1O = 0;
		M0O = 0;
		M1O = 0;
		M2O = 0;
		EX0O = 0;
		EX1O = 0;
		ulaOpO = 0;
		jAddressO = 0;
		dataAO = 0;
		dataBO = 0;
		immediateO = 0;
		addressAO = 0;
		addressBO = 0;
	}
	clk_out = tclk_out;
}