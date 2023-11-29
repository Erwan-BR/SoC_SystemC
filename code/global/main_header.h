#ifndef MAIN_HEADER_H
#define MAIN_HEADER_H

#include <systemc.h>

#define T_ns 100 // 100 ns
 
char winimage[200];
char FichierIn[100], FichierOut[100];

// Affichage d'une image 
void affiche_image(char *nomIMAGE, int x, int y)
{
	char str[20];
	strcpy(winimage, "xv ");
	strcat(winimage, nomIMAGE); 
	
	sprintf(str, " %d ", x);
	strcat(winimage, str);
	sprintf(str, "%d &", y);
	strcat(winimage, str);

	// Afficher les images sous Visual C++
	//WinExec(winimage, 1);

	// Afficher les images sous UNIX
	int STATUS = system(winimage);
}

#endif