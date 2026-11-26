/********************************************************************/
/*	INF147 - Travail pratique #2                                    */
/*	liste.cpp                                                       */
/*  Auteur : Massimo Faulkner, Tristan Bouchard, Olivier Frechette  */
/*                                                                  */
/*	Description: Module de gestion d'une liste chainee d'animaux    */
/********************************************************************/


/*=========================================================*/
/*                      LIBRAIRIES                         */
/*=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "liste.h"


/*=========================================================*/
/*                       INIT_LISTE                        */
/*   Fonction qui initialise une liste vide. Tous les      */
/*        pointeurs sont mis a NULL et le compte a 0.      */
/*      ENTREE: le pointeur de la liste a initialiser.     */
/*=========================================================*/
void init_liste(t_liste *liste) {
    liste->tete = NULL;
    liste->fin = NULL;
    liste->courant = NULL;
    liste->precedent = NULL;
    liste->nb_elements = 0;
}


/*=========================================================*/
/*                    AJOUTER_FIN_LISTE                    */
/*  Fonction qui ajoute une copie de l'animal recu a la    */
/*  fin de la liste. Le pointeur courant n'est PAS deplace.*/
/*  ENTREE: le pointeur de la liste et l'animal a ajouter. */
/*  SORTIE: la reference du nouvel animal dans la liste,   */
/*          ou NULL si l'allocation a echoue.              */
/*=========================================================*/
t_animal *ajouter_fin_liste(t_liste *liste, t_animal animal) {
    t_noeud *nouveau;

    nouveau = (t_noeud *)malloc(sizeof(t_noeud));

    if (nouveau == NULL) {
        return NULL;
    }

    nouveau->animal = animal;
    nouveau->suivant = NULL;

    if (liste->tete == NULL) {
        liste->tete = nouveau;
    } else {
        liste->fin->suivant = nouveau;
    }

    liste->fin = nouveau;
    liste->nb_elements++;

    return &nouveau->animal;
}


/*=========================================================*/
/*                    NB_ELEMENTS_LISTE                    */
/*   Fonction qui retourne le nombre d'animaux presents    */
/*                    dans la liste.                       */
/*            ENTREE: le pointeur de la liste.             */
/*           SORTIE: le nombre d'animaux.                  */
/*=========================================================*/
int nb_elements_liste(const t_liste *liste) {
    return liste->nb_elements;
}


/*=========================================================*/
/*                      DEBUT_LISTE                        */
/*   Fonction qui place le pointeur courant au debut de    */
/*      la liste (NULL si la liste est vide).              */
/*            ENTREE: le pointeur de la liste.             */
/*=========================================================*/
void debut_liste(t_liste *liste) {
    liste->courant = liste->tete;
    liste->precedent = NULL;
}


/*=========================================================*/
/*                     SUIVANT_LISTE                       */
/*  Fonction qui deplace le pointeur courant au prochain   */
/*  element de la liste. Il devient NULL s'il etait place  */
/*                sur le dernier element.                  */
/*            ENTREE: le pointeur de la liste.             */
/*=========================================================*/
void suivant_liste(t_liste *liste) {
    if (liste->courant == NULL) {
        return;
    }

    liste->precedent = liste->courant;
    liste->courant = liste->courant->suivant;
}


/*=========================================================*/
/*                    OBTENIR_COURANT                      */
/*   Fonction qui retourne la reference de l'animal du     */
/*                   noeud courant.                        */
/*            ENTREE: le pointeur de la liste.             */
/*  SORTIE: la reference de l'animal courant, ou NULL si   */
/*        le pointeur courant est hors de la liste.        */
/*=========================================================*/
t_animal *obtenir_courant(const t_liste *liste) {
    if (liste->courant == NULL) {
        return NULL;
    }

    return &liste->courant->animal;
}


/*=========================================================*/
/*                    RETIRER_COURANT                      */
/*   Fonction qui retire le noeud courant de la liste. Le  */
/*  pointeur courant pointe ensuite sur l'element suivant. */
/*            ENTREE: le pointeur de la liste.             */
/*  SORTIE: une copie de l'animal retire (un animal remis  */
/*          a zero si le pointeur courant etait NULL).     */
/*=========================================================*/
t_animal retirer_courant(t_liste *liste) {
    t_noeud *a_retirer = liste->courant;
    t_animal copie;

    if (a_retirer == NULL) {
        init_animal(&copie, 0, 0, 0, 0, 0);
        return copie;
    }

    copie = a_retirer->animal;

    if (liste->precedent == NULL) {
        liste->tete = a_retirer->suivant;
    } else {
        liste->precedent->suivant = a_retirer->suivant;
    }

    if (a_retirer == liste->fin) {
        liste->fin = liste->precedent;
    }

    liste->courant = a_retirer->suivant;
    liste->nb_elements--;

    free(a_retirer);

    return copie;
}


/*=========================================================*/
/*                      VIDER_LISTE                        */
/*   Fonction qui detruit tous les noeuds de la liste et   */
/*           la remet dans son etat initial.               */
/*            ENTREE: le pointeur de la liste.             */
/*=========================================================*/
void vider_liste(t_liste *liste) {
    t_noeud *noeud = liste->tete;
    t_noeud *suivant;

    while (noeud != NULL) {
        suivant = noeud->suivant;
        free(noeud);
        noeud = suivant;
    }

    init_liste(liste);
}
