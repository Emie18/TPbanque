/*-----------------------------
    
fichier.c contenant les fonctions
name: fonctions.c
date: 19/02/2021
by :Le Rouzic Emilie

-------------------------------*/

#include "banque.h"

//fonction qui permet la saisie d'un nouveau client.
//total est le nombre de clients
int saisie(struct Client *pt_client, int *total)
{
    int solde = 0;
    char soldetexte[MAX];

    //nouv est la nouvelle place qu'on rajoute dans la liste des clients
    int nouv = *total;
    *total = *total + 1;
    pt_client[nouv].num_compte = nouv + 1;
    printf("\n----------------\n");

    printf("nom:");
    fgets(pt_client[nouv].nom, MAX, stdin);
    pt_client[nouv].nom[strlen(pt_client[nouv].nom) - 1] = '\0';
    // appel à la fonction verif_nom_et prenom pour vérifier que le texte entré est valide.
    int vf = verif_nom_et_prenom(pt_client[nouv].nom);

    //si le texte est invalide.
    if (vf == 1)
    {
        //suppression de la place du client qui n'a pas un nom valide.
        *total = *total - 1;
        return 1;
    }

    printf("Prénom:");
    fgets(pt_client[nouv].prenom, MAX, stdin);
    pt_client[nouv].prenom[strlen(pt_client[nouv].prenom) - 1] = '\0';
    //on vérifie si le prenom entré n'est pas vide ou commence par un nombre grâce à la fonction : verif_nom_et_prenom.
    vf = verif_nom_et_prenom(pt_client[nouv].prenom);

    //si le texte est invalide vf = 1.
    if (vf == 1)
    {
        //suppression de la place du client qui n'a pas un prenom valide.
        *total = *total - 1;
        return 1;
    }

    printf("solde: ");
    fgets(soldetexte, MAX, stdin);
    soldetexte[strlen(soldetexte) - 1] = '\0';
    //appel à la fonction verif_solde qui vérifie si la saisie est bien un nombre strictement positif.
    vf = verif_solde(soldetexte);
    if (vf < 1)
    {
        //suppression de la place du client qui n'a pas un prenom valide.
        *total = *total - 1;
        return 1;
    }
    // on convertit soldetexte(tab de caractère) en solde (int).
    solde = atoi(soldetexte);

    pt_client[nouv].solde = solde;

    printf("----------------\n");
}

//fonction de recherche et/ou affiche liste clients
void recherche(struct Client *pt_client, int *total)
{

    int choix;
    char choixtexte[MAX];
    char rch[MAX];
    do
    {
        // demande à l'utilisateur son choix : voir la liste ou rechercher un client.
        printf(BLEU "Tapez 1 pour voir tout les clients\nTapez 2 pour une recherche avec un nom/prenom.\n");
        printf("Ou autre touche pour quitter\n" NORMAL);
        fgets(choixtexte, MAX, stdin);
        choixtexte[strlen(choixtexte) - 1] = '\0';
        choix = atoi(choixtexte);
        if (choix == 1)
        {
            printf("\nliste des clients:\n");
            printf("------------------------------------------\n");
            printf("num:\n");
            //boucle qui affiche la liste des clients.
            for (int i = 0; i < *total; i++)
            {
                printf("%d   %s  %s \t %d €\n", pt_client[i].num_compte, pt_client[i].nom, pt_client[i].prenom, pt_client[i].solde);
                printf("------------------------------------------\n");
            }
            //appel à la fonction qui affiche les soldes totaux.
            sommetotaldesclients(pt_client, total);
            continue;
        }
        // bout de code qui va faire la recherche.
        else if (choix == 2)
        {
            char rch[MAX];
            printf("recherche :");
            fgets(rch, MAX, stdin);
            rch[strlen(rch) - 1] = '\0';

            //non est une variable qui va récupérer 1 si le nom entré est inconnu.
            int non;
            non = verification(pt_client, total, rch);
            if (non)
            {
                printf("------------------------------------------\n");
                printf(ROUGE "Nous n'avons pas de client à ce nom !\n" NORMAL);
                printf("------------------------------------------\n");
            }
            else
            { 
                //boucle qui va afficher tout les clients qui ont le même nom/prenom saisis (rch).
                for (int j = 0; j < *total; j++)
                {
                    if ((strcmp(rch, pt_client[j].nom) == 0) || (strcmp(rch, pt_client[j].prenom) == 0))
                    {
                        printf("------------------------------------------\n");
                        printf("Oui nous avons un client à ce nom:\n");
                        printf(BLEUCLAIR "%s  %s \t %d €\n" NORMAL, pt_client[j].nom, pt_client[j].prenom, pt_client[j].solde);
                        printf("Son numéro de compte est :");
                        printf(BLEUCLAIR "%d\n" NORMAL, pt_client[j].num_compte);
                        printf("------------------------------------------\n");
                    }
                }
            }
        }
        // quand une touche autre que 1/2 est entré on retourne au menu.
        else
        {
            break;
        }
    } while (1);
}

