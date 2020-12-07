#include <DataMem.h>

void DataMem::write_mem(){
	if(MemW.read()){
		mem[static_cast< sc_uint<32> >(address.read())] = data_in.read();
	}
}

void DataMem::read_mem(){
	if(!MemW.read() && MemR.read()){
		data_out.write(mem[static_cast< sc_uint<32> >(address.read())]);
	}
}