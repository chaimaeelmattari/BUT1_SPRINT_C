#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996)

typedef int bool;
#define false  0
#define true  1

#define lgMot 30                              //Taille maximale d’une chaine de caractères saisie: 30
#define maxTournois 10                        //Nombre maximum de tournois: 10
#define nbMatchTournoi 127                   //Nombre de matchs par tournoi: 127
#define nbJoueusesTournoi 128                //Nombre de joueuses par tournoi: 128

unsigned int nbTournoistraite = 0;          // A incrémenter à chaque nouvelle saisie
unsigned int nbTournoi = 1;

typedef struct {                                        //Définition du type joueuse
	char nom[lgMot];                                       //Nom de la joueuse
	unsigned int points;                                   //Points de la joueuse
} Joueuse;

typedef struct {                                       //Définition du type Match
	unsigned int idxGagnante;                               //Index de la gagnante
	unsigned int idxPerdante;                               //Index de la perdante
} Match;

typedef struct {                                      //Définition du type tournoi
	char nom[lgMot];                                       //Nom du tournoi
	char date[lgMot];                                      //Date du tournoi
	Match dataMatch[nbMatchTournoi];                       //Matchs de ce tournoi
} Tournoi;

typedef struct {                                      //Définition du type tournoiWTA
	Tournoi dataTournoi[maxTournois];                      //Tableau des tournois
	Joueuse dataJoueuse[nbJoueusesTournoi*maxTournois];    //Tableau des joueuses
	Match dataMatch[nbMatchTournoi*maxTournois];           //Tableau des match
} TournoiWTA;

int definir_nombre_tournois() {
	/*
	DESCRIPTON : Permet de définir le nombre de tournois qui seront enregistrés

	PARAMETRES :
	- entrée        : aucun
	- sortie        : aucun
	- entrée-sortie : nbTournoi
	*/
	scanf("%u", &nbTournoi);

	if ((nbTournoi < 0) || (nbTournoi > maxTournois)) {      //Vérification de la validité de nbTournoi
		printf("\nErreur: le nombre de tournoi saisi est incorrect. il faut qu'il soit compris entre 1 et %d", maxTournois);
		return 1;
	}
	else return 0;
}

int get_idx_joueuse(unsigned int idTournoi, Joueuse* tab, char* nom) {
	/*
	DESCRIPTON : Permet de récupérer l'indice d'une joueuse dans dataJoueuse à partir de son nom

	PARAMETRES :
	- entrée        : unsigned int idTournoi qui correspond au nombre de tournois déjà traités
					: Joueuse tab qui correspond au tableau des joueuses
					! char nom qui correspond au nom de la joueuse recherchée
	- sortie        : int indice qui correspond à l'indice de la joueuse cherchée dans tab
	- entrée-sortie : aucun
	*/
	int i;
	Joueuse j;
	for (i = idTournoi * nbJoueusesTournoi; i< nbJoueusesTournoi + idTournoi * nbJoueusesTournoi; i++) {
		j = tab[i];
		if (strcmp(nom, j.nom) == 0)
			return i;
	}
	return -1; // joueuse inconnue
}

const char*  get_nom_joueuse(Joueuse* tab, unsigned int idx) {
	/*
	DESCRIPTON : Permet de récupérer le nom d'une joueuse dans dataJoueuse à partir de son indice

	PARAMETRES :
	- entrée        : Joueuse tab qui correspond au tableau des joueuses
					: unsigned int idx qui correspond à l'indice de la joueuse recherchée
	- sortie        : char nom qui correspond au nom de la joueuse recherchée
	- entrée-sortie : aucun
	*/
	return tab[idx].nom;
}

void definir_points(int nbMatch, unsigned int *nb_points) {
	/*
	DESCRIPTON : Permet de définir le nombre de points à attribuer aux joueuses

	PARAMETRES :
	- entrée        : int nbMatch qui correspond au nombre de matchs réalisés au cours du tournoi
	- sortie        : aucun
	- entrée-sortie : unsigned int nb_points correspond au nombre de points à attribuer aux joueuses
	*/
	switch (nbMatch) {
	case(0):
		*nb_points = 10; break;
	case(64):
		*nb_points = 45; break;
	case(96):
		*nb_points = 90; break;
	case(112):
		*nb_points = 180; break;
	case(120):
		*nb_points = 360; break;
	case(124):
		*nb_points = 720; break;
	case(126):
		*nb_points = 1200; break;
	default:
		break;
	}
}

