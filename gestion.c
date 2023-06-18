#include <stdio.h> // Pour pouvoir utilisé printf() et scanf()
#include <stdlib.h> // Pour pouvoir utilisé exit()
#include <stdbool.h> // Pour pouvoir utilisé le booléens, True et False
#include <string.h> // Pour pouvoir utilisé les fonctions liées aux chaines de caractères
#include <time.h> // Pour pouvoir utilisé le random
#include<unistd.h> // Pour pouvoir utilisé le sleep(), ce qui fait une pause entre deux actions
#include "gestion.h"

//Les arguments du main dans l'ordre sont : Capital du Joueur , Hauteur de la fenètre, Largeur de la fenètre


/*Joueur initJoueur(float capital, int mise, float gain, Transfert transfert,int etat, int nbCartes)
{
	// sleep(0.1);
	Carte cartesJoueur[21] = {0};
    cartesJoueur[0] = choisiCarte(&transfert);
    cartesJoueur[1] = choisiCarte(&transfert);
	cartesJoueur[0].numero = 5;
	cartesJoueur[0].couleur = 2;
	cartesJoueur[1].numero = 11;
	cartesJoueur[1].couleur = 2;
	cartesJoueur[2].numero = 10;
	cartesJoueur[2].couleur = 2;
	Joueur joueur = {capital, mise, gain, cartesJoueur, etat, nbCartes};
	return joueur;
} */

Joueur initJoueur(float Capital, Transfert transfert){
    Joueur joueur = {0};
    joueur.capital = Capital;
    joueur.mise = 0;
    //joueur.mise = choisiMise(&Capital, indiceJeton, joueur.mise);
    // Le gain est mit à 0;
    joueur.cartes[0] = choisiCarte(&transfert, &joueur);
    joueur.cartes[1] = choisiCarte(&transfert, &joueur);

    joueur.etat = 1;
    joueur.nbCartes = 3;

    return joueur;

}


//pour couleur 1 = trefle, 2 = pique, 3 = carreau, 4 = coeur
Carte choisiCarte(Transfert* transfert, Joueur* joueur)
{
	int paquetCarte[52] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 
				,11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 
				,11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 
				,11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10}; 
	
    /*int tab_numero[13] = {11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    int tab_couleur[4] = {1, 2, 3, 4};*/
    int iteration = 4;
    Carte c = {0};
    while(iteration == 4)
    {

        iteration = 0;
        
        int numeroRand = rand() % 52;
        int couleurRand = 0;
        if (numeroRand < 13)
        {
        	couleurRand = 1;// trefle
        }
        else if (numeroRand < 26)
        {
        	couleurRand = 2;// pique
        }
        else if (numeroRand < 39)
        {
        	couleurRand = 3;// carreau
        }
        else
        {
        	couleurRand = 4;// coeur
        }
        // int couleurRand = rand() % 4;
        /*printf("Le numéro aléatoire est : %d\n",numero );
        printf("La couleur aléatoire est : %d\n",coul );*/
        for (int i = 0; i < transfert->nbCartes; ++i)
        {
            if(transfert->sorti[i].numero == paquetCarte[numeroRand] && transfert->sorti[i].couleur == couleurRand)
            {
                iteration ++;
            }
        }
        if (iteration != 4){
            c.numero = paquetCarte[numeroRand]; //valeur de la carte 
            for(int i = 0; i < 21; i++)
            {
            	if(joueur->numeroRand[i] == 0)
            	{
            		joueur->numeroRand[i] = numeroRand;
            		break;
            	}
            }
            c.couleur = couleurRand;
        }
    }

    /*transfert->sorti[transfert->nbCartes] = c;
    (transfert->nbCartes)  ++;*/
    return c;
}

