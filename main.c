/*-----------------------------
    
fichier.c contenant le main()
name: main.c
date: 19/02/2021
by :Le Rouzic Emilie

-------------------------------*/

#include "banque.h"

int main()
{
    printf(BLEUCLAIR "Bievenue!\n" NORMAL);
    int choix = 0;
    int total = 0;
    char choixtexte[MAX];
    struct Client *pt_client;

    //allocation de la mémoire pour le pointeur (pt_client).
    pt_client = malloc(sizeof(struct Client) * MAX);
    
    //boucle infinie pour le menu
    do
    {
        //affichage des instructions du menu.
        printf(BLEU "Que souhaitez-vous faire ?\n");
        printf("Tapez 1 : \t→ Pour la saisi d'un nouveau client.\n");
        printf("Tapez 2 : \t→ Pour rechercher un client.\n\t\t Ou pour la liste des clients.\n");
        printf("Tapez 3 : \t→ Pour faire un virement. \n");
        printf("Tapez 4 : \t→ Pour supprimer un client.\n");
        printf("Tapez 5 : \t→ Pour sortir du menu.\n" NORMAL);

        //recupère le choix de l'utilisateur
        fgets(choixtexte, MAX, stdin);
        choixtexte[strlen(choixtexte) - 1] = '\0';

        //convertie le choix en chiffre.
        choix = atoi(choixtexte);

        //erreur sera la variable dans laquelle on retournera les fonctions pour savoir si il y a une erreur ou non (1 = erreur).
        int erreur;
        
        switch (choix)
        {
            case 1:

                erreur = saisie(pt_client, &total);
                if (erreur == 1)
                {
                    printf(ROUGE "ERREUR : une des informations rentrées est mauvaise\nou\nNombre d'essai dépassé !\n\n" NORMAL);
                }
                else
                {
                    printf("------------------------------------------\n");
                    printf(BLEUCLAIR "Numéro de client: %d\n" NORMAL, total);
                    printf(SOULIGNE "ATTENTION le numéro de client change quand un compte est supprimé\n");
                    printf("Il faut se référer à la liste de clients !\n" NORMAL);
                    printf("------------------------------------------\n");
                }
                continue;

            case 2:

                recherche(pt_client, &total);
                continue;

            case 3:

                erreur = 1;
                erreur = virement(pt_client, &total);
                if (erreur == 1)
                {
                    printf(ROUGE "ERREUR : une des informations rentrées est mauvaise\nou\nNombre d'essai dépassé !");
                    printf("\nou\nVous avez tapé 'r'\n\n" NORMAL);
                }

                continue;

            case 4:

                erreur = supprimer(pt_client, &total);
                if (erreur == 1)
                {
                    printf(ROUGE "ERREUR : compte innexistant!\nou\nNombre d'essai dépassé\n\n" NORMAL);
                }
                else
                {
                    printf(BLEUCLAIR "Le compte à bien été suprimé\n\n" NORMAL);
                }
                continue;

            case 5:

                return 0;

            default:

                printf(ROUGE "ERREUR : ceci n'est pas un choix possible!\n" NORMAL);
                continue;

        };

    } while (1);
}

/*---FIN---*/
