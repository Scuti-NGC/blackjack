#include <stdlib.h> // Pour pouvoir utiliser exit()
#include <stdio.h> // Pour pouvoir utiliser printf()
#include <math.h> // Pour pouvoir utiliser sin() et cos()
#include <string.h>
#include "GfxLib.h" // Seul cet include est necessaire pour faire du graphique
#include "BmpLib.h" // Cet include permet de manipuler des fichiers BMP
#include "ESLib.h" // Pour utiliser valeurAleatoire()
#include "affichage.h"
#include "gestion.h"

// Largeur et hauteur par defaut d'une image correspondant a nos criteres

#define StartLargeur 75
#define StartHauteur 30
#define LargeurImageFond 1294
#define HauteurImageFond 800
#define MARGIN 10
#define BORDER 5

// Fonction de trace de cercle
void cercle(float centreX, float centreY, float rayon);
/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement);


int main(int argc, char **argv)
{

	srand(time(NULL));
	//Normalement la fonction atol renvoie un long int mais je préfère le stocker dans un int.
	//Les valeurs reçus peuvent être misent dans un int car elle ne sont pas trop grande.
	float capital = atol(argv[1]);          // Peut-être faire une fonction qui permet de donner ces valeurs comme en POO.
	int HauteurFenetre = atol(argv[2]);
	int LargeurFenetre = atol(argv[3]);

	// Carte sorti[416] = {0};
	Transfert transfert = {0};
	
	transfert.capital = capital;
	transfert.hauteurFenetre = HauteurFenetre;
	transfert.largeurFenetre = LargeurFenetre;

	transfert = fonctionDeTransfert(transfert);
    /*Carte c1;
    choisiCarte(c1, sorti);
    choisiCarte(sorti);*/

    //3 pour l'indice du jeton



	/*Carte carteBanque[22] = {0};
	carteBanque[0] = choisiCarte(sorti);
	carteBanque[1] = choisiCarte(sorti);
	Banque banque = {{carteBanque[22]}};*/

	// Pour l'instant on part du principe qu'il n'y a qu'un seul joueur, mais on est quand même obligé de définir les deux autres.
	/*Joueur joueur2 = {0};
	Joueur joueur3 = {0};
	joueur1 = verifieBlackjack(joueur1);

	int somme = AdditionJoueur(&joueur1);
	printf("\n\n\nLa valeur de la somme est de : %d\n", somme);
	printf("Dans la main carte 1 = %d\n", joueur1.cartes[0].numero );
    	printf("Dans la main carte 2 = %d\n", joueur1.cartes[1].numero );
    	printf("Dans la main carte 3 = %d\n\n\n\n", joueur1.cartes[2].numero );*/
    	
	initialiseGfx(argc, argv);
	
	prepareFenetreGraphique("GfxLib", LargeurFenetre, HauteurFenetre);
	
	/* Lance la boucle qui aiguille les evenements sur la fonction gestionEvenement ci-apres,
		qui elle-meme utilise fonctionAffichage ci-dessous */
	lanceBoucleEvenements();
	
	return 0;
}



/* Fonction de trace de cercle */
void cercle(float centreX, float centreY, float rayon)
{
	const int Pas = 20; // Nombre de secteurs pour tracer le cercle
	const double PasAngulaire = 2.*M_PI/Pas;
	int index;
	
	for (index = 0; index < Pas; ++index) // Pour chaque secteur
	{
		const double angle = 2.*M_PI*index/Pas; // on calcule l'angle de depart du secteur
		triangle(centreX, centreY,
				 centreX+rayon*cos(angle), centreY+rayon*sin(angle),
				 centreX+rayon*cos(angle+PasAngulaire), centreY+rayon*sin(angle+PasAngulaire));
			// On trace le secteur a l'aide d'un triangle => approximation d'un cercle
	}
	
}


