#include <systemc.h>

SC_MODULE(testB){
	sc_out< bool > rst;
	sc_out< sc_bv<10> > in_data;
	sc_out< bool > in_val;
	sc_in< bool > in_ret;	//ack

	// comandos e sinais de status interconectando os canais de entrada e saída
	sc_in< bool > x_reqL;
	sc_in< bool > x_reqN;
	sc_in< bool > x_reqE;
	sc_in< bool > x_reqS;
	sc_in< bool > x_reqW;
	sc_in< bool > x_rok;

	sc_out< sc_bv<4> > x_rd;
	sc_out< sc_bv<4> > x_gnt;

	sc_out< bool > x_Lidle;
	sc_out< bool > x_Nidle;
	sc_out< bool > x_Eidle;
	sc_out< bool > x_Sidle;
	sc_out< bool > x_Widle;

	sc_in< sc_bv<10> > x_dout;

	sc_in< bool > clk;

	void source(){
		rst.write(1);
		in_data.write(0);
		in_val.write(0);
		x_rd.write(0);
		x_gnt.write(0);
		x_Lidle.write(0);
		x_Nidle.write(0);
		x_Eidle.write(0);
		x_Sidle.write(0);
		x_Widle.write(0);
		wait();

		bool trst = 0;
		sc_bv<10> tin_data = 0;
		bool tin_val = 0;
		sc_bv<4> tx_rd = 0;
		sc_bv<4> tx_gnt = 0;
		bool tx_Lidle = 0;
		bool tx_Nidle = 0;
		bool tx_Eidle = 0;
		bool tx_Sidle = 0;
		bool tx_Widle = 0;


		for(int i = 0; i<32; i++){
			if(i>=4 && i<6){
				trst = 0;
				tin_data = "1010101010";
				tin_val = 0;
				tx_rd = "0100";
				tx_gnt = "0100";
				tx_Lidle = 0;
				tx_Nidle = 0;
				tx_Eidle = 0;
				tx_Sidle = 0;
				tx_Widle = 0;
			}
			if(i>=8 && i<10){
				trst = 0;
				tin_data = "1010101010";
				tin_val = 1;
				tx_rd = "0100";
				tx_gnt = "0100";
				tx_Lidle = 0;
				tx_Nidle = 0;
				tx_Eidle = 0;
				tx_Sidle = 0;
				tx_Widle = 0;
			}
			if(i>=12 && i<14){
				trst = 0;
				tin_data = "1010111111";
				tin_val = 1;
				tx_rd = "0010";
				tx_gnt = "0010";
				tx_Lidle = 0;
				tx_Nidle = 0;
				tx_Eidle = 0;
				tx_Sidle = 0;
				tx_Widle = 0;
			}
			if(i>=16 && i<18){
				trst = 0;
				tin_data = "1111101010";
				tin_val = 1;
				tx_rd = "0001";
				tx_gnt = "0001";
				tx_Lidle = 0;
				tx_Nidle = 0;
				tx_Eidle = 0;
				tx_Sidle = 0;
				tx_Widle = 0;
			}
			if(i>=20 && i<23){
				trst = 0;
				tin_data = "1111111111";
				tin_val = 1;
				tx_rd = "1000";
				tx_gnt = "1000";
				tx_Lidle = 0;
				tx_Nidle = 0;
				tx_Eidle = 0;
				tx_Sidle = 0;
				tx_Widle = 0;
			}
			if(i>=25 && i<27){
				trst = 0;
				tin_data = "0010001000";
				tin_val = 1;
				tx_rd = "0100";
				tx_gnt = "0100";
				tx_Lidle = 0;
				tx_Nidle = 0;
				tx_Eidle = 0;
				tx_Sidle = 0;
				tx_Widle = 0;
			}

			rst.write(trst);
			in_data.write(tin_data);
			in_val.write(tin_val);
			x_rd.write(tx_rd);
			x_gnt.write(tx_gnt);
			x_Lidle.write(tx_Lidle);
			x_Nidle.write(tx_Nidle);
			x_Eidle.write(tx_Eidle);
			x_Sidle.write(tx_Sidle);
			x_Widle.write(tx_Widle);
			wait();
		}
	}

	void sink(){
		bool tin_ret;
		bool tx_reqL;
		bool tx_reqN;
		bool tx_reqE;
		bool tx_reqS;
		bool tx_reqW;
		bool tx_rok;
		sc_bv<10> tx_dout;

		for(int i = 0; i<32; i++){
			tin_ret = in_ret.read();
			tx_reqL = x_reqL.read();
			tx_reqN = x_reqN.read();
			tx_reqE = x_reqE.read();
			tx_reqS = x_reqS.read();
			tx_reqW = x_reqW.read();
			tx_rok = x_rok.read();
			tx_dout = x_dout.read();
			wait();
			
			cout << i << ":\t" << tin_ret << " " << tx_reqL << tx_reqN << tx_reqE << tx_reqS << tx_reqW << " " << tx_rok << " " << tx_dout << endl;
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};