#include "P_C.h"

void P_C::proxEstado(){
	// Initialize handshake
	if(reset)
		mstate = init;
	else{

		switch(mstate){
			case init:
			valid.read()? mstate = instFetch : mstate = init;
			break;	

			case instFetch:
			mstate = instDecode;
			break;

			case instDec:
			mstate = instDecode;
			break;

			case instDecode: {
			sc_bv<2> nextOP = op.read().range(4, 3);
			
			if(op.read().range(5, 3) == "100")
				mstate = opJ;
			else if(nextOP == "00")
				mstate = opR1;
			else if(nextOP == "01")
				mstate = opI1;
			else if(nextOP == "10")
				mstate = opMeM_JR;
			else if(nextOP == "11")
				mstate = opBeq;
			}
			break;

			case opR1:
			mstate = opR2;
			break;

			case opI1:
			mstate = opI2;
			break;

			case opMeM_JR: {
			sc_bv<2> nextOP2 = op.read().range(1, 0);
			
			if(nextOP2 == "00")
				mstate = opL1;
			else if(nextOP2 == "01")
				mstate = opS;
			else if(nextOP2 == "10")
				mstate = opJr2;
			}
			break;

			case opBeq:
			mstate = instFetch;
			break;

			case opJ:
			mstate = instFetch;
			break;

			case opR2:
			mstate = instFetch;
			break;

			case opI2:
			mstate = instFetch;
			break;

			case opL1:
			mstate = opL2;
			break;

			case opL2:
			mstate = instFetch;
			break;

			case opS:
			mstate = instFetch;
			break;

			case opJr2:
			mstate = instFetch;
			break;
		}

	}
}

void P_C::pc_outputs(){
	switch(mstate){
		case init:
			PCwCond = 0; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 0; 
			SrcB = "00";
			PCSrc = "00";
			ULAOp = "000";
		break;
			
		case instFetch:
			PCwCond = 0; PCw = 1; IorD = 0;
			MemRead = 1; MemWrite = 0; IRWrite = 1;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 0; 
			SrcB = "01";
			PCSrc = "00";
			ULAOp = "000";
		break;
			
		/*case instDec:
			PCwCond = 0; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 0; 
			SrcB = "10";
			PCSrc = "00";
			ULAOp = "000";
		break;*/

		case instDecode:
			PCwCond = 0; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 0; 
			SrcB = "10";
			PCSrc = "00";
			ULAOp = "000";
		break;

		case opR1:
			PCwCond = 0; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 1; 
			SrcB = "00";
			PCSrc = "00";
			ULAOp = op.read().range(2, 0);
		break;

		case opR2: 
			PCwCond = 0; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 1; MemtoReg = 0; RegWrite = 1;
			SrcA = 1; 
			SrcB = "00";
			PCSrc = "00";
			ULAOp = op.read().range(2, 0);
		break;

		case opI1:
			PCwCond = 0; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 1; 
			SrcB = "10";
			PCSrc = "00";
			ULAOp = op.read().range(2, 0);
		break;

		case opI2:
			PCwCond = 0; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 1;
			SrcA = 1; 
			SrcB = "10";
			PCSrc = "00";
			ULAOp = op.read().range(2, 0);
		break;

		case opMeM_JR:
			PCwCond = 0; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 1; 
			SrcB = "10";
			PCSrc = "00";
			ULAOp = "000";
		break;

		case opL1:
			PCwCond = 0; PCw = 0; IorD = 1;
			MemRead = 1; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 1; 
			SrcB = "10";
			PCSrc = "00";
			ULAOp = "000";
		break;

		case opL2:
			PCwCond = 0; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 1; RegWrite = 1;
			SrcA = 1; 
			SrcB = "10";
			PCSrc = "00";
			ULAOp = "000";
		break;

		case opS:
			PCwCond = 0; PCw = 0; IorD = 1;
			MemRead = 0; MemWrite = 1; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 1; 
			SrcB = "10";
			PCSrc = "00";
			ULAOp = "000";
		break;

		case opBeq:
			PCwCond = 1; PCw = 0; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 1; 
			SrcB = "00";
			PCSrc = "01";
			ULAOp = "001";
		break;

		case opJ:
			PCwCond = 0; PCw = 1; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 0; 
			SrcB = "00";
			PCSrc = "10";
			ULAOp = "000";
		break;

		case opJr2:
			PCwCond = 0; PCw = 1; IorD = 0;
			MemRead = 0; MemWrite = 0; IRWrite = 0;
			RegDst = 0; MemtoReg = 0; RegWrite = 0;
			SrcA = 1; 
			SrcB = "10";
			PCSrc = "01";
			ULAOp = "000";
		break;
		
	}
}