// fonction qui fait un virement entre deux client, ou lui même,
// elle renvoit 1 si il y a une erreur dans les informations rentrées ou que le nombre d'essai est dépasssé.
int virement(struct Client *pt_client, int *total)
{
    char rch[MAX];
    char rch2[MAX];
    char numtexte[MAX];
    int somme,num, verif = 1;
    int essai = 0;

    //donneur
    while (verif != 0)
    {
        printf("nom ou prenom du donneur:");
        fgets(rch, MAX, stdin);
        rch[strlen(rch) - 1] = '\0';

        //appel à la fonction qui verifie si le client est dans la liste.
        verif = verification(pt_client, total, rch);
        
        if (verif != 0)
        {
            printf(ROUGE "Nom ou Prénom inconnu\n" NORMAL);
        }
        //limite le nombre d'essai à 5.
        if (essai > MAX_ESSAI - 1)
        {
            return 1;
        }
        essai++;
    }

    // recherche du numéro client correspondant au nom ou prenom du donneur.
    printf("numero de client du %sdonneur:%s",BLEUCLAIR,NORMAL);
    fgets(numtexte, MAX, stdin);
    numtexte[strlen(numtexte) - 1] = '\0';
    int num_donneur = 0;

    // appel à la fonction numeroclient qui verifie si le numero entrer est valide et bien correspondant.
    int num_valide = numeroclient(pt_client,total,numtexte, rch,&num_donneur);

    // si le numéro client est invalide retour au menu.
    if (num_valide)
    {
        return 1;
    }
    
    //on réinitialise verif et essai
    essai = 0;
    verif = 1;

    //receveur:
    while (verif != 0)
    {
        printf("nom ou prenom du receveur:");
        fgets(rch2, MAX, stdin);
        rch2[strlen(rch2) - 1] = '\0';

        //appel à la fonction verification qui vérifie si le client est dans la liste.
        verif = verification(pt_client, total, rch2);

        //si nom/prenom inconnue.
        if (verif != 0)
        {
            printf(ROUGE "Nom ou Prénom inconnu\n" NORMAL);
        }
        //limite le nombre d'essai à 5.
        if (essai > MAX_ESSAI - 1)
        {
            return 1;
        }
        essai++;
    }
    //recherche de la correspondance du receveur et de son numéro client.
    printf("numero de client du %sreceveur:%s",BLEUCLAIR,NORMAL);
    fgets(numtexte, MAX, stdin);
    numtexte[strlen(numtexte) - 1] = '\0';
    int num_receveur = 0;

    //appel à la fonction numeroclient qui verifie si le numero entré est valide et a une correspondance.
    num_valide = numeroclient(pt_client,total,numtexte, rch2,&num_receveur);

    //si numéro client invalide retour au menu
    if (num_valide)
    {
        return 1;
    }
    
    // saisie de la somme de virement.
    char sommetexte[MAX];
    printf("somme de virement:");
    fgets(sommetexte, MAX, stdin);
    sommetexte[strlen(sommetexte) - 1] = '\0';

    //convertit sommetexte(tab de caractères) en somme(int).
    somme = atoi(sommetexte);

    int nbessai = 1;
    // tant que la somme entrée n'est pas un chiffre strictement positif.
    while (somme <= 0)
    {
        printf(ROUGE "erreur veuillez donne une somme > 0 !\n" NORMAL);
        printf("somme de virement:");
        fgets(sommetexte, MAX, stdin);
        sommetexte[strlen(sommetexte) - 1] = '\0';
        somme = atoi(sommetexte);
        nbessai++;
        //limite le nombre d'essai à 5 (voir define(banque.h) pour modifier).
        if (nbessai > MAX_ESSAI)
        {
            return 1;
        }
    }

    // afffiche avant le virement donneur:
    printf("%s\t%s \t %d €", pt_client[num_donneur-1].nom, pt_client[num_donneur-1].prenom, pt_client[num_donneur-1].solde);
    printf(ROUGE "  -%d\n" NORMAL, somme);

    //fait la soustraction de somme au solde du client.
    pt_client[num_donneur-1].solde -= somme;

    printf(BLEUCLAIR"Nouveau solde:\n"NORMAL);

    //Affiche après virement donneur.
    printf("%s\t%s \t %d €\n", pt_client[num_donneur-1].nom, pt_client[num_donneur-1].prenom, pt_client[num_donneur-1].solde);

    printf("------------------------------------------\n");

    // afffiche avant le virement receveur:
    printf("%s\t%s \t%d €", pt_client[num_receveur-1].nom, pt_client[num_receveur-1].prenom, pt_client[num_receveur-1].solde);
    printf(ROUGE "  +%d\n" NORMAL, somme);

    //fait l'ajout de somme.
    pt_client[num_receveur-1].solde += somme;

    
    //Affiche après virement receveur.
    printf(BLEUCLAIR"Nouveau solde:\n"NORMAL);
    printf("%s\t%s \t %d €\n", pt_client[num_receveur-1].nom, pt_client[num_receveur-1].prenom, pt_client[num_receveur-1].solde);

    return verif;
}

