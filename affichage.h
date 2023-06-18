typedef struct
{
	int cJeton;
	int dJeton;
	int cMenu;
	int indexProbabilites;
	int centre;
	int gauche;
	int droite;
	int croupier;
	int transfert;
	int tour;
} Compteur;

typedef struct
{
	int xGauche;
	int xDroite;
	int yBas;
	int yHaut;

}Rectangle;

typedef struct
{
	char valeur[5];
	int couleur[3];
	
}Jeton;

void accueil(Rectangle* pStart, int centreX, int centreY, char *mStart);
void initialiseJetons(Jeton jetons[8]);
void deplaceJetonVersGauche(int* centreDeplGaucheX, int* centreDeplGaucheY, int* rayonDeplacement, int* deplacementGauche, Compteur* compteur, int centreDeplGaucheXRef, char *JDchaine, char valeur[5]);
void deplaceJetonVersDroite(int* centreDeplDroiteX, int* centreDeplDroiteY, int* rayonDeplacement, int* deplacementDroite, Compteur* compteur, int centreDeplDroiteXRef, char *JGchaine, char valeur[5]);
void afficheProba(char probabilites[10][38], Compteur* cpt, float *proba, int* hauteurProba);
