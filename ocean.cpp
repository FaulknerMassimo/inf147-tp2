/********************************************************************/
/*	INF147 - Travail pratique #2                                    */
/*	ocean.cpp                                                       */
/*  Auteur : Massimo Faulkner, Tristan Bouchard, Olivier Frechette  */
/*                                                                  */
/*	Description: Module qui permet la gestion des poissons          */
/*               et des requins dans l'ocean                        */
/********************************************************************/


/*=========================================================*/
/*                      LIBRAIRIES                         */
/*=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ocean.h"
#include "util.h"
#include "utilitaire_affichage.h"


/*=========================================================*/
/*                      CONSTANTES                         */
/*=========================================================*/

//Deplacements associes aux directions de t_direction
static const int DEPLACEMENT_X[8] = {0, 1, 1, 1, 0, -1, -1, -1};
static const int DEPLACEMENT_Y[8] = {-1, -1, 0, 1, 1, 1, 0, -1};


/*=========================================================*/
/*                       INIT_OCEAN                        */
/*   Fonction qui vide toutes les cases de la grille de    */
/*                        l'ocean.                         */
/* ENTREE: le tableau de l'ocean a initialiser.            */
/*=========================================================*/
void init_ocean(t_ocean ocean) {
    int posx;
    int posy;

    for (posy = 0; posy < HAUTEUR; posy++) {
        for (posx = 0; posx < LARGEUR; posx++) {
            ocean[posy][posx].contenu = VIDE;
            ocean[posy][posx].animal = NULL;
        }
    }
}


/*=========================================================*/
/*                    POSITION_VALIDE                      */
/*  Fonction qui retourne 1 si la position recue est dans  */
/*                 les limites de l'ocean.                 */
/*    ENTREE: les coordonnees posx et posy a verifier.     */
/*     SORTIE: 1 si la position est valide, 0 sinon.       */
/*=========================================================*/
int position_valide(int posx, int posy) {
    return posx >= 0 && posx < LARGEUR && posy >= 0 && posy < HAUTEUR;
}


/*=========================================================*/
/*                   POSITION_VOISINE                      */
/*  Fonction qui retourne la position dans la direction    */
/*   recue. Le deplacement horizontal traverse l'ocean.    */
/*  ENTREE: une position, une direction et les pointeurs   */
/*         qui recevront les coordonnees du voisin.        */
/*  SORTIE: 1 et les coordonnees du voisin, ou 0 s'il n'y  */
/*         a pas de voisin dans cette direction.           */
/*=========================================================*/
int position_voisine(int posx, int posy, t_direction direction,
                     int *voisin_x, int *voisin_y) {
    int x;
    int y;

    if (!position_valide(posx, posy) || direction < HAUT || direction > HAUT_G ||
        voisin_x == NULL || voisin_y == NULL) {
        return 0;
    }

    x = posx + DEPLACEMENT_X[direction];
    y = posy + DEPLACEMENT_Y[direction];

    if (x < 0) {
        x = LARGEUR - 1;
    } else if (x >= LARGEUR) {
        x = 0;
    }

    if (y < 0 || y >= HAUTEUR) {
        return 0;
    }

    *voisin_x = x;
    *voisin_y = y;
    return 1;
}


/*=========================================================*/
/*                    OBTENIR_CONTENU                      */
/*    Fonction qui retourne le contenu de la case a la     */
/*                    position recue.                      */
/*    ENTREE: l'ocean et les coordonnees de la case.       */
/* SORTIE: le contenu de la case ou VIDE si elle est hors  */
/*                  des limites de l'ocean.                */
/*=========================================================*/
t_contenu obtenir_contenu(const t_ocean ocean, int posx, int posy) {
    if (!position_valide(posx, posy)) {
        return VIDE;
    }

    return ocean[posy][posx].contenu;
}


/*=========================================================*/
/*                    OBTENIR_ANIMAL                       */
/*  Fonction qui retourne la reference de l'animal a la    */
/*                  position recue.                        */
/*    ENTREE: l'ocean et les coordonnees de la case.       */
/* SORTIE: la reference de l'animal ou NULL si la position */
/*                     est invalide.                       */
/*=========================================================*/
void *obtenir_animal(const t_ocean ocean, int posx, int posy) {
    if (!position_valide(posx, posy)) {
        return NULL;
    }

    return ocean[posy][posx].animal;
}