//fonction qui supprime un client, elle renvoit 1 si le client rentré n'existe pas, et 0 quand il existe.
int supprimer(struct Client *pt_client, int *total)
{
    char rch[MAX];
    char numtexte[MAX];

    //recupère le nom/prenom du client qu'on souhaite supprimer
    printf("nom ou prenom du compte à suprimier: ");
    fgets(rch, MAX, stdin);
    rch[strlen(rch) - 1] = '\0';

    //on recupère son numéro de compte correspondant(dans le cas de même nom/prenom c'est important)
    printf("numéro du client:");
    fgets(numtexte, MAX, stdin);
    numtexte[strlen(numtexte) - 1] = '\0';

    int num_a_supprimer = 0;
    //on verifie grace à la fonction numeroclient que le nom/prenom correspond bien au numero client.
    int num_valide = numeroclient(pt_client, total, numtexte, rch, &num_a_supprimer);

    //si le numero de client est invalide ou 'r' entrer ou trop d'essai retour au menu.
    if (num_valide)
    {
        return 1;
    }

    // copie en déplaçant d'un rang tout les clients dans la liste.
    // !attention! Les numéros des clients changent!
    for (int k = 0; k < *total; k++)
    {
        //boucle qui copie les chaines de caractère (nom et prenom)
        for (int i = 0; i < MAX; i++)
        {
            pt_client[num_a_supprimer - 1].nom[i] = pt_client[num_a_supprimer].nom[i];
            pt_client[num_a_supprimer - 1].prenom[i] = pt_client[num_a_supprimer].prenom[i];
        }

        pt_client[num_a_supprimer - 1].solde = pt_client[num_a_supprimer].solde;
        num_a_supprimer++;
    }
    //supression de la place en trop.
    *total = *total - 1;
}

