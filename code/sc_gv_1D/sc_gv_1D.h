#include <systemc.h>
#include "../global/gdr.h"

#ifndef GV_1D_H
#define GV_1D_H

// Recuperation du nombre de colonnes pour la taille de la FIFO.
extern int nombreColonnes;

/////////////////////
SC_MODULE (gv_1D)
{
	sc_in <bool> clk;
	sc_in <bool> reset;
	sc_in <bool> blank;
	// Besoin de la synchronisation horizontale
	sc_in <bool> sh;
	sc_in <sc_uint<8> > pixel_in;
	sc_out <sc_uint<8> > pixel_out;

	sc_out <bool> bk_out;
	sc_out <bool> hpix_out;

	// FIFO et l'index auquel on regarde (dernier element toujours)
	int* colonne;
	int curentColonneIndex;

	void gv_1D_trait();
	void synchro_out();
	void filtre_sh();
	SC_CTOR(gv_1D)
	{
		// Initialisation des variables
		colonne = new int[nombreColonnes];
		curentColonneIndex = 0;

		SC_METHOD(gv_1D_trait);
		sensitive << clk.pos(); 

		SC_METHOD(synchro_out);
		sensitive << clk; // sans pos() pour generer l'horloge en sortie

		// Circularite de la FIFO.
		SC_METHOD(filtre_sh);
		sensitive << sh.pos();
	}
};

#endif
