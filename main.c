#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Header.h"

int menu()
{
    int choix=0;
    printf("\nChoisissez une des possibilites suivantes en saisissant sur votre clavier le chiffre correspondant !\n\n");
    printf("1- Vous commencez ! \n");
    printf("2- Vous laissez l'ordi jouer \n");
    while(choix==0)
    {
        printf("\n\n\n Votre choix : ");
        scanf("%d", &choix);
        if (choix==1) printf("vous avez choisi de commencer, bonne chance!\n\n");
        else if(choix==2) printf("vous etes bien temeraire pour laisser l'IA jouer en premier...\n\n");
        else
        {
            choix=0;
            printf("la saisie est incorrecte, fin du jeu\n");
        }
    }
    return choix;
}

int fonction_periodique(int num)
{
    if(num == 1) return 2;
    else return 1;
}

int** creer_matrice3X3()
{
    int** matrice = (int**) malloc(sizeof(int*)*3); // 3 pointeurs (debuts de colonnes)
    
    for(int a = 0; a<3; a++)
    {
        matrice[a] = malloc(sizeof(int)*3); // 3 cases "par" pointeurs
    }
    return matrice;
}
int** init_matrice(int** matrice)
{
    for(int i=0; i<3; i++)
    {
        for (int j=0; j<3; j++)
        {
            matrice[i][j] = 0;
        }
    }
    return matrice;
}
void affiche_matrice(int** matrice)
{
    printf("\n");
    for(int i=0; i<3; i++)
    {
        printf("|");
        for (int j=0; j<3; j++)
        {
            printf(" %d ", matrice[i][j]);
        }
        printf("|\n");
    }
    printf("\n");
}
int coup_gagnant_lignes(int** matrice)
{
    for(int i=0; i<3; i++)
    {
        if(matrice[i][0] == matrice[i][1] && matrice[i][1] == matrice[i][2] && matrice[i][2] !=0) return 1;
    }
    return 0;
}
int coup_gagnant_colonnes(int** matrice)
{
    for(int i=0; i<3; i++)
    {
        if(matrice[0][i] == matrice[1][i] &&  matrice[1][i] == matrice[2][i] && matrice[2][i]!=0) return 1; //matrice[0][i]!=0 pour eviter les 0
    }
    return 0;
}
int coup_gagnant_diagonale(int** matrice)
{
    if (matrice[0][0] == matrice[1][1] && matrice[1][1] == matrice[2][2] && matrice[2][2]!=0) return 1;
    if (matrice[0][2] ==  matrice[1][1] &&  matrice[1][1] == matrice[2][0] && matrice[2][0]!=0) return 1;
    return 0;
}
int est_remplie_matrice(int** matrice)
{
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(matrice[i][j] ==0) return 0;
        }
    }
    return 1;
}

int est_gagnee_partie(int** matrice)
{
    if(coup_gagnant_lignes(matrice)==1 || coup_gagnant_diagonale(matrice) ==1 || coup_gagnant_colonnes(matrice) ==1) return 1;
    return 0;
}
int est_finie_partie(int** matrice)
{
    if(est_gagnee_partie(matrice)==1 || est_remplie_matrice(matrice)==1) return 1;
    return 0;
}

int est_occupee_place(int** matrice, int i, int j)
{
    if(matrice[i][j]!=0)
    {
        return 1;
    }
    return 0;
}

int** remplissage_matrice(int num_ligne, int num_colonne, int** matrice, int symbole)
{
    matrice[num_ligne-1][num_colonne-1] = symbole;
    return matrice;
}

int** remplissage_joueur(int** matrice, int symbole)
{
    int boolean=0;
    printf("choisissez une case a remplir, lignes et colonnes debutent a 1\n");
    affiche_matrice(matrice);
    int num_ligne=0, num_colonne=0;
    while(boolean==0)
    {
        printf("numero de ligne : ");
        scanf("%d", &num_ligne);
        printf("\n");
        printf("numero de colonne : ");
        scanf("%d", &num_colonne);
        printf("\n");
        
        if(num_colonne>3 || num_ligne>3)
        {
            printf("attention, erreur sur la colonne ou la ligne choisie, elles doivent etres <= 3\n");
            boolean =0;
        }
        else if(est_occupee_place(matrice, num_ligne-1, num_colonne-1)==1)
        {
            printf("la place est occupee\n");
            boolean =0;
        }
        else
        {
            remplissage_matrice(num_ligne, num_colonne, matrice, symbole);
            boolean =1;
        }
    }
    return matrice;
}

