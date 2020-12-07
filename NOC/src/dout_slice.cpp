#include <systemc.h>

SC_MODULE(dout_slice){
	sc_in< sc_bv<10> > dout;
	sc_out< sc_bv<4> > Xdest;
	sc_out< sc_bv<4> > Ydest;
	sc_out< bool > bop, eop;

	void slice_p(){
		Xdest = dout.read().range(7, 4);
		Ydest = dout.read().range(3, 0);
		bop = dout.read()[8];
		eop = dout.read()[9];
	}

	SC_CTOR(dout_slice){
		SC_METHOD(slice_p);
		sensitive << dout;
	}
};