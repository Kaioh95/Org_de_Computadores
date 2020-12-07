#include <systemc.h>
#include "Xin.cpp"
#include "Xout.cpp"
#include "X.cpp"

#define DATA_WIDTH 8
/**
* @file Router.cpp
* @details Esta é uma reprodução em SYSTEMC de um roteador ParIS
* da rede SoCINfp, a devidas refências constarão no relatório
* junto ao código fonte.
* @author Kaio Henrique de Sousa
* @since 03/12/2020
*/

SC_MODULE(Router){
	sc_in< bool > clk, rst;

	// Porta de comunicação local
	sc_in< sc_bv<DATA_WIDTH+2> > Lin_data;
	sc_in< bool > Lin_val;
	sc_out< bool > Lin_ret;
	sc_out< sc_bv<DATA_WIDTH+2> > Lout_data;
	sc_out< bool > Lout_val;
	sc_in< bool > Lout_ret;

	// Porta Norte de comunicação
	sc_in< sc_bv<DATA_WIDTH+2> > Nin_data;
	sc_in< bool > Nin_val;
	sc_out< bool > Nin_ret;
	sc_out< sc_bv<DATA_WIDTH+2> > Nout_data;
	sc_out< bool > Nout_val;
	sc_in< bool > Nout_ret;

	// Porta Leste de comunicação
	sc_in< sc_bv<DATA_WIDTH+2> > Ein_data;
	sc_in< bool > Ein_val;
	sc_out< bool > Ein_ret;
	sc_out< sc_bv<DATA_WIDTH+2> > Eout_data;
	sc_out< bool > Eout_val;
	sc_in< bool > Eout_ret;

	// Porta Sul de comunicação
	sc_in< sc_bv<DATA_WIDTH+2> > Sin_data;
	sc_in< bool > Sin_val;
	sc_out< bool > Sin_ret;
	sc_out< sc_bv<DATA_WIDTH+2> > Sout_data;
	sc_out< bool > Sout_val;
	sc_in< bool > Sout_ret;

	// Porta Oeste de comunicação
	sc_in< sc_bv<DATA_WIDTH+2> > Win_data;
	sc_in< bool > Win_val;
	sc_out< bool > Win_ret;
	sc_out< sc_bv<DATA_WIDTH+2> > Wout_data;
	sc_out< bool > Wout_val;
	sc_in< bool > Wout_ret;

//--------------------Sinais-------------------------
	// Requests de L
	sc_signal< bool > Lunused;
	sc_signal< bool > LreqN_Xin;
	sc_signal< bool > LreqN_Xout;
	sc_signal< bool > LreqE_Xin;
	sc_signal< bool > LreqE_Xout;
	sc_signal< bool > LreqS_Xin;
	sc_signal< bool > LreqS_Xout;
	sc_signal< bool > LreqW_Xin;
	sc_signal< bool > LreqW_Xout;
	// Requests de N
	sc_signal< bool > Nunused;
	sc_signal< bool > NreqL_Xin;
	sc_signal< bool > NreqL_Xout;
	sc_signal< bool > NreqE_Xin;
	sc_signal< bool > NreqE_Xout;
	sc_signal< bool > NreqS_Xin;
	sc_signal< bool > NreqS_Xout;
	sc_signal< bool > NreqW_Xin;
	sc_signal< bool > NreqW_Xout;
	// Requests de E
	sc_signal< bool > Eunused;
	sc_signal< bool > EreqL_Xin;
	sc_signal< bool > EreqL_Xout;
	sc_signal< bool > EreqN_Xin;
	sc_signal< bool > EreqN_Xout;
	sc_signal< bool > EreqS_Xin;
	sc_signal< bool > EreqS_Xout;
	sc_signal< bool > EreqW_Xin;
	sc_signal< bool > EreqW_Xout;
	// Requests de S
	sc_signal< bool > Sunused;
	sc_signal< bool > SreqL_Xin;
	sc_signal< bool > SreqL_Xout;
	sc_signal< bool > SreqN_Xin;
	sc_signal< bool > SreqN_Xout;
	sc_signal< bool > SreqE_Xin;
	sc_signal< bool > SreqE_Xout;
	sc_signal< bool > SreqW_Xin;
	sc_signal< bool > SreqW_Xout;
	// Requests de W
	sc_signal< bool > Wunused;
	sc_signal< bool > WreqL_Xin;
	sc_signal< bool > WreqL_Xout;
	sc_signal< bool > WreqN_Xin;
	sc_signal< bool > WreqN_Xout;
	sc_signal< bool > WreqE_Xin;
	sc_signal< bool > WreqE_Xout;
	sc_signal< bool > WreqS_Xin;
	sc_signal< bool > WreqS_Xout;

	// Concessões de L
	sc_signal< bool > LgntN_Xin;
	sc_signal< bool > LgntN_Xout;
	sc_signal< bool > LgntE_Xin;
	sc_signal< bool > LgntE_Xout;
	sc_signal< bool > LgntS_Xin;
	sc_signal< bool > LgntS_Xout;
	sc_signal< bool > LgntW_Xin;
	sc_signal< bool > LgntW_Xout;
	// Concessões de N
	sc_signal< bool > NgntL_Xin;
	sc_signal< bool > NgntL_Xout;
	sc_signal< bool > NgntE_Xin;
	sc_signal< bool > NgntE_Xout;
	sc_signal< bool > NgntS_Xin;
	sc_signal< bool > NgntS_Xout;
	sc_signal< bool > NgntW_Xin;
	sc_signal< bool > NgntW_Xout;
	// Concessões de E
	sc_signal< bool > EgntL_Xin;
	sc_signal< bool > EgntL_Xout;
	sc_signal< bool > EgntN_Xin;
	sc_signal< bool > EgntN_Xout;
	sc_signal< bool > EgntS_Xin;
	sc_signal< bool > EgntS_Xout;
	sc_signal< bool > EgntW_Xin;
	sc_signal< bool > EgntW_Xout;
	// Concessões de S
	sc_signal< bool > SgntL_Xin;
	sc_signal< bool > SgntL_Xout;
	sc_signal< bool > SgntN_Xin;
	sc_signal< bool > SgntN_Xout;
	sc_signal< bool > SgntE_Xin;
	sc_signal< bool > SgntE_Xout;
	sc_signal< bool > SgntW_Xin;
	sc_signal< bool > SgntW_Xout;
	// Concessões de W
	sc_signal< bool > WgntL_Xin;
	sc_signal< bool > WgntL_Xout;
	sc_signal< bool > WgntN_Xin;
	sc_signal< bool > WgntN_Xout;
	sc_signal< bool > WgntE_Xin;
	sc_signal< bool > WgntE_Xout;
	sc_signal< bool > WgntS_Xin;
	sc_signal< bool > WgntS_Xout;

	// Barramentos de dados
	sc_signal< sc_bv<DATA_WIDTH+2> > Ldata;
	sc_signal< sc_bv<DATA_WIDTH+2> > Ndata;
	sc_signal< sc_bv<DATA_WIDTH+2> > Edata;
	sc_signal< sc_bv<DATA_WIDTH+2> > Sdata;
	sc_signal< sc_bv<DATA_WIDTH+2> > Wdata;

	// Status da escrita
	sc_signal< bool > Lrok;
	sc_signal< bool > Nrok;
	sc_signal< bool > Erok;
	sc_signal< bool > Srok;
	sc_signal< bool > Wrok;

	// Comandos de escrita
	sc_signal< bool > Lrd;
	sc_signal< bool > Nrd;
	sc_signal< bool > Erd;
	sc_signal< bool > Srd;
	sc_signal< bool > Wrd;

	// Ociosos
	sc_signal< bool > Lidle;
	sc_signal< bool > Nidle;
	sc_signal< bool > Eidle;
	sc_signal< bool > Sidle;
	sc_signal< bool > Widle;

//-------------Variáveis internas---------------
	sc_bv<4> Lx_rdi;
	sc_bv<4> Lx_gnti;
	sc_bv<4> Lx_reqo;
	sc_bv<4> Lx_roko;
	sc_signal< sc_bv<4> > Lx_gnto;

	sc_bv<4> Nx_rdi;
	sc_bv<4> Nx_gnti;
	sc_bv<4> Nx_reqo;
	sc_bv<4> Nx_roko;
	sc_signal< sc_bv<4> > Nx_gnto;

	sc_bv<4> Ex_rdi;
	sc_bv<4> Ex_gnti;
	sc_bv<4> Ex_reqo;
	sc_bv<4> Ex_roko;
	sc_signal< sc_bv<4> > Ex_gnto;

	sc_bv<4> Sx_rdi;
	sc_bv<4> Sx_gnti;
	sc_bv<4> Sx_reqo;
	sc_bv<4> Sx_roko;
	sc_signal< sc_bv<4> > Sx_gnto;

	sc_bv<4> Wx_rdi;
	sc_bv<4> Wx_gnti;
	sc_bv<4> Wx_reqo;
	sc_bv<4> Wx_roko;
	sc_signal< sc_bv<4> > Wx_gnto;

	// Sinais
	sc_signal< sc_bv<4> > sLx_rdi;
	sc_signal< sc_bv<4> > sLx_gnti;
	sc_signal< sc_bv<4> > sLx_reqo;
	sc_signal< sc_bv<4> > sLx_roko;

	sc_signal< sc_bv<4> > sNx_rdi;
	sc_signal< sc_bv<4> > sNx_gnti;
	sc_signal< sc_bv<4> > sNx_reqo;
	sc_signal< sc_bv<4> > sNx_roko;

	sc_signal< sc_bv<4> > sEx_rdi;
	sc_signal< sc_bv<4> > sEx_gnti;
	sc_signal< sc_bv<4> > sEx_reqo;
	sc_signal< sc_bv<4> > sEx_roko;

	sc_signal< sc_bv<4> > sSx_rdi;
	sc_signal< sc_bv<4> > sSx_gnti;
	sc_signal< sc_bv<4> > sSx_reqo;
	sc_signal< sc_bv<4> > sSx_roko;

	sc_signal< sc_bv<4> > sWx_rdi;
	sc_signal< sc_bv<4> > sWx_gnti;
	sc_signal< sc_bv<4> > sWx_reqo;
	sc_signal< sc_bv<4> > sWx_roko;


	Xin *Lin;
	Xin *Nin;
	Xin *Ein;
	Xin *Sin;
	Xin *Win;

	Xout *Lout;
	Xout *Nout;
	Xout *Eout;
	Xout *Sout;
	Xout *Wout;

	X *X0;

	void sliced_bits(){
		// Bits do canais de input
		Lx_rdi[0] = Nrd;
		Lx_rdi[1] = Erd;
		Lx_rdi[2] = Srd;
		Lx_rdi[3] = Wrd;

		Lx_gnti[0] = NgntL_Xin;
		Lx_gnti[1] = EgntL_Xin;
		Lx_gnti[2] = SgntL_Xin;
		Lx_gnti[3] = WgntL_Xin;
		sLx_rdi = Lx_rdi;
		sLx_gnti = Lx_gnti;

		Nx_rdi[0] = Lrd;
		Nx_rdi[1] = Erd;
		Nx_rdi[2] = Srd;
		Nx_rdi[3] = Wrd;

		Nx_gnti[0] = LgntN_Xin;
		Nx_gnti[1] = EgntN_Xin;
		Nx_gnti[2] = SgntN_Xin;
		Nx_gnti[3] = WgntN_Xin;
		sNx_rdi = Nx_rdi;
		sNx_gnti = Nx_gnti;

		Ex_rdi[0] = Lrd;
		Ex_rdi[1] = Nrd;
		Ex_rdi[2] = Srd;
		Ex_rdi[3] = Wrd;

		Ex_gnti[0] = LgntE_Xin;
		Ex_gnti[1] = NgntE_Xin;
		Ex_gnti[2] = SgntE_Xin;
		Ex_gnti[3] = WgntE_Xin;
		sEx_rdi = Ex_rdi;
		sEx_gnti = Ex_gnti;

		Sx_rdi[0] = Lrd;
		Sx_rdi[1] = Nrd;
		Sx_rdi[2] = Erd;
		Sx_rdi[3] = Wrd;

		Sx_gnti[0] = LgntS_Xin;
		Sx_gnti[1] = NgntS_Xin;
		Sx_gnti[2] = EgntS_Xin;
		Sx_gnti[3] = WgntS_Xin;
		sSx_rdi = Sx_rdi;
		sSx_gnti = Sx_gnti;

		Wx_rdi[0] = Lrd;
		Wx_rdi[1] = Nrd;
		Wx_rdi[2] = Erd;
		Wx_rdi[3] = Srd;

		Wx_gnti[0] = LgntW_Xin;
		Wx_gnti[1] = NgntW_Xin;
		Wx_gnti[2] = EgntW_Xin;
		Wx_gnti[3] = SgntW_Xin;
		sWx_rdi = Wx_rdi;
		sWx_gnti = Wx_gnti;

		// Bits do canais de output
		Lx_reqo[0] = NreqL_Xout;
		Lx_reqo[1] = EreqL_Xout;
		Lx_reqo[2] = SreqL_Xout;
		Lx_reqo[3] = WreqL_Xout;
		LgntN_Xout = Lx_gnto.read()[0];
		LgntE_Xout = Lx_gnto.read()[1];
		LgntS_Xout = Lx_gnto.read()[2];
		LgntW_Xout = Lx_gnto.read()[3];

		Lx_roko[0] = Nrok;
		Lx_roko[1] = Erok;
		Lx_roko[2] = Srok;
		Lx_roko[3] = Wrok;
		sLx_reqo = Lx_reqo;
		sLx_roko = Lx_roko;

		Nx_reqo[0] = LreqN_Xout;
		Nx_reqo[1] = EreqN_Xout;
		Nx_reqo[2] = SreqN_Xout;
		Nx_reqo[3] = WreqN_Xout;
		NgntL_Xout = Nx_gnto.read()[0];
		NgntE_Xout = Nx_gnto.read()[1];
		NgntS_Xout = Nx_gnto.read()[2];
		NgntW_Xout = Nx_gnto.read()[3];

		Nx_roko[0] = Lrok;
		Nx_roko[1] = Erok;
		Nx_roko[2] = Srok;
		Nx_roko[3] = Wrok;
		sNx_reqo = Nx_reqo;
		sNx_roko = Nx_roko;

		Ex_reqo[0] = LreqE_Xout;
		Ex_reqo[1] = NreqE_Xout;
		Ex_reqo[2] = SreqE_Xout;
		Ex_reqo[3] = WreqE_Xout;
		EgntL_Xout = Ex_gnto.read()[0];
		EgntN_Xout = Ex_gnto.read()[1];
		EgntS_Xout = Ex_gnto.read()[2];
		EgntW_Xout = Ex_gnto.read()[3];

		Ex_roko[0] = Lrok;
		Ex_roko[1] = Nrok;
		Ex_roko[2] = Srok;
		Ex_roko[3] = Wrok;
		sEx_reqo = Ex_reqo;
		sEx_roko = Ex_roko;

		Sx_reqo[0] = LreqS_Xout;
		Sx_reqo[1] = NreqS_Xout;
		Sx_reqo[2] = EreqS_Xout;
		Sx_reqo[3] = WreqS_Xout;
		SgntL_Xout = Sx_gnto.read()[0];
		SgntN_Xout = Sx_gnto.read()[1];
		SgntE_Xout = Sx_gnto.read()[2];
		SgntW_Xout = Sx_gnto.read()[3];

		Sx_roko[0] = Lrok;
		Sx_roko[1] = Nrok;
		Sx_roko[2] = Erok;
		Sx_roko[3] = Wrok;
		sSx_reqo = Sx_reqo;
		sSx_roko = Sx_roko;

		Wx_reqo[0] = LreqW_Xout;
		Wx_reqo[1] = NreqW_Xout;
		Wx_reqo[2] = EreqW_Xout;
		Wx_reqo[3] = SreqW_Xout;
		WgntL_Xout = Wx_gnto.read()[0];
		WgntN_Xout = Wx_gnto.read()[1];
		WgntE_Xout = Wx_gnto.read()[2];
		WgntS_Xout = Wx_gnto.read()[3];

		Wx_roko[0] = Lrok;
		Wx_roko[1] = Nrok;
		Wx_roko[2] = Erok;
		Wx_roko[3] = Srok;
		sWx_reqo = Wx_reqo;
		sWx_roko = Wx_roko;
	}

	SC_CTOR(Router){

		Lin = new Xin("Lin");
		Lin->clk(clk);
		Lin->rst(rst);
		Lin->in_data(Lin_data);
		Lin->in_val(Lin_val);
		Lin->in_ret(Lin_ret);
		Lin->x_reqL(Lunused);
		Lin->x_reqN(LreqN_Xin);
		Lin->x_reqE(LreqE_Xin);
		Lin->x_reqS(LreqS_Xin);
		Lin->x_reqW(LreqW_Xin);
		Lin->x_rok(Lrok);
		Lin->x_rd(sLx_rdi);
		Lin->x_gnt(sLx_gnti);
		Lin->x_Lidle(Lidle);
		Lin->x_Nidle(Nidle);
		Lin->x_Eidle(Eidle);
		Lin->x_Sidle(Sidle);
		Lin->x_Widle(Widle);
		Lin->x_dout(Ldata);


		Nin = new Xin("Nin");
		Nin->clk(clk);
		Nin->rst(rst);
		Nin->in_data(Nin_data);
		Nin->in_val(Nin_val);
		Nin->in_ret(Nin_ret);
		Nin->x_reqL(NreqL_Xin);
		Nin->x_reqN(Nunused);
		Nin->x_reqE(NreqE_Xin);
		Nin->x_reqS(NreqS_Xin);
		Nin->x_reqW(NreqW_Xin);
		Nin->x_rok(Nrok);
		Nin->x_rd(sNx_rdi);
		Nin->x_gnt(sNx_gnti);
		Nin->x_Lidle(Lidle);
		Nin->x_Nidle(Nidle);
		Nin->x_Eidle(Eidle);
		Nin->x_Sidle(Sidle);
		Nin->x_Widle(Widle);
		Nin->x_dout(Ndata);


		Ein = new Xin("Ein");
		Ein->clk(clk);
		Ein->rst(rst);
		Ein->in_data(Ein_data);
		Ein->in_val(Ein_val);
		Ein->in_ret(Ein_ret);
		Ein->x_reqL(EreqL_Xin);
		Ein->x_reqN(EreqN_Xin);
		Ein->x_reqE(Eunused);
		Ein->x_reqS(EreqS_Xin);
		Ein->x_reqW(EreqW_Xin);
		Ein->x_rok(Erok);
		Ein->x_rd(sEx_rdi);
		Ein->x_gnt(sEx_gnti);
		Ein->x_Lidle(Lidle);
		Ein->x_Nidle(Nidle);
		Ein->x_Eidle(Eidle);
		Ein->x_Sidle(Sidle);
		Ein->x_Widle(Widle);
		Ein->x_dout(Edata);


		Sin = new Xin("Sin");
		Sin->clk(clk);
		Sin->rst(rst);
		Sin->in_data(Sin_data);
		Sin->in_val(Sin_val);
		Sin->in_ret(Sin_ret);
		Sin->x_reqL(SreqL_Xin);
		Sin->x_reqN(SreqN_Xin);
		Sin->x_reqE(SreqE_Xin);
		Sin->x_reqS(Sunused);
		Sin->x_reqW(SreqW_Xin);
		Sin->x_rok(Srok);
		Sin->x_rd(sSx_rdi);
		Sin->x_gnt(sSx_gnti);
		Sin->x_Lidle(Lidle);
		Sin->x_Nidle(Nidle);
		Sin->x_Eidle(Eidle);
		Sin->x_Sidle(Sidle);
		Sin->x_Widle(Widle);
		Sin->x_dout(Sdata);


		Win = new Xin("Win");
		Win->clk(clk);
		Win->rst(rst);
		Win->in_data(Win_data);
		Win->in_val(Win_val);
		Win->in_ret(Win_ret);
		Win->x_reqL(WreqL_Xin);
		Win->x_reqN(WreqN_Xin);
		Win->x_reqE(WreqE_Xin);
		Win->x_reqS(WreqS_Xin);
		Win->x_reqW(Wunused);
		Win->x_rok(Wrok);
		Win->x_rd(sWx_rdi);
		Win->x_gnt(sWx_gnti);
		Win->x_Lidle(Lidle);
		Win->x_Nidle(Nidle);
		Win->x_Eidle(Eidle);
		Win->x_Sidle(Sidle);
		Win->x_Widle(Widle);
		Win->x_dout(Wdata);


		Lout = new Xout("Lout");
		Lout->clk(clk);
		Lout->rst(rst);
		Lout->out_data(Lout_data);
		Lout->out_val(Lout_val);
		Lout->out_ret(Lout_ret);
		Lout->x_req(sLx_reqo);
		Lout->x_rok(sLx_roko);
		Lout->x_rd(Lrd);
		Lout->x_gnt(Lx_gnto);
		Lout->x_idle(Lidle);
		Lout->x_din0(Ndata);
		Lout->x_din1(Edata);
		Lout->x_din2(Sdata);
		Lout->x_din3(Wdata);


		Nout = new Xout("Nout");
		Nout->clk(clk);
		Nout->rst(rst);
		Nout->out_data(Nout_data);
		Nout->out_val(Nout_val);
		Nout->out_ret(Nout_ret);
		Nout->x_req(sNx_reqo);
		Nout->x_rok(sNx_roko);
		Nout->x_rd(Nrd);
		Nout->x_gnt(Nx_gnto);
		Nout->x_idle(Nidle);
		Nout->x_din0(Ldata);
		Nout->x_din1(Edata);
		Nout->x_din2(Sdata);
		Nout->x_din3(Wdata);


		Eout = new Xout("Eout");
		Eout->clk(clk);
		Eout->rst(rst);
		Eout->out_data(Eout_data);
		Eout->out_val(Eout_val);
		Eout->out_ret(Eout_ret);
		Eout->x_req(sEx_reqo);
		Eout->x_rok(sEx_roko);
		Eout->x_rd(Erd);
		Eout->x_gnt(Ex_gnto);
		Eout->x_idle(Eidle);
		Eout->x_din0(Ldata);
		Eout->x_din1(Ndata);
		Eout->x_din2(Sdata);
		Eout->x_din3(Wdata);


		Sout = new Xout("Sout");
		Sout->clk(clk);
		Sout->rst(rst);
		Sout->out_data(Sout_data);
		Sout->out_val(Sout_val);
		Sout->out_ret(Sout_ret);
		Sout->x_req(sSx_reqo);
		Sout->x_rok(sSx_roko);
		Sout->x_rd(Srd);
		Sout->x_gnt(Sx_gnto);
		Sout->x_idle(Sidle);
		Sout->x_din0(Ldata);
		Sout->x_din1(Ndata);
		Sout->x_din2(Edata);
		Sout->x_din3(Wdata);


		Wout = new Xout("Wout");
		Wout->clk(clk);
		Wout->rst(rst);
		Wout->out_data(Wout_data);
		Wout->out_val(Wout_val);
		Wout->out_ret(Wout_ret);
		Wout->x_req(sWx_reqo);
		Wout->x_rok(sWx_roko);
		Wout->x_rd(Wrd);
		Wout->x_gnt(Wx_gnto);
		Wout->x_idle(Widle);
		Wout->x_din0(Ldata);
		Wout->x_din1(Ndata);
		Wout->x_din2(Edata);
		Wout->x_din3(Sdata);


		X0 = new X("X0");

		X0->LreqN_in(LreqN_Xin);
		X0->LreqE_in(LreqE_Xin);
		X0->LreqS_in(LreqS_Xin);
		X0->LreqW_in(LreqW_Xin);

		X0->LreqN_out(LreqN_Xout);
		X0->LreqE_out(LreqE_Xout);
		X0->LreqS_out(LreqS_Xout);
		X0->LreqW_out(LreqW_Xout);

		X0->NreqL_in(NreqL_Xin);
		X0->NreqE_in(NreqE_Xin);
		X0->NreqS_in(NreqS_Xin);
		X0->NreqW_in(NreqW_Xin);

		X0->NreqL_out(NreqL_Xout);
		X0->NreqE_out(NreqE_Xout);
		X0->NreqS_out(NreqS_Xout);
		X0->NreqW_out(NreqW_Xout);

		X0->EreqL_in(EreqL_Xin);
		X0->EreqN_in(EreqN_Xin);
		X0->EreqS_in(EreqS_Xin);
		X0->EreqW_in(EreqW_Xin);

		X0->EreqL_out(EreqL_Xout);
		X0->EreqN_out(EreqN_Xout);
		X0->EreqS_out(EreqS_Xout);
		X0->EreqW_out(EreqW_Xout);

		X0->SreqL_in(SreqL_Xin);
		X0->SreqN_in(SreqN_Xin);
		X0->SreqE_in(SreqE_Xin);
		X0->SreqW_in(SreqW_Xin);

		X0->SreqL_out(SreqL_Xout);
		X0->SreqN_out(SreqN_Xout);
		X0->SreqE_out(SreqE_Xout);
		X0->SreqW_out(SreqW_Xout);

		X0->WreqL_in(WreqL_Xin);
		X0->WreqN_in(WreqN_Xin);
		X0->WreqE_in(WreqE_Xin);
		X0->WreqS_in(WreqS_Xin);

		X0->WreqL_out(WreqL_Xout);
		X0->WreqN_out(WreqN_Xout);
		X0->WreqE_out(WreqE_Xout);
		X0->WreqS_out(WreqS_Xout);

		X0->LgntN_in(LgntN_Xout);
		X0->LgntE_in(LgntE_Xout);
		X0->LgntS_in(LgntS_Xout);
		X0->LgntW_in(LgntW_Xout);

		X0->LgntN_out(LgntN_Xin);
		X0->LgntE_out(LgntE_Xin);
		X0->LgntS_out(LgntS_Xin);
		X0->LgntW_out(LgntW_Xin);

		X0->NgntL_in(NgntL_Xout);
		X0->NgntE_in(NgntE_Xout);
		X0->NgntS_in(NgntS_Xout);
		X0->NgntW_in(NgntW_Xout);

		X0->NgntL_out(NgntL_Xin);
		X0->NgntE_out(NgntE_Xin);
		X0->NgntS_out(NgntS_Xin);
		X0->NgntW_out(NgntW_Xin);

		X0->EgntL_in(EgntL_Xout);
		X0->EgntN_in(EgntN_Xout);
		X0->EgntS_in(EgntS_Xout);
		X0->EgntW_in(EgntW_Xout);

		X0->EgntL_out(EgntL_Xin);
		X0->EgntN_out(EgntN_Xin);
		X0->EgntS_out(EgntS_Xin);
		X0->EgntW_out(EgntW_Xin);

		X0->SgntL_in(SgntL_Xout);
		X0->SgntN_in(SgntN_Xout);
		X0->SgntE_in(SgntE_Xout);
		X0->SgntW_in(SgntW_Xout);

		X0->SgntL_out(SgntL_Xin);
		X0->SgntN_out(SgntN_Xin);
		X0->SgntE_out(SgntE_Xin);
		X0->SgntW_out(SgntW_Xin);

		X0->WgntL_in(WgntL_Xout);
		X0->WgntN_in(WgntN_Xout);
		X0->WgntE_in(WgntE_Xout);
		X0->WgntS_in(WgntS_Xout);

		X0->WgntL_out(WgntL_Xin);
		X0->WgntN_out(WgntN_Xin);
		X0->WgntE_out(WgntE_Xin);
		X0->WgntS_out(WgntS_Xin);



		SC_METHOD(sliced_bits);
		sensitive << Lrd << Nrd << Erd << Srd << Wrd

		<< NgntL_Xin << EgntL_Xin << SgntL_Xin << WgntL_Xin
		<< LgntN_Xin << EgntN_Xin << SgntN_Xin << WgntN_Xin
		<< LgntE_Xin << NgntE_Xin << SgntE_Xin << WgntE_Xin
		<< LgntS_Xin << NgntS_Xin << EgntS_Xin << WgntS_Xin
		<< LgntW_Xin << NgntW_Xin << EgntW_Xin << SgntW_Xin

		<< Lrok << Nrok << Erok << Srok << Wrok
		
		<< NreqL_Xout << EreqL_Xout << SreqL_Xout << WreqL_Xout
		<< LreqN_Xout << EreqN_Xout << SreqN_Xout << WreqN_Xout
		<< LreqE_Xout << NreqE_Xout << SreqE_Xout << WreqE_Xout
		<< LreqS_Xout << NreqS_Xout << EreqS_Xout << WreqS_Xout
		<< LreqW_Xout << NreqW_Xout << EreqW_Xout << SreqW_Xout
	
		<< Lx_gnto << Nx_gnto << Ex_gnto << Sx_gnto << Wx_gnto;
	}

	~Router(){
		delete Lin;
		delete Nin;
		delete Ein;
		delete Sin;
		delete Win;
		delete Lout;
		delete Nout;
		delete Eout;
		delete Sout;
		delete Wout;
		delete X0;
	}

};