// Le joueur appuie sur une des mises, ce qui met l'indice de ce jeton en paramètre de cette fonction. 
// Grâce à cet indice on peut connaître la valeur du jeu jeton clické.
// On vérifie alors si le joueur à le capital nécessaire pour mettre cette mise.
// Si c'est le cas alors on renvoie la mise, et on déduit la mise à la valeur capital.
// Si ce n'est pas le cas on écris un message d'erreur, comme quoi vous n'avez pas le capital nécessaire à cette mise. Et on renvoie 0.
// Mise[indiceJeton] = la valeur du jeton clické.
int choisiMise(float* capital, const int indiceJeton, int mise)
{
	int MISE[8] = {1,5,10,20,50,100,500,1000};
	if (MISE[indiceJeton] <= *capital)
	{
		*capital -= MISE[indiceJeton];
		mise += MISE[indiceJeton];
		return mise;
	}
	printf("Vous avez saisi une mise supérieur à votre capital\nVeuillez choisir une mise qui soit dans vos moyens\n");
	//Au lieux d'un printf , il faudrait afficher un message dans "case Affichage".
	return mise;
}

//on lance la fonction menu pour le joueur 1, puis on lance la fonction menu pour la banque.
//Solution1 :Si il y a d'autres joueur on peut sois créer une autre fonction similaire mais avec le nb joueur qui joue.
//Solution 2 : Sois on peut rester sur cette fonction mais on peut créer un etat (vie par exemple), qui nous permet de savoir si le joueur joue ou non.
//La deuxième solution requiert de créer les deux autres joueur au début mais de décider de leur état en fonction du nb joueur choisi au début du jeu.

/*void passeTour(Joueur joueur1, Joueur joueur2, Joueur joueur3, Banque banque, int cpt, Transfert transfert)
{
	cpt = 1;
	switch(cpt)
		case 1:
			Menu(joueur1, transfert);

		case 2:
			Menu(joueur2, transfert);

		case 3:
			Menu(joueur3, transfert);
		case 4:
			//Ordi pour la banque.
			//On met le compteur à 0 pour être sûr que même si la fonction est relancé elle ne fera pas n'importe quoi.
			//Les compteur seront chnager dans le fichier gfx, car cpt va être changé à la fin des affichage d'un tour. Donc quand le joueur aura fini de jouer cela va changer cpt.
			cpt = 0;
}*/



int AdditionJoueur(Joueur joueur)
{
	int somme = 0;
	int indice = -1;
	for (int i = 0; i < joueur.nbCartes ; ++i)
	{	
		if (joueur.cartes[i].numero == 11)
		{
			indice = i;
		}
		somme += joueur.cartes[i].numero;
	}
	if (somme > 21)
	{
		if (indice != -1)// on vérifie s'il y a un AS dans le jeu du joueur. Si oui on le transforme en 1 et on re-calcul. 
		{
			joueur.cartes[indice].numero = 1;
			somme -= 10;
		}
	}
	return somme;
}

int AdditionBanque(Banque banque)
{
	int somme = 0;
	int indice = -1;
	for (int i = 0; i < banque.nbCartes ; ++i)
	{
		somme += banque.cartes[i].numero;
		if (banque.cartes[i].numero == 11)
		{
			indice = i;
		}
	}
	if (somme > 21)
	{
		if (indice != -1)
		{
			banque.cartes[indice].numero = 1;
			somme -= 10;
		}
	}
	return somme;
}


int bustJoueur(Joueur joueur)
{
	if (AdditionJoueur(joueur) > 21)
	{
		//tu bust, donc on renvoie 0;
		return 0;
	}
	return 1;
}

int bustBanque(Banque banque)
{
	if (AdditionBanque(banque) > 21)
	{
		//tu bust, donc on renvoie 0;
		return 0;
	}
	return 1;
}



int VerifieVictoire(Joueur joueur, Banque banque)
{
	if (AdditionJoueur(joueur) > AdditionBanque(banque))
	{
		//Le joueur a gagné contre la banque
		return 1;
	}
	else if (AdditionJoueur(joueur) < AdditionBanque(banque))
	{
		//Le joueur a perdu, donc la banque a gagné
		return 0;
	}

	else
	{
		//Le joueur est à égalité avec la banque il reprend sa mise
		return 2;
	}
}