/* La fonction de gestion des evenements, appelee automatiquement par le systeme
des qu'une evenement survient */
void gestionEvenement(EvenementGfx evenement)
{

	static Transfert transfert = {0};
	
	static float capital = 0;
	static int HauteurFenetre = 0;
	static int LargeurFenetre = 0;
	
	static Joueur joueur1 = {0};
	static Joueur joueur2 = {0};
	static Joueur joueur3 = {0};
	
	static int indiceAction = 0;
	static Banque banque = {0};
	
	static int sommeJoueur1 = 0;
	static int sommeJoueur2 = 0;
	static int sommeJoueur3 = 0;
	
	



	static bool pleinEcran = false; // Pour savoir si on est en mode plein ecran ou pas
	

	static DonneesImageRGB *paquetCartes = NULL;
	static DonneesImageRGB *carteCachee = NULL;
	
	static DonneesImageRGB *cartes[52] = {0};
	
	static DonneesImageRGB *cartesCentre[4] = {0};
	static DonneesImageRGB *cartesDroite[4] = {0};
	static DonneesImageRGB *cartesGauche[4] = {0};
	//static DonneesImageRGB *cartesCroupier[3] = {0};


	int centreX = largeurFenetre()/2;
	int centreY = hauteurFenetre()/2;
	int centreJetonX = largeurFenetre()/8;
	int centreJetonY = hauteurFenetre()/10;
	int flecheX = largeurFenetre()/24;
	int flecheY = hauteurFenetre()/80;
	int tailleFleche = largeurFenetre()/41;
	int centreJetonDroite = centreJetonX  + 1.3 * flecheX + tailleFleche;
	int centreJetonGauche = centreJetonX  - 1.3 * flecheX - tailleFleche;
	
	int debutBoutonX = largeurFenetre()/3.5;
	int debutBoutonY = hauteurFenetre()/30;
	int largeurBouton = largeurFenetre()/15;
	int hauteurBouton = hauteurFenetre()/11;
	int espacementBouton = largeurFenetre()/30;
	
	int largeurCarte = largeurFenetre()/20;
	int largeurCroix = largeurFenetre()/60;
	int hauteurCroix = hauteurFenetre()/42;
	int basCarteCentre = hauteurFenetre() * 1/8;
	int hautCarteCentre = hauteurFenetre() * 3/8;
	int basCarteCote = hauteurFenetre() * 3/16;
	int hautCarteCote = hauteurFenetre() * 7/16;
	int milieuCarteCentre = (basCarteCentre + hautCarteCentre) /2;
	int milieuCarteCote = (basCarteCote + hautCarteCote) /2;
	int espacementMemePersonne = largeurFenetre() /100;
	
	int largeurChaineBouton = largeurFenetre()/74;
	int largeurChaineAssurance = largeurFenetre()/46;
	int largeurChainePaie = largeurFenetre()/70;
	int largeurJeton = largeurFenetre()/46;
	int largeurPoliceJeton = largeurFenetre()/62;
	
	int basAssurance = hauteurFenetre()/2;
	int hautAssurance = hauteurFenetre() * 4/7;

	int basCarteCroupier = hauteurFenetre() * 23/32;
	int hautCarteCroupier = hauteurFenetre() * 31/32;
	
	
	static int hauteurProba = 795;
	static int* hProba = &hauteurProba;

	static int centreDeplGaucheX1 = 0;
	static int centreDeplGaucheY1 = 0;
	static int centreDeplGaucheXRef = 0;
	centreDeplGaucheXRef = 1.3 * flecheX + tailleFleche;
	static int rayonDeplacementGauche1 = 0;
	static int deplacementGauche1 = 0;
	
	static int* PcentreDeplGaucheX1 = &centreDeplGaucheX1;
	static int* PcentreDeplGaucheY1 = &centreDeplGaucheY1;
	static int* PrayonDeplacementGauche1 = &rayonDeplacementGauche1;
	static int* PdeplacementGauche1 = &deplacementGauche1;
	
	static int centreDeplGaucheX2 = 0;
	static int centreDeplGaucheY2 = 0;
	static int rayonDeplacementGauche2 = 0;
	static int deplacementGauche2 = 0;
	
	static int* PcentreDeplGaucheX2 = &centreDeplGaucheX2;
	static int* PcentreDeplGaucheY2 = &centreDeplGaucheY2;
	static int* PrayonDeplacementGauche2 = &rayonDeplacementGauche2;
	static int* PdeplacementGauche2 = &deplacementGauche2;
	
	static int centreDeplDroiteX1 = 0;
	static int centreDeplDroiteY1 = 0;
	static int centreDeplDroiteXRef = 0;
	centreDeplDroiteXRef = (-1) * 1.3 * flecheX - tailleFleche;
	static int rayonDeplacementDroite1 = 0;
	static int deplacementDroite1 = 0;
	
	static int* PcentreDeplDroiteX1 = &centreDeplDroiteX1;
	static int* PcentreDeplDroiteY1 = &centreDeplDroiteY1;
	static int* PrayonDeplacementDroite1 = &rayonDeplacementDroite1;
	static int* PdeplacementDroite1 = &deplacementDroite1;
	
	static int centreDeplDroiteX2 = 0;
	static int centreDeplDroiteY2 = 0;
	static int rayonDeplacementDroite2 = 0;
	static int deplacementDroite2 = 0;
	
	static int* PcentreDeplDroiteX2 = &centreDeplDroiteX2;
	static int* PcentreDeplDroiteY2 = &centreDeplDroiteY2;
	static int* PrayonDeplacementDroite2 = &rayonDeplacementDroite2;
	static int* PdeplacementDroite2 = &deplacementDroite2;
	
	static char JDchaine1[5] = {0};
	
	static char JDchaine2[5] = {0};


	static char JGchaine1[5] = {0};
	
	static char JGchaine2[5] = {0};
	
	
	static Rectangle start = {0};
	static Rectangle* pStart = &start;
	
	static Compteur compteur = {0};
	static Compteur* Pcpt = &compteur;
	
	static char mStart[6] = "Jouer";
	
	static char assurance[10] = "INSURANCE";
	static char paie[12] = "Paid 3 to 2";
	//static char blackJack[10] = "BLACKJACK";
	
	static char split[6] = "Split";
	static char hit[4] = "Hit";
	static char doubler[8] = "Doubler";
	static char push[6] = "Push";
	static char stand[6] = "Stand";
	
	static char sJ1[3] = {0};
	static char sJ2[3] = {0};
	static char sJ3[3] = {0};
	static int largeurPoliceSomme = 0;
	largeurPoliceSomme = largeurFenetre()/60;
	
	static int curseurJ1[3] = {0};
	static int curseurJ2[3] = {0};
	static int curseurJ3[3] = {0};
	
	
	static Jeton jetons[8] = {0};
	
	
	
	
	static char probabilites[10][38] = {0};
	
	float proba = 0;
	float* prob = &proba;
	
	
	switch (evenement)
	{
		case Initialisation:
			accueil(pStart, centreX, centreY, mStart);
			
			transfert = fonctionDeTransfert(transfert);
			capital = transfert.capital;
			HauteurFenetre = hauteurFenetre();
			LargeurFenetre = largeurFenetre();
			
				
			joueur1 = initJoueur(capital, transfert);
			joueur2 = initJoueur(capital, transfert);
			joueur3 = initJoueur(capital, transfert);			
			
			cartes[0] = lisBMPRGB("./images/TA.bmp");
			cartes[1] = lisBMPRGB("./images/T2.bmp");
			cartes[2] = lisBMPRGB("./images/T3.bmp");
			cartes[3] = lisBMPRGB("./images/T4.bmp");
			cartes[4] = lisBMPRGB("./images/T5.bmp");
			cartes[5] = lisBMPRGB("./images/T6.bmp");
			cartes[6] = lisBMPRGB("./images/T7.bmp");
			cartes[7] = lisBMPRGB("./images/T8.bmp");
			cartes[8] = lisBMPRGB("./images/T9.bmp");
			cartes[9] = lisBMPRGB("./images/T10.bmp");
			cartes[10] = lisBMPRGB("./images/TJ.bmp");
			cartes[11] = lisBMPRGB("./images/TQ.bmp");
			cartes[12] = lisBMPRGB("./images/TK.bmp");
			
			cartes[13] = lisBMPRGB("./images/PA.bmp");
			cartes[14] = lisBMPRGB("./images/P2.bmp");
			cartes[15] = lisBMPRGB("./images/P3.bmp");
			cartes[16] = lisBMPRGB("./images/P4.bmp");
			cartes[17] = lisBMPRGB("./images/P5.bmp");
			cartes[18] = lisBMPRGB("./images/P6.bmp");
			cartes[19] = lisBMPRGB("./images/P7.bmp");
			cartes[20] = lisBMPRGB("./images/P8.bmp");
			cartes[21] = lisBMPRGB("./images/P9.bmp");
			cartes[22] = lisBMPRGB("./images/P10.bmp");
			cartes[23] = lisBMPRGB("./images/PJ.bmp");
			cartes[24] = lisBMPRGB("./images/PQ.bmp");
			cartes[25] = lisBMPRGB("./images/PK.bmp");
			
			cartes[26] = lisBMPRGB("./images/CA.bmp");
			cartes[27] = lisBMPRGB("./images/C2.bmp");
			cartes[28] = lisBMPRGB("./images/C3.bmp");
			cartes[29] = lisBMPRGB("./images/C4.bmp");
			cartes[30] = lisBMPRGB("./images/C5.bmp");
			cartes[31] = lisBMPRGB("./images/C6.bmp");
			cartes[32] = lisBMPRGB("./images/C7.bmp");
			cartes[33] = lisBMPRGB("./images/C8.bmp");
			cartes[34] = lisBMPRGB("./images/C9.bmp");
			cartes[35] = lisBMPRGB("./images/C10.bmp");
			cartes[36] = lisBMPRGB("./images/CJ.bmp");
			cartes[37] = lisBMPRGB("./images/CQ.bmp");
			cartes[38] = lisBMPRGB("./images/CK.bmp");
			
			cartes[39] = lisBMPRGB("./images/HA.bmp");
			cartes[40] = lisBMPRGB("./images/H2.bmp");
			cartes[41] = lisBMPRGB("./images/H3.bmp");
			cartes[42] = lisBMPRGB("./images/H4.bmp");
			cartes[43] = lisBMPRGB("./images/H5.bmp");
			cartes[44] = lisBMPRGB("./images/H6.bmp");
			cartes[45] = lisBMPRGB("./images/H7.bmp");
			cartes[46] = lisBMPRGB("./images/H8.bmp");
			cartes[47] = lisBMPRGB("./images/H9.bmp");
			cartes[48] = lisBMPRGB("./images/H10.bmp");
			cartes[49] = lisBMPRGB("./images/HJ.bmp");
			cartes[50] = lisBMPRGB("./images/HQ.bmp");
			cartes[51] = lisBMPRGB("./images/HK.bmp");
			
			//sécurité si 'limage n'a pas pue être changée 
			cartesCentre[0] = lisBMPRGB("./images/C2.bmp");
			cartesCentre[1] = lisBMPRGB("./images/C2.bmp");
			cartesCentre[2] = lisBMPRGB("./images/C2.bmp");
			cartesCentre[3] = lisBMPRGB("./images/C2.bmp");
			
			cartesDroite[0] = lisBMPRGB("./images/C2.bmp");
			cartesDroite[1] = lisBMPRGB("./images/C2.bmp");
			cartesDroite[2] = lisBMPRGB("./images/C2.bmp");
			cartesDroite[3] = lisBMPRGB("./images/C2.bmp");
			
			cartesGauche[0] = lisBMPRGB("./images/C2.bmp");
			cartesGauche[1] = lisBMPRGB("./images/C2.bmp");
			cartesGauche[2] = lisBMPRGB("./images/C2.bmp");
			cartesGauche[3] = lisBMPRGB("./images/C2.bmp");
			
			/*cartesCroupier[0] = lisBMPRGB("./images/C2.bmp");
			cartesCroupier[1] = lisBMPRGB("./images/C2.bmp");
			cartesCroupier[2] = lisBMPRGB("./images/C2.bmp");*/
			
			paquetCartes = lisBMPRGB("./images/paquetCartes.bmp");
			carteCachee = lisBMPRGB("./images/carteCachee.bmp");
			
			apparaitCarte(cartesCentre, cartes, joueur1, compteur.centre);	
			apparaitCarte(cartesDroite, cartes, joueur2, compteur.droite);	
			apparaitCarte(cartesGauche, cartes, joueur3, compteur.gauche);	
			
			
			sommeJoueur1 = AdditionJoueur(joueur1);
			sommeJoueur2 = AdditionJoueur(joueur2);
			sommeJoueur3 = AdditionJoueur(joueur3);
			
			verifieBlackjack(&joueur1);
			verifieBlackjack(&joueur2);
			verifieBlackjack(&joueur3);
			
			sprintf(sJ1, "%d", sommeJoueur1);
			sprintf(sJ2, "%d", sommeJoueur2);
			sprintf(sJ3, "%d", sommeJoueur3);
			
			curseurJ1[0] = 32;
			curseurJ1[1] = 168;
			curseurJ1[2] = 72;
			
			curseurJ2[0] = 32;
			curseurJ2[1] = 168;
			curseurJ2[2] = 72;
			
			curseurJ3[0] = 32;
			curseurJ3[1] = 168;
			curseurJ3[2] = 72;
			
			
				
			demandeTemporisation(1);
			
			
			break;
			
		case Temporisation:
		
			initialiseJetons(jetons);
			deplaceJetonVersGauche(PcentreDeplGaucheX1, PcentreDeplGaucheY1, PrayonDeplacementGauche1, PdeplacementGauche1, Pcpt, centreDeplGaucheXRef, JDchaine1, jetons[compteur.cJeton].valeur);
			deplaceJetonVersDroite(PcentreDeplDroiteX1, PcentreDeplDroiteY1, PrayonDeplacementDroite1, PdeplacementDroite1, Pcpt, centreDeplDroiteXRef, JGchaine1, jetons[compteur.cJeton].valeur);
			deplaceJetonVersDroite(PcentreDeplDroiteX2, PcentreDeplDroiteY2, PrayonDeplacementDroite2, PdeplacementDroite2, Pcpt, centreDeplDroiteXRef, JGchaine2, jetons[compteur.cJeton + 1].valeur);
			deplaceJetonVersGauche(PcentreDeplGaucheX2, PcentreDeplGaucheY2, PrayonDeplacementGauche2, PdeplacementGauche2, Pcpt, centreDeplGaucheXRef, JDchaine2, jetons[compteur.cJeton - 1].valeur);	
			
			if(joueur1.etat == 0 && indiceAction == 2)
			{
				indiceAction = 0;
				compteur.tour++;
			}
			
			if(compteur.tour == 0)
			{
				menu(&joueur1, &banque, &indiceAction, &transfert);
				apparaitCarte(cartesCentre, cartes, joueur1, compteur.centre);
				sommeJoueur1 = AdditionJoueur(joueur1);
				sprintf(sJ1, "%d", sommeJoueur1);

				curseurJ1[0] = 159;
				curseurJ1[1] = 252;
				curseurJ1[2] = 253;
				
				if(joueur1.etat == 2 || joueur1.etat == 5)
				{
					compteur.tour++;
				}
			}
			
			
			if(joueur2.etat == 0 && indiceAction == 2)
			{
				indiceAction = 0;
				compteur.tour++;
			}
			
			if(compteur.tour == 1)
			{
				menu(&joueur2, &banque, &indiceAction, &transfert);
				apparaitCarte(cartesDroite, cartes, joueur2, compteur.droite);
				sommeJoueur2 = AdditionJoueur(joueur2);
				sprintf(sJ2, "%d", sommeJoueur2);
				
				curseurJ1[0] = 32;
				curseurJ1[1] = 168;
				curseurJ1[2] = 72;
				
				curseurJ2[0] = 159;
				curseurJ2[1] = 252;
				curseurJ2[2] = 253;
				
				if(joueur2.etat == 2 || joueur2.etat == 5)
				{
					compteur.tour++;
				}
			}
			
			if(joueur3.etat == 0 && indiceAction == 2)
			{
				indiceAction = 0;
				compteur.tour++;
			}
			if(compteur.tour == 2)
			{
				menu(&joueur3, &banque, &indiceAction, &transfert);
				apparaitCarte(cartesGauche, cartes, joueur3, compteur.gauche);
				sommeJoueur3 = AdditionJoueur(joueur3);
				sprintf(sJ3, "%d", sommeJoueur3);
				
				curseurJ2[0] = 32;
				curseurJ2[1] = 168;
				curseurJ2[2] = 72;
				
				curseurJ3[0] = 159;
				curseurJ3[1] = 252;
				curseurJ3[2] = 253;
				
				if(joueur3.etat == 2 || joueur3.etat == 5)
				{
					compteur.tour++;
				}
			}
			
               		paquetCartes = lisBMPRGB("./images/paquetCartes.bmp");
			rafraichisFenetre();
			break;
			
		case Affichage:
            	
			
			// On part d'un fond d'ecran blanc
			effaceFenetre (255, 255, 255);
			
			if (compteur.cMenu == 0)
			{
				couleurCourante(0,35,245);
			
				rectangle(start.xGauche, start.yBas, start.xDroite, start.yHaut);
			
				couleurCourante(255, 253, 85);
			
				afficheChaine(mStart, 40, centreX - tailleChaine(mStart,40)/2, centreY - tailleChaine("o",40)/1.5);				
				
			}
			
			
			if (compteur.cMenu == 1)
        		{
        		
				couleurCourante(32, 168, 72);
        			rectangle(MARGIN, MARGIN, largeurFenetre() - MARGIN, hauteurFenetre() - MARGIN); 
        			
        			couleurCourante(235, 51, 56);
        			rectangle(4 * largeurFenetre()/5, hauteurFenetre()*3/5, largeurFenetre() * 4/5 + 2 * largeurCarte, hauteurFenetre() * 17/20);
        			afficheChaine(paie, largeurChainePaie, largeurFenetre()/2  - tailleChaine(paie, largeurChainePaie)/2, hautAssurance  + tailleChaine("1",largeurChainePaie));
        			
        			
        			couleurCourante(255, 255, 255);
				//bordure assurance
        			rectangle(largeurFenetre()/3 - BORDER, basAssurance - BORDER, largeurFenetre() * 2/3 + BORDER, hautAssurance + BORDER);
        			
        			//Pour les cartes
        			
        			//des joueurs
        			
        			if (compteur.centre == 0 || joueur1.etat == 5)
        			{
        				rectangle(centreX - largeurCarte - BORDER, basCarteCentre - BORDER, centreX + largeurCarte + BORDER, hautCarteCentre + BORDER); 
        			}
        			
        			if(compteur.gauche == 0 || joueur3.etat == 5)
        			{
					rectangle(centreX - 6 * largeurCarte - BORDER, basCarteCote - BORDER, centreX - 4 * largeurCarte + BORDER, hautCarteCote + BORDER); 
				}
				
				if(compteur.droite == 0 || joueur2.etat == 5)
				{
					rectangle(centreX + 4 * largeurCarte - BORDER, basCarteCote - BORDER, centreX + 6 * largeurCarte + BORDER, hautCarteCote + BORDER); 
				}
				
				//du croupier
				if(compteur.croupier == 0)
				{
					rectangle(centreX - 2 * largeurCarte - BORDER -espacementMemePersonne, basCarteCroupier - BORDER, centreX -espacementMemePersonne + BORDER, hautCarteCroupier + BORDER); 
					rectangle(centreX + espacementMemePersonne - BORDER, basCarteCroupier - BORDER, centreX + 2 * largeurCarte + espacementMemePersonne + BORDER, hautCarteCroupier + BORDER); 
				}
				
				
				
				//assurance
				couleurCourante(32, 168, 72);
				rectangle(largeurFenetre()/3, basAssurance, 2 * largeurFenetre()/3, hautAssurance);
				
				couleurCourante(255, 255, 0);
				afficheChaine(assurance, largeurChaineAssurance, largeurFenetre()/2  - tailleChaine(assurance, largeurChaineAssurance)/2, (basAssurance + hautAssurance)/2 - tailleChaine("1",largeurChaineAssurance)/1.5);
				
				
				//blackJack
				//afficheChaine(blackJack, 50, largeurFenetre()/2  - tailleChaine(blackJack,50)/2, hauteurFenetre() * 9/10 - tailleChaine("1",50)/1.5);
				//arrondis des cartes
				couleurCourante(32, 168, 72);
        			
        			//pour les joueurs
        			
        			if (compteur.centre == 0 || joueur1.etat == 5)
        			{
        				cercle(centreX - largeurCarte - BORDER, basCarteCentre - BORDER, 5 * sqrt(2)); 
        				cercle(centreX + largeurCarte + BORDER, basCarteCentre - BORDER, 5 * sqrt(2)); 
        				cercle(centreX - largeurCarte - BORDER, hautCarteCentre + BORDER, 5 * sqrt(2)); 
        				cercle(centreX + largeurCarte + BORDER, hautCarteCentre + BORDER, 5 * sqrt(2)); 
        			}
        			
        			if (compteur.gauche == 0 || joueur3.etat == 5)
        			{
        				cercle(centreX - 6 * largeurCarte - BORDER, basCarteCote - BORDER, 5 * sqrt(2)); 
        				cercle(centreX - 4 * largeurCarte + BORDER, basCarteCote - BORDER, 5 * sqrt(2)); 
        				cercle(centreX - 6 * largeurCarte - BORDER, hautCarteCote + BORDER, 5 * sqrt(2)); 
        				cercle(centreX - 4 * largeurCarte + BORDER, hautCarteCote + BORDER, 5 * sqrt(2)); 
        			}
        			
        			if (compteur.droite == 0 || joueur2.etat == 5)
        			{
        				cercle(centreX + 4 * largeurCarte - BORDER, basCarteCote - BORDER, 5 * sqrt(2)); 
        				cercle(centreX + 6 * largeurCarte + BORDER, basCarteCote - BORDER, 5 * sqrt(2)); 
        				cercle(centreX + 4 * largeurCarte - BORDER, hautCarteCote + BORDER, 5 * sqrt(2)); 
        				cercle(centreX + 6 * largeurCarte + BORDER, hautCarteCote + BORDER, 5 * sqrt(2)); 
        			}
        			
        			//Pour le croupier
        			if(compteur.croupier == 0)
        			{
        				cercle(centreX - 2 * largeurCarte - BORDER - espacementMemePersonne, basCarteCroupier - BORDER, 5 * sqrt(2)); 
        				cercle(centreX + BORDER - espacementMemePersonne, basCarteCroupier - BORDER, 5 * sqrt(2)); 
        				cercle(centreX - 2 * largeurCarte - BORDER - espacementMemePersonne, hautCarteCroupier + BORDER, 5 * sqrt(2)); 
        				cercle(centreX + BORDER - espacementMemePersonne, hautCarteCroupier + BORDER, 5 * sqrt(2)); 
        			
        				cercle(centreX - BORDER + espacementMemePersonne, basCarteCroupier - BORDER, 5 * sqrt(2)); 
        				cercle(centreX + 2 * largeurCarte + BORDER + espacementMemePersonne, basCarteCroupier - BORDER, 5 * sqrt(2)); 
        				cercle(centreX - BORDER + espacementMemePersonne, hautCarteCroupier + BORDER, 5 * sqrt(2)); 
        				cercle(centreX + 2 * largeurCarte + BORDER + espacementMemePersonne, hautCarteCroupier + BORDER, 5 * sqrt(2)); 
        			}
        			
        			
        			couleurCourante(255, 255, 255);
        			//Pour les joueurs
        			if (compteur.centre == 0 || joueur1.etat == 5)
        			{
					cercle(centreX - largeurCarte, basCarteCentre, 3.5 * sqrt(2)); 
					cercle(centreX + largeurCarte, basCarteCentre, 3.5 * sqrt(2)); 
					cercle(centreX - largeurCarte, hautCarteCentre, 3.5 * sqrt(2)); 
					cercle(centreX + largeurCarte, hautCarteCentre, 3.5 * sqrt(2)); 
				}
				
				if (compteur.gauche == 0 || joueur3.etat == 5)
        			{
					cercle(centreX - 6 * largeurCarte, basCarteCote, 3.5 * sqrt(2)); 
					cercle(centreX - 4 * largeurCarte, basCarteCote, 3.5 * sqrt(2)); 
					cercle(centreX - 6 * largeurCarte, hautCarteCote, 3.5 * sqrt(2)); 
					cercle(centreX - 4 * largeurCarte, hautCarteCote, 3.5 * sqrt(2)); 
				}
				
				if (compteur.droite == 0 || joueur2.etat == 5)
        			{
					cercle(centreX + 4 * largeurCarte, basCarteCote, 3.5 * sqrt(2)); 
					cercle(centreX + 6 * largeurCarte, basCarteCote, 3.5 * sqrt(2)); 
					cercle(centreX + 4 * largeurCarte, hautCarteCote, 3.5 * sqrt(2)); 
					cercle(centreX + 6 * largeurCarte, hautCarteCote, 3.5 * sqrt(2)); 
				 }
				
				//Pour le croupier
				
				if(compteur.croupier == 0)
				{
					cercle(centreX - 2 * largeurCarte - espacementMemePersonne, basCarteCroupier, 3.5 * sqrt(2)); 
        				cercle(centreX - espacementMemePersonne, basCarteCroupier, 3.5 * sqrt(2)); 
        				cercle(centreX - 2 * largeurCarte - espacementMemePersonne, hautCarteCroupier, 3.5 * sqrt(2)); 
        				cercle(centreX - espacementMemePersonne, hautCarteCroupier, 3.5 * sqrt(2)); 
        			
        				cercle(centreX + espacementMemePersonne, basCarteCroupier, 3.5 * sqrt(2)); 
        				cercle(centreX + 2 * largeurCarte + espacementMemePersonne, basCarteCroupier, 3.5 * sqrt(2)); 
        				cercle(centreX + espacementMemePersonne, hautCarteCroupier, 3.5 * sqrt(2)); 
        				cercle(centreX + 2 * largeurCarte + espacementMemePersonne, hautCarteCroupier, 3.5 * sqrt(2)); 
        			}
				
				
				
				//fond des cartes
				//des joueurs
				couleurCourante(32, 168, 72);
				
				rectangle(centreX - largeurCarte , basCarteCentre, centreX + largeurCarte, hautCarteCentre); 
				
				rectangle(centreX - 6 * largeurCarte, basCarteCote, centreX - 4 * largeurCarte, hautCarteCote); 
				
				rectangle(centreX + 4 * largeurCarte, basCarteCote, centreX + 6 * largeurCarte, hautCarteCote); 
				
				//du croupier
				
				rectangle(centreX - 2 * largeurCarte - espacementMemePersonne, basCarteCroupier, centreX - espacementMemePersonne, hautCarteCroupier); 
				
				couleurCourante(0, 0, 0);
				rectangle(centreX + espacementMemePersonne, basCarteCroupier, centreX + 2 * largeurCarte + espacementMemePersonne, hautCarteCroupier); 
				
				
				//Pour les losanges
				
				couleurCourante(115, 251, 253);
				triangle(centreX - largeurCroix, milieuCarteCentre, centreX + largeurCroix, milieuCarteCentre, centreX, milieuCarteCentre + hauteurCroix);
				triangle(centreX - largeurCroix, milieuCarteCentre, centreX + largeurCroix, milieuCarteCentre, centreX, milieuCarteCentre - hauteurCroix);
				
				triangle(centreX - largeurCroix - 5 * largeurCarte, milieuCarteCote, centreX + largeurCroix - 5 * largeurCarte, milieuCarteCote, centreX - 5 * largeurCarte, milieuCarteCote + hauteurCroix);
				triangle(centreX - largeurCroix - 5 * largeurCarte, milieuCarteCote, centreX + largeurCroix - 5 * largeurCarte, milieuCarteCote, centreX - 5 * largeurCarte, milieuCarteCote - hauteurCroix);
				
				triangle(centreX - largeurCroix + 5 * largeurCarte, milieuCarteCote, centreX + largeurCroix + 5 * largeurCarte, milieuCarteCote, centreX + 5 * largeurCarte, milieuCarteCote + hauteurCroix);
				triangle(centreX - largeurCroix + 5 * largeurCarte, milieuCarteCote, centreX + largeurCroix + 5 * largeurCarte, milieuCarteCote, centreX + 5 * largeurCarte, milieuCarteCote - hauteurCroix);
				
				
				
				
				// Pour la somme des cartes
				couleurCourante(192, 192, 192);
				cercle(centreX, hautCarteCentre + hauteurFenetre()/20, largeurFenetre() / 55); // Joueur 1
				cercle(centreX + 5 * largeurCarte, hautCarteCote + hauteurFenetre()/20, largeurFenetre() / 55); //Joueur 2
				cercle(centreX - 5 * largeurCarte, hautCarteCote + hauteurFenetre()/20, largeurFenetre() / 55); //Joueur 3
				cercle(centreX, basCarteCroupier - hauteurFenetre()/20, largeurFenetre() / 55); //croupier
				
				//Pour les couleurs des sommes
				if(compteur.tour == 0)
				{
					couleurCourante(50, 130, 246);
				}
				
				else if(joueur1.etat == 5)
				{
					couleurCourante(255, 0, 0);
				}
				
				if(joueur1.etat == 0)
				{
					couleurCourante(255, 253, 83);
				}
				
				else
				{
					couleurCourante(0, 0, 0);
				}
				afficheChaine(sJ1, largeurPoliceSomme, centreX - tailleChaine(sJ1, largeurPoliceSomme)/2, hautCarteCentre + hauteurFenetre()/20 - tailleChaine("1", largeurPoliceSomme)/1.5);
				
				
				if(compteur.tour == 1)
				{
					couleurCourante(50, 130, 246);
				}
				
				else if(joueur2.etat == 5)
				{
					couleurCourante(255, 0, 0);
				}
				
				if(joueur2.etat == 0)
				{
					couleurCourante(255, 253, 83);
				}
				
				else
				{
					couleurCourante(0, 0, 0);
				}
				
				afficheChaine(sJ2, largeurPoliceSomme, centreX + 5 * largeurCarte - tailleChaine(sJ2, largeurPoliceSomme)/2, hautCarteCote + hauteurFenetre()/20 - tailleChaine("1", largeurPoliceSomme)/1.5);
				
				
				if(compteur.tour == 2)
				{
					couleurCourante(50, 130, 246);
				}
				
				else if(joueur3.etat == 5)
				{
					couleurCourante(255, 0, 0);
				}
				
				if(joueur3.etat == 0)
				{
					couleurCourante(255, 253, 83);
				}
				
				else
				{
					couleurCourante(0, 0, 0);
				}
				afficheChaine(sJ3, largeurPoliceSomme, centreX - 5 * largeurCarte - tailleChaine(sJ3, largeurPoliceSomme)/2, hautCarteCote + hauteurFenetre()/20 - tailleChaine("1", largeurPoliceSomme)/1.5);
				
				
				
				//Pour savoir quel joueur joue
				couleurCourante(curseurJ1[0], curseurJ1[1], curseurJ1[2]);
				rectangle(centreX - 1.5 * largeurCarte - BORDER, basCarteCentre - 3 * BORDER, centreX + 1.5 * largeurCarte + BORDER, basCarteCentre - 2.5 * BORDER); //joueur 1
				
				
				couleurCourante(curseurJ2[0], curseurJ2[1], curseurJ2[2]);
				rectangle(centreX + 3.5 * largeurCarte - BORDER, basCarteCote - 3 * BORDER, centreX + 6.5 * largeurCarte + BORDER, basCarteCote - 2.5 * BORDER); //joueur 2
				
				couleurCourante(curseurJ3[0], curseurJ3[1], curseurJ3[2]);
				rectangle(centreX - 6.5 * largeurCarte - BORDER, basCarteCote - 3 * BORDER, centreX - 3.5 * largeurCarte + BORDER, basCarteCote - 2.5 * BORDER); //joueur 3
				
						
				
				
				
				//Jetons
				couleurCourante(jetons[compteur.cJeton].couleur[0], jetons[compteur.cJeton].couleur[1], jetons[compteur.cJeton].couleur[2]);
				
				
				cercle(centreDeplGaucheX1, centreDeplGaucheY1, rayonDeplacementGauche1);
				
				
				cercle(centreDeplDroiteX1, centreDeplDroiteY1, rayonDeplacementDroite1);

				if(compteur.dJeton == 0)
				{				
					cercle(centreJetonX, centreJetonY, largeurJeton);
				}
				
				if (compteur.cJeton == 5)
				{
					couleurCourante(255, 255, 255);
				}
				
				else if (compteur.cJeton != 5)
				{
					couleurCourante(0, 0, 0);
				}
				
				if(compteur.dJeton == 0)
				{
					afficheChaine(jetons[compteur.cJeton].valeur, largeurPoliceJeton, centreJetonX - tailleChaine(jetons[compteur.cJeton].valeur, largeurPoliceJeton)/2, centreJetonY - tailleChaine("1", largeurPoliceJeton)/1.5);
				}
				
				if (compteur.dJeton == 1)
				{
					afficheChaine(JDchaine1, largeurPoliceJeton, centreDeplGaucheX1 - tailleChaine(JDchaine1, largeurPoliceJeton)/2, centreDeplGaucheY1 - tailleChaine("1", largeurPoliceJeton)/1.5);
				}
				
				if (compteur.dJeton == 2)
				{
					afficheChaine(JGchaine1, largeurPoliceJeton, centreDeplDroiteX1 - tailleChaine(JGchaine1, largeurPoliceJeton)/2, centreDeplDroiteY1 - tailleChaine("1",largeurPoliceJeton)/1.5);
				}

				
				if(compteur.cJeton < 7)
				{
					couleurCourante(0, 0, 0);
					
					rectangle(centreJetonX + tailleFleche,  centreJetonY - flecheY, centreJetonX + flecheX, centreJetonY + flecheY);
				
					triangle(centreJetonX + flecheX, centreJetonY + 1.5 *flecheY, centreJetonX + flecheX, centreJetonY - 1.5 * flecheY, centreJetonX + 1.3 * flecheX, centreJetonY);
				
					couleurCourante(jetons[compteur.cJeton + 1].couleur[0], jetons[compteur.cJeton + 1].couleur[1], jetons[compteur.cJeton + 1].couleur[2]);
					
					
				cercle(centreDeplDroiteX2, centreDeplDroiteY2, rayonDeplacementDroite2);
				
					if(compteur.dJeton == 0)
					{
						cercle(centreJetonDroite, centreJetonY, largeurJeton);
					}
					
					if (compteur.cJeton + 1 == 5)
					{
						couleurCourante(255, 255, 255);
					}
				
					else if (compteur.cJeton + 1 != 5)
					{
						couleurCourante(0, 0, 0);
					}
					
					if(compteur.dJeton == 0)
					{
						afficheChaine(jetons[compteur.cJeton + 1].valeur, largeurPoliceJeton, centreJetonX  + 1.3 * flecheX + tailleFleche - tailleChaine(jetons[compteur.cJeton + 1].valeur, largeurPoliceJeton)/2, centreJetonY - tailleChaine("1", largeurPoliceJeton)/1.5);
					}
					
					if (compteur.dJeton == 2)
					{
						afficheChaine(JGchaine2, largeurPoliceJeton, centreDeplDroiteX2 - tailleChaine(JGchaine2, largeurPoliceJeton)/2, centreDeplDroiteY2 - tailleChaine("1", largeurPoliceJeton)/1.5);
					}
						
				}
				
				if (compteur.cJeton > 0)
				{
				
					couleurCourante(jetons[compteur.cJeton - 1].couleur[0], jetons[compteur.cJeton - 1].couleur[1], jetons[compteur.cJeton - 1].couleur[2]);
				
					cercle(centreDeplGaucheX2, centreDeplGaucheY2, rayonDeplacementGauche2);
				
					couleurCourante(0, 0, 0);	
					
					rectangle(centreJetonX - tailleFleche,  centreJetonY - flecheY, centreJetonX - flecheX, centreJetonY + flecheY);
				
					triangle(centreJetonX - flecheX, centreJetonY + 1.5 *flecheY, centreJetonX - flecheX, centreJetonY - 1.5 * flecheY, centreJetonX - 1.3 * flecheX, centreJetonY);
				
					couleurCourante(jetons[compteur.cJeton - 1].couleur[0], jetons[compteur.cJeton - 1].couleur[1], jetons[compteur.cJeton - 1].couleur[2]);
				
					if(compteur.dJeton == 0)
					{
						cercle(centreJetonGauche, centreJetonY, largeurJeton);
					}
					
					if (compteur.cJeton - 1 == 5)
					{
						couleurCourante(255, 255, 255);
					}
				
					else if (compteur.cJeton - 1 != 5)
					{
						couleurCourante(0, 0, 0);
					}
					
					if(compteur.dJeton == 0)
					{
						afficheChaine(jetons[compteur.cJeton - 1].valeur, largeurPoliceJeton, centreJetonX  - 1.3 * flecheX - tailleFleche - tailleChaine(jetons[compteur.cJeton - 1].valeur, largeurPoliceJeton)/2, centreJetonY - tailleChaine("1", largeurPoliceJeton)/1.5);
					}
						
					if (compteur.dJeton == 1)
					{
						afficheChaine(JDchaine2, largeurPoliceJeton, centreDeplGaucheX2 - tailleChaine(JDchaine2, largeurPoliceJeton)/2, centreDeplGaucheY2 - tailleChaine("1", largeurPoliceJeton)/1.5);
					}
					


				}
				
				couleurCourante(96, 96, 96);
				//menu
				
				
				
				rectangle(debutBoutonX + 1 * largeurBouton + 1 * espacementBouton, debutBoutonY, debutBoutonX + 2 * largeurBouton + 1 * espacementBouton,hauteurBouton);
				rectangle(debutBoutonX + 2 * largeurBouton + 2 * espacementBouton, debutBoutonY, debutBoutonX + 3 * largeurBouton + 2 * espacementBouton,hauteurBouton);
				rectangle(debutBoutonX + 3 * largeurBouton + 3 * espacementBouton, debutBoutonY, debutBoutonX + 4 * largeurBouton + 3 * espacementBouton,hauteurBouton);
				
				if (transfert.tabAffiche[2] == 1)
				{
					rectangle(debutBoutonX + 4 * largeurBouton + 4 * espacementBouton, debutBoutonY, debutBoutonX + 5 * largeurBouton + 4 * espacementBouton,hauteurBouton);
					
					couleurCourante(255,255,255);
					afficheChaine(doubler, largeurChaineBouton,debutBoutonX +4*largeurBouton + 5 *espacementBouton- tailleChaine(doubler,largeurChaineBouton)/2, debutBoutonY + hauteurBouton/4 - tailleChaine("1",largeurChaineBouton)/1.5);
				}
				
				if (transfert.tabAffiche[3] == 1)
				{
					couleurCourante(96, 96, 96);
					rectangle(debutBoutonX + 5 * largeurBouton + 5 * espacementBouton, debutBoutonY, debutBoutonX + 6 * largeurBouton + 5 * espacementBouton,hauteurBouton);
					
					couleurCourante(255,255,255);
					afficheChaine(split, largeurChaineBouton,debutBoutonX + 5 * largeurBouton + 6 * espacementBouton- tailleChaine(split,largeurChaineBouton)/2, debutBoutonY + hauteurBouton/4 - tailleChaine("1",largeurChaineBouton)/1.5);
				}
				
				couleurCourante(255,255,255);
				
				afficheChaine(hit, largeurChaineBouton,debutBoutonX + 1 * largeurBouton + 2 * espacementBouton- tailleChaine(hit,largeurChaineBouton)/2, debutBoutonY + hauteurBouton/4- tailleChaine("1",largeurChaineBouton)/1.5);
				afficheChaine(stand, largeurChaineBouton,debutBoutonX + 2 *largeurBouton + 3 * espacementBouton-tailleChaine(stand,largeurChaineBouton)/2, debutBoutonY + hauteurBouton/4 - tailleChaine("1",largeurChaineBouton)/1.5);
				afficheChaine(push, largeurChaineBouton,debutBoutonX + 3 * largeurBouton + 4 * espacementBouton- tailleChaine(push,largeurChaineBouton)/2, debutBoutonY + hauteurBouton/4- tailleChaine("1",largeurChaineBouton)/1.5);
				
			
				
				//Probabilites
				couleurCourante(96, 96, 96);
				rectangle(MARGIN, 2 * hauteurFenetre()/3, largeurFenetre()/5, hauteurFenetre() - MARGIN);

				couleurCourante(255, 255, 255);
				afficheChaine(probabilites[0], 15, 20, 795 - tailleChaine("1",15)/1.5);
				
				
				ecrisImage(largeurFenetre()* 4/5, hauteurFenetre() * 3/5, paquetCartes->largeurImage, paquetCartes->hauteurImage, paquetCartes->donneesRGB);
				
				ecrisImage(centreX + espacementMemePersonne - BORDER, basCarteCroupier - BORDER, carteCachee->largeurImage, carteCachee->hauteurImage, carteCachee->donneesRGB);
				
				
				
				// Pour le joueur 1 (centre)
				
				if (joueur1.etat != 5)
				{
					if(compteur.centre > 2)
					{
						ecrisImage(centreX - largeurCarte, basCarteCentre, paquetCartes->largeurImage, paquetCartes->hauteurImage, paquetCartes->donneesRGB);
					}
				
					if(compteur.centre < 3)
					{
						ecrisImage(centreX - largeurCarte, basCarteCentre, cartesCentre[0]->largeurImage, cartesCentre[0]->hauteurImage, cartesCentre[0]->donneesRGB);
					}
				
					ecrisImage(centreX - 0.65 * largeurCarte, basCarteCentre, cartesCentre[1]->largeurImage, cartesCentre[1]->hauteurImage, cartesCentre[1]->donneesRGB);
					
					if(compteur.centre >= 1 && compteur.centre < 3)
					{
						ecrisImage(centreX - 0.3 * largeurCarte, basCarteCentre, cartesCentre[2]->largeurImage, cartesCentre[2]->hauteurImage, cartesCentre[2]->donneesRGB);
					}
				
					if(compteur.centre == 2)
					{
						ecrisImage(centreX + 0.05 * largeurCarte, basCarteCentre, cartesCentre[3]->largeurImage, cartesCentre[3]->hauteurImage, cartesCentre[3]->donneesRGB);
					}
				}
				
				
				///Pour le joueur 2 (droite)
				
				if(joueur2.etat != 5)
				{
					
					if(compteur.droite > 2)
					{
						ecrisImage(centreX + 4 * largeurCarte, basCarteCote, paquetCartes->largeurImage, paquetCartes->hauteurImage, paquetCartes->donneesRGB);
					}
					
						if(compteur.droite < 3)
					{
						ecrisImage(centreX + 4 * largeurCarte, basCarteCote, cartesDroite[0]->largeurImage, cartesDroite[0]->hauteurImage, cartesDroite[0]->donneesRGB);
					}
			
					ecrisImage(centreX + 4.35 * largeurCarte, basCarteCote, cartesDroite[1]->largeurImage, cartesDroite[1]->hauteurImage, cartesDroite[1]->donneesRGB);
					
					if(compteur.droite >= 1 && compteur.droite < 3)
					{
						ecrisImage(centreX + 4.70 * largeurCarte, basCarteCote, cartesDroite[2]->largeurImage, cartesDroite[2]->hauteurImage, cartesDroite[2]->donneesRGB);
					}
					
					if(compteur.droite == 2)
					{
						ecrisImage(centreX + 5.05 * largeurCarte, basCarteCote, cartesDroite[3]->largeurImage, cartesDroite[3]->hauteurImage, cartesDroite[3]->donneesRGB);
					}
				}
				
				
				//Pour le joueur 3 (gauche)
				
				if(joueur3.etat != 5)
				{
					if(compteur.gauche > 2)
					{
						ecrisImage(centreX - 6 * largeurCarte, basCarteCote, paquetCartes->largeurImage, paquetCartes->hauteurImage, paquetCartes->donneesRGB);
					}
					
					if(compteur.gauche < 3)
					{
						ecrisImage(centreX - 6 * largeurCarte, basCarteCote, cartesGauche[0]->largeurImage, cartesGauche[0]->hauteurImage, cartesGauche[0]->donneesRGB);
					}
					
					ecrisImage(centreX - 5.65 * largeurCarte, basCarteCote, cartesGauche[1]->largeurImage, cartesGauche[1]->hauteurImage, cartesGauche[1]->donneesRGB);
			
					if(compteur.gauche >= 1 && compteur.gauche < 3)
					{
						ecrisImage(centreX - 5.3 * largeurCarte, basCarteCote, cartesGauche[2]->largeurImage, cartesGauche[2]->hauteurImage, cartesGauche[2]->donneesRGB);
					}
					
					if(compteur.gauche == 2)
					{
						ecrisImage(centreX - 4.95 * largeurCarte, basCarteCote, cartesGauche[3]->largeurImage, cartesGauche[3]->hauteurImage, cartesGauche[3]->donneesRGB);
					}
				}				
				
				
				//Pour le croupier
				/*if(compteur.croupier >= 1)
				{
					ecrisImage(centreX - 2 * largeurCarte - espacementMemePersonne, basCarteCroupier, cartesCroupier[0]->largeurImage, cartesCroupier[0]->hauteurImage, cartesCroupier[0]->donneesRGB);
				}
				if(compteur.croupier >= 2)
				{
					ecrisImage(centreX - 1.5 * largeurCarte - espacementMemePersonne, basCarteCroupier, cartesCroupier[1]->largeurImage, cartesCroupier[1]->hauteurImage, cartesCroupier[1]->donneesRGB);
				}
				if(compteur.croupier >= 3)
				{
					ecrisImage(centreX - largeurCarte - espacementMemePersonne, basCarteCroupier, cartesCroupier[2]->largeurImage, cartesCroupier[2]->hauteurImage, cartesCroupier[2]->donneesRGB);
				}*/
				
				
			}
			
             		
             		break;
			
			
		case Clavier:
			//printf("%c : ASCII %d\n", caractereClavier(), caractereClavier());

			switch (caractereClavier())
			{
				case 'Q': /* Pour sortir quelque peu proprement du programme */
				case 'q':
				
					for(int i = 0; i < 52; i++)
					{
						libereDonneesImageRGB(&cartes[i]); 
					}

					termineBoucleEvenements();
					break;

				case 'F':
				case 'f':
					pleinEcran = !pleinEcran; // Changement de mode plein ecran
					if (pleinEcran)
						modePleinEcran();
					else
						redimensionneFenetre(LargeurFenetre, HauteurFenetre);
					break;

				case 'R':
				case 'r':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 20 millisecondes (rapide)
					demandeTemporisation(20);
					break;

				case 'L':
				case 'l':
					// Configure le systeme pour generer un message Temporisation
					// toutes les 100 millisecondes (lent)
					demandeTemporisation(100);
					break;

				case 'S':
				case 's':
					// Configure le systeme pour ne plus generer de message Temporisation
					demandeTemporisation(-1);
					break;
					
				case '1':
					afficheProba(probabilites, Pcpt, prob, hProba);
					
					break;
			}
			break;
			
		case ClavierSpecial:
			printf("ASCII %d\n", toucheClavier());
			break;

		case BoutonSouris:
			if (etatBoutonSouris() == GaucheAppuye)
			{
			   if (abscisseSouris() >= start.xGauche && abscisseSouris() <= start.xDroite && ordonneeSouris() >= start.yBas && ordonneeSouris() <= start.yHaut && compteur.cMenu == 0)
			   {
			   	
			   	compteur.cMenu = 1;
			   	centreDeplGaucheX1 = centreJetonDroite;
			   	centreDeplGaucheY1 = centreJetonY;
			   	
			   	centreDeplGaucheX2 = centreJetonX;
			   	centreDeplGaucheY2 = centreJetonY;

			   }
			   
			   else if (abscisseSouris() >= (centreJetonX  + 1.3 * flecheX) && abscisseSouris() <= (centreJetonX  + 1.3 * flecheX + 80) && ordonneeSouris() >= (centreJetonY - 20) && ordonneeSouris() <= (centreJetonY + 20) && compteur.cMenu == 1 && compteur.cJeton < 7 && compteur.dJeton == 0)
			   {
			   	compteur.cJeton++;
			   	centreDeplGaucheX1 = centreJetonDroite;
			   	centreDeplGaucheY1 = centreJetonY;
			   	rayonDeplacementGauche1 = largeurJeton;
				deplacementGauche1 = 1.3 * flecheX + tailleFleche;
			   	deplaceJetonVersGauche(PcentreDeplGaucheX1, PcentreDeplGaucheY1, PrayonDeplacementGauche1, PdeplacementGauche1, Pcpt, centreDeplGaucheXRef, JDchaine1, jetons[compteur.cJeton].valeur);
			   	
			   	centreDeplGaucheX2 = centreJetonX;
			   	centreDeplGaucheY2 = centreJetonY;
			   	rayonDeplacementGauche2 = largeurJeton;
				deplacementGauche2 = 1.3 * flecheX + tailleFleche;
			   	deplaceJetonVersGauche(PcentreDeplGaucheX2, PcentreDeplGaucheY2, PrayonDeplacementGauche2, PdeplacementGauche2, Pcpt, centreDeplGaucheXRef, JDchaine2, jetons[compteur.cJeton - 1].valeur);
			   	compteur.dJeton = 1;
			   	
			   }
			   
			   
			   
			   else if (abscisseSouris() <= (centreJetonX  - 1.3 * flecheX) && abscisseSouris() >= (centreJetonX  - 1.3 * flecheX - 80) && ordonneeSouris() >= (centreJetonY - 20) && ordonneeSouris() <= (centreJetonY + 20) && compteur.cMenu == 1 && compteur.cJeton > 0 && compteur.dJeton == 0)
			   {
			   	compteur.cJeton--;

			   	centreDeplDroiteX1 = centreJetonGauche;
			   	centreDeplDroiteY1 = centreJetonY;
			   	rayonDeplacementDroite1 = largeurJeton;
				deplacementDroite1 = (-1) *(1.3 * flecheX + tailleFleche);
			   	deplaceJetonVersDroite(PcentreDeplDroiteX1, PcentreDeplDroiteY1, PrayonDeplacementDroite1, PdeplacementDroite1, Pcpt, centreDeplDroiteXRef, JGchaine1, jetons[compteur.cJeton].valeur);
			   	
			   	centreDeplDroiteX2 = centreJetonX;
			   	centreDeplDroiteY2 = centreJetonY;
			   	rayonDeplacementDroite2 = largeurJeton;
				deplacementDroite2 = (-1) *(1.3 * flecheX + tailleFleche);
			   	deplaceJetonVersDroite(PcentreDeplDroiteX2, PcentreDeplDroiteY2, PrayonDeplacementDroite2, PdeplacementDroite2, Pcpt, centreDeplDroiteXRef, JGchaine2, jetons[compteur.cJeton + 1].valeur);
			   	
			   	compteur.dJeton = 2;
			   }
			   
			   //hit
			   
			   else if (abscisseSouris() >= debutBoutonX + 1 * largeurBouton + 1 * espacementBouton && abscisseSouris() <= debutBoutonX + 2 * largeurBouton + 1 * espacementBouton && ordonneeSouris() >= debutBoutonY && ordonneeSouris() <= hauteurBouton) 
              		 {
              		 	if(compteur.tour == 0)
              		 	{
                			compteur.centre++;
                		}
                		
                		else if(compteur.tour == 1)
                		{
                			compteur.droite++;
                		}
                		
                		else if(compteur.tour == 2)
                		{
                			compteur.gauche++;
                		}
                		
				indiceAction = 1;
               		 } 

			// stand
               		else if (abscisseSouris() >= debutBoutonX + 2 * largeurBouton + 2 * espacementBouton && abscisseSouris() <= debutBoutonX + 3 * largeurBouton + 2 * espacementBouton && ordonneeSouris() >= debutBoutonY && ordonneeSouris() <= hauteurBouton) 
               		{ 
               			indiceAction = 2;
               		} 

               		else if (abscisseSouris() >= debutBoutonX + 3 * largeurBouton + 3 * espacementBouton && abscisseSouris() <= debutBoutonX + 4 * largeurBouton + 3 * espacementBouton && ordonneeSouris() >= debutBoutonY && ordonneeSouris() <= hauteurBouton) 
               		{ 
                		
               		} 

               		else if (abscisseSouris() >= debutBoutonX + 4 * largeurBouton + 4 * espacementBouton && abscisseSouris() <= debutBoutonX + 5 * largeurBouton + 4 * espacementBouton && ordonneeSouris() >= debutBoutonY && ordonneeSouris() <= hauteurBouton) 
               		{ 
                		
               		} 

               		else if (abscisseSouris() >= debutBoutonX + 5 * largeurBouton + 5 * espacementBouton && abscisseSouris() <= debutBoutonX + 6 * largeurBouton + 5* espacementBouton && ordonneeSouris() >= debutBoutonY && ordonneeSouris() <= hauteurBouton) 
               		{ 
               			
               		} 


                	else if (abscisseSouris() >= largeurFenetre()/4 && abscisseSouris() <= 3 * largeurFenetre()/4 && ordonneeSouris() >= hauteurFenetre() * 17/28 && ordonneeSouris() <= 5 * hauteurFenetre()/7) 
               		{ 
               			 
               		} 
 
			   
			   
			   //fin
            		}
            		
            		
			break;
		
		case Souris: // Si la souris est deplacee
			break;
		
		case Inactivite: // Quand aucun message n'est disponible
			break;
		
		case Redimensionnement: // La taille de la fenetre a ete modifie ou on est passe en plein ecran
			// Donc le systeme nous en informe
				
			
			printf("Largeur : %d\t", largeurFenetre());
			printf("Hauteur : %d\n", hauteurFenetre());
			break;
	}
}
