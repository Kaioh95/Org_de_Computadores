#include "P_C.h"

void P_C::pc_outputs(){
	if(valid.read()){
		nextOP = op.read().range(5, 3);
				
		if(nextOP == "000"){
			WB0 = 1; WB1 = 1;
			M0 = 0; M1 = 0; M2 = 0;
			EX0 = 0; EX1 = 1;
			ulaOp = op.read().range(2, 0);
		}
		else if(nextOP == "001"){
			WB0 = 1; WB1 = 1;
			M0 = 0; M1 = 0; M2 = 0;
			EX0 = 1; EX1 = 0;
			ulaOp = op.read().range(2, 0);
		}
		else if(nextOP == "010"){
			WB0 = 1; WB1 = 0;
			M0 = 0; M1 = 0; M2 = 1;
			EX0 = 1; EX1 = 0;
			ulaOp = "000";
		}
		else if(nextOP == "011"){
			WB0 = 0; WB1 = 0;
			M0 = 0; M1 = 1; M2 = 0;
			EX0 = 1; EX1 = 0;
			ulaOp = "000";
		}
		else if(nextOP == "100"){
			WB0 = 0; WB1 = 0;
			M0 = 1; M1 = 0; M2 = 0;
			EX0 = 0; EX1 = 0;
			ulaOp = "001";
		}
	}
}