//La structure transfert permet d'avoir des variables qu'on utilise souvent dans tout nos fichiers.
//Le tableau "tabAffiche", permet de savoir si un bouton est affiché ou non et donc pour savoir comment gérer son espace de click.
//transfert.tabAffiche[0] : bouton hit
//transfert.tabAffiche[1] : bouton stand
//transfert.tabAffiche[2] : bouton double
//transfert.tabAffiche[3] : bouton split
//transfert.tabAffiche[4] : bouton assurance
//transfert.tabAffiche[5] : bouton push (abandon)
//transfert.tabAffiche[6] : bouton tirerCarte (pioche)
//transfert.tabAffiche[7] : bouton resetMise (permet de reset la mise)
//transfert.tabAffiche est modifié dans la fonction menu même si il n'est pas renvoyé car c'est un tableau.
void menu(Joueur* joueur, Banque* banque, int* indiceAction, Transfert* transfert)
{

    //boucle qui durera jusqu'à ce que le joueur ait fini son tour
    	// GFX fonction qui affiche le bouton hit
    	transfert->tabAffiche[0] = 1; // c'est pour le bouton hit

        // GFX fonction qui affiche le bouton stand
        transfert->tabAffiche[1] = 1;// c'est pour le bouton stand

        // GFX fonction qui affiche le bouton push
        transfert->tabAffiche[5] = 1;// c'est pour le bouton push

        if (joueur->mise <= joueur->capital ){
            // GFX fonction qui affiche le bouton double
            transfert->tabAffiche[2] = 1;// c'est pour le bouton double
        }

        //on regarde si c'est le début de la partie
        if (joueur->cartes[2].numero == 0){

            // on reverifie le capital car le split double la mise
            if (joueur->cartes[0].numero == joueur->cartes[1].numero && joueur->mise <= joueur->capital){
                // GFX fonction gfx qui affiche le bouton split
                transfert->tabAffiche[3] = 1;// c'est pour le bouton split
            }

            if (banque->cartes[0].numero == 11){
                // GFX fonction qui affiche le bouton assurance
                transfert->tabAffiche[4] = 1;// c'est pour le bouton assurance
            }
        }

        // GFX doit attendre que l'un des boutons soit cliqué et retourne l'indice du bouton cliqué ici 3 pour l'exemple
        // le lancement de la fonction faitAction() se fera directement dans les différentes fonctions du gfx (dans la partie case click)
        faitAction(joueur, banque, indiceAction, *transfert);
        
}


void faitAction(Joueur* joueur, Banque* banque, int* indiceAction, Transfert transfert)
{
    switch(*indiceAction)
    {
      		case 1:
			hit(joueur, transfert);
			break;

		case 2:
			stand(joueur);
			break;

		case 3:
			doubler(joueur, transfert);
			break;
        
        	case 4:
			// joueur = split(&joueur, transfert);
			break;

        	case 5:
            		assurance(joueur, banque);
            		break;

        	case 6:
            		push(joueur);
            		break;
    }
	*indiceAction = 0;
}



void hit(Joueur* joueur, Transfert transfert)
{
    joueur->cartes[joueur->nbCartes] = choisiCarte(&transfert, joueur);

    joueur->nbCartes ++;
    
    if (bustJoueur(*joueur) == 0 && joueur->etat == 3){
        joueur->etat = 4;
    }
    if (bustJoueur(*joueur) == 0){
        // etat 5 si le joueur bust et la banque n'aura pas à s'occuper de ce joueur pour savoir s'il gagne ou non
        joueur->etat = 5;
    }

}

void stand(Joueur* joueur)
{
    // GFX faire une animation de changement de joueur
    joueur->etat = 2;

}

void doubler(Joueur* joueur, Transfert transfert)
{
    // pas besoins de verifier si le joueur a le capital necessaire car c'est déjà fait
    joueur->capital -= joueur->mise;
    joueur->mise = joueur->mise * 2;
    // GFX changer en conséquent l'affichage sur la table de jeu
    hit(joueur, transfert);
    stand(joueur);
    
    if (bustJoueur(*joueur) == 0 && joueur->etat == 3){
        joueur->etat = 4;
    }
    if (bustJoueur(*joueur) == 0){
        // etat 5 si le joueur bust et la banque n'aura pas à s'occuper de ce joueur pour savoir si il gagne ou non
        joueur->etat = 5;
    }

}

//Pour l'instant je met la fonction split en commentaire car elle demande de renvoyer plusieurs variables mais ce n'est pas possible en c.
// A VOIR !!
/*Joueur split(Joueur joueur, Transfert transfert)
{

    
    Banque banque;
    joueur.capital -= joueur.mise;

    Joueur joueurSplit1;
    Joueur joueurSplit2;

    joueurSplit1.mise = joueur.mise;
    joueurSplit1.cartes[0] = joueur.cartes[0];
    joueurSplit1.cartes[1] = choisiCarte(transfert.sorti);
    joueurSplit1.etat = joueur.etat;

    joueurSplit2.mise = joueur.mise;
    joueurSplit2.cartes[1] = joueur.cartes[1];
    joueurSplit2.cartes[1] = choisiCarte(transfert.sorti);
    joueurSplit2.etat = joueur.etat;

    menu(joueurSplit1, banque, transfert);
    menu(joueurSplit2, banque, transfert);

    if (bustJoueur(joueur) == 0){
        // etat 5 si le joueur bust et la banque n'aura pas à s'occuper de ce joueur pour savoir si il gagne ou non
        joueur.etat = 5;
    }
    return joueurSplit1, joueurSplit2;
}*/

void assurance(Joueur* joueur, Banque* banque)
{
    // etat 3 car la banque lorsqu'elle a un as et qu'elle va retourner sa carte, va vérifier si un joueur avait pris une assurance grace à etat = 3
    joueur->etat = 3;

}

void push(Joueur* joueur)
{
    // GFX faire une animation de changement de joueur
    joueur->capital += joueur->mise / 2;
    joueur->etat = 2;
}


void victoire(Joueur joueur1, Joueur joueur2, Joueur joueur3, Banque banque)
{
    //regardons si les joueurs n'ont pas bust
    //regardons si la banque a bust
    if (banque.etat == 2){
        if (bustJoueur(joueur1) == 1){
            initVictoire(joueur1);
        }
        if (bustJoueur(joueur2) == 1){
            initVictoire(joueur2);
        }
        if (bustJoueur(joueur3) == 1){
            initVictoire(joueur3);
        }
    }
    else {

        if (verifieVictoire(joueur1, banque) == 1){
        // GFX afficher une victoire du joueur
        }

        else if (verifieVictoire(joueur1, banque) == 0){
            // GFX afficher une défaite du joueur
        }


        if (verifieVictoire(joueur2, banque) == 1){
            // GFX afficher une victoire du joueur
        }

        else if (verifieVictoire(joueur2, banque) == 0){
            // GFX afficher une défaite du joueur
        }


        if (verifieVictoire(joueur3, banque) == 1){
            // GFX afficher une victoire du joueur
        }

        else if (verifieVictoire(joueur3, banque) == 0){
            // GFX afficher une défaite du joueur
        }
    }
}

//fonction qui réinitialise à 0 un joueur et lui donne ses gains
Joueur initVictoire(Joueur joueur)
{
        // GFX affiche une victoire du joueur
        //on ne s'occupe pas de la somme de l'assurance car c'est la banque qui le fera
        joueur.capital += joueur.mise * 2;
        joueur.gain += joueur.mise * 2;
        for (int i = 0; i < joueur.nbCartes; i++)
        {
            joueur.cartes[i].numero = 0;
            joueur.cartes[i].couleur = 0;
        }
        joueur.mise += 0;
        joueur.etat += 0;
        joueur.nbCartes = 0;
        return joueur;
}


int verifieVictoire(Joueur joueur, Banque banque)
{
    if (bustJoueur(joueur) == 1){
        if (AdditionJoueur(joueur) > AdditionBanque(banque))
        {
            //Le joueur a gagné contre la banque
            return 1;
        }
        else if (AdditionJoueur(joueur) < AdditionBanque(banque))
        {
            //Le joueur a perdu, donc la banque a gagné
            return 0;
        }
    
    }
     //Le joueur est à égalité avec la banque il reprend sa mise
            return 2;
}

//A modifier !!
void tourBanque(Joueur* joueur1, Joueur* joueur2, Joueur* joueur3, Banque* banque, Transfert transfert)
{
	Joueur fictif;
    while (AdditionBanque(*banque) < 17){
        banque->cartes[banque->nbCartes] = choisiCarte(&transfert, &fictif);
        banque->nbCartes ++;
            
        if (bustBanque(*banque) == 0){
            banque->etat = 2;
        }
    }
    //on regarde si la banque a fait blackjack si oui, on redonne l'assurance fois 2 à ceux qui l'ont prise
    if (banque->cartes[0].numero == 11 && banque->cartes[0].numero == 10){
            if (joueur1->etat == 3 || joueur1->etat == 4){
                joueur1->capital = joueur1->mise * 2;
            }

            if (joueur2->etat == 3 || joueur2->etat == 4){
                joueur2->capital = joueur2->mise * 2;
            }

            if (joueur3->etat == 3 || joueur3->etat == 4){
                joueur3->capital = joueur3->mise * 2;
            }
    }
    //si la banque n'a pas fait blackjack on regarde qui a gagné
    if (banque->cartes[0].numero != 11 && banque->cartes[0].numero != 10){ 
        victoire(*joueur1, *joueur2, *joueur3, *banque);
    }
}
//il faut regarder lorsque la banque tire sa première carte dans la fonction initJeu, si la banque a un AS pour proposer une assurance


// Il faut faire attention à faire disparaitre ou rendre inutilisable le bouton 
Joueur resetMise(Joueur joueur)
{
	joueur.mise = 0;
	return joueur;
}


//il faut appeler cette fonction seulement lorsque l'on donne les 2 premières cartes au joueur
void verifieBlackjack(Joueur* joueur)
{
    //met à jour le capital et le gain du joueur lorsqu'il fait un blackjack
    if (AdditionJoueur(*joueur) == 21){
        joueur->capital += joueur->mise * 2.5; //2.5 c'est le gain, nan ?
        joueur->gain += joueur->mise * 2.5;
        joueur->etat = 0;
        printf("Felicitation !!\nVous avez un Blackjack\n");
    }
}

Transfert fonctionDeTransfert (Transfert transfert)
{
	static Transfert temp = {0};
	static int compteur = 0;
	if(compteur == 0)
	{	
		temp = transfert;
		compteur++;
		return temp;
	}
	
	else if(compteur == 1)
	{
		transfert = temp;
		compteur++;
		return transfert;
	}
	return temp;
}


void apparaitCarte(DonneesImageRGB** cartesGfx, DonneesImageRGB** cartes, Joueur joueur, int cpt)
{
	for(int i = 0; i < 4; i++)
	{
		cartesGfx[i] = cartes[joueur.numeroRand[i]];
	}	
	            		         	       		
	if(cpt > 2)
	{
		for(int j = 0; j < 21; j++) // on patrouille le tableau des randoms
		{
			if(joueur.numeroRand[j] == 0) // indique l'indice qui est nul donc l'indice nbCarte + 1
			{
				cartesGfx[1] = cartes[joueur.numeroRand[j - 1]];
				break;
			}
		}
	}
}
