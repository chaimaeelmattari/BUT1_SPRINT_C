#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning (disable: 4996)

typedef enum {false=0, true=1}  bool ;



#define lgMot 30                                                                                                                                //Taille maximale d’une chaine de caractères saisie: 30
#define maxTournois 10                                                                                                                  //Nombre maximum de tournois: 10
#define nbMatchTournoi 127                                                                                                         //Nombre de matchs par tournoi: 127
#define nbJoueusesTournoi 128                                   //Nombre de joueuses par tournoi: 128
 
enum {nbTournoisMax = 10};
unsigned int nbTournoistraite = 0;          // A incremeter à chaque nouvelle saisie

typedef struct {                                                                                                                                   //Définition du type joueuse
             char nom[lgMot];                                                                                                                              //Nom de la joueuse
             unsigned int points;                                                                                                              //Points de la joueuse
} Joueuse;
 
typedef struct {                                                                                                                                  //Définition du type Match
             unsigned int idxGagnante;                                                                                                  //Index de la gagnante
             unsigned int idxPerdante;                                                                                                   //Index de la perdante
} Match;
 
typedef struct {                                                                                                                                  //Définition du type tournoi
             char nom[lgMot];                                                                                                                              //Nom du tournoi
             char date[lgMot];                                                                                                                              //Date du tournoi
             Match dataMatch[nbMatchTournoi];                                  //Matchs de ce tournoi
} Tournoi;
 
typedef struct {                                                                                                                                  //Définition du type TournoisWTA
             Tournoi dataTournoi[maxTournois];                                 //Tableau des tournois
             Joueuse dataJoueuse[nbJoueusesTournoi*nbTournoisMax];            //Tableau des joueuses
             Match dataMatch[nbMatchTournoi*nbTournoisMax];                    //Tableau des match
} TournoisWTA;

void affichage_joueuses_tournoi(TournoisWTA* ins);
void tri_insertion(Joueuse *t,unsigned int n);

unsigned int nbTournoi = 1;

 
int definir_nombre_tournois() {                                                //Fonction définir nbTournoi
             scanf("%u", &nbTournoi);
             //printf("#echo >%u<", nbTournoi);
 
             if ((nbTournoi < 0) || (nbTournoi > maxTournois))               //Vérification de la validité de nbTournoi
             {
                           printf("\nErreur: le nombre de tournoi saisi est incorrect. il faut qu'il soit compris entre 1 et %d", maxTournois);
                           return 1;
             }
             else return 0;
}



int get_idx_joueuse(unsigned int  idtournoi,Joueuse* tab, char* nom) {       // fonction a ameliorer --> cas joueuese pas trouvée
    int i;
    Joueuse j;
    for (i=0;i<nbJoueusesTournoi;i++) {
        j = tab[i];
        if (strcmp(nom, j.nom) == 0) {
            return i;
        }
    }
    return -1; // joeuse inconnue
}

const char*  get_nom_joueuse(Joueuse* tab, unsigned int idx) {       // fonction a ameliorer --> cas joueuese pas trouvée
    int i;
    Joueuse j;
    if  (idx < nbJoueusesTournoi * nbTournoi ) {
        
            return tab[idx].nom;
        }

}

