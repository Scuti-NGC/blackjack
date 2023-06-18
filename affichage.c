#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <string.h>
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()
#include "affichage.h"
#include "gestion.h"


#define LargeurFenetre 800
#define HauteurFenetre 600
#define StartLargeur 75
#define StartHauteur 30
#define LargeurImageFond 1294
#define HauteurImageFond 800

void accueil(Rectangle* pStart, int centreX, int centreY, char *mStart)
{
		pStart->xGauche = centreX - StartLargeur;
		pStart->xDroite = centreX + StartLargeur;
		pStart->yBas = centreY - StartHauteur;
		pStart->yHaut = centreY + StartHauteur;
}

void initialiseJetons(Jeton jetons[8])
{
	jetons[0].couleur[0] = 255;
	jetons[0].couleur[1] = 255;
	jetons[0].couleur[2] = 255;
	strncpy(jetons[0].valeur, "1", sizeof(jetons[0].valeur));
	
	
	jetons[1].couleur[0] = 255;
	jetons[1].couleur[1] = 0;
	jetons[1].couleur[2] = 0;
	strncpy(jetons[1].valeur, "5", sizeof(jetons[1].valeur));
	
	jetons[2].couleur[0] = 0;
	jetons[2].couleur[1] = 255;
	jetons[2].couleur[2] = 255;
	strncpy(jetons[2].valeur, "10", sizeof(jetons[2].valeur));
	
	jetons[3].couleur[0] = 0;
	jetons[3].couleur[1] = 255;
	jetons[3].couleur[2] = 0;
	strncpy(jetons[3].valeur, "20", sizeof(jetons[3].valeur));
	
	jetons[4].couleur[0] = 0;
	jetons[4].couleur[1] = 0;
	jetons[4].couleur[2] = 255;
	strncpy(jetons[4].valeur, "50", sizeof(jetons[4].valeur));
	
	jetons[5].couleur[0] = 0;
	jetons[5].couleur[1] = 0;
	jetons[5].couleur[2] = 0;
	strncpy(jetons[5].valeur, "100", sizeof(jetons[5].valeur));
	
	jetons[6].couleur[0] = 255;
	jetons[6].couleur[1] = 0;
	jetons[6].couleur[2] = 255;
	strncpy(jetons[6].valeur, "500", sizeof(jetons[6].valeur));
	
	jetons[7].couleur[0] = 255;
	jetons[7].couleur[1] = 255;
	jetons[7].couleur[2] = 0;
	strncpy(jetons[7].valeur, "1000", sizeof(jetons[7].valeur));
}

void deplaceJetonVersGauche(int* centreDeplGaucheX, int* centreDeplGaucheY, int* rayonDeplacement, int* deplacementGauche, Compteur* compteur, int centreDeplGaucheXRef, char *JDchaine, char valeur[5])
{
	if(*rayonDeplacement > 0)
	{
	
		if(*deplacementGauche > 0)
		{
			*centreDeplGaucheX -= 9;
			*deplacementGauche -= 9;
			strcpy(JDchaine, valeur);
			
			if((*deplacementGauche) >= centreDeplGaucheXRef/2)
			{
				*centreDeplGaucheY -= 4;
			} 
			
			else if((*deplacementGauche) < centreDeplGaucheXRef/2)
			{
				*centreDeplGaucheY += 4;
			} 
		}
	
		else
		{
			compteur->dJeton = 0;
			*rayonDeplacement = 0;
		}
	}
}


void deplaceJetonVersDroite(int* centreDeplDroiteX, int* centreDeplDroiteY, int* rayonDeplacement, int* deplacementDroite, Compteur* compteur, int centreDeplDroiteXRef, char *JGchaine, char valeur[5])
{
	if(*rayonDeplacement > 0)
	{
		if(*deplacementDroite < 0)
		{
			*centreDeplDroiteX += 9;
			*deplacementDroite += 9;
			strcpy(JGchaine, valeur);
			
			if((*deplacementDroite) >= centreDeplDroiteXRef/2)
			{
				*centreDeplDroiteY -= 4;
			} 
			
			else if((*deplacementDroite) < centreDeplDroiteXRef/2)
			{
				*centreDeplDroiteY += 4;
			} 
		}
	
		else
		{
			compteur->dJeton = 0;
			*rayonDeplacement = 0;
		}
	}
}

void afficheProba(char probabilites[10][38], Compteur* cpt, float *proba, int* hauteurProba)
{
	if (cpt->indexProbabilites == 10)
	{
		cpt->indexProbabilites = 0;
	}

	if (cpt->indexProbabilites < 10)
	{
	
	 //int i = 247593; char str[10]; sprintf(str, "%d", i);
		strcpy(probabilites[cpt->indexProbabilites], "Vos chances de gagner sont de : 100%.");
	}
}


