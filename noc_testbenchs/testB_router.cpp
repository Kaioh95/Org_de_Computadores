#include <systemc.h>

SC_MODULE(testB){
	sc_out< bool > rst;

	// Porta de comunicação local
	sc_out< sc_bv<10> > Lin_data;
	sc_out< bool > Lin_val;
	sc_in< bool > Lin_ret;
	sc_in< sc_bv<10> > Lout_data;
	sc_in< bool > Lout_val;
	sc_out< bool > Lout_ret;

	// Porta Norte de comunicação
	sc_out< sc_bv<10> > Nin_data;
	sc_out< bool > Nin_val;
	sc_in< bool > Nin_ret;
	sc_in< sc_bv<10> > Nout_data;
	sc_in< bool > Nout_val;
	sc_out< bool > Nout_ret;

	// Porta Leste de comunicação
	sc_out< sc_bv<10> > Ein_data;
	sc_out< bool > Ein_val;
	sc_in< bool > Ein_ret;
	sc_in< sc_bv<10> > Eout_data;
	sc_in< bool > Eout_val;
	sc_out< bool > Eout_ret;

	// Porta Sul de comunicação
	sc_out< sc_bv<10> > Sin_data;
	sc_out< bool > Sin_val;
	sc_in< bool > Sin_ret;
	sc_in< sc_bv<10> > Sout_data;
	sc_in< bool > Sout_val;
	sc_out< bool > Sout_ret;

	// Porta Oeste de comunicação
	sc_out< sc_bv<10> > Win_data;
	sc_out< bool > Win_val;
	sc_in< bool > Win_ret;
	sc_in< sc_bv<10> > Wout_data;
	sc_in< bool > Wout_val;
	sc_out< bool > Wout_ret;

	sc_in< bool > clk;

	void source(){
		rst.write(1);

		Lin_data.write(0);
		Lin_val.write(0);
		Lout_ret.write(0);

		Nin_data.write(0);
		Nin_val.write(0);
		Nout_ret.write(0);

		Ein_data.write(0);
		Ein_val.write(0);
		Eout_ret.write(0);

		Sin_data.write(0);
		Sin_val.write(0);
		Sout_ret.write(0);

		Win_data.write(0);
		Win_val.write(0);
		Wout_ret.write(0);

		wait();

		bool trst;

		sc_bv<10> tLin_data;
		bool tLin_val;
		bool tLout_ret;

		sc_bv<10> tNin_data;
		bool tNin_val;
		bool tNout_ret;

		sc_bv<10> tEin_data;
		bool tEin_val;
		bool tEout_ret;

		sc_bv<10> tSin_data;
		bool tSin_val;
		bool tSout_ret;

		sc_bv<10> tWin_data;
		bool tWin_val;
		bool tWout_ret;

		for(int i = 0; i<40; i++){
			if(i>=1 && i<3){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 1;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=3 && i<5){
				trst = 0;
				
				tLin_data = "0100100011";
				tLin_val = 1;
				tLout_ret = 1;

				tNin_data = "0110100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0100001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0111111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0100100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=5 && i<7){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 1;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=7 && i<9){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 1;
				tNout_ret = 1;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=9 && i<11){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 1;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=11 && i<13){
				trst = 0;
				
				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 1;
				tEout_ret = 1;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=13 && i<15){
				trst = 0;
				
				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 1;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=15 && i<17){
				trst = 0;
				
				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 1;
				tSout_ret = 1;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=17 && i<19){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 1;
				tWout_ret = 0;
			}
			else if(i>=19 && i<21){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 1;
				tWout_ret = 1;
			}
			else if(i>=21 && i<23){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=23 && i<25){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;;
			}
			else if(i>=25 && i<27){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=27 && i<29){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=29 && i<31){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=31 && i<33){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=33 && i<35){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=35 && i<37){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}
			else if(i>=37 && i<39){
				trst = 0;

				tLin_data = "0000100011";
				tLin_val = 0;
				tLout_ret = 0;

				tNin_data = "0010100000";
				tNin_val = 0;
				tNout_ret = 0;

				tEin_data = "0000001010";
				tEin_val = 0;
				tEout_ret = 0;

				tSin_data = "0011111111";
				tSin_val = 0;
				tSout_ret = 0;

				tWin_data = "0000100100";
				tWin_val = 0;
				tWout_ret = 0;
			}

			rst.write(trst);
			
			Lin_data.write(tLin_data);
			Lin_val.write(tLin_val);
			Lout_ret.write(tLout_ret);

			Nin_data.write(tNin_data);
			Nin_val.write(tNin_val);
			Nout_ret.write(tNout_ret);

			Ein_data.write(tEin_data);
			Ein_val.write(tEin_val);
			Eout_ret.write(tEout_ret);

			Sin_data.write(tSin_data);
			Sin_val.write(tSin_val);
			Sout_ret.write(tSout_ret);

			Win_data.write(tWin_data);
			Win_val.write(tWin_val);
			Wout_ret.write(tWout_ret);

			wait();
		}
	}

	void sink(){
		bool tLin_ret;
		sc_bv<10> tLout_data;
		bool tLout_val;

		bool tNin_ret;
		sc_bv<10> tNout_data;
		bool tNout_val;

		bool tEin_ret;
		sc_bv<10> tEout_data;
		bool tEout_val;

		bool tSin_ret;
		sc_bv<10> tSout_data;
		bool tSout_val;

		bool tWin_ret;
		sc_bv<10> tWout_data;
		bool tWout_val;


		for(int i = 0; i<40; i++){
			tLin_ret = Lin_ret.read();
			tLout_data = Lout_data.read();
			tLout_val = Lout_val.read();

			tNin_ret = Nin_ret.read();
			tNout_data = Nout_data.read();
			tNout_val = Nout_val.read();

			tEin_ret = Ein_ret.read();
			tEout_data = Eout_data.read();
			tEout_val = Eout_val.read();

			tSin_ret = Sin_ret.read();
			tSout_data = Sout_data.read();
			tSout_val = Sout_val.read();

			tWin_ret = Win_ret.read();
			tWout_data = Wout_data.read();
			tWout_val = Wout_val.read();

			wait();
			
			cout << i << "---------------------------------------------------"<< endl;
			cout << "\t L: " << tLin_ret << " " << tLout_val << " " << tLout_data << endl;
			cout << "\t N: " << tNin_ret << " " << tNout_val << " " << tNout_data << endl;
			cout << "\t E: " << tEin_ret << " " << tEout_val << " " << tEout_data << endl;
			cout << "\t S: " << tSin_ret << " " << tSout_val << " " << tSout_data << endl;
			cout << "\t W: " << tWin_ret << " " << tWout_val << " " << tWout_data << endl;
		
		}

		sc_stop();
	}

	SC_CTOR(testB){
		SC_CTHREAD(source, clk.pos());
		SC_CTHREAD(sink, clk.pos());
	}
};