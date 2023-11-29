/////////////////////////////////////////////////////////////
// Filename : sc_gv_1D.cpp
// Author   : Erwan BROUDIN, Adrien MILLASSEAU
// Company  : ENSEA
// Comment  : Coder le traitement du gradient vertical 1D de l'image
/////////////////////////////////////////////////////////////
#include "./sc_gv_1D.h"
#include <stdlib.h>

/// @brief Traitement d'un pixel pour le gradient vertical 1D.
void gv_1D::gv_1D_trait()
{
    int pix_tmp = 0;
	
	if (reset.read() == 0) // reset
	{
		pix_tmp = 0; 
	}
	else if(blank.read() == 1)
	{
		int currentValue = pixel_in.read();
        
		// On prend une fois la valeur précédente depuis la FIFO, et on retire l'actuelle.
		pix_tmp = abs(colonne[curentColonneIndex] - currentValue);
		
		// Actualisation de la FIFO.
		colonne[curentColonneIndex] = currentValue;

		// On s'assure que pix_tmp est compris entre 0 et 255.
		if (pix_tmp > 255)
		{
			pix_tmp = 255;
		}
		else if (pix_tmp < 0)
		{
			pix_tmp = 0;
		}
		
		// Augmenter l'index pour la FIFO
		curentColonneIndex++;
	}
	// Ecrire la sortie sur le port pixel_out
    pixel_out.write(pix_tmp);
}

/// @brief Generation des synchronisations en sortie
void gv_1D::synchro_out()
{
	// Laisser passer les controles
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}

/// @brief Si on depasse la valeur limite, on remet l'index a 0 pour que la FIFO soit circulaire.
void gv_1D::filtre_sh()
{
	curentColonneIndex = 0;
}