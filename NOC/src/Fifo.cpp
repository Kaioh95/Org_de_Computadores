#include <systemc.h>

#define FIFO_TYPE "SHIFT"
#define WIDTH 8
#define DEPTH 4
#define LOGDEPTH 2
#define LOGDEPTHPLUSONE 3
/**
* @file Fifo.cpp
* @details Uma entidade FIFO
* @author Kaio Henrique de Sousa
* @since 25/11/2020
*/

SC_MODULE(Fifo){
	sc_in< sc_bv<WIDTH+2> > din;
	sc_in< bool > rd;	//Comando para ler do FIFO
	sc_in< bool > wr;	//Comando para escrever do FIFO
	sc_in< bool > clk, rst;

	sc_out< sc_bv<WIDTH+2> > dout;
	sc_out< bool > rok;	//FIFO tem dado para ler (não vazio)
	sc_out< bool > wok;	//FIFO tem room para escrever (não cheio)

//-----------Variáveis Internas--------------
	sc_signal< int > buf0, buf0_next;
	sc_signal< int > buf1, buf1_next;
	sc_signal< int > buf2, buf2_next;
	sc_signal< int > buf3, buf3_next;
	sc_signal< sc_uint<LOGDEPTHPLUSONE> > num_in_buf, num_in_buf_next;
	sc_signal< bool > swok, srok;
	sc_signal< int > data_out_next;

	void ns_logic(){
		buf0_next = buf0;
		buf1_next = buf1;
		buf2_next = buf2;
		buf3_next = buf3;
		num_in_buf_next = num_in_buf;
		data_out_next = 0;

		if(rd.read()){
			if(num_in_buf.read() != 0){
				data_out_next = buf0;
				buf0_next = buf1;
				buf1_next = buf2;
				buf2_next = buf3;
				num_in_buf_next = num_in_buf.read()-1;
			}
		}
		if(wr.read()){
			switch(int(num_in_buf.read())){
				case 0:
					buf0_next = din.read().to_int();
					num_in_buf_next = num_in_buf.read() + 1;
					break;
				case 1:
					buf1_next = din.read().to_int();
					num_in_buf_next = num_in_buf.read() + 1;
					break;
				case 2:
					buf2_next = din.read().to_int();
					num_in_buf_next = num_in_buf.read() + 1;
					break;
				case 3:
					buf3_next = din.read().to_int();
					num_in_buf_next = num_in_buf.read() + 1;
					break;
				default:
					break;
			}
		}
	}

	void update_regs(){
		if(rst.read() == 1){
			wok.write(1);
			rok.write(0);
			num_in_buf = 0;
			buf0 = 0;
			buf1 = 0;
			buf2 = 0;
			buf3 = 0;
			dout = 0;
		}
		else{
			wok = swok;
			rok = srok;
			num_in_buf = num_in_buf_next;
			buf0 = buf0_next;
			buf1 = buf1_next;
			buf2 = buf2_next;
			buf3 = buf3_next;
			dout = static_cast<sc_bv<WIDTH+2>>(data_out_next);
		}
	}

	void wok_p(){
		if(num_in_buf_next.read() != DEPTH)
			swok.write(1);
		else
			swok.write(0);
	}

	void rok_p(){
		if(num_in_buf_next.read() == 0)
			srok.write(0);
		else
			srok.write(1);
	}

	SC_CTOR(Fifo){
		SC_METHOD(ns_logic);
		sensitive << wr << rd << din << num_in_buf;

		SC_METHOD(update_regs);
		sensitive << clk.pos();

		SC_METHOD(wok_p);
		sensitive << num_in_buf_next;

		SC_METHOD(rok_p);
		sensitive << num_in_buf_next;
	}

};