void enregistrement_tournoi(TournoiWTA* ptr_tournoi) {
	/*
	DESCRIPTON : Permet d'enregistrer un tournoi

	PARAMETRES :
	- entrée        : TournoiWTA ptr_tournoi qui correspond à l'objet qui regroupe l'ensemble des données
	- sortie        : aucun
	- entrée-sortie : aucun
	*/
	Tournoi nouveauTournoi;
	Joueuse tmpJoueuse;
	Match tmpMatch;
	int nbmatch;
	unsigned int nb_points = 0;			//2000 1200 720 360 180 90 45 10

	scanf("%s", nouveauTournoi.nom);                               //Saisie du nom du tournoi
	scanf("%s", nouveauTournoi.date);							   //Saisie de la date du tournoi

	for (nbmatch = 0; nbmatch < nbMatchTournoi; nbmatch++) {		//Pour chaque match, saisie du nom de la gagnante puis de la perdante
		char nomJoueuseGagnante[lgMot], nomJoueusePerdante[lgMot];
		scanf("%s", nomJoueuseGagnante);
		scanf("%s", nomJoueusePerdante);

		definir_points(nbmatch, &nb_points);

		if (nbmatch < 64) {								//Enregistrement des noms des joueuses dans dataJoueuses et dans tournoiWTA
			tmpMatch.idxGagnante = nbmatch * 2;
			strcpy(tmpJoueuse.nom, nomJoueuseGagnante);
			tmpJoueuse.points = nb_points;
			ptr_tournoi->dataJoueuse[(nbJoueusesTournoi*nbTournoistraite) + tmpMatch.idxGagnante] = tmpJoueuse;

			tmpMatch.idxPerdante = nbmatch * 2 + 1;
			strcpy(tmpJoueuse.nom, nomJoueusePerdante);
			tmpJoueuse.points = nb_points;
			ptr_tournoi->dataJoueuse[(nbJoueusesTournoi*nbTournoistraite) + tmpMatch.idxPerdante] = tmpJoueuse;
		}
		else {											//Enregistrement des joueuses par leur indice dans tournoiWTA
			tmpMatch.idxGagnante = get_idx_joueuse(nbTournoistraite, ptr_tournoi->dataJoueuse, nomJoueuseGagnante);
			ptr_tournoi->dataJoueuse[tmpMatch.idxGagnante].points = nb_points;
			tmpMatch.idxPerdante = get_idx_joueuse(nbTournoistraite, ptr_tournoi->dataJoueuse, nomJoueusePerdante);
			ptr_tournoi->dataJoueuse[tmpMatch.idxPerdante].points = nb_points;
		}
		nouveauTournoi.dataMatch[nbmatch] = tmpMatch;
	}
	ptr_tournoi->dataJoueuse[tmpMatch.idxGagnante].points = 2000;
	ptr_tournoi->dataTournoi[nbTournoistraite++] = nouveauTournoi;
}

void affichage_position_tournoi(int pos) {
	/*
	DESCRIPTON : Permet d'afficher, au sein d'un tournoi, la position dans le tournoi (64eme, 32eme...)

	PARAMETRES :
	- entrée        : int pos qui correspond au nombre de matchs réalisés
	- sortie        : aucun
	- entrée-sortie : aucun
	*/
	switch (pos) {
	case(0):
		printf("\n64emes de finale");	break;
	case(64):
		printf("\n32emes de finale");	break;
	case(96):
		printf("\n16emes de finale");	break;
	case(112):
		printf("\n8emes de finale");	break;
	case(120):
		printf("\nquarts de finale");	break;
	case(124):
		printf("\ndemi-finales");	break;
	case(126):
		printf("\nfinale");	break;
	default:
		break;
	}
}