int** remplissage_IA(int** matrice, int symbole)
{
    int nb_alea_ligne = rand()%3+1, nb_alea_colonne = rand()%3+1;
    while(est_occupee_place(matrice, nb_alea_ligne-1, nb_alea_colonne-1)==1)
    {
        nb_alea_ligne = rand()%3+1;
        nb_alea_colonne = rand()%3+1;
    }
    printf("l'IA a joue sur ligne = %d , colonne = %d\n", nb_alea_ligne, nb_alea_colonne);
    return remplissage_matrice(nb_alea_ligne, nb_alea_colonne, matrice, symbole);
}

int jeu(int** matrice, int choix_premier_joueur)
//on convient que num_joueur =1 pour l'homme et 2 pour l'IA
{
    if(est_remplie_matrice(matrice)==1 || est_gagnee_partie(matrice)==1)
    {
        if(est_gagnee_partie(matrice)==1) return fonction_periodique(choix_premier_joueur);
        return 3; // sinon aucun joueur n'a gagne
    }
    if(choix_premier_joueur==1)
    {
        matrice=remplissage_joueur(matrice, choix_premier_joueur);
        affiche_matrice(matrice);
        return jeu(matrice, fonction_periodique(choix_premier_joueur));
    }
    else
    {
        matrice=remplissage_IA(matrice, choix_premier_joueur);
        affiche_matrice(matrice);
        return jeu(matrice, fonction_periodique(choix_premier_joueur));
    }
}

void enonciation_gagnant(int gagnant)
{
    if(gagnant==1) printf("BRAVO A l'HUMAIN QUI A GAGNe !!!\n");
    else if(gagnant==2) printf("LA MACHINE TRIOMPHERA TOUJOURS !!!\n");
    else printf("MATCH NUL !!!\n");
}

//CONSTRUCTION DE L'ARBRE

noeud* creer_element(int** matrice)
{
    noeud* element = (noeud*) malloc(sizeof(noeud));
    element->fils=NULL;
    element->frere=NULL;
    element->matrice=matrice;
    element->score=-1000; //initialisation des scores
    element->pere=NULL;
    return element;
}

int** dupliquer_matrice(int** matrice)
{
    int** copie = creer_matrice3X3();
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            copie[i][j] = matrice[i][j];
        }
    }
    return copie;
}

int nbr_cases_vide(int** matrice) // peut remplacer est_remplie_matrice
{
    int cpt=0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            if(matrice[i][j] ==0) cpt++;
        }
    }
    return cpt;
}


void test(int* i, int* j, int** matrice, int symbol) //d'abord a 0 et 0 puis des qu'on trouve une case libre on la remplie, on conserve i et j puis on applique la fonction mais pour i, j+1
//utiliser des pointeurs avec adresses de i et j
{
    while(matrice[*i][*j] !=0 && *i<=2 && *j<=2 && (*i+*j)<=4) //on sort de la matrice quand matrice[2][2] est testee
    {
        if(*j==2 && *i<2) // si on arrrive a la derniere colonne
        {
            (*j)=-1; // pour qu'au prochain tour on reteste a la colonne 0
            (*i)++; // mais a la ligne suivante !
        }
        (*j)++; //pour la meme ligne on teste la case a la colonne suivante
    }
    if(*i<=2 && *j<=2 && matrice[*i][*j] ==0) matrice[*i][*j] = symbol;
    
    if(*i<=2 && *j<2) (*j)++;
    else if((*i)<2 && (*j)==2)
    {
        (*j)=0;
        (*i)++;
    }
    //pour i et j valant 2 on mettra une condition de fin a l'exterieur de test()
}

int*** creer_tableau_de_matrices(int** matrice, int symbol) // avec une matrice partiellement occupee on fait les combinaisons possibles pour un coup sur cette matrice
{
    if(est_finie_partie(matrice))
    {
        return NULL;
    }
    else
    {
        int TAILLE = nbr_cases_vide(matrice);
        int*** tableau_de_matrices = (int***) malloc(sizeof(int**)*TAILLE);
        int i=0, j=0;
        for(int a = 0; a<TAILLE; a++)
        {
            tableau_de_matrices[a] = dupliquer_matrice(matrice); //ça les identent PAS tous SI ON FAIT UNE COPIE DE CHACUN...
        }
        for(int a = 0; a<TAILLE; a++)
        {
            test(&i, &j, tableau_de_matrices[a], symbol);
        }
        return tableau_de_matrices;
    }
}

