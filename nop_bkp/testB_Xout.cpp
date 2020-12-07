#include <systemc.h>

SC_MODULE(testB){
	sc_out< bool > rst;
	sc_in< sc_bv<10> > out_data;
	sc_in< bool > out_val;
	sc_out< bool > out_ret;
	sc_out< sc_bv<4> > x_req;
	sc_out< sc_bv<4> > x_rok;
	sc_in< bool > x_rd;
	sc_in< sc_bv<4> > x_gnt;
	sc_in< bool > x_idle;
	sc_out< sc_bv<10> > x_din0;
	sc_out< sc_bv<10> > x_din1;
	sc_out< sc_bv<10> > x_din2;
	sc_out< sc_bv<10> > x_din3;

	sc_in< bool > clk;

	void source(){
		rst.write(1);
		out_ret.write(0);
		x_req.write(0);
		x_rok.write(0);
		x_din0.write(0);
		x_din1.write(0);
		x_din2.write(0);
		x_din3.write(0);
		wait();

		bool trst;
		bool tout_ret;
		sc_bv<4> tx_req;
		sc_bv<4> tx_rok;
		sc_bv<10> tx_din0;
		sc_bv<10> tx_din1;
		sc_bv<10> tx_din2;
		sc_bv<10> tx_din3;

		for(int i = 0; i<40; i++){
			if(i>=1 && i<3){
				trst = 0;
				tout_ret = 1;
				tx_req = "0001";
				tx_rok = "0001";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=3 && i<5){
				trst = 0;
				tout_ret = 0;
				tx_req = "0001";
				tx_rok = "0001";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=5 && i<7){
				trst = 0;
				tout_ret = 1;
				tx_req = "0010";
				tx_rok = "0010";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=7 && i<9){
				trst = 0;
				tout_ret = 0;
				tx_req = "0010";
				tx_rok = "0010";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=9 && i<11){
				trst = 0;
				tout_ret = 1;
				tx_req = "0100";
				tx_rok = "0100";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=11 && i<13){
				trst = 0;
				tout_ret = 0;
				tx_req = "0100";
				tx_rok = "0100";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=13 && i<15){
				trst = 0;
				tout_ret = 1;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=15 && i<17){
				trst = 0;
				tout_ret = 0;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=17 && i<19){
				trst = 0;
				tout_ret = 1;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=19 && i<21){
				trst = 0;
				tout_ret = 0;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=21 && i<23){
				trst = 0;
				tout_ret = 1;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=23 && i<25){
				trst = 0;
				tout_ret = 0;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=25 && i<27){
				trst = 0;
				tout_ret = 1;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=27 && i<29){
				trst = 0;
				tout_ret = 0;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=29 && i<31){
				trst = 0;
				tout_ret = 1;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=31 && i<33){
				trst = 0;
				tout_ret = 0;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=33 && i<35){
				trst = 0;
				tout_ret = 1;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=35 && i<37){
				trst = 0;
				tout_ret = 1;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}
			else if(i>=37 && i<39){
				trst = 0;
				tout_ret = 1;
				tx_req = "1000";
				tx_rok = "1000";
				tx_din0 = "0000101010";
				tx_din1 = "1010100000";
				tx_din2 = "1010101010";
				tx_din3 = "1111111111";
			}

			rst.write(trst);
			out_ret.write(tout_ret);
			x_req.write(tx_req);
			x_rok.write(tx_rok);
			x_din0.write(tx_din0);
			x_din1.write(tx_din1);
			x_din2.write(tx_din2);
			x_din3.write(tx_din3);
			wait();
		}
	}

	void sink(){
		sc_bv<10> tout_data;
		bool tout_val;
		bool tx_rd;
		sc_bv<4> tx_gnt;
		bool tx_idle;

		for(int i = 0; i<40; i++){
			tout_data = out_data.read();
			tout_val = out_val.read();
			tx_rd = x_rd.read();
			tx_gnt = x_gnt.read();
			tx_idle = x_idle.read();
			wait();
			
			cout << i << ":\t" << out_data << " " << tout_val << " " << tx_rd << " " << tx_gnt << " " << tx_idle << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};