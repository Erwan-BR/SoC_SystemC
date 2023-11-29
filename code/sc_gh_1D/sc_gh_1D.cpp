/////////////////////////////////////////////////////////////
// Filename : sc_gh_1D.cpp
// Author   : Erwan BROUDIN, Adrien MILLASSEAU
// Company  : ENSEA
// Comment  : Coder le traitement du gradient horizontal 1D image
/////////////////////////////////////////////////////////////
#include "./sc_gh_1D.h"

/// @brief Traitement d'un pixel pour le gradient horizontal 1D.
void gh_1D::gh_1D_trait()
{
    int pix_tmp = 0;
	
	if (reset.read() == 0) // reset
	{
		pix_tmp = 0; 
	}
	else if(blank.read() == 1)
	{
		int currentValue = pixel_in.read();
		
		// On prend une fois la valeur précédente, et on actualise la valeur précédente.
		pix_tmp = previousValue;
		previousValue = currentValue;

		// On retire la valeur actuelle.
		pix_tmp -= currentValue;

		// On prend la valeur absolue afin de voir le passage de clair a sombre mais aussi de sombre a clair.
		pix_tmp = abs(pix_tmp);

		// On s'assure que pix_tmp est compris entre 0 et 255.
		if (pix_tmp > 255)
		{
			pix_tmp = 255;
		}
		else if (pix_tmp < 0)
		{
			pix_tmp = 0;
		}
	}
	// Ecrire la sortie sur le port pixel_out
    pixel_out.write(pix_tmp);
}

/// @brief Generation des synchronisations en sortie.
void gh_1D::synchro_out()
{
	// Laisser passer les controles
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}
