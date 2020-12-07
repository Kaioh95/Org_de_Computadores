#include <InstMem.h>

void InstMem::write_mem(){
	if(MemW.read()){
		mem[static_cast< sc_uint<32> >(address.read())] = data_in.read();
	}
}

void InstMem::read_mem(){
	data_out.write(mem[static_cast< sc_uint<32> >(address.read())]);
}