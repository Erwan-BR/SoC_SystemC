#include <systemc.h>
#include "../global/gdr.h"

#ifndef ROBERTS_H
#define ROBERTS_H

// Recuperation du nombre de colonnes pour la taille de la FIFO.
extern int nombreColonnes;

/////////////////////
SC_MODULE (roberts)
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

	// FIFO pour Roberts horizontal et vertical, index de la colonne
	int* premiereFifo;
	int* deuxiemeFifo;

	int colonneIndex;

	void roberts_trait(void);
	void synchro_out(void);
	void filtre_sh();
	SC_CTOR(roberts)
	{
		// Initialisation des variables
		premiereFifo = new int[nombreColonnes];
		deuxiemeFifo = new int[nombreColonnes];

		colonneIndex = 0;

		SC_METHOD(roberts_trait);
		sensitive << clk.pos(); 

		SC_METHOD(synchro_out);
		sensitive << clk; // sans pos() pour generer l'horloge en sortie

		// Circularite de la FIFO.
		SC_METHOD(filtre_sh);
		sensitive << sh.pos();
	}
};

#endif
