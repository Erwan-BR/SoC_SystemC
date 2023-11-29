#include <systemc.h>
#include "../global/gdr.h"

#ifndef GH_1D_H
#define GH_1D_H

/////////////////////
SC_MODULE (gh_1D)
{
	sc_in <bool> clk;
	sc_in <bool> reset;
	sc_in <bool> blank;
	sc_in <sc_uint<8> > pixel_in;
	sc_out <sc_uint<8> > pixel_out;

	sc_out <bool> bk_out;
	sc_out <bool> hpix_out;

	// Stockage de la valeur precedente pour la recuperer pour le pixel suivant.
	int previousValue;

	void gh_1D_trait(void);
	void synchro_out(void);
	SC_CTOR(gh_1D)
	{
		previousValue = 0;

		SC_METHOD(gh_1D_trait);
		sensitive << clk.pos(); 

		SC_METHOD(synchro_out);
		sensitive << clk; // sans pos() pour generer l'horloge en sortie
	}
};

#endif
