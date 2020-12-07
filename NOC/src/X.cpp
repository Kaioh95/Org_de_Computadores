#include <systemc.h>

/**
* @file X.cpp
* @details Uma matriz que permite a implementação
* do roteador com base no tipo de algoritmo de roteamento
* a ser usado.  
* @author Kaio Henrique de Sousa
* @since 03/12/2020
*/

SC_MODULE(X){
	sc_in< bool > LreqN_in;
	sc_in< bool > LreqE_in;
	sc_in< bool > LreqS_in;
	sc_in< bool > LreqW_in;

	sc_out< bool > LreqN_out;
	sc_out< bool > LreqE_out;
	sc_out< bool > LreqS_out;
	sc_out< bool > LreqW_out;

	sc_in< bool > NreqL_in;
	sc_in< bool > NreqE_in;
	sc_in< bool > NreqS_in;
	sc_in< bool > NreqW_in;

	sc_out< bool > NreqL_out;
	sc_out< bool > NreqE_out;
	sc_out< bool > NreqS_out;
	sc_out< bool > NreqW_out;

	sc_in< bool > EreqL_in;
	sc_in< bool > EreqN_in;
	sc_in< bool > EreqS_in;
	sc_in< bool > EreqW_in;

	sc_out< bool > EreqL_out;
	sc_out< bool > EreqN_out;
	sc_out< bool > EreqS_out;
	sc_out< bool > EreqW_out;

	sc_in< bool > SreqL_in;
	sc_in< bool > SreqN_in;
	sc_in< bool > SreqE_in;
	sc_in< bool > SreqW_in;

	sc_out< bool > SreqL_out;
	sc_out< bool > SreqN_out;
	sc_out< bool > SreqE_out;
	sc_out< bool > SreqW_out;

	sc_in< bool > WreqL_in;
	sc_in< bool > WreqN_in;
	sc_in< bool > WreqE_in;
	sc_in< bool > WreqS_in;

	sc_out< bool > WreqL_out;
	sc_out< bool > WreqN_out;
	sc_out< bool > WreqE_out;
	sc_out< bool > WreqS_out;

	sc_in< bool > LgntN_in;
	sc_in< bool > LgntE_in;
	sc_in< bool > LgntS_in;
	sc_in< bool > LgntW_in;

	sc_out< bool > LgntN_out;
	sc_out< bool > LgntE_out;
	sc_out< bool > LgntS_out;
	sc_out< bool > LgntW_out;

	sc_in< bool > NgntL_in;
	sc_in< bool > NgntE_in;
	sc_in< bool > NgntS_in;
	sc_in< bool > NgntW_in;

	sc_out< bool > NgntL_out;
	sc_out< bool > NgntE_out;
	sc_out< bool > NgntS_out;
	sc_out< bool > NgntW_out;

	sc_in< bool > EgntL_in;
	sc_in< bool > EgntN_in;
	sc_in< bool > EgntS_in;
	sc_in< bool > EgntW_in;

	sc_out< bool > EgntL_out;
	sc_out< bool > EgntN_out;
	sc_out< bool > EgntS_out;
	sc_out< bool > EgntW_out;

	sc_in< bool > SgntL_in;
	sc_in< bool > SgntN_in;
	sc_in< bool > SgntE_in;
	sc_in< bool > SgntW_in;

	sc_out< bool > SgntL_out;
	sc_out< bool > SgntN_out;
	sc_out< bool > SgntE_out;
	sc_out< bool > SgntW_out;

	sc_in< bool > WgntL_in;
	sc_in< bool > WgntN_in;
	sc_in< bool > WgntE_in;
	sc_in< bool > WgntS_in;

	sc_out< bool > WgntL_out;
	sc_out< bool > WgntN_out;
	sc_out< bool > WgntE_out;
	sc_out< bool > WgntS_out;

	void xy_routing(){

		LreqN_out = LreqN_in;
		LreqE_out = LreqE_in;
	    LreqS_out = LreqS_in;
	    LreqW_out = LreqW_in;

		NreqL_out = NreqL_in;
		NreqE_out = '0';
		NreqS_out = NreqS_in;
		NreqW_out = '0';

		EreqL_out = EreqL_in;
		EreqN_out = EreqN_in;
		EreqS_out = EreqS_in;
		EreqW_out = EreqW_in;

		SreqL_out = SreqL_in;
		SreqN_out = SreqN_in;
		SreqE_out = '0';
		SreqW_out = '0';

		WreqL_out = WreqL_in;
		WreqN_out = WreqN_in;
		WreqE_out = WreqE_in;
		WreqS_out = WreqS_in;

		LgntN_out = LgntN_in;
		LgntE_out = LgntE_in;
		LgntS_out = LgntS_in;
		LgntW_out = LgntW_in;

		NgntL_out = NgntL_in;
		NgntE_out = NgntE_in;
		NgntS_out = NgntS_in;
		NgntW_out = NgntW_in;

		EgntL_out = EgntL_in; 
		EgntN_out = '0';
		EgntS_out = '0';
		EgntW_out = EgntW_in;

		SgntL_out = SgntL_in;
		SgntN_out = SgntN_in;
		SgntE_out = SgntE_in;
		SgntW_out = SgntW_in;

		WgntL_out = WgntL_in;
		WgntN_out = '0';
		WgntE_out = WgntE_in;
		WgntS_out = '0';

	}

	SC_CTOR(X){
		SC_METHOD(xy_routing);
		sensitive << LreqN_in << LreqE_in << LreqS_in << LreqW_in
		<< NreqL_in << NreqS_in
		<< EreqL_in << EreqN_in << EreqS_in << EreqW_in
		<< LreqN_in << LreqE_in << LreqS_in << LreqW_in
		<< SreqL_in << SreqN_in
		<< WreqL_in << WreqN_in << WreqE_in << WreqS_in
		
		<< LgntN_in << LgntE_in << LgntS_in << LgntW_in
		<< NgntL_in << NgntE_in << NgntS_in << NgntW_in
		<< EgntL_in << EgntW_in
		<< SgntL_in << SgntN_in << SgntE_in << SgntW_in
		<< WgntL_in << WgntE_in;

	}

};