/*=========================================================*/
/*                      ECRIRE_CASE                        */
/*  Fonction qui inscrit un contenu et une reference dans  */
/*                  une case de l'ocean.                   */
/*    ENTREE: l'ocean, une position, le contenu et la      */
/*           reference generique de l'animal.              */
/*=========================================================*/
void ecrire_case(t_ocean ocean, int posx, int posy,
                 t_contenu contenu, void *animal) {
    if (!position_valide(posx, posy)) {
        return;
    }

    ocean[posy][posx].contenu = contenu;

    if (contenu == VIDE) {
        ocean[posy][posx].animal = NULL;
    } else {
        ocean[posy][posx].animal = animal;
    }
}


/*=========================================================*/
/*                      VIDER_CASE                         */
/*  Fonction qui efface le contenu et la reference d'une   */
/*                   case de l'ocean.                      */
/* ENTREE: l'ocean et les coordonnees de la case a vider.  */
/*=========================================================*/
void vider_case(t_ocean ocean, int posx, int posy) {
    ecrire_case(ocean, posx, posy, VIDE, NULL);
}


/*=========================================================*/
/*               NB_CASES_VOISINES_VIDES                   */
/*  Fonction qui retourne le nombre de cases libres dans   */
/*           le voisinage immediat d'une position.         */
/* ENTREE: l'ocean et les coordonnees de la case centrale. */
/*   SORTIE: le nombre de cases voisines qui sont vides.   */
/*=========================================================*/
int nb_cases_voisines_vides(const t_ocean ocean, int posx, int posy) {
    int direction;
    int voisin_x;
    int voisin_y;
    int nb_vides = 0;

    for (direction = HAUT; direction <= HAUT_G; direction++) {
        if (position_voisine(posx, posy, (t_direction)direction,
                             &voisin_x, &voisin_y) &&
            obtenir_contenu(ocean, voisin_x, voisin_y) == VIDE) {
            nb_vides++;
        }
    }

    return nb_vides;
}


/*=========================================================*/
/*               CHOISIR_CASE_VOISINE_VIDE                 */
/*  Fonction qui choisit aleatoirement une case libre dans */
/*              le voisinage d'une position.               */
/*   ENTREE: l'ocean, une position et les pointeurs qui    */
/*        recevront les coordonnees de la case choisie.    */
/* SORTIE: 1 et les coordonnees de la case libre, ou 0 si  */
/*          aucune case voisine n'est disponible.          */
/*=========================================================*/
int choisir_case_voisine_vide(const t_ocean ocean, int posx, int posy,
                               int *voisin_x, int *voisin_y) {
    int cases_x[8];
    int cases_y[8];
    int direction;
    int x;
    int y;
    int nb_vides = 0;
    int choix;

    if (voisin_x == NULL || voisin_y == NULL) {
        return 0;
    }

    for (direction = HAUT; direction <= HAUT_G; direction++) {
        if (position_voisine(posx, posy, (t_direction)direction, &x, &y) &&
            obtenir_contenu(ocean, x, y) == VIDE) {
            cases_x[nb_vides] = x;
            cases_y[nb_vides] = y;
            nb_vides++;
        }
    }

    if (nb_vides == 0) {
        return 0;
    }

    choix = alea(0, nb_vides - 1);
    *voisin_x = cases_x[choix];
    *voisin_y = cases_y[choix];
    return 1;
}


/*=========================================================*/
/*                    DESSINER_OCEAN                       */
/*  Fonction qui efface puis dessine tous les animaux de   */
/*                   l'ocean a l'ecran.                    */
/*              ENTREE: l'ocean a dessiner.                */
/*=========================================================*/
void dessiner_ocean(const t_ocean ocean) {
    int posx;
    int posy;

    effacer_zone_environnement(HAUTEUR, LARGEUR);
    init_zone_environnement(HAUTEUR, LARGEUR);

    for (posy = 0; posy < HAUTEUR; posy++) {
        for (posx = 0; posx < LARGEUR; posx++) {
            if (ocean[posy][posx].contenu == POISSON) {
                afficher_case(posy, posx, HAUTEUR, LARGEUR, COUL_POISSON);
            } else if (ocean[posy][posx].contenu == REQUIN) {
                afficher_case(posy, posx, HAUTEUR, LARGEUR, COUL_REQUIN);
            }
        }
    }
}