void affiche_tableau_de_matrices(int*** tableau, int TAILLE)
{
    for(int a = 0; a<TAILLE; a++)
    {
        printf("tableau [%d] = \n", a);
        affiche_matrice(tableau[a]);
        printf("\n");
    }
}

noeud* ajouter_element(noeud* element, noeud* liste_Chainee)
{
    if(liste_Chainee == NULL)
    {
        liste_Chainee = element;
        return liste_Chainee;
    }
    else
    {
        noeud* tmp= liste_Chainee;
        while(tmp->frere!=NULL)
        {
            tmp=tmp->frere;
        }
        tmp->frere = element;
        return liste_Chainee;
    }
}

void creer_descendance2(noeud* arbre, int symbol_joueur) //on cree une generation d'enfants
{//POUR REVENIR COMME AVANT ENLEVER LE IF (TABLEAU ==NULL)
    int *** tableau = creer_tableau_de_matrices(arbre->matrice, symbol_joueur);
    
    if(tableau!=NULL)
    {
        noeud* aine = creer_element(tableau[0]);
        for(int i = 1; i<nbr_cases_vide(arbre->matrice); i++)
        {
            aine = ajouter_element(creer_element(tableau[i]), aine);
        }
        arbre->fils = aine;
        aine->pere = arbre;
    }
}

void creer_heritage2(noeud* arbre, int symbol_joueur) //on cree TOUTES les generations (enfants des enfants) donc tout l'arbre
{
    if(arbre != NULL)
    {
        creer_descendance2(arbre, symbol_joueur);
        
        creer_heritage2(arbre->frere, symbol_joueur);
        symbol_joueur = fonction_periodique(symbol_joueur);
        creer_heritage2(arbre->fils, symbol_joueur);
    }
}

//AFFICHAGES
void affiche_liste_chainee(noeud* liste)
{
    if(liste!=NULL)
    {
        affiche_matrice(liste->matrice);
        affiche_liste_chainee(liste->frere);
    }
}

void affiche_ligne_matrice(int ** matrice, int ligne)
{
    printf("|");
    for(int i=0; i<3; i++)
    {
        printf(" %d ", matrice[ligne][i]);
    }
    printf("|");
}

void affiche_arbre2(noeud* arbre, int profondeur)
{
    if(arbre != NULL)
    {
        for(int i=0; i<profondeur; i++)
        {
            printf("          ");
        }
        printf("|   ");
        affiche_ligne_matrice(arbre->matrice, 0);
        printf("\n");
        for(int i=0; i<profondeur; i++)
        {
            printf("          ");
        }
        printf("|-> ");
        affiche_ligne_matrice(arbre->matrice, 1);
        printf("    score : %d", arbre->score); //ENLEVER SI ON VEUT PAS VOIR APPARAÎTRE LES SCORES !
        printf("\n");
        for(int i=0; i<profondeur; i++)
        {
            printf("          ");
        }
        printf("|   ");
        affiche_ligne_matrice(arbre->matrice, 2);
        printf("\n\n");
        
        affiche_arbre2(arbre->fils, profondeur+1);
        affiche_arbre2(arbre->frere, profondeur);
    }
}

void affiche_arbre_partiel(noeud* arbre, int profondeur, int profondeur_max)
{
    if(arbre != NULL && profondeur < profondeur_max)
    {
        for(int i=0; i<profondeur; i++)
        {
            printf("          ");
        }
        printf("|   ");
        affiche_ligne_matrice(arbre->matrice, 0);
        printf("\n");
        for(int i=0; i<profondeur; i++)
        {
            printf("          ");
        }
        printf("|-> ");
        affiche_ligne_matrice(arbre->matrice, 1);
        printf("    score : %d", arbre->score); //ENLEVER SI ON VEUT PAS VOIR APPARAÎTRE LES SCORES !
        printf("\n");
        for(int i=0; i<profondeur; i++)
        {
            printf("          ");
        }
        printf("|   ");
        affiche_ligne_matrice(arbre->matrice, 2);
        printf("\n\n");
        
        affiche_arbre_partiel(arbre->fils, profondeur+1, profondeur_max);
        affiche_arbre_partiel(arbre->frere, profondeur, profondeur_max);
    }
}


