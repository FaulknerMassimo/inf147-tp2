/********************************************************************/
/*	INF147 - Travail pratique #2                                    */
/*	ocean.h                                                         */
/*  Auteur : Massimo Faulkner, Tristan Bouchard, Olivier Frechette  */
/*                                                                  */
/*	Description: Module qui permet la gestion des poissons          */
/*               et des requins dans l’océan                        */
/********************************************************************/

#ifndef LIB_OCEAN
#define LIB_OCEAN 1

/*=========================================================*/
/*                      CONSTANTES                         */
/*=========================================================*/

#define HAUTEUR   60
#define LARGEUR  120

#define COUL_POISSON  1  //en BLEU
#define COUL_REQUIN   4  //en ROUGE


/*=========================================================*/
/*                         TYPES                           */
/*=========================================================*/

/* Type énuméré pour les 8 directions de déplacement */
typedef enum {HAUT, HAUT_DR, DROITE, BAS_DR, BAS, BAS_G, GAUCHE, HAUT_G} t_direction;

/* Type énuméré pour le contenu d'une case */
typedef enum {VIDE, POISSON, REQUIN} t_contenu;

/* Type structure pour le contenu d'une case de la grille */
typedef struct{
  t_contenu contenu;     //Soit: VIDE, POISSON ou REQUIN
  void     *animal;      //Pointeur générique à un animal à cette case, sinon NULL
} t_case;

/* Type-tableau de la grille de l’océan (taille : 60 X 120) */
typedef t_case t_ocean[HAUTEUR][LARGEUR];


/*=========================================================*/
/*                      PROTOTYPES                         */
/*=========================================================*/


/*=========================================================*/
/*                       INIT_OCEAN                        */
/*   Fonction qui vide toutes les cases de la grille de    */
/*                        l'ocean.                         */
/* ENTREE: le tableau de l'ocean a initialiser.            */
/*=========================================================*/
void init_ocean(t_ocean ocean);


/*=========================================================*/
/*                    POSITION_VALIDE                      */
/*  Fonction qui retourne 1 si la position recue est dans  */
/*                 les limites de l'ocean.                 */
/*    ENTREE: les coordonnees posx et posy a verifier.     */
/*     SORTIE: 1 si la position est valide, 0 sinon.       */
/*=========================================================*/
int position_valide(int posx, int posy);


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
                     int *voisin_x, int *voisin_y);


/*=========================================================*/
/*                    OBTENIR_CONTENU                      */
/*    Fonction qui retourne le contenu de la case a la     */
/*                    position recue.                      */
/*    ENTREE: l'ocean et les coordonnees de la case.       */
/* SORTIE: le contenu de la case ou VIDE si elle est hors  */
/*                  des limites de l'ocean.                */
/*=========================================================*/
t_contenu obtenir_contenu(const t_ocean ocean, int posx, int posy);


/*=========================================================*/
/*                    OBTENIR_ANIMAL                       */
/*  Fonction qui retourne la reference de l'animal a la    */
/*                  position recue.                        */
/*    ENTREE: l'ocean et les coordonnees de la case.       */
/* SORTIE: la reference de l'animal ou NULL si la position */
/*                     est invalide.                       */
/*=========================================================*/
void *obtenir_animal(const t_ocean ocean, int posx, int posy);


/*=========================================================*/
/*                      ECRIRE_CASE                        */
/*  Fonction qui inscrit un contenu et une reference dans  */
/*                  une case de l'ocean.                   */
/*    ENTREE: l'ocean, une position, le contenu et la      */
/*           reference generique de l'animal.              */
/*=========================================================*/
void ecrire_case(t_ocean ocean, int posx, int posy,
                 t_contenu contenu, void *animal);


/*=========================================================*/
/*                      VIDER_CASE                         */
/*  Fonction qui efface le contenu et la reference d'une   */
/*                   case de l'ocean.                      */
/* ENTREE: l'ocean et les coordonnees de la case a vider.  */
/*=========================================================*/
void vider_case(t_ocean ocean, int posx, int posy);


/*=========================================================*/
/*               NB_CASES_VOISINES_VIDES                   */
/*  Fonction qui retourne le nombre de cases libres dans   */
/*           le voisinage immediat d'une position.         */
/* ENTREE: l'ocean et les coordonnees de la case centrale. */
/*   SORTIE: le nombre de cases voisines qui sont vides.   */
/*=========================================================*/
int nb_cases_voisines_vides(const t_ocean ocean, int posx, int posy);


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
                               int *voisin_x, int *voisin_y);


/*=========================================================*/
/*                    DESSINER_OCEAN                       */
/*  Fonction qui efface puis dessine tous les animaux de   */
/*                   l'ocean a l'ecran.                    */
/*              ENTREE: l'ocean a dessiner.                */
/*=========================================================*/
void dessiner_ocean(const t_ocean ocean);

#endif
