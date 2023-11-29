/////////////////////////////////////////////////////////////
// Filename : sc_gv_2D.cpp
// Author   : Erwan BROUDIN, Adrien MILLASSEAU
// Company  : ENSEA
// Comment  : Coder le traitement du gradient vertical 2D de l'image
/////////////////////////////////////////////////////////////
#include "./sc_gv_2D.h"

/// @brief Traitement d'un pixel pour le gradient vertical 2D.
void gv_2D::gv_2D_trait()
{
	int pix_tmp = 0;
	
	if (reset.read() == 0) // reset
	{
		pix_tmp = 0; 
	}
	else if(blank.read() == 1)
	{
		int currentValue = pixel_in.read();

		// On ne traite pas la premiere colonne 
		if (curentColonneIndex > 0)
		{
			// Calcul 2D
			pix_tmp = abs(previousPixel + colonne[curentColonneIndex] - currentValue);
		}
		
		// Stockage de la difference des pixels pour la prochaine iteration.
		previousPixel = colonne[curentColonneIndex] - currentValue;
		// Mise a jour de la FIFO
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

		// Augmenter l'index pour lire la bonne valeur de la FIFO (la derniere)
		curentColonneIndex++;
	}
	// Ecrire la sortie sur le port pixel_out
	pixel_out.write(pix_tmp);
}

/// @brief Generation des synchronisations en sortie
void gv_2D::synchro_out()
{
	// Laisser passer les controles
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}

/// @brief Si on depasse la valeur limite, on remet l'index a 0 pour rendre la FIFO circulaire.
void gv_2D::filtre_sh()
{
	curentColonneIndex = 0;
}