/////////////////////////////////////////////////////////////
// Filename : sc_seuil.cpp
// Author   : Erwan BROUDIN, Adrien MILLASSEAU
// Company  : ENSEA
// Comment  : Coder le traitement du gradient complet avec un seuil de l'image
/////////////////////////////////////////////////////////////
#include "./sc_seuil.h"
#include <iostream>
#include <stdlib.h>

/// @brief Traitement d'un pixel pour le gradient avec un seuil
void seuil::seuil_trait()
{
    int pix_tmp = 0;
	
	if (reset.read() == 0) // reset
	{
		pix_tmp = 0; 
	}
	else if(blank.read() == 1)
	{
		int currentValue = pixel_in.read();
		
		// Calcul du gradient 2D horizontal
		int gradHValue = 0;
		if (colonneIndex > 0)
		{
			gradHValue = abs(previousPixelH - colonneH[colonneIndex] - currentValue);
		}
		// Mise a jour du pixel stocke et de la FIFO horizontale
		previousPixelH = colonneH[colonneIndex] + currentValue;
		colonneH[colonneIndex] = currentValue;

		// Calcul du gradient 2D vertical
		int gradVValue = 0;
		if (colonneIndex > 0)
		{
			gradVValue = abs(previousPixelV + colonneV[colonneIndex] - currentValue);
		}
		// Mise a jour du pixel stocke et de la FIFO verticale
		previousPixelV = colonneV[colonneIndex] - currentValue;
		colonneV[colonneIndex] = currentValue;

		// Calcul des 3/4 de la somme
		int troisieme = 0.75 * (gradHValue + gradVValue);

		// Selection du max (Approximation de la norme)
		pix_tmp = std::max({gradHValue, gradVValue, troisieme});	

		// On s'assure que pix_tmp est compris entre 0 et 255.
		if (pix_tmp > 255)
		{
			pix_tmp = 255;
		}
		// On place le seuil a la valeur indiquée par l'utilisateur.
		else if (pix_tmp < valeurSeuil)
		{
			pix_tmp = 0;
		}

		// Augmenter l'index pour lire la bonne valeur de la FIFO (la derniere)
		colonneIndex++;
	}
	// Ecrire la sortie sur le port pixel_out
    pixel_out.write(pix_tmp);
}

/// @brief Generation des synchronisations en sortie
void seuil::synchro_out()
{
	// Laisser passer les controles
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}

/// @brief Si on depasse la valeur limite, on remet l'index a 0 pour rendre la FIFO circulaire.
void seuil::filtre_sh()
{
	colonneIndex = 0;
}