void enregistrement_tournoi(TournoisWTA* ins) {                                  
       Tournoi nouveauTournoi;
       Joueuse tmpJoueuse;
       Match tmpMatch;
       int nbmatch;
       unsigned int nb_points;           //2000 1200 720 360 180 90 45 10

        scanf("%s", nouveauTournoi.nom);                                                                                                                      //Saisie du nom du tournoi
        //printf("\nnouveauTournoi.nom >%s<", nouveauTournoi.nom);
        scanf("%s", nouveauTournoi.date); 
        //printf("\nnouveauTournoi.dat>%s<", nouveauTournoi.date);
        
        for (nbmatch = 0; nbmatch < nbMatchTournoi; nbmatch++) {
            char nomJoueuseGagnate[lgMot], nomJoueusePerdante[lgMot];
            scanf("%s",  nomJoueuseGagnate);
            // printf("\nnomJoueuseGagnate >%s<",  nomJoueuseGagnate);
            
            scanf("%s", nomJoueusePerdante);
            
            // printf("\nnomJoueusePerdante >%s<", nomJoueusePerdante);
            
            switch (nbmatch)                                                                                                                    //Affichage de la position dans le tournoi
                           {
                           case(0):
                                        nb_points=10;
                                        break;
                           case(64):                                                                                                                    //64 - 1
                                        nb_points=45;
                                        break;
                           case(96):                                                                                                                    //64 + 32 - 1
                                        nb_points=90;
                                        break;
                           case(112):                                                                                                                  //64 + 32 + 16 - 1
                                        nb_points=180;
                                        break;
                           case(120):                                                                                                                  //64 + 32 + 16 + 8 - 1
                                        nb_points=360;
                                        break;
                           case(124):                                                                                                                  //64 + 32 + 16 + 8 + 4 - 1
                                        nb_points=720;
                                        break;
                           case(126):                                                                                                                  //64 + 32 + 16 + 8 + 4 + 2 - 1
                                        nb_points=1200;
                                        break;
                           default:
                                        break;
                           }
            if ( nbmatch < 64) {
                tmpMatch.idxGagnante = nbmatch * 2 + nbTournoistraite * nbTournoistraite ;
                strcpy(tmpJoueuse.nom,nomJoueuseGagnate);
                tmpJoueuse.points=nb_points;
                ins->dataJoueuse[nbmatch * 2 + nbTournoistraite * nbTournoistraite] = tmpJoueuse;

                tmpMatch.idxPerdante = nbmatch * 2  + 1 + nbTournoistraite * nbTournoistraite ;
                strcpy(tmpJoueuse.nom,nomJoueusePerdante);
                tmpJoueuse.points=nb_points;
                ins->dataJoueuse[nbmatch * 2 + 1 + nbTournoistraite * nbTournoistraite] = tmpJoueuse;
                

            } else {
                tmpMatch.idxGagnante = get_idx_joueuse(nbTournoistraite,ins->dataJoueuse,nomJoueuseGagnate);
                ins->dataJoueuse[tmpMatch.idxGagnante].points=nb_points;
                tmpMatch.idxPerdante = get_idx_joueuse(nbTournoistraite,ins->dataJoueuse,nomJoueusePerdante);
                ins->dataJoueuse[tmpMatch.idxPerdante].points=nb_points;
              }

            //printf("\n%d --> idxGagnante(%s) = %u, idxPerdante(%s) = %u",nbmatch,nomJoueuseGagnate,tmpMatch.idxGagnante,nomJoueusePerdante,tmpMatch.idxPerdante);
            
            nouveauTournoi.dataMatch[nbmatch] = tmpMatch ;

        }
        ins->dataJoueuse[tmpMatch.idxGagnante].points=2000;
        ins->dataTournoi[nbTournoistraite++] = nouveauTournoi ;
 
   }
 
void affichage_matchs_tournoi(const TournoisWTA * ins) {            //Fonction afficher matchs tournoi
    int i_tournoi, i_match ;
    Tournoi trn;
    char nomtrn[lgMot + 1];
    char datetrn[lgMot +1 ];
    Match match;
    bool TournoiTrouve = false; 

    scanf("%s", &nomtrn);
    scanf("%s", &datetrn);

   
    for(i_tournoi=0;i_tournoi<nbTournoistraite;i_tournoi++){
        trn=ins->dataTournoi[i_tournoi];
        //printf("\n%s == %s    |   %s == %s",nomtrn, trn.nom,datetrn, trn.date);
        if ((strcmp(nomtrn, trn.nom) == 0) && (strcmp(datetrn, trn.date) == 0)) {
            printf("%s %s",trn.nom,trn.date);
            for (i_match=0;i_match<nbMatchTournoi;i_match++){
                match = trn.dataMatch[i_match];
                char nomG[lgMot + 1] ;
                char nomP[lgMot + 1] ;

                strcpy(nomG,ins->dataJoueuse[match.idxGagnante].nom);
                strcpy(nomP,ins->dataJoueuse[match.idxPerdante].nom); 

                switch (i_match)                                                                                                                    //Affichage de la position dans le tournoi
                           {
                           case(0):
                                        printf("\n64emes de finale");
                                        break;
                           case(64):                                                                                                                    //64 - 1
                                        printf("\n32emes de finale");
                                        break;
                           case(96):                                                                                                                    //64 + 32 - 1
                                        printf("\n16emes de finale");
                                        break;
                           case(112):                                                                                                                  //64 + 32 + 16 - 1
                                        printf("\n8emes de finale");
                                        break;
                           case(120):                                                                                                                  //64 + 32 + 16 + 8 - 1
                                        printf("\nquarts de finale");
                                        break;
                           case(124):                                                                                                                  //64 + 32 + 16 + 8 + 4 - 1
                                        printf("\ndemi-finales");
                                        break;
                           case(126):                                                                                                                  //64 + 32 + 16 + 8 + 4 + 2 - 1
                                        printf("\nfinale");
                                        break;
                           default:
                                        break;
                           }
                printf("\n%s %s",nomG,nomP);
            }
            TournoiTrouve = true;
        }
        

    }
    if ( ! TournoiTrouve){
        printf("\ntournoi inconnu");
    }

}


