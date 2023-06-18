#include <stdio.h> // Pour pouvoir utilisé printf() et scanf()
#include <stdlib.h> // Pour pouvoir utilisé exit()
#include <stdbool.h> // Pour pouvoir utilisé le booléens, True et False
#include <string.h> // Pour pouvoir utilisé les fonctions liées aux chaines de caractères
#include <time.h> // Pour pouvoir utilisé le random
#include<unistd.h> // Pour pouvoir utilisé le sleep(), ce qui fait une pause entre deux actions
#include "GfxLib.h"
#include "BmpLib.h"

//Il y a 3 joueurs jouablent 
//il y a 8 paquets, donc 416 cartes
//Le tableau "tabAffiche", permet de savoir si un bouton est affiché ou non et donc pour savoir comment gérer son espace de click.
//transfert.tabAffiche[0] : bouton hit
//transfert.tabAffiche[1] : bouton stand
//transfert.tabAffiche[2] : bouton double
//transfert.tabAffiche[3] : bouton split
//transfert.tabAffiche[4] : bouton assurance
//transfert.tabAffiche[5] : bouton push (abandon)
//transfert.tabAffiche[6] : bouton tirerCarte (pioche)
//transfert.tabAffiche[7] : bouton resetMise (permet de reset la mise)


//pour couleur 1 = trefle, 2 = pique, 3 = carreau, 4 = coeur
typedef struct{
    int numero; // valeur de la carte 
    int couleur; // couleur de la carte 
}Carte;

typedef struct {
	float capital;
	int mise;
	float gain;
	Carte cartes[21]; //Il ne faut pas oublier de faire un free.
	int etat;
	int nbCartes;
	int numeroRand[21];
}Joueur;

typedef struct {
	Carte cartes[16];// La première carte est visible et la deuxième est face caché.
	// Il ne faut pas oublier de faire un free.
	int nbCartes;
	int etat;
}Banque;

typedef struct{
	Carte sorti[416]; //C'est le nb de carte maximum qu'il y a dans les 8 paquets. 52*8=416.
	int tabAffiche[6]; 
    	int nbCartes;
    	float capital;
    	int hauteurFenetre;
    	int largeurFenetre;
}Transfert;



//pour couleur 1 = trefle, 2 = pique, 3 = carreau, 4 = coeur

Joueur initJoueur(float Capital, Transfert transfert);

Carte choisiCarte(Transfert* transfert, Joueur* joueur);
int choisiMise(float* capital, const int indiceJeton, int mise);
// void passeTour(Joueur joueur1, Joueur joueur2, Joueur joueur3, Banque banque, int cpt, Transfert transfert);

int AdditionJoueur(Joueur joueur);
int AdditionBanque(Banque joueur);

void menu(Joueur* joueur, Banque* banque, int* indiceAction, Transfert* transfert);
void faitAction(Joueur* joueur, Banque* banque, int* indiceAction, Transfert transfert);

void hit(Joueur* joueur, Transfert transfert);// transfert.tabAffiche : 0
void stand(Joueur* joueur);// transfert.tabAffiche : 1
void doubler(Joueur* joueur, Transfert transfert);// transfert.tabAffiche : 2
// Joueur split(Joueur joueur, Transfert transfert);// transfert.tabAffiche : 3 , pour l'instant elle ne marche pas 
void assurance(Joueur* joueur, Banque* banque);// transfert.tabAffiche : 4
void push(Joueur* joueur);// transfert.tabAffiche : 5
Joueur resetMise(Joueur joueur);// transfert.tabAffiche : 6
//Il manque la fonction qui permet d'afficher le fait que m'on pioche une carte avec animation. transfert.tabAffiche : 7

int bustJoueur(Joueur joueur);
int bustBanque(Banque banque);
int bustJoueur(Joueur joueur);

Joueur initVictoire(Joueur joueur);
void victoire(Joueur joueur1, Joueur joueur2, Joueur joueur3, Banque banque);
int verifieVictoire(Joueur joueur, Banque banque);
void verifieBlackjack(Joueur* joueur);


void tourBanque(Joueur* joueur1, Joueur* joueur2, Joueur* joueur3, Banque* banque, Transfert transfert);

Transfert fonctionDeTransfert (Transfert transfert);

void apparaitCarte(DonneesImageRGB** cartesGfx, DonneesImageRGB **cartes, Joueur joueur, int cpt);
