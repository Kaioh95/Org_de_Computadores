#include "B_Reg.h"

void B_Reg::READ_A(){
	data_A = bank[static_cast< sc_uint<5> >(address_A.read())];
}
  
void B_Reg::READ_B(){
	data_B = bank[static_cast< sc_uint<5> >(address_B.read())];
}
  
void B_Reg::WRITE_DATA(){
	if(wReg.read()){
		bank[static_cast< sc_uint<5> >(address_data.read())] = data_in.read();
	} 
}
