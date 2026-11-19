/********************************************************************/
/*	INF147 - Travail pratique #2                                    */
/*	animal.cpp                                                      */
/*  Auteur : Massimo Faulkner, Tristan Bouchard, Olivier Frechette  */
/*                                                                  */
/*	Description: Module utilitaire qui permet de                    */
/*               gerer un type "t_animal"                           */
/********************************************************************/


/*=========================================================*/
/*                      LIBRAIRIES                         */
/*=========================================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "animal.h"


/*=========================================================*/
/*                      INIT_ANIMAL                        */
/*      fonction qui recoit un animal et ses valeurs       */
/*        initiales, va initialiser l'animal recu.         */
/* ENTREE: le pointeur du tableau de l'animal, sa position */
/* px et py, son age, son enerie, et ses jours de gestation*/
/*=========================================================*/
void init_animal(t_animal *animal, int px, int py, int age, int energie, int gest) {
    animal->posx = px;
    animal->posy = py;
    animal->age = age;
    animal->energie_sante = energie;
    animal->jrs_gest = gest;
}


/*=========================================================*/
/*                     GET_POSITION                        */
/*       fonction qui recoit un animal et retourne         */
/*             sa position via [*px, *py].                 */
/*    ENTREE: le tableau de l'animal, et les pointeurs     */
/*                   pour posx et posy                     */
/*=========================================================*/
void get_position(const t_animal *animal, int *px, int *py) {
    *px = animal->posx;
    *py = animal->posy;
}


/*=========================================================*/
/*                     SET_POSITION                        */
/*       fonction qui recoit un animal et une position     */
/*         et va inscrire cette position a l'animal.       */
/* ENTREE: le pointeur du tableau de l'animal, sa position */
/*                       px et py                          */
/*=========================================================*/
void set_position(t_animal *animal, int px, int py) {
    animal->posx = px;
    animal->posy = py;
}


/*=========================================================*/
/*                   PUBERTE_ATTEINTE                      */
/*    fonction qui recoit un animal et retourne 1 si le    */
/*   poisson a attient l'age de puberte ET a termine sa    */
/*      periode de gestation (donc, il va procreer),       */
/*                  retourne 0 sinon.                      */
/* ENTREE: le pointeur du tableau de l'animal, son age de  */
/*        puberte et sa periode de gestation               */
/*=========================================================*/
int puberte_atteinte(const t_animal *animal, int puberte, int gestation) {
    return animal->age >= puberte && animal->jrs_gest >= gestation;
}


/*=========================================================*/
/*                        INC_AGE                          */
/* fonction qui recoit un animal et va incrementer son age */
/* ainsi que le nombre de jours en gestation de +1 jour si */
/*           il est assez vieux pour procreer.             */
/*  ENTREE: le pointeur du tableau de l'animal et son age  */
/*                       de puberte                        */
/*=========================================================*/
void inc_age(t_animal *animal, int puberte) {
    animal->age++;

    if (animal->age >= puberte) {
        animal->jrs_gest++;
    }
}


/*=========================================================*/
/*                    RESET_GESTATION                      */
/*        Recoit un animal et va reinitialiser les         */
/*               jours de gestation a "val".               */
/* ENTREE: le pointeur du tableau de l'animal et la valeur */
/*=========================================================*/
void reset_gestation(t_animal *animal, int val) {
    animal->jrs_gest = val;
}


/*=========================================================*/
/*                     AJOUT_ENERGIE                       */
/*     fonction qui recoit un animal et va incrementer     */
/*        son niveau d'energie de la valeur recue.         */
/* ENTREE: le pointeur du tableau de l'animal et la valeur */
/*                       d'energie                         */
/*=========================================================*/
void ajout_energie(t_animal *animal, int energie) {
    animal->energie_sante += energie;
}


/*=========================================================*/
/*                       DEC_ENERGIE                       */
/*    fonction qui recoit un animal et va decrementer      */
/*             son niveau d'energie de -1.                 */
/*      ENTREE: le pointeur du tableau de l'animal         */
/*=========================================================*/
void dec_energie(t_animal *animal) {
    animal->energie_sante--;
}


/*=========================================================*/
/*                       GET_ENERGIE                       */
/*            fonction qui recoit un animal et             */
/*            va retourner son niveau d'energie.           */
/*        ENTREE: le pointeur du tableau de l'animal       */
/*=========================================================*/
int get_energie(t_animal *animal) {
    return animal->energie_sante;
}


/*=========================================================*/
/*                         EST_MORT                        */
/*    fonction qui retourne 1 si l'animal recu vient de    */
/*  mourir de faim (plus d'energie) OU si il a atteint son */
/*       age maximal (age_max). On retourne 0 sinon.       */
/*  ENTREE: le pointeur du tableau de l'animal et son age  */
/*                         maximal                         */
/*=========================================================*/
int est_mort(const t_animal *animal, int age_max) {
    return animal->energie_sante <= 0 || animal->age >= age_max;
}