void afficher_matchs_joueuse(TournoisWTA * ins) {
    char nomtrn[lgMot + 1], datetrn[lgMot +1 ], nomjoueuse[lgMot + 1];
    
    bool TournoiTrouve = false; 

    scanf("%s", &nomtrn);
    scanf("%s", &datetrn);
    scanf("%s", &nomjoueuse);

    int i_tournoi=0;

    while (( i_tournoi < nbTournoistraite ) && (! TournoiTrouve)) {
        Tournoi trn=ins->dataTournoi[i_tournoi];
        if ((strcmp(nomtrn, trn.nom) == 0) && (strcmp(datetrn, trn.date) == 0)) {
            TournoiTrouve = true;
            int IdxJoueuse = get_idx_joueuse(i_tournoi,ins->dataJoueuse, nomjoueuse);
            if ( IdxJoueuse > -1){
                for (int i_match=0;i_match<nbMatchTournoi;i_match++){
                    Match match = trn.dataMatch[i_match];
                    if ((match.idxGagnante == IdxJoueuse) || (match.idxPerdante == IdxJoueuse)) {
                        printf("%s %s\n",get_nom_joueuse(ins->dataJoueuse, match.idxGagnante),get_nom_joueuse(ins->dataJoueuse, match.idxPerdante));

                    }
                }
            } else printf("\n joueuse inconnue");
        }
        i_tournoi++;
    }

    if ( ! TournoiTrouve ){
        printf("\n tournoi inconnu");
    }
} 

void affichage_joueuses_tournoi(TournoisWTA* ins){
    char nomtrn[lgMot + 1], datetrn[lgMot +1 ];
    
    bool TournoiTrouve = false; 
    Joueuse Tri_Joueuse[nbJoueusesTournoi];

    scanf("%s", &nomtrn);
    scanf("%s", &datetrn);

    int i_tournoi=0;

    while (( i_tournoi < nbTournoistraite ) && (! TournoiTrouve)) {
        Tournoi trn=ins->dataTournoi[i_tournoi];
        if ((strcmp(nomtrn, trn.nom) == 0) && (strcmp(datetrn, trn.date) == 0)) {
            TournoiTrouve = true;
            printf("%s %s\n",nomtrn,datetrn);
            for(int j=0;j<nbJoueusesTournoi ;j++){
                //printf("%s %d\n",ins->dataJoueuse[j + i_tournoi * nbJoueusesTournoi].nom,ins->dataJoueuse[j + i_tournoi * nbJoueusesTournoi].points);
                strcpy(Tri_Joueuse[j].nom,ins->dataJoueuse[j + i_tournoi * nbJoueusesTournoi].nom);
                Tri_Joueuse[j].points = ins->dataJoueuse[j + i_tournoi * nbJoueusesTournoi].points;
                
            }
            tri_insertion(Tri_Joueuse,nbJoueusesTournoi);
            for(int j=0;j<nbJoueusesTournoi ;j++){
                printf("%s %d\n",Tri_Joueuse[j].nom,Tri_Joueuse[j].points);
            }
        }
        i_tournoi++;
    }

    if ( ! TournoiTrouve ){
        printf("\n tournoi inconnu");   
    } 
    
}
// tri d’un tableau t de taille n (indexé de 1 à n)
/*procedure tri_insertion(tableau t, entier n)
    debut_procedure
        pour i allant de 2 à n
            v ← t[i]
            j ← i
            tant que j > 1 et t[j - 1] > v
                t[j] ← t[j - 1]
                j ← j - 1
            fin tant que
            T[j] ← v
        fin pour
    fin_procedure*/

void tri_insertion( Joueuse* t,unsigned int n){
    for(int i=1 ; i<n; i++){
        Joueuse v=t[i];
        int j=i;
        while ((j>0) && (strcmp(t[j - 1].nom, v.nom) > 0 )) {
            t[j] = t[j - 1];
            j = j - 1;
        }
        t[j] = v;
    }
}

int main() {
    TournoisWTA Tournois;
    char mot[lgMot + 1];   
                                                                                                                     //Chaîne de caractères de taille maximale lgMot
 
             while (1) {        
                           scanf("%s", &mot);                                                                                                               //Lecture de la commande
 
                           if (strcmp(mot, "definir_nombre_tournois") == 0) {            //Si la commande est "definir_nombre_tournois"
                                        definir_nombre_tournois();
                           }
                           
                           if (strcmp(mot, "enregistrement_tournoi") == 0) {    //Si la commande est "enregistrement_tournoi"
                               //printf("\nAppel de la fonction enregistrement_tournoi()");
                                

                                        enregistrement_tournoi(&Tournois);
                           }
 
                           if (strcmp(mot, "affichage_matchs_tournoi") == 0) {          //Si la commande est "affichage_matchs_tournoi"
                                        affichage_matchs_tournoi(&Tournois);
                           }

                           if (strcmp(mot, "afficher_matchs_joueuse") == 0) {          //Si la commande est "affichage_matchs_tournoi"
                                        afficher_matchs_joueuse(&Tournois);
                           }

                           if (strcmp(mot, "affichage_joueuses_tournoi") == 0) {          //Si la commande est "affichage_matchs_tournoi"
                                        affichage_joueuses_tournoi(&Tournois);
                           }
 
                           if (strcmp(mot, "exit") == 0) {                                                                               //Si la commande est "exit"                                                                  
                                        //printf("\n");
                                        exit(0);                                                                                                                        //Sortie du programme principal
                           }                                                                                                                                                                            //End if
             }                                                                                                                                                                                         //End while
}                                                                                                                                                                                                      //End main
