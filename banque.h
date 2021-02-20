/*-----------------------------
    
fichier.h contenant les déclarations
name: banque.h
date: 19/02/2021
by :Le Rouzic Emilie

-------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50
#define MAX_ESSAI 4

//la déclaration define permet de mettre des couleurs dans la console
#define BLEUCLAIR "\033[01;34m"
#define ROUGE "\033[00;31m"
#define BLEU "\033[00;34m"
#define SOULIGNE "\033[04m"
#define NORMAL "\033[00m"


 struct Client {

      char nom [MAX];
      char prenom [MAX];
      int solde;
      int num_compte;

};

//toutes les fonctions:
int saisie( struct Client * pt_client,int *total);
void recherche (struct Client * pt_client, int *total);
int virement(struct Client * pt_client, int *total);
int supprimer(struct Client * pt_client, int *total);
int verification(struct Client * pt_client, int *total, char *nom);
void sommetotaldesclients(struct Client * pt_client, int *total);
int verif_nom_et_prenom(char *chaine);
int verif_solde(char * soldetexte);
int numeroclient(struct Client *pt_client, int *total, char * numtexte, char * nom, int * num );

/*---FIN---*/