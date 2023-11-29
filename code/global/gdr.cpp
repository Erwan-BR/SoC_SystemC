#include "./gdr.h"

//******************************************************
ENTETE_GDR::ENTETE_GDR(unsigned Colonnes,unsigned Lignes,unsigned Oct,unsigned Code,
					char *Attr,char *Com,
					unsigned Mux,unsigned Nimage,unsigned Nature,
					char *Chaine,char *PasX, char *PasY)
{
	NbrePixParLigne=Colonnes;NbreLigne=Lignes;NbreOctet=Oct;Codage=Code;
    Multiplexage=Mux;NbreImage=Nimage;NatureImage=Nature;
	strcpy(AttribVisu,Attr);strcpy(Chainage,Chaine);
	strcpy(PasEchant_x,PasX);strcpy(PasEchant_y,PasY);
	strcpy(Comment,Com);
}
//******************************************************
ENTETE_GDR::ENTETE_GDR(ENTETE_GDR &ent)
{
	NbrePixParLigne=ent.NbrePixParLigne;NbreLigne=ent.NbreLigne;
	NbreOctet=ent.NbreOctet;Codage=ent.Codage;
	Multiplexage=ent.Multiplexage;
	NbreImage=ent.NbreImage;
	NatureImage=ent.NatureImage;
	strcpy(AttribVisu,ent.AttribVisu);
	strcpy(Chainage,ent.Chainage);
	strcpy(PasEchant_x,ent.PasEchant_x);
	strcpy(PasEchant_y,ent.PasEchant_y);
	strcpy(Comment,ent.Comment);
}
//******************************************************
void ENTETE_GDR::operator = (ENTETE_GDR &entete)
{
	NbrePixParLigne=entete.NbrePixParLigne;
	NbreLigne=entete.NbreLigne;
	NbreOctet=entete.NbreOctet;
	Codage=entete.Codage;
	Multiplexage=entete.Multiplexage;
	NbreImage=entete.NbreImage;
	NatureImage=entete.NatureImage;
	strcpy(AttribVisu,entete.AttribVisu);
	strcpy(Chainage,entete.Chainage);
	strcpy(PasEchant_x,entete.PasEchant_x);
	strcpy(PasEchant_y,entete.PasEchant_y);
	strcpy(Comment,entete.Comment);
}
/*******************************************************/
void ENTETE_GDR::Pixel_From_File(char *file, unsigned char *ptr)
{
	unsigned NbrePixel = NbPixel();
	FILE *pFile ;
	if ((pFile=fopen(file,"rb")) == NULL)
	{
		printf("Pb. d'ouverture du fichier %s\n", file);
		exit(1);
	}
	fseek(pFile, 256, SEEK_SET);

	if (NbrePixel != fread (ptr,1,NbrePixel, pFile))
	{
			printf("Pb. de lecture des pixels dans lire_pixel() \n");
			fclose (pFile);	exit(1);
	}
	fclose (pFile) ;
}
//******************************************************
void ENTETE_GDR::Affiche()
{	// afficher l'entete
	printf("\n\n Entete image : \n");
	printf("--------------\n");;
	printf("=> Nx : %d\n", NbrePixParLigne);
	printf("=> Ny : %d\n", NbreLigne);
	printf("=> Noctets %d\n", NbreOctet);
	printf("=> codage  : %d\n", Codage);
	printf("=> attribut : %s\n", AttribVisu);
	printf("-----------------------\n\n");
}
//******************************************************
void ENTETE_GDR::Str2Entete(char *descri)
{
	char Type[8];
    unsigned NbreBit;

	strncpy(Type,descri,7);Type[7]='\0';
	if(strcmp(Type, "GDR 1.0") !=0 )
	{printf("Pb. de Format GDR\n"); exit(1);}

	sscanf(&descri[8],"%6d",&NbrePixParLigne);
	sscanf(&descri[14],"%6d",&NbreLigne);
	sscanf(&descri[20],"%4d",&NbreBit);NbreOctet =NbreBit>>3;

	sscanf(&descri[24],"%3d",&Multiplexage);
	sscanf(&descri[27],"%3d",&Codage);
	sscanf(&descri[30],"%5d",&NbreImage);
	sscanf(&descri[35],"%5d",&NatureImage);

	strncpy(AttribVisu,&descri[40],32);AttribVisu[31] = '\0';
	strncpy(Chainage,&descri[72],64);Chainage[63] = '\0';
	strncpy(PasEchant_x,&descri[136],16);PasEchant_x[15] = '\0';
	strncpy(PasEchant_y,&descri[152],16);PasEchant_y[15] = '\0';
	strncpy(Comment,&descri[168],88);Comment[87] = '\0';
}
//******************************************************
void ENTETE_GDR::Entete2Str(char *descri)
{
	for(unsigned i=0;i<256;i++) descri[i]=' ';
	strncpy(descri,"GDR 1.0",7);
	sprintf(descri+8,"%-6d ", NbrePixParLigne);
	sprintf(descri+14,"%-6d ", NbreLigne);
	sprintf(descri+20,"%-4d ", NbreOctet<<3);
	sprintf(descri+24,"%-3d ", Multiplexage);
	sprintf(descri+27,"%-3d ", Codage);
	sprintf(descri+30,"%-5d ", NbreImage);
	sprintf(descri+35,"%-5d ", NatureImage);
	strncpy(descri+40, AttribVisu,strlen(AttribVisu));
	sprintf(descri+72, Chainage,strlen(Chainage));
	sprintf(descri+136, PasEchant_x,strlen(PasEchant_x));
	sprintf(descri+152, PasEchant_y,strlen(PasEchant_y));
	sprintf(descri+168, Comment,strlen(Comment));

	descri[255]='\0';
}

//******************************************************
ENTETE_GDR::ENTETE_GDR(char *fichier)
{
	FILE *pFile ;
	char EnteteString[256];

	if ((pFile=fopen(fichier,"r"))==NULL)
	{
		printf("Pb. d'ouverture du fichier %s\n", fichier);
		exit(1);
	}
	if (fread(EnteteString,1, 256, pFile)!=256)
	{
		printf("Pb. de lecture de l'entete\n");
		exit(1);
	}
	Str2Entete(EnteteString);
	fclose (pFile);
};

//******************************************************
void ENTETE_GDR::Lire_Entete_From_File(char *fichier)
{
	FILE *pFile ;
	char EnteteString[256];

	if ((pFile=fopen(fichier,"r"))==NULL)
	{
		printf("Pb. d'ouverture du fichier %s\n", fichier);
		exit(1);
	}
	if (fread(EnteteString,1, 256, pFile)!=256)
	{
		printf("Pb. de lecture de l'entete\n");
		exit(1);
	}
	Str2Entete(EnteteString);
	fclose (pFile);
};
///////////////////////
//******************************************************
void ENTETE_GDR::save(char *fichier, unsigned char *ptr)
{
	FILE *pFile;
	unsigned NbrePixel=NbPixel();
	char EnteteString[256];

	Entete2Str(EnteteString);
	if ((pFile = fopen(fichier,"wb")) == NULL)
    {
		printf("Pb. d'ouverture du fichier %s\n", fichier);
		exit(1);
	} 
	if (fwrite(EnteteString, 1, 256, pFile) != 256)
	{
		printf("Pb. d'ecriture de l'entete ::save()\n");
		fclose (pFile);	exit(1);
	}

	if (NbrePixel != fwrite (ptr,1,NbrePixel, pFile))
	{
		printf("Pb. d'ecriture des pixels dans ::save()\n");
		fclose (pFile); 
		exit(1);
	}
	fclose (pFile) ;
}
