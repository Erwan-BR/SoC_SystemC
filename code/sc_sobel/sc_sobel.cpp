/////////////////////////////////////////////////////////////
// Filename : sc_sobel.cpp
// Author   : Erwan BROUDIN, Adrien MILLASSEAU
// Company  : ENSEA
// Comment  : Coder le traitement du de l'image a travers le masque de Sobel
/////////////////////////////////////////////////////////////
#include "./sc_sobel.h"
#include <iostream>
#include <stdlib.h>

/// @brief Realise le traitement d'un pixel pour le masque de Sobel (horizontal et vertical)
void sobel::sobel_trait()
{
    int pix_tmp = 0;
	
	if (reset.read() == 0) // reset
	{
		pix_tmp = 0;
	}
	else if(blank.read() == 1)
	{
        int currentValue = pixel_in.read();

		// Variables stockes en mmoire d'un appel a l'autre
		static int var1_H = 0, var2_H = 0;
		static int var1_V = 0, var2_V = 0;

		// Calcul de Sobel horizontal et vertical
		int sobelHValue = 0, sobelVValue = 0;
		int outHValue = 0, outVValue = 0;
		
		// On evite les deux premieres colonnes pour les effets de bord
		if (colonneIndex > 1)
		{
			// Calcul des matrices lignes / colonnes
			sobelHValue = currentValue + 2 * premiereFifo[colonneIndex] + deuxiemeFifo[colonneIndex];
			sobelVValue = - currentValue + deuxiemeFifo[colonneIndex];
		}
		// Calcul du Sobel horizontal
		outHValue = abs(- sobelHValue + var2_H);
		var2_H = var1_H;
		var1_H = sobelHValue;

		// Calcul du Sobel vertical
		outVValue = abs(var2_V + 2 * var1_V + sobelVValue);
		var2_V = var1_V;
		var1_V = sobelVValue;

		// Actualisation de la FIFO
		deuxiemeFifo[colonneIndex] = premiereFifo[colonneIndex];
		premiereFifo[colonneIndex] = currentValue;
		
		// Calcul des 3/4 de la somme
		int troisieme = 0.75 * (outHValue + outVValue);

		// Selection du max pour la norme (Approximation de la norme)
		pix_tmp = std::max({outHValue, outVValue, troisieme});

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
		colonneIndex++;
	}
	// Ecrire la sortie sur le port pixel_out
    pixel_out.write(pix_tmp);
}

/// @brief Generation des synchronisation en sortie.
void sobel::synchro_out()
{
	// Laisser passer les controles
	bk_out.write(blank.read());
	hpix_out.write(clk.read()); 
}

/// @brief Reinitialisation de l'index de la colonne sur le signal sh.
void sobel::filtre_sh()
{
	colonneIndex = 0;
}