int nbr_noeuds(noeud* arbre)
{
    if(arbre!=NULL) return 1 + nbr_noeuds(arbre->fils) + nbr_noeuds(arbre->frere);
    return 0;
}
int nbr_etats_finaux(noeud* arbre)
{
    if(arbre!=NULL)
    {
        if(arbre->fils == NULL) return 1 + nbr_etats_finaux(arbre->frere);
        else return nbr_etats_finaux(arbre->fils) + nbr_etats_finaux(arbre->frere);
    }
    return 0;
}
int coup_gagnant_lignes_entier(int** matrice, int entier_joueur)
{
    for(int i=0; i<3; i++)
    {
        if(matrice[i][0] == matrice[i][1] && matrice[i][1] == matrice[i][2] && matrice[i][2] == entier_joueur) return 1;
    }
    return 0;
}
int coup_gagnant_colonnes_entier(int** matrice, int entier_joueur)
{
    for(int i=0; i<3; i++)
    {
        if(matrice[0][i] == matrice[1][i] &&  matrice[1][i] == matrice[2][i] && matrice[2][i] == entier_joueur) return 1; //matrice[0][i]!=0 pour eviter les 0
    }
    return 0;
}
int coup_gagnant_diagonale_entier(int** matrice, int entier_joueur)
{
    if (matrice[0][0] == matrice[1][1] && matrice[1][1] == matrice[2][2] && matrice[2][2]==entier_joueur) return 1;
    if (matrice[0][2] ==  matrice[1][1] &&  matrice[1][1] == matrice[2][0] && matrice[2][0]==entier_joueur) return 1;
    return 0;
}

int nbr_etats_finaux_gagnant(noeud* arbre, int num_joueur)
{
    if(arbre!=NULL)
    {
        if(arbre->fils == NULL && (coup_gagnant_lignes_entier(arbre->matrice, num_joueur)==1 || coup_gagnant_colonnes_entier(arbre->matrice, num_joueur)==1 || coup_gagnant_diagonale_entier(arbre->matrice, num_joueur) ==1))
        {
            return 1 + nbr_etats_finaux_gagnant(arbre->frere, num_joueur);
        }
        else return nbr_etats_finaux_gagnant(arbre->fils, num_joueur) + nbr_etats_finaux_gagnant(arbre->frere, num_joueur);
    }
    return 0;
}

//DEVELOPPEMENT DE L'ALGORITHME MIN_MAX !!!

int score_matrice(int** matrice, int num_joueur)
{
    if((coup_gagnant_lignes_entier(matrice, num_joueur)==1 || coup_gagnant_colonnes_entier(matrice, num_joueur)==1 || coup_gagnant_diagonale_entier(matrice, num_joueur) ==1))
    {
        return 10;
    }
    else if((coup_gagnant_lignes_entier(matrice, fonction_periodique(num_joueur)==1) || coup_gagnant_colonnes_entier(matrice, fonction_periodique(num_joueur))==1 || coup_gagnant_diagonale_entier(matrice, fonction_periodique(num_joueur)) ==1))
    {
        return -10;
    }
    else
    {
        return 0;
    }
}

noeud* recherche_victoire_la_plus_rapide(noeud* arbre)
{
    if(arbre != NULL && arbre->fils!=NULL)
    {
        if(arbre->fils->frere!=NULL)
        {
            noeud* tmp =arbre->fils;
            int cpt=0; //compteurs de scores identiques dans la descendance au score retourne par MinMax de l'arbre
            while(tmp->frere!=NULL)
            {
                if(tmp->score == arbre->score) cpt++;
                tmp=tmp->frere;
            }
            if(tmp->score == arbre->score) cpt++;
            tmp=arbre->fils;
            noeud** pointeurs_sur_chemins_possibles = (noeud**) malloc(sizeof(noeud*)*cpt);
            //on recommence une boucle pour remplir le tableau de pointeurs sur les chemins possibles pour gagner
            int i=0;
            while(tmp->frere!=NULL)
            {
                if(tmp->score == arbre->score)
                {
                    pointeurs_sur_chemins_possibles[i] = tmp;
                    i++;
                }
                tmp=tmp->frere;
            }
            if(tmp->score == arbre->score)
            {
                pointeurs_sur_chemins_possibles[i] = tmp;
                i++;
            }
            //on va calculer le nbr de noeuds pour chacun des chemins possibles, car on prendra le chemin le plus court possible vers la victoire ;-)
            int minimum = nbr_noeuds(pointeurs_sur_chemins_possibles[0]);
            int indice_minimum = 0;
            for(int j=0; j<cpt; j++)
            {
                if(minimum > nbr_noeuds(pointeurs_sur_chemins_possibles[j]))
                {
                    minimum = nbr_noeuds(pointeurs_sur_chemins_possibles[j]);
                    indice_minimum = j;
                }
            }
            return pointeurs_sur_chemins_possibles[indice_minimum];
        }
        return arbre->fils;
    }
    return 0;
    
}

