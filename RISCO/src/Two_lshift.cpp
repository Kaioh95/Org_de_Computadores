#include "Two_lshift.h"

void Two_lshift::desloc(){
	sc_int<32> temp_sdata_out = static_cast< sc_int<32> >(sdata_in.read());
	temp_sdata_out = temp_sdata_out << 2;
	sdata_out.write(static_cast< sc_bv<32> >(temp_sdata_out));
}