/********************************************************************/
/*	INF147 - Travail pratique #2                                    */
/*	liste.cpp                                                       */
/*  Auteur : Massimo Faulkner, Tristan Bouchard, Olivier Frechette  */
/*                                                                  */
/*	Description: Module de gestion d'une liste chainee d'animaux    */
/********************************************************************/

#ifndef LIB_LISTE
#define LIB_LISTE 1

/*=========================================================*/
/*                      LIBRAIRIES                         */
/*=========================================================*/

#include "animal.h"


/*=========================================================*/
/*                         TYPES                           */
/*=========================================================*/

//type structure pour un noeud de la liste chainee
typedef struct noeud {
    t_animal animal;        //l'animal contenu dans ce noeud
    struct noeud *suivant;  //pointeur vers le prochain noeud, sinon NULL
} t_noeud;

//type structure pour la gestion de la liste chainee
typedef struct {
    t_noeud *tete;      //premier noeud de la liste
    t_noeud *fin;       //dernier noeud de la liste
    t_noeud *courant;   //noeud courant pour parcourir la liste
    t_noeud *precedent; //noeud avant le courant (pour retirer en O(1))
    int nb_elements;    //nombre d'animaux dans la liste
} t_liste;


/*=========================================================*/
/*                      PROTOTYPES                         */
/*=========================================================*/


/*=========================================================*/
/*                       INIT_LISTE                        */
/*   Fonction qui initialise une liste vide. Tous les      */
/*        pointeurs sont mis a NULL et le compte a 0.      */
/*      ENTREE: le pointeur de la liste a initialiser.     */
/*=========================================================*/
void init_liste(t_liste *liste);


/*=========================================================*/
/*                    AJOUTER_FIN_LISTE                    */
/*  Fonction qui ajoute une copie de l'animal recu a la    */
/*  fin de la liste. Le pointeur courant n'est PAS deplace.*/
/*  ENTREE: le pointeur de la liste et l'animal a ajouter. */
/*  SORTIE: la reference du nouvel animal dans la liste,   */
/*          ou NULL si l'allocation a echoue.              */
/*=========================================================*/
t_animal *ajouter_fin_liste(t_liste *liste, t_animal animal);


/*=========================================================*/
/*                    NB_ELEMENTS_LISTE                    */
/*   Fonction qui retourne le nombre d'animaux presents    */
/*                    dans la liste.                       */
/*            ENTREE: le pointeur de la liste.             */
/*           SORTIE: le nombre d'animaux.                  */
/*=========================================================*/
int nb_elements_liste(const t_liste *liste);


/*=========================================================*/
/*                      DEBUT_LISTE                        */
/*   Fonction qui place le pointeur courant au debut de    */
/*      la liste (NULL si la liste est vide).              */
/*            ENTREE: le pointeur de la liste.             */
/*=========================================================*/
void debut_liste(t_liste *liste);


/*=========================================================*/
/*                     SUIVANT_LISTE                       */
/*  Fonction qui deplace le pointeur courant au prochain   */
/*  element de la liste. Il devient NULL s'il etait place  */
/*                sur le dernier element.                  */
/*            ENTREE: le pointeur de la liste.             */
/*=========================================================*/
void suivant_liste(t_liste *liste);


/*=========================================================*/
/*                    OBTENIR_COURANT                      */
/*   Fonction qui retourne la reference de l'animal du     */
/*                   noeud courant.                        */
/*            ENTREE: le pointeur de la liste.             */
/*  SORTIE: la reference de l'animal courant, ou NULL si   */
/*        le pointeur courant est hors de la liste.        */
/*=========================================================*/
t_animal *obtenir_courant(const t_liste *liste);


/*=========================================================*/
/*                    RETIRER_COURANT                      */
/*   Fonction qui retire le noeud courant de la liste. Le  */
/*  pointeur courant pointe ensuite sur l'element suivant. */
/*            ENTREE: le pointeur de la liste.             */
/*  SORTIE: une copie de l'animal retire (un animal remis  */
/*          a zero si le pointeur courant etait NULL).     */
/*=========================================================*/
t_animal retirer_courant(t_liste *liste);


/*=========================================================*/
/*                      VIDER_LISTE                        */
/*   Fonction qui detruit tous les noeuds de la liste et   */
/*           la remet dans son etat initial.               */
/*            ENTREE: le pointeur de la liste.             */
/*=========================================================*/
void vider_liste(t_liste *liste);

#endif
