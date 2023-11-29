/////////////////////////////////////////////////////////////
// Filename : sc_image.cpp
// Author   : Lounis KESSAL 
// Company  : ENSEA
// Comment  : Generer les stimulis ==> modeliser cyclope
/////////////////////////////////////////////////////////////
#include "./sc_image.h"

//*************************************************
// horloge_out: sortir horloge pixel              *
//*************************************************
void image::horloge_out()
{
	if (reset.read() == 1) 
	{
		index=0;
 		pckout =  0;
	}
	// Generation de l'horloge pixel
	while(true)
	{	
		pckout =  0; wait(TCLK_2, SC_NS);

		pckout = 1; wait(TCLK_2, SC_NS);
	}
}

//*******************************************************
// sych_out : sortir les signaux SH, SV, BLANK et PIXEL *
//*******************************************************
void image::synch_out()
{
	unsigned int i,j;
	// reset
	if (reset.read() == 0)
	{
		sh =  1;
		sv =  1;
		blank =  0;
	}
	
	// Generation des signaux CYCLOPE
	while(true)
	{	
		// synchronisation SV et SH 
		sv =  1;
		for(i=0; i<=N55; i++)
		{
			sh = 1; blank = 0; wait(TrSH, SC_NS);

			sh = 0; wait(TOSH, SC_NS);

			sh = 1; 
			wait(TSH2, SC_NS);
			wait(TBLK, SC_NS);
			wait(TSH1-TrSH, SC_NS);

			sv = 0;
		}
		sv = 1;
		
		// activation du blank, lignes paires 0,2,...
		for(i=0; i<Ny/2; i++)
		{
			sh = 1; 
			wait(TrSH, SC_NS);

			sh = 0;
			wait(TOSH, SC_NS);
			
			sh = 1;
			wait(TSH2-TrSH, SC_NS);
			wait(TrBLK, SC_NS);
			
			blank =  1;
			wait(TPIX-TrBLK, SC_NS);

	
			// Envoie des pixels 
			for(j=0; j<Nx; j++)
			{
				pixel_in.write(pixel_rd[index]);
				wait(TCLK, SC_NS);
				index++;
			}

			blank =  0;
			wait(TSH1-TPIX, SC_NS);
		} // end loop
	
		// Deuxieme synchronisation Verticale, lignes imapires
		sv =  1;
		for(i=0; i<=N56; i++)
		{
			sh = 1;
			blank = 0;
			wait(TrSH, SC_NS);

			sh = 0;
			wait(TOSH, SC_NS);

			sh = 1;
			wait(TSH2, SC_NS);
			wait(TBLK, SC_NS);
			wait(TSH1-TrSH, SC_NS);

			sv = 0;
		} // end loop
		sv = 1;

		// activation du blank, lignes impaires 1,3,...
		for(i=0; i<Ny/2; i++)
		{
			sh = 1;
			wait(TrSH, SC_NS);

			sh = 0;
			wait(TOSH, SC_NS);

			sh = 1;
			wait(TSH2-TrSH, SC_NS);
			wait(TrBLK, SC_NS);

			blank =  1;
			wait(TPIX-TrBLK, SC_NS);//

			// Envoie des pixels 
			for(j=0; j<Nx; j++)
			{
				pixel_in.write(pixel_rd[index]);
				wait(TCLK, SC_NS);//
				index++;
			}

			blank =  0;
			wait(TSH1-TPIX, SC_NS);
		} // end loop
	}
}
//**********************************************
// get_result : ecrire les pixels dans tab_result
//**********************************************
void image::get_result()
{
	if(bk_out.read() == 1)
	{
		pixel_wr[index_save]=pixel_out.read();
		index_save++;

	    if(index_save >= NbrePixel) // Si fin de trait. ==> STOP simulation 
	    {
	    	EnteteOut->save (FichierOut, pixel_wr);
 	    	sc_stop();
	    	printf("Sauvegarde du resultat dans %s\n", FichierOut); 
	    }	
	}
}
