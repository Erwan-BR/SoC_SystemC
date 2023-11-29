#include <systemc.h>
#include "../global/gdr.h"

#ifndef GV_2D_H
#define GV_2D_H

// Recuperation du nombre de colonnes pour la taille de la FIFO.
extern int nombreColonnes;

/////////////////////
SC_MODULE (gv_2D)
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

	// Creation de la FIFO, l'index et la valeur precedente.
	int* colonne;
	int curentColonneIndex;
	int previousPixel;

	void gv_2D_trait(void);
	void synchro_out(void);
	void filtre_sh();
	SC_CTOR(gv_2D)
	{
		// Initialisation des variables
		colonne = new int[nombreColonnes];
		curentColonneIndex = 0;
		previousPixel = 0;
		
		SC_METHOD(gv_2D_trait);
		sensitive << clk.pos(); 

		SC_METHOD(synchro_out);
		sensitive << clk; // sans pos() pour generer l'horloge en sortie

		// Circularite de la FIFO.
		SC_METHOD(filtre_sh);
		sensitive << sh.pos();
	}
};

#endif