void affichage_matchs_tournoi(const TournoiWTA * ins) { 
	/*
	DESCRIPTON : Permet d'afficher les résultats d'un tournoi donné

	PARAMETRES :
	- entrée        : TournoiWTA ptr_tournoi qui correspond à l'objet qui regroupe l'ensemble des données
	- sortie        : aucun
	- entrée-sortie : aucun
	*/
	int i_tournoi, i_match;
	Tournoi trn;
	char nomtrn[lgMot];
	char datetrn[lgMot];
	Match match;
	bool TournoiTrouve = false;

	scanf("%s", &nomtrn);										//Saisie nom et date du tournoi à afficher
	scanf("%s", &datetrn);

	for (i_tournoi = 0; i_tournoi<nbTournoistraite; i_tournoi++) {
		trn = ins->dataTournoi[i_tournoi];
		if ((strcmp(nomtrn, trn.nom) == 0) && (strcmp(datetrn, trn.date) == 0)) {
			printf("%s %s", trn.nom, trn.date);
			for (i_match = 0; i_match<nbMatchTournoi; i_match++) {
				match = trn.dataMatch[i_match];
				char nomG[lgMot];
				char nomP[lgMot];

				strcpy(nomG, ins->dataJoueuse[match.idxGagnante].nom);
				strcpy(nomP, ins->dataJoueuse[match.idxPerdante].nom);

				affichage_position_tournoi(i_match);  //Affichage de la position dans le tournoi (64eme, 32eme...)
				printf("\n%s %s", nomG, nomP);		  //Affichage nom des joueuses
			}
			TournoiTrouve = true;
		}
	}
	if (!TournoiTrouve)
		printf("\ntournoi inconnu");
}

void afficher_matchs_joueuse(TournoiWTA * ins) {
	/*
	DESCRIPTON : Permet d'afficher l'ensemble des matchs auxquels a participé une joueuse

	PARAMETRES :
	- entrée        : TournoiWTA ptr_tournoi qui correspond à l'objet qui regroupe l'ensemble des données
	- sortie        : aucun
	- entrée-sortie : aucun
	*/
	char nomtrn[lgMot], datetrn[lgMot], nomjoueuse[lgMot];

	bool TournoiTrouve = false;

	scanf("%s", &nomtrn);								//Saisie du nom de la joueuse et du tournoi
	scanf("%s", &datetrn);
	scanf("%s", &nomjoueuse);

	int i_tournoi = 0;

	while ((i_tournoi < nbTournoistraite) && (!TournoiTrouve)) {
		Tournoi trn = ins->dataTournoi[i_tournoi];
		if ((strcmp(nomtrn, trn.nom) == 0) && (strcmp(datetrn, trn.date) == 0)) {	//Recherche du tournoi
			TournoiTrouve = true;
			int IdxJoueuse = get_idx_joueuse(nbTournoistraite, ins->dataJoueuse, nomjoueuse);
			if (IdxJoueuse > -1) {													//Recherche de la joueuse
				for (int i_match = 0; i_match<nbMatchTournoi; ++i_match) {
					Match match = trn.dataMatch[i_match];
					if ((match.idxGagnante == IdxJoueuse) || (match.idxPerdante == IdxJoueuse))	//Recherche des matchs de la joueuse puis affichage
						printf("%s %s\n", get_nom_joueuse(ins->dataJoueuse, match.idxGagnante), get_nom_joueuse(ins->dataJoueuse, match.idxPerdante));
				}
			}
			else printf("\n joueuse inconnue");
		}
		i_tournoi++;
	}
	if (!TournoiTrouve)
		printf("\ntournoi inconnu");
}

void tri_insertion(Joueuse* t, unsigned int n) {
	/*
	DESCRIPTON : permet de trier un tableau de type Joueuse selon les points et le nom des Joueuses en cas d'egalité.

	PARAMETRES :
	- entrée        : unsigned int n qui correspond à la taille du tableau à trier
	- sortie        : aucun
	- entrée-sortie : Joueuse t qui correspond au tableau des joueuses à trier
	*/
	// tri du tableau selon les points des joueuses
	for (int i = 1; i<n; i++) {
		Joueuse v = t[i];
		int j = i;
		while ((j>0) && (t[j - 1].points < v.points)) {
			t[j] = t[j - 1];
			j = j - 1;
		}
		t[j] = v;
	}
	// tri du tableau selon le nom des joueuses en cas d'egalité de points
	for (int i = 1; i<n; i++) {
		Joueuse v = t[i];
		int j = i;
		while ((j>0) && (t[j - 1].points == v.points) && (strcmp(t[j - 1].nom, v.nom) > 0)) {
			t[j] = t[j - 1];
			j = j - 1;
		}
		t[j] = v;
	}
}