void affichage_etats_menant_vers_victoire(noeud* arbre, int profondeur) //vers la victoire LA PLUS COURTE EN NBR DE COUPS
{
    if(arbre!=NULL)
    {
        for(int i=0; i<profondeur; i++)
        {
            printf("          ");
        }
        printf("|   ");
        affiche_ligne_matrice(arbre->matrice, 0);
        printf("\n");
        for(int i=0; i<profondeur; i++)
        {
            printf("          ");
        }
        printf("|-> ");
        affiche_ligne_matrice(arbre->matrice, 1);
        printf("    score : %d", arbre->score); //ENLEVER SI ON VEUT PAS VOIR APPARAÎTRE LES SCORES !
        printf("\n");
        for(int i=0; i<profondeur; i++)
        {
            printf("          ");
        }
        printf("|   ");
        affiche_ligne_matrice(arbre->matrice, 2);
        printf("\n\n");
        
        affichage_etats_menant_vers_victoire(recherche_victoire_la_plus_rapide(arbre), profondeur+1);
    }
}

int** remplissage_par_MinMax(noeud* arbre, int** matrice) //le num initial sera 1 ou 2 a chaque fois car on saute une etape quand l'autre joueur joue
{
    return recherche_victoire_la_plus_rapide(arbre)->matrice;
}

noeud* VoirArbreJeuEtPossibilites(int** matrice, int choix_premier_joueur, noeud* arbre)
{
    int VoirOUpas = 0;
    printf("Appuyer sur 1 pour voir l'arbre des possibilites pour l'IA ainsi que les scores dans son cas?");
    scanf("%d", &VoirOUpas);
    if(VoirOUpas==1)
    {
        //CREATION D'ARBRE ET AFFICHAGE AU JOUEUR
        creer_heritage2(arbre, choix_premier_joueur);
        printf("    Voici l'arbre des possibilites ainsi que les scores contenus dans chaque noeud de l'arbre :\n\n");
        scores_feuiles(arbre, 1);
        MinMax_global(arbre);
        affiche_arbre2(arbre, 0);
    }
    return arbre;
}

int jeu2(int** matrice, int choix_premier_joueur, noeud* arbre) // JEU UTILISANT L'ALGO MinMax POUR GAGNER !
//on convient que num_joueur =1 pour l'homme et 2 pour l'IA
{
    if(est_remplie_matrice(matrice)==1 || est_gagnee_partie(matrice)==1)
    {
        if(est_gagnee_partie(matrice)==1) return fonction_periodique(choix_premier_joueur);
        return 3; // sinon aucun joueur n'a gagne
    }
    if(choix_premier_joueur==1)
    {
        matrice=remplissage_joueur(matrice, choix_premier_joueur);
        return jeu2(matrice, fonction_periodique(choix_premier_joueur), arbre);
    }
    else
    {
        //genere l'arbre des possibilites pour l'IA\\
        printf("\n");
        arbre=creer_element(matrice);
        creer_heritage2(arbre, 2);
        scores_feuiles(arbre, 1);
        MinMax_global(arbre);
        matrice=remplissage_par_MinMax(arbre, matrice);
        
        printf("\nVoici la succession d'etats menant vers la victoire pour l'IA :\n");
        printf("\n\n");
        affichage_etats_menant_vers_victoire(arbre, 0);
        printf("\n\n");
        printf("l'IA joue ceci : ");
        affiche_matrice(matrice);
        
        return jeu2(matrice, fonction_periodique(choix_premier_joueur), arbre);
    }
}

void creer_heritage_partiel(noeud* arbre, int symbol_joueur, int profondeur_max_h)
{
    if(arbre != NULL)
    {
        if(profondeur_max_h>1)
        {
            creer_descendance2(arbre, symbol_joueur);
            
            creer_heritage_partiel(arbre->frere, symbol_joueur, profondeur_max_h);
            symbol_joueur = fonction_periodique(symbol_joueur);
            creer_heritage_partiel(arbre->fils, symbol_joueur, profondeur_max_h-1);
        }
        if(profondeur_max_h==-1) creer_heritage2(arbre, 2);
    }
}

