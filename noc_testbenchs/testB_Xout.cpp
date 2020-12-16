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

		int tMODULE_ID;
		bool trst = 0;
		bool tout_ret = 0;
		sc_bv<4> tx_req = 0;
		sc_bv<4> tx_rok = 0;
		sc_bv<10> tx_din0 = 0;
		sc_bv<10> tx_din1 = 0;
		sc_bv<10> tx_din2 = 0;
		sc_bv<10> tx_din3 = 0;


		for(int i = 0; i<32; i++){
			if(i>=4 && i<6){
				trst = 0;
				tout_ret = 0;
				tx_req = "0010";
				tx_rok = "1111";
				tx_din0 = "0010101010";
				tx_din1 = "0000001010";
				tx_din2 = "0010100000";
				tx_din3 = "0011111111";
			}
			if(i>=8 && i<10){
				trst = 0;
				tout_ret = 1;
				tx_req = "0010";
				tx_rok = "1111";
				tx_din0 = "0010101010";
				tx_din1 = "0000001010";
				tx_din2 = "0010100000";
				tx_din3 = "0011111111";
			}
			if(i>=12 && i<14){
				trst = 0;
				tout_ret = 0;
				tx_req = "0001";
				tx_rok = "1111";
				tx_din0 = "0010101010";
				tx_din1 = "0000001010";
				tx_din2 = "0010100000";
				tx_din3 = "0011111111";
			}
			if(i>=16 && i<18){
				trst = 0;
				tout_ret = 1;
				tx_req = "0001";
				tx_rok = "1111";
				tx_din0 = "0010101010";
				tx_din1 = "0000001010";
				tx_din2 = "0010100000";
				tx_din3 = "0011111111";
			}
			if(i>=20 && i<23){
				trst = 0;
				tout_ret = 0;
				tx_req = "1000";
				tx_rok = "1111";
				tx_din0 = "0010101010";
				tx_din1 = "0000001010";
				tx_din2 = "0010100000";
				tx_din3 = "0011111111";
			}
			if(i>=25 && i<27){
				trst = 0;
				tout_ret = 1;
				tx_req = "1000";
				tx_rok = "1111";
				tx_din0 = "0010101010";
				tx_din1 = "0000001010";
				tx_din2 = "0010100000";
				tx_din3 = "0011111111";
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

		for(int i = 0; i<32; i++){
			tout_data = out_data.read();
			tout_val = out_val.read();
			tx_rd = x_rd.read();
			tx_gnt = x_gnt.read();
			tx_idle = x_idle.read();
			wait();
			
			cout << i << ":\t" << tout_val << " " << tx_rd << " " << tx_gnt << " " << tx_idle << " " << tout_data << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};