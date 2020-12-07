#include "ULA.h"

void ULA::ula_op(void){
	sc_bv<3> opSelI = opSel.read();
	sc_int<32> valA = static_cast< sc_int<32> >(A.read());
	sc_int<32> valB = static_cast< sc_int<32> >(B.read());
	sc_int<32> valresult;
	bool valz;

	if(opSelI == "000"){
		valresult = (valA + valB);
	}
	else if(opSelI == "001"){
		valresult = (valA - valB);
	}
	else if(opSelI == "010"){
		valresult = (valA << valB);
	}
	else if(opSelI == "011"){
		valresult = (valA >> valB);
	}
	else if(opSelI == "100"){
		valresult = (valA & valB);
	}
	else if(opSelI == "101"){
		valresult = (valA | valB);
	}
	else if(opSelI == "110"){
		valresult = (valA ^ valB);
	}
	else if(opSelI == "111"){
		valresult = (~valA);
	}

	result.write(static_cast< sc_bv<32> >(valresult));

	if(valresult.to_int() == 0)
		valz = 1;
	else
		valz = 0;
	z.write(valz);
}