
//  Created by Luc BERTIN on 13/01/2017.
//  Copyright © 2017 Luc BERTIN. All rights reserved.

#ifndef Header_h
#define Header_h

//faire une matrice de caracteres plutôt que de int
typedef struct _noeud
{
    int** matrice;
    struct _noeud* fils;
    struct _noeud* frere;
    struct _noeud* pere;
    int score; // pour MinMax
}noeud;

//PROTOTYPE DES FONCTIONS
int menu();
int fonction_periodique(int num);
int** creer_matrice3X3();
int** init_matrice(int** matrice);
void affiche_matrice(int** matrice);
int coup_gagnant_lignes(int** matrice);
int coup_gagnant_colonnes(int** matrice);
int coup_gagnant_diagonale(int** matrice);
int est_remplie_matrice(int** matrice);
int est_gagnee_partie(int** matrice);
int est_finie_partie(int** matrice);
int est_occupee_place(int** matrice, int i, int j);
int** remplissage_matrice(int num_ligne, int num_colonne, int** matrice, int symbole);
int** remplissage_joueur(int** matrice, int symbole);
int** remplissage_IA(int** matrice, int symbole);
int jeu(int** matrice, int choix_premier_joueur);
void enonciation_gagnant(int gagnant);
noeud* creer_element(int** matrice);
int** dupliquer_matrice(int** matrice);
int nbr_cases_vide(int** matrice); // peut remplacer est_remplie_matrice
void test(int* i, int* j, int** matrice, int symbol);
int*** creer_tableau_de_matrices(int** matrice, int symbol);
void affiche_tableau_de_matrices(int*** tableau, int TAILLE);
noeud* ajouter_element(noeud* element, noeud* liste_Chainee);
void creer_descendance2(noeud* arbre, int symbol_joueur);
void creer_heritage2(noeud* arbre, int symbol_joueur);
void affiche_liste_chainee(noeud* liste);
void affiche_ligne_matrice(int ** matrice, int ligne);
void affiche_arbre2(noeud* arbre, int profondeur);
void affiche_arbre_partiel(noeud* arbre, int profondeur, int profondeur_max);
int nbr_noeuds(noeud* arbre);
int nbr_etats_finaux(noeud* arbre);
int coup_gagnant_lignes_entier(int** matrice, int entier_joueur);
int coup_gagnant_colonnes_entier(int** matrice, int entier_joueur);
int coup_gagnant_diagonale_entier(int** matrice, int entier_joueur);
int nbr_etats_finaux_gagnant(noeud* arbre, int num_joueur);


int score_matrice(int** matrice, int num_joueur);
noeud* recherche_victoire_la_plus_rapide(noeud* arbre);
void affichage_etats_menant_vers_victoire(noeud* arbre, int profondeur);
int** remplissage_par_MinMax(noeud* arbre, int** matrice);
int jeu2(int** matrice, int choix_premier_joueur, noeud* arbre);
void creer_heritage_partiel(noeud* arbre, int symbol_joueur, int profondeur_max_h);
int menu_total();
void VoirArbreOuPas(noeud* arbre, int h);
int jeu3(int** matrice, int choix_premier_joueur, noeud* arbre, int h);
void Resultats_TD(int choix, int** matrice);

//Declaration des fonctions pour le RESULTAT 2 (necessaire car MinMax est aussi utilise pour le Resultat 1)
int pions_alignes_lignes(int** matrice, int num_joueur, int nbr_a_aligner);
int pions_alignes_colonnes(int** matrice, int num_joueur, int nbr_a_aligner);
int pions_alignes_diagonales(int** matrice, int num_joueur, int nbr_a_aligner);
int instructions_score(int** matrice, int num_joueur);
int score_matrice_etat_partiel(int** matrice, int num_joueur);
void scores_feuiles(noeud* arbre, int reponse_resultat);
int scores_inscrits_fraternite(noeud* arbre);
int maximum_generation(noeud* arbre);
int minimum_generation(noeud* arbre);
int MinMax(noeud* arbre, int periode);
void MinMax_entier(noeud* arbre, int periode);
void MinMax_global(noeud* arbre);

#endif /* Header_h */
