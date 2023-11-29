#include <systemc.h>
#include "./gdr.h"

#ifndef IMAGE_H
#define IMAGE_H

#define N_PIX 256
#define TCLK 100
#define TCLK_2 TCLK/2
#define TBLK N_PIX*TCLK
#define TOSH 7*TCLK // Vraie valeur = 47
#define TSH2 5*TCLK	// Vraie valeur = 65
#define TSH1 6*TCLK	// Vraie valeur = 16
#define TSH	 TOSH+TSH1+TSH2+TBLK
#define TrSV 68		// 68 ns
#define TPIX 36		// 36 ns	
#define TrBLK 16	// 16 ns
#define TrSH 28		// 28 ns

#define N55 1 // 55 -- 1
#define N56 2 // 56 -- 2

//////////////////////////////////////
// Declare dans main (ne pas modifier 
   extern char FichierIn[100],FichierOut[100];
// Jusqu'ici (ne pas modifier)
//////////////////////////////////////
SC_MODULE (image)
{
	sc_in <bool> reset;

	sc_out <bool> pckout;	// Horloge Pixel
	sc_out <bool> sv;
	sc_out <bool> sh;
	sc_out <bool> blank;
	sc_out <sc_uint<8> > pixel_in;
	
	// Pour la suvegarde du resultat
	sc_in <sc_uint<8> > pixel_out;
	sc_in <bool> bk_out; // valide le resultat
	sc_in <bool> hpix_out;

	ENTETE_GDR EnteteIn, *EnteteOut;
	unsigned Nx, Ny;	// nb pixels par ligne et nb lignes
	unsigned NbrePixel;

	unsigned char *pixel_rd, *pixel_wr;
	unsigned index, index_save;

	void synch_out();
	void horloge_out();
	void get_result();

	SC_CTOR(image)
	{
		SC_THREAD (horloge_out);
		sensitive << reset;

		SC_THREAD (synch_out);
		sensitive << reset;

		SC_METHOD (get_result);
		sensitive << hpix_out.pos();

		EnteteIn.Lire_Entete_From_File(FichierIn);
		NbrePixel = EnteteIn.NbPixel();
		Nx = EnteteIn.NbLigne();
		Ny = EnteteIn.NbColonne();

		EnteteOut = new ENTETE_GDR(EnteteIn);

		pixel_rd = (unsigned char *) malloc(NbrePixel);		
		pixel_wr = (unsigned char *) malloc(NbrePixel);

		if(!pixel_rd || !pixel_wr) 
		{ 
			printf("Erreur de malloc \n");
			exit(-1);
		}

		EnteteIn.Pixel_From_File (FichierIn, pixel_rd);
		EnteteIn.Affiche();	/* affiche l'entete */
		index_save=0;
		index = 0; 
	}
};

#endif