//fonction qui renvoit 1 si le client entré n'existe pas dans la liste des clients,et renvoit 0 quand il existe.
int verification(struct Client *pt_client, int *total, char *nom)
{
    int vf;

    //recherche du nom/prenom dans la liste de client
    for (int j = 0; j < *total + 1; j++)
    {
        if ((strcmp(nom, pt_client[j].nom) == 0) || (strcmp(nom, pt_client[j].prenom) == 0))
        {
            //on vérifie si ce qui est rentré n'est pas vide
            if ((strcmp("", pt_client[j].nom) == 0) || (strcmp("", pt_client[j].prenom) == 0))
            {
                vf = 1 ;
                break;
            }
            vf = 0;
            break;
        }
        else
        {
            vf = 1;
        }
    }

    return vf;
}

//fonction pour calculer la somme total des soldes enregistrés dans la banque et de l'afficher.
void sommetotaldesclients(struct Client *pt_client, int *total)
{
    int sommetotal = 0;
    for (int i = 0; i < *total; i++)
    {
        sommetotal = sommetotal + pt_client[i].solde;
    }
    printf(BLEUCLAIR "---TOTAL des soldes---\n" NORMAL);
    printf(ROUGE "\n\t  %d€\n" NORMAL, sommetotal);
    printf(BLEUCLAIR "----------------------\n" NORMAL);
}

//fonction qui vérifie si la chaine entrée n'est pas vide ou commence par un/des chiffre(s).
int verif_nom_et_prenom(char *chaine)
{
    int i = 0;
    int chiffre = atoi(chaine);
    while ((strcmp("", chaine) == 0) || (chiffre != 0))
    {
        printf(ROUGE "mauvaise saisie veuillez recommencer :\n" NORMAL);
        fgets(chaine, MAX, stdin);
        chaine[strlen(chaine) - 1] = '\0';
        chiffre = atoi(chaine);
        if (MAX_ESSAI == i)
        {
            return 1;
        }
        i++;
    }
}

//fonction qui vérifie si le solde entrée est valide
int verif_solde(char *soldetexte)
{
    int solde = atoi(soldetexte);

    //on initialise nbessai à 1 pour qu'au total il y ai 5 essai max
    //(valeur à changer dans banque.h -> define MAX_ESSAI)
    int nbessai = 1;

    //boucle qui permet de vérifier si c'est bien un  nombre positif qui est rentré;
    while (solde <= 0)
    {
        printf(ROUGE "veuillez enter solde valide et positif :\n" NORMAL);

        printf("solde: ");
        fgets(soldetexte, MAX, stdin);
        soldetexte[strlen(soldetexte) - 1] = '\0';
        solde = atoi(soldetexte);
        nbessai++;

        //si au bout de 5 essai l'utilisateur n'a pas rentré une valeur correcte il est renvoyé au menu principal
        if (nbessai > MAX_ESSAI)
        {
            return 1;
        }
    }
}

//fonction qui vérifie si le numero de client correspond ou nom/prenom entré.
int numeroclient(struct Client *pt_client, int *total, char * numtexte, char * nom, int * num )
{
    *num = atoi(numtexte);
    int i = 0;

    //tant que le num ne correspond pas à celui du nom/prenom on boucle
    while ((*num <= 0) || ((strcmp(nom, pt_client[*num - 1].nom) != 0) && (strcmp(nom, pt_client[*num - 1].prenom) != 0)))
    {
        printf(ROUGE "Numéro de compte invalide ou non corespondant\n" NORMAL);
        printf(SOULIGNE "Si vous ne savez pas, allez dans menu et tapez 2 pour rechercher\nTapez %s'r'%s %sPour retourner au menu\n" NORMAL, BLEUCLAIR, SOULIGNE, NORMAL);
        printf(BLEUCLAIR "numero de client:" NORMAL);
        fgets(numtexte, MAX, stdin);
        numtexte[strlen(numtexte) - 1] = '\0';
        *num = atoi(numtexte);

        //si au bout de 5 fois on n'y arrive pas on sort
        //(valeur à changer dans banque.h -> define MAX_ESSAI)
        if ((i > MAX_ESSAI))
        {
            return 1;
        }
        
        //si l'utilisateur entre la lettre 'r' il sort directement.
        if ((strcmp(numtexte, "r") == 0))
        {
            return 1;
        }
        i++;
    }
}

/*---FIN---*/