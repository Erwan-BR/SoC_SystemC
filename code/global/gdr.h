#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#ifndef GDR_H
#define GDR_H

// ****************************************************************
// definition de la class ENTETE_GDR pour image au format "gdr"
// ****************************************************************
class ENTETE_GDR
{
	protected :
		unsigned NbrePixParLigne;	// nombre de pixels par ligne  
		unsigned NbreLigne;			// nombre de lignes 		
		unsigned NbreOctet;			// nombre d'octets par pixel
		unsigned Codage;			// nature de la valeur du pixel:
								//	   0:entier, 1:reel, 2:ASCII	
		unsigned Multiplexage;		/* Multiplexage:
									0: par composante
									1: par ligne
									2: par pixel ....*/         
		unsigned NbreImage;
		unsigned NatureImage;		/* Nature de l'image:
									0: Niveau de gris
									1: Couleur RVB  ....  */
		char AttribVisu[32];	/* 	INTENSITE REGION CONTOUR */

		char Chainage[64];		/*	chainage vers un autre fichier */
		char PasEchant_x[16];	/*	Pas d'Echantillonnage en x		*/
		char PasEchant_y[16];	/*	Pas d'Echantillonnage en y		*/
		char Comment[88];		/*	commentaire		*/

	public :
		ENTETE_GDR(){NbrePixParLigne=0;NbreLigne=0;NbreOctet=1;NbreImage=1;};
		ENTETE_GDR(ENTETE_GDR &ent);
		ENTETE_GDR(char *fichier); // constructeur 1
		ENTETE_GDR(unsigned Colonnes,unsigned Lignes,unsigned Oct=0,unsigned Code=0,
			char *Attr=(char *)"INTENSITE",char *Com=(char *)"FORMAT GDR ENSEA",
			unsigned Mux=0,unsigned Nimage=1,unsigned Nature=0,
			char *Chaine=(char *)"RIEN",
			char *PasX=(char *)"ZERO", char *PasY=(char *)"ZERO");
		~ENTETE_GDR(){};

		void Pixel_From_File (char *file, unsigned char *ptr);

		void SetLigne(unsigned Lignes){NbreLigne=Lignes;};
		void SetColonne(unsigned Colonnes){NbrePixParLigne=Colonnes;};
		void SetOctet(unsigned Oct){NbreOctet=Oct;};
		unsigned NbPixel() {return(NbrePixParLigne*NbreLigne*NbreOctet);}
		void SetCodage(unsigned Code){Codage=Code;};
		void SetImage(unsigned Nimage){NbreImage=Nimage;};
		void SetAttrib(char *Attr){strcpy(AttribVisu,Attr);};
		void SetChaine(char *Chaine){strcpy(Chainage,Chaine);}
		void SetComm(char *Comm){strcpy(Comment,Comm);}

		void Lire_Entete_From_File(char *fichier);
		void Str2Entete(char *descri);
		void Entete2Str(char *descri);
		
		void save(char *fichier, unsigned char *ptr);

		unsigned NbLigne(void){return NbreLigne;};
		unsigned NbColonne(void){return NbrePixParLigne;};
		unsigned NbOctet(void){return NbreOctet;};
		unsigned NCodage(void){return Codage;}
		char *Attrib(void){return AttribVisu;}
		char *Chaine(void){return Chainage;}
		char *Comm(void){return Comment;}

		void operator = (ENTETE_GDR &ent);
		void Affiche ();
};

#endif
