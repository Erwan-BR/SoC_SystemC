#include <systemc.h>
#include "../global/gdr.h"

#ifndef SEUIL_H
#define SEUIL_H

// Recuperation des variables globales
extern int nombreColonnes;
extern int valeurSeuil;

/////////////////////
SC_MODULE (seuil)
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

	// Valeur pour les deux gradient
	int colonneIndex;

	// Valeurs pour le gradient horizontal
	int* colonneH;
	int previousPixelH;

	// Valeurs pour le gradient vertical
	int* colonneV;
	int previousPixelV;

	void seuil_trait(void);
	void synchro_out(void);
	void filtre_sh();
	SC_CTOR(seuil)
	{
		// Intialisation des FIFO et des variables
		colonneH = new int[nombreColonnes];
		colonneV = new int[nombreColonnes];

		colonneIndex = 0;
		previousPixelH = 0;
		previousPixelV = 0;

		SC_METHOD(seuil_trait);
		sensitive << clk.pos(); 

		SC_METHOD(synchro_out);
		sensitive << clk; // sans pos() pour generer l'horloge en sortie

		// Circularite de la FIFO.
		SC_METHOD(filtre_sh);
		sensitive << sh.pos();
	}
};

#endif