int menu_total()
{
    int type_partie=0;
    printf("\n\nTIC TAC TOE !!!\n\n");
    printf("Choisissez le type de jeu en rentrant le chiffre correspondant puis en tapent sur Entree !\n\n");
    printf("1- Jeu simple avec placement aleatoire par l'ordi (Resultat 0 du TD) ! \n");
    printf("2- Difficulte extreme, depuis un etat donne du jeu, la machine est intelligente (Resultat 1 du TD) !\n");
    printf("3- Difficulte extreme, partie complete avec la machine intelligente (Resultat 2 du TD) !\n");
    
    while(type_partie==0)
    {
        printf("\n\n\n Votre choix : ");
        scanf("%d", &type_partie);
        if (type_partie==1) printf("Vous avez choisi un jeu facile !\n\n");
        else if(type_partie==2) printf("Jeu difficile !\n\n");
        else if(type_partie==3) printf("Partie complete avec l'IA, difficile et depuis le debut!\n\n");
        else
        {
            type_partie=0;
            printf("la saisie est incorrecte, fin du jeu\n");
        }
    }
    return type_partie;
    
}

void VoirArbreOuPas(noeud* arbre, int h)
{
    int d=0;
    printf("\nVoulez-vous voir l'arbre des possbilites? Si Oui rentrez '1' !\n");
    scanf("%d", &d);
    if(d==1)
    {
        printf("\nGeneration de l'arbre partiel de profondeur h = %d \n", h);
        affiche_arbre2(arbre, 0);
    }
}

int jeu3(int** matrice, int choix_premier_joueur, noeud* arbre, int h)
//on convient que num_joueur =1 pour l'homme et 2 pour l'IA
{
    if(est_remplie_matrice(matrice)==1 || est_gagnee_partie(matrice)==1)
    {
        if(est_gagnee_partie(matrice)==1) return fonction_periodique(choix_premier_joueur);
        return 3; // sinon aucun joueur n'a gagne
    }
    if(choix_premier_joueur==1)
    {
        matrice=remplissage_joueur(matrice, choix_premier_joueur);
        return jeu3(matrice, fonction_periodique(choix_premier_joueur), arbre, h);
    }
    else
    {
        //genere l'arbre des possibilites pour l'IA
        printf("\n");
        arbre=creer_element(matrice);
        creer_heritage_partiel(arbre, 2, h);
        
        scores_feuiles(arbre, 2);//RESULTAT2
        MinMax_global(arbre);
        matrice=remplissage_par_MinMax(arbre, matrice);
        
        VoirArbreOuPas(arbre, h);
        
        printf("\nl'IA joue ceci : ");
        affiche_matrice(matrice);
        
        return jeu3(matrice, fonction_periodique(choix_premier_joueur), arbre, h);
    }
}


void Resultats_TD(int choix, int** matrice)
{
    if (choix ==1) enonciation_gagnant(jeu(matrice, menu())); //RESULTAT 0
    else if (choix ==2) //RESULTAT 1
    {
        printf("D'abord, avant de jouer ensemble,\n    on va vous montrer que l'algorithme MinMax...\n        ainsi que la generation d'un arbre a partir d'une matrice...\n            fonctionnent bien tous les deux !\n                Considerez donc ceci comme un didactiel :)\n\n Pour ce faire on utilise l'exemple du PDF sur l'explication de MinMax avec les O et les X\n");
        
        printf(" -le '2' c'est l'IA, qui va jouer et tenter de gagner avec MinMax\n");
        printf(" -le '1' c'est le joueur\n");
        matrice[0][0]= 1; //voir schema 1 c'est le rond (le joueur)
        matrice[0][1]= 1;
        matrice[0][2]= 2; //2 c'est la croix sur le PDF, donc l'IA, c'est l'IA qui joue en premier
        matrice[1][1]= 2;
        matrice[2][0]= 1;
        matrice[2][1]= 2;
        
        //generation de l'arbre
        printf("\nVoici l'arbre des possibilites ainsi que les scores contenus dans chaque noeud de l'arbre :\n\n");// par rapport a l'IA
        noeud* arbre = creer_element(matrice);
        creer_heritage2(arbre, 2);//par rapport a L'IA
        scores_feuiles(arbre, 1);
        MinMax_global(arbre);
        affiche_arbre2(arbre, 0);
        printf("\nLe Resultat de MinMax est : %d\n", arbre->score);
        printf("Quelques infos supplementaires sur l'arbre qu'on a genere...");
        
        printf("\n -il y a %d noeuds dans l'arbre total des possibilites\n", nbr_noeuds(arbre));
        printf("\n -il y a %d etats finaux au jeu du morpion\n", nbr_etats_finaux(arbre));
        printf("\n -il y a %d etats finaux gagnants pour le premier joueur du morpion\n", nbr_etats_finaux_gagnant(arbre, 1));
        printf("\n -il y a %d etats finaux gagnants pour le joueur qui joue en second au morpion\n", nbr_etats_finaux_gagnant(arbre, 2));
        printf("\n -il y a %d matchs nuls \n\n", nbr_etats_finaux(arbre) - nbr_etats_finaux_gagnant(arbre, 1) - nbr_etats_finaux_gagnant(arbre, 2));
        
        int pause;
        printf("Appuyer sur 1 pour jouer cette fois...\n");
        scanf("%d", &pause);
        
        printf("\n\n On reprend la matrice precedente et vous allez jouer le rôle du joueur ;-) \n On commencera pas la partie depuis le debut avec une matrice vide \n car on va generer ici tout l'arbre des possibilites \n et MinMax ne sera pas efficace sur une grille vide contenant 8! combinaisons. \n\n Voir Resultat 2 si vous voulez jouer une partie entiere avec l'IA grâce a MinMax :-)\n\n");
        enonciation_gagnant(jeu2(matrice, menu(), creer_element(matrice)));
    }
    else if(choix==3) //RESULTAT2
    {
        int profondeur_h_max=0;
        printf("\n\n Il s'agit du Resultat 2, vous allez jouer une partie entiere avec l'IA\n\n Choisissez une profondeur max 'h' de generation de l'arbre des possibilites, on conseille un grand h pour une meilleure prevision ! (h = -1 => generation integrale) :\n");
        scanf("%d", &profondeur_h_max);
        
        enonciation_gagnant(jeu3(matrice, menu(), creer_element(matrice), profondeur_h_max));
    }
}

//RESULTAT 2
int pions_alignes_lignes(int** matrice, int num_joueur, int nbr_a_aligner)
{
    int nbr_alignes=0;
    int result=0; //result represente le nbr de cas de pions alignes et avec une case libre qui permettrait en la remplissant de gagner
    int j=0, i=0;
    while(j<3)
    {
        while(i<3 && nbr_alignes>=0)
        {
            if(matrice[j][i] == num_joueur) nbr_alignes++;
            else if(matrice[j][i] == fonction_periodique(num_joueur)) nbr_alignes=-1;
            i++;
        }
        if(nbr_alignes==nbr_a_aligner) result++;
        nbr_alignes=0;
        i=0;
        j++;
    }
    return result;
}
int pions_alignes_colonnes(int** matrice, int num_joueur, int nbr_a_aligner)
{
    int nbr_alignes=0;
    int result=0; //result represente le nbr de cas de pions alignes et avec une case libre qui permettrait en la remplissant de gagner
    int j=0, i=0;
    while(j<3)
    {
        while(i<3 && nbr_alignes>=0)
        {
            if(matrice[i][j] == num_joueur) nbr_alignes++;
            else if(matrice[i][j] == fonction_periodique(num_joueur)) nbr_alignes=-1;
            i++;
        }
        if(nbr_alignes==nbr_a_aligner) result++;
        nbr_alignes=0;
        i=0;
        j++;
    }
    return result;
}
int pions_alignes_diagonales(int** matrice, int num_joueur, int nbr_a_aligner)
{
    int nbr_alignes=0;
    int result=0; //result represente le nbr de cas de pions alignes et avec une case libre qui permettrait en la remplissant de gagner
    int i=0;
    while(i<3 && nbr_alignes>=0)
    {
        if(matrice[i][i] == num_joueur) nbr_alignes++;
        else if(matrice[i][i] == fonction_periodique(num_joueur)) nbr_alignes=-1;
        i++;
    }
    if(nbr_alignes==nbr_a_aligner) result++;
    nbr_alignes=0;
    i=0;
    while(i<3 && nbr_alignes>=0)
    {
        if(matrice[i][2-i] == num_joueur) nbr_alignes++;
        else if(matrice[i][2-i] == fonction_periodique(num_joueur)) nbr_alignes=-1;
        i++;
    }
    if(nbr_alignes==nbr_a_aligner) result++;
    return result;
}

int instructions_score(int** matrice, int num_joueur)
{
    int score = 0;
    
    //s'il y a sur une ligne, une colonne ou une diagonale 2 pions avec possibilite d'en mettre un troisieme
    if((pions_alignes_lignes(matrice, num_joueur, 2) + pions_alignes_colonnes(matrice, num_joueur, 2) + pions_alignes_diagonales(matrice, num_joueur, 2)) ==1) score +=2;
    
    //s'il y a au depart ou a un moment donne 1 pion au milieu ou dans les coins, avec aucun autre adverse place sur la diagonale du pion concerne
    if(pions_alignes_diagonales(matrice, num_joueur, 1)==1) score +=3;
    
    //3 cases consecutives\\\\\\\
    //si l'IA gagne
    if(coup_gagnant_lignes_entier(matrice, num_joueur)==1|| coup_gagnant_colonnes_entier(matrice, num_joueur)==1 || coup_gagnant_diagonale_entier(matrice, num_joueur) ==1) score = 100;
    
    //s'il y a sur une ligne, une colonne ou une diagonale 2 fois 2 pions avec possibilite pour les 2 d'en mettre un troisieme (la partie est alors gagnee)
    if((pions_alignes_lignes(matrice, num_joueur, 2) + pions_alignes_colonnes(matrice, num_joueur, 2) + pions_alignes_diagonales(matrice, num_joueur, 2))==2) score = 9;
    
    return score;
}

int score_matrice_etat_partiel(int** matrice, int num_joueur)
{
    
    if(instructions_score(matrice, num_joueur)==100 || instructions_score(matrice, fonction_periodique(num_joueur))==100)
    {
        if(instructions_score(matrice, 2)==100) return 10;
        return -10;
    }
    //printf("%d    -     %d\n", instructions_score(matrice, num_joueur), instructions_score(matrice, fonction_periodique(num_joueur)));
    return instructions_score(matrice, num_joueur) - instructions_score(matrice, fonction_periodique(num_joueur));
}


void scores_feuiles(noeud* arbre, int reponse_resultat)
{
    if(arbre->fils==NULL)
    {
        if(reponse_resultat==2)
        {
            arbre->score = score_matrice_etat_partiel(arbre->matrice, 2);
        }
        else arbre->score = score_matrice(arbre->matrice, 2);
        
        if(arbre->frere!=NULL)
        {
            scores_feuiles(arbre->frere, reponse_resultat);
        }
    }
    else
    {
        if(arbre->frere!=NULL)
        {
            scores_feuiles(arbre->frere, reponse_resultat);
        }
        scores_feuiles(arbre->fils, reponse_resultat);
    }
}

int scores_inscrits_fraternite(noeud* arbre)
{
    noeud* tmp=arbre;
    while(tmp->frere!=NULL && tmp->score!=-1000)
    {
        tmp=tmp->frere;
    }
    if(tmp->score==-1000) return 0;
    else return 1;
}

int maximum_generation(noeud* arbre)
{
    noeud* tmp=arbre;
    int maximum=tmp->score;
    while(tmp->frere!=NULL)
    {
        if(tmp->score > maximum)
        {
            maximum = tmp->score;
        }
        tmp=tmp->frere;
    }
    return maximum;
}

int minimum_generation(noeud* arbre)
{
    noeud* tmp=arbre;
    int minimum=tmp->score;
    while(tmp->frere!=NULL)
    {
        if(tmp->score < minimum)
        {
            minimum = tmp->score;
        }
        tmp=tmp->frere;
    }
    return minimum;
}

int MinMax(noeud* arbre, int periode)
{
    if(arbre!=NULL && arbre->pere!=NULL && scores_inscrits_fraternite(arbre)==1)
    {
        if(periode==2) arbre->pere->score = maximum_generation(arbre); //et les parents des freres ??
        else arbre->pere->score = minimum_generation(arbre);
        return 1;
    }
    return 0;
}

void MinMax_entier(noeud* arbre, int periode)
{
    if(arbre!=NULL)
    {
        if(MinMax(arbre, periode)==0)
        {
            MinMax_entier(arbre->fils, fonction_periodique(periode));
            MinMax_entier(arbre->frere, periode);
        }
    }
}

void MinMax_global(noeud* arbre)
{
    if(arbre!=NULL)
    {
        if(arbre->score==-1000)
        {
            MinMax_entier(arbre, 1);
            MinMax_global(arbre);
        }
    }
}


int main(int argc, char* argh[])
{
    srand(time(NULL));
    int** matrice = creer_matrice3X3();
    matrice = init_matrice(matrice);
    Resultats_TD(menu_total(), matrice);
	
    return 0;
}