#include "Ext_16to32.h"

void Ext_16to32::extend(){
	extdata_out = static_cast< sc_bv<32> >(extdata_in.read());
}