void affichage_joueuses_tournoi(TournoiWTA * ins) {
	/*
	DESCRIPTON : Permet d'afficher toutes les joueuses ayant participé à un tournoi donné

	PARAMETRES :
	- entrée        : TournoiWTA ptr_tournoi qui correspond à l'objet qui regroupe l'ensemble des données
	- sortie        : aucun
	- entrée-sortie : aucun
	*/
	char nomtrn[lgMot], datetrn[lgMot];
	bool tournoiTrouve = false;
	Joueuse listeJoueuses[nbJoueusesTournoi];
	int i_tournoi = 0;
	scanf("%s", &nomtrn);									//Saisie du nom et de la date du tournoi
	scanf("%s", &datetrn);

	while ((i_tournoi < nbTournoistraite) && (!tournoiTrouve)) {
		Tournoi trn = ins->dataTournoi[i_tournoi];
		if ((strcmp(nomtrn, trn.nom) == 0) && (strcmp(datetrn, trn.date) == 0)) {	//Recherche du tournoi
			tournoiTrouve = true;
			printf("%s %s\n", nomtrn, datetrn);
			for (int j = 0; j<nbJoueusesTournoi; j++) {								//Enregistrement des joueuses et de leur points dans listeJoueuses
				strcpy(listeJoueuses[j].nom, ins->dataJoueuse[j + i_tournoi * nbJoueusesTournoi].nom);
				listeJoueuses[j].points = ins->dataJoueuse[j + i_tournoi * nbJoueusesTournoi].points;
			}
			tri_insertion(listeJoueuses, nbJoueusesTournoi);						//Tri de listeJoueuses
			for (int j = 0; j < nbJoueusesTournoi; j++) {
				printf("%s %d\n", listeJoueuses[j].nom, listeJoueuses[j].points);	//Affichage joueuse et points
			}
		}
		i_tournoi++;
	}
	if (!tournoiTrouve)
		printf("\ntournoi inconnu");
}

void afficher_classement(TournoiWTA* ins) {
	/*
	DESCRIPTON : Permet d'afficher le classement global de toutes les joueuses

	PARAMETRES :
	- entrée        : TournoiWTA ptr_tournoi qui correspond à l'objet qui regroupe l'ensemble des données
	- sortie        : aucun
	- entrée-sortie : aucun
	*/
	Joueuse JoueuseClassement[nbJoueusesTournoi*maxTournois];
	unsigned int nbjoueuse = 0;
	int premierElement = nbTournoistraite > 4 ? nbJoueusesTournoi * (nbTournoistraite - 4) : 0;

	for (int i = premierElement; i < nbJoueusesTournoi * nbTournoistraite;  ++i) {
		bool dejatraite = false;
		for (int j = 0; j <= nbjoueuse; ++j) {
			if (strcmp(JoueuseClassement[j].nom, ins->dataJoueuse[i].nom) == 0) {
				JoueuseClassement[j].points += ins->dataJoueuse[i].points;
				dejatraite = true;
			}
		}
		if (!dejatraite)
			JoueuseClassement[nbjoueuse++] = ins->dataJoueuse[i];
	}
	tri_insertion(JoueuseClassement, nbjoueuse);
	for (int i = 0; i < nbjoueuse; i++) {
		printf("%s %d\n", JoueuseClassement[i].nom, JoueuseClassement[i].points);
	}
}

int main() {
	TournoiWTA Tournois;
	char mot[lgMot];		//Chaîne de caractères de taille maximale lgMot

	while (1) {
		scanf("%s", &mot);                                   //Lecture de la commande

		if (strcmp(mot, "definir_nombre_tournois") == 0)             //Si la commande est "definir_nombre_tournois"
			definir_nombre_tournois();

		if (strcmp(mot, "enregistrement_tournoi") == 0) 			 //Si la commande est "enregistrement_tournoi"
			enregistrement_tournoi(&Tournois);

		if (strcmp(mot, "affichage_matchs_tournoi") == 0)          //Si la commande est "affichage_matchs_tournoi"
			affichage_matchs_tournoi(&Tournois);

		if (strcmp(mot, "afficher_matchs_joueuse") == 0)          //Si la commande est "affichage_matchs_tournoi"
			afficher_matchs_joueuse(&Tournois);

		if (strcmp(mot, "affichage_joueuses_tournoi") == 0)			//Si la commande est "affichage_joueuses_tournoi"
			affichage_joueuses_tournoi(&Tournois);

		if (strcmp(mot, "afficher_classement") == 0)
			afficher_classement(&Tournois);

		if (strcmp(mot, "exit") == 0)                             //Si la commande est "exit"                                                                  
			exit(0);												//Sortie du programme principal
	}
}