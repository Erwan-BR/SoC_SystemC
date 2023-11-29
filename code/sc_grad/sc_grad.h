#include <systemc.h>
#include "../global/gdr.h"

#ifndef GRAD_H
#define GRAD_H

// Recuperation du nombre de colonnes pour la taille de la FIFO.
extern int nombreColonnes;

/////////////////////
SC_MODULE (grad)
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

	// Valeur pour les deux gradients
	int colonneIndex;

	// Valeurs pour le gradient horizontal
	int* colonneH;
	int previousPixelH;

	// Valeurs pour le gradient vertical
	int* colonneV;
	int previousPixelV;

	void grad_trait(void);
	void synchro_out(void);
	void filtre_sh();
	SC_CTOR(grad)
	{
		// Initialisation des deux FIFO et des variables.
		colonneH = new int[nombreColonnes];
		colonneV = new int[nombreColonnes];

		colonneIndex = 0;
		previousPixelH = 0;
		previousPixelV = 0;

		SC_METHOD(grad_trait);
		sensitive << clk.pos(); 

		SC_METHOD(synchro_out);
		sensitive << clk; // sans pos() pour generer l'horloge en sortie

		// Circularite de la FIFO.
		SC_METHOD(filtre_sh);
		sensitive << sh.pos();
	}
};

#endif
