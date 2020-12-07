#include "Mem_Wb.h"

void Mem_Wb::write(){
	if(valid.read()){
		tWB0 = WB0.read();
		tWB1 = WB1.read();
		tdataOut = dataOut.read();
		tulaResult = ulaResult.read();
		taddressWriteReg = addressWriteReg.read();
	}
	if(reset.read()){
		tWB0 = 0;
		tWB1 = 0;
		tdataOut = 0;
		tulaResult = 0;
		taddressWriteReg = 0;
	}
	tclk_out = clk.read();
}

void Mem_Wb::read(){
	if(valid.read()){
		WB0O = tWB0;
		WB1O = tWB1;
		dataOutO = tdataOut;
		ulaResultO = tulaResult;
		addressWriteRegO = taddressWriteReg;
	}
	if(reset.read()){
		WB0O = 0;
		WB1O = 0;
		dataOutO = 0;
		ulaResultO = 0;
		addressWriteRegO = 0;
	}
	clk_out = tclk_out;
}