#include "Adder.h"

void Adder::add(){
	vAdata_in = static_cast<sc_int<32>>(Adata_in.read());
	vBdata_in = static_cast<sc_int<32>>(Bdata_in.read());
	vdata_out = vAdata_in + vBdata_in;

	data_out.write(vdata_out);
}