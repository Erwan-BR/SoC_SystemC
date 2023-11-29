#include <systemc.h>
#include "../global/gdr.h"
#include "../global/sc_image.h"
#include "./sc_gh_1D.h"
#include "../global/main_header.h"

int sc_main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf("Arguments incorrects \n"); 
		printf("Usage : %s image_in  image_out\n", argv[0]); 
		return 1;
	}
	// Exporter nom du fichier image
	strcpy(FichierIn, argv[1]); 
	strcpy(FichierOut, argv[2]);

	// Si argument => Creer un objet image GDR
	ENTETE_GDR EnteteImageIn(argv[1]);
	unsigned NbrePixel=EnteteImageIn.NbPixel();


	sc_signal <bool> pckout; // Clock Pixel
	sc_signal <bool> reset;
	sc_signal <sc_uint<8> > pixel_in, pixel_out;
	sc_signal <bool> sh, sv, blank;
	
	// Utiles pour la sauvegarde de l'image
	sc_signal <bool> bk_out, hpix_out;

	// Modelisation CYCLOPE
	image image1("image");
	image1.reset(reset);
	image1.bk_out(bk_out); // valider la sauvegarde de l'image
	image1.hpix_out(hpix_out); // valider la sauvegarde de l'image

	// Signaux utiles
	image1.sh(sh);
	image1.sv(sv);
	image1.blank(blank);
	image1.pckout(pckout);
	image1.pixel_in(pixel_in);  	
	image1.pixel_out(pixel_out);  	
	// END Modele cyclope

	// Traitement du gradient horizontal 1D de l'image.
	gh_1D gh_1D1("gh_1D");
	gh_1D1.reset(reset);
	gh_1D1.blank(blank);
	gh_1D1.clk(pckout);
	gh_1D1.pixel_in(pixel_in);
	gh_1D1.pixel_out(pixel_out);
	gh_1D1.hpix_out(hpix_out);
	gh_1D1.bk_out(bk_out);

	//<Begin TRACE>
	sc_trace_file *tf = sc_create_vcd_trace_file("image");
	sc_trace(tf, pckout, "HPIXEL");
	sc_trace(tf, reset, "RESET");
	sc_trace(tf, sh, "SH");
	sc_trace(tf, sv, "SV");
	sc_trace(tf, blank, "BLANK");
	sc_trace(tf, pixel_in, "PIXEL_IN");
	sc_trace(tf, pixel_out,"PIXEL_OUT");
	//<End TRACE>

	reset = 0; 
	sc_start(10, SC_NS);
	
	reset = 1;
	sc_start(); // Lancement de la simulation

	sc_close_vcd_trace_file(tf);

	affiche_image (argv[1], 200, 0);// Afficher l'image d'entree
	affiche_image (argv[2], 500, 0);// Afficher l'image resultat

	// Afficher les chrons sous Visual C++
	//WinExec("gtkwave image.vcd", 1);	
	
	// Afficher les chrons sous UNIX
	//int STATUS = system("gtkwave image.vcd &");	// Afficher les chrons

	exit(0);
}
