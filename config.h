#ifndef PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1_CONFIG_H
#define PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1_CONFIG_H

#include "ressources.h"
#include "manette_PS.h"
#include "_fonctionsAllegro.h"
#include "_temps.h"
#include "gestionObjets.h"
#include <allegro.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>

// DEBUG
#define INTERRACTION_HITBOX_CERCLE             0
#define INTERRACTION_HITBOX_CERCLE_CASE        0
#define MODE_DEV                 0   // passer à 0 pour les démonstrations, ou 1 pour jouer vraiment

// Taille du niveau
#define NB_COLONNES             20
#define NB_LIGNES               12

// Touches joueur
#define TOUCHE_INTERRACTION_JOUEUR1 KEY_L
//#define TOUCHE_INTERRACTION_JOUEUR1 KEY_1_PAD
#define TOUCHE_INTERRACTION_JOUEUR2 KEY_C
#define TOUCHE_ACTION_JOUEUR1 KEY_0_PAD //KEY_SEMICOLON
//#define TOUCHE_ACTION_JOUEUR1 KEY_2_PAD
#define TOUCHE_ACTION_JOUEUR2 KEY_V

// Commandes
#define NOMBRE_COMMANDES        6
#define ASSOMBRISSEMENT         70
#define ASSOMBRISSEMENTGAMEOVER 45
#define TIMER_PARTIE            180
#define DUREE_TICK_EN_MS        1000
#define VARIABLE_TEMPORELLE     250
#define NB_PIXELS_CASE          70
#define TAILLE_SELECTION        50

#define TAILLE_Y_COMMANDE       100
#define TAILLE_X_COMMANDE       100
#define TEMPS_COMMANDES         45

// Affichage des objets
#define SPRITE_X                SCREEN_W-230
#define SPRITE_Y                220
#define DECALAGE_EFFET_3D       -NB_PIXELS_CASE/2

// Changer les limites du niveau
#define LIMITE_X_MIN            NB_PIXELS_CASE/2
#define LIMITE_X_MAX            SCREEN_W-NB_PIXELS_CASE/2
#define LIMITE_Y_MIN            NB_PIXELS_CASE/2
#define LIMITE_Y_MAX            SCREEN_H- NB_PIXELS_CASE/2

// Collision et déplacement personnage
#define DELTA_VERS_PIED         10+(2*NB_PIXELS_CASE/3) // 20
#define VITESSE_MOUVEMENT       3
#define HAUTEUR_DECOUPE_FRONT   12+3*NB_PIXELS_CASE/10   // 8

// GESTION DES OBJETS
#define NOMBRE_OBJETS 68
#define NOMBRE_ASSIETTES_MAX 6
#define B_AUTORISATION_POSER_OBJET_SOL 0

#define TICK_CUISSON_MAX     5
#define TICK_CUISSON_PLAQUE_MAX     TICK_CUISSON_MAX
#define TICK_CUISSON_FRITTEUSE_MAX  TICK_CUISSON_MAX
#define TICK_CUISSON_FOUR_MAX       TICK_CUISSON_MAX
#define NOMBRE_CLICK_COUPER         6


typedef struct {
    int id_meuble;          // ID du meuble (sol, table, chaise, ...)
    int b_infranchissable;  // 0 faux donc franchissable, 1 vrai donc infranchissable
    short objet[NOMBRE_OBJETS];
} t_case;

typedef struct {
    short assiette[NOMBRE_OBJETS];
    short painBurger[NOMBRE_OBJETS];
    short poel[NOMBRE_OBJETS];
    short friteuse[NOMBRE_OBJETS];
    short four[NOMBRE_OBJETS];
    short friteuse_ancienne[NOMBRE_OBJETS];
    short decoupage[NOMBRE_OBJETS];
    short cuisson[NOMBRE_OBJETS];
    short falafels[NOMBRE_OBJETS];
    short basboussa[NOMBRE_OBJETS];
}t_permissionsObjets;

typedef struct {
    char username[25];
    BITMAP* imagejoueur;
    BITMAP* sprite;
    short int taille_du_nom;
    double pos_milieux_X;
    double pos_milieux_Y;
    int pos_case_X;
    int pos_case_Y;
    int pos_interaction_case_X;
    int pos_interaction_case_Y;
    int direction_angle;
    int score;
    int avancement_de_marche;
    short objet[NOMBRE_OBJETS];
    // t_objet objetMain;
} t_player;

typedef struct {
    BITMAP *background_back;
    BITMAP *background_front;
} t_backgrounds;

typedef struct {
    short activated;
    short alarm_playing;
    short alarm_played;
    short alarm_must_play;
    short nbr_alarm_playing;
    short nbr_pan_playing;
    short nbr_fryer_playing;
    short nbr_oven_playing;
} t_sound;

typedef struct{
    int temps_pro_commande; //temps avant que la prochaine commande soit envoyé
    long temps; //temps actuel
    long temps_prec_commande; //temps, le moment où a été envoyé la dernière commande
    long temps_seconde; //temps en milli seconde pour incrémenter le temps en seconde
    int seconde; //temps en seconde après le lancement du niveau
    int seconde_prec;
    long decalage; //entre le début du programme et le moment où on lance le niveau
    int timer; //timer du niveau
    int pause; //détecte si la pause est actibe (pause = 1)
    int decalage_pause; //durée en seconde de la pause
    int temps_pause_ON; //moment en seconde de l'activation de la pause
    int duree_totale_pause; //durée totale de toutes les pauses qui ont été activées
}t_temps;

typedef struct {
    t_player joueur1;
    t_player joueur2;
    t_backgrounds backgrounds;
    t_case matrice[NB_LIGNES][NB_COLONNES];
    t_sound music;
    t_temps time;
    short b_controller;
    short niveau_select;
    short tempete_active;
    short nombre_assiettes_restante;
    t_permissionsObjets permissionsObjets;
    short lvl4_succes;
}t_partie;

// liste chainée pour les commandes
/*
typedef struct commande{
    int type_commande;
    int chrono;
    int done;
    struct commandes* next;
}t_commande;
 */

typedef struct commande t_commande;
struct commande {
    int type_commande;
    int chrono;
    int done;
    t_commande* next;
};

typedef struct{
    t_commande* first;
    int nb_commande;
    int niveau;
    int score;
} File_commandes;



/// menu.c
void initialisationAllegro(void);
void fondueImage(double param, BITMAP* fond , BITMAP*bitmap, BITMAP*buffer,int X,int Y, int i , int j);
void fonduDuMenu(BITMAP* buffer, t_ressources RESSOURCES);
int boutonLancerMenuPartie(t_ressources RESSOURCES, BITMAP* buffer, t_partie* partie, File_commandes* file_commandes, int state[TAM_MAX], int state2[TAM_MAX], int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]);
void boutonAfficherAides(t_ressources RESSOURCES, BITMAP* buffer, int state[TAM_MAX], int state2[TAM_MAX]);
void boutonMusiqueOnOff(t_ressources RESSOURCES, SAMPLE* music, short speed, BITMAP* buffer, short* mouse_pressed, short* music_active, int state[TAM_MAX], int state2[TAM_MAX]);
void boutonManetteOnOff(t_ressources RESSOURCES, BITMAP* buffer, short* mouse_pressed, short* controller_active, int state[TAM_MAX], int state2[TAM_MAX]);
void deplacement_cursseur_manette( int state[TAM_MAX] ,int state2[TAM_MAX]);
int boutonQuitterJeu(t_ressources RESSOURCES, BITMAP* buffer, int state[TAM_MAX], int state2[TAM_MAX]);
int menuChoixNiveau(t_ressources RESSOURCES, BITMAP* buffer, int state[TAM_MAX], int state2[TAM_MAX], File_commandes* commandes);
void creation_niveau_personel (BITMAP* buffer, t_ressources RESSOURCES, int state[TAM_MAX], int state2[TAM_MAX]);
void waitingScreen(t_ressources RESSOURCES, BITMAP* buffer,t_partie* partie);
void initialisationPartie (t_partie* partie, int state[TAM_MAX], int state2[TAM_MAX]);
void creerJoueursNEW(t_partie* partie, int state[TAM_MAX], int state2[TAM_MAX]);

/// ressources.c
t_ressources importationAllRessources ();
void destroyAllRessources(t_ressources RESSOURCES);


/// partie.c
int lancerNiveau(t_ressources RESSOURCES, BITMAP* buffer, t_partie* partie, File_commandes* file_commandes, int state[TAM_MAX], int state2[TAM_MAX], int* i, int* j, int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]);
void choixPersonnagesEtNiveau(t_ressources RESSOURCES, BITMAP* buffer, t_partie* partie, File_commandes* commandes, int state[TAM_MAX], int state2[TAM_MAX]);
t_player creerJoueur(t_ressources RESSOURCES, BITMAP* buffer, int X, int Y, int number, t_partie partie, int state[TAM_MAX], int state2[TAM_MAX]);
void coloration_selection_personnage(BITMAP *buffer,BITMAP *launcher, short V1, short V2);
short menuChoixDuPersonnage(t_ressources RESSOURCES, BITMAP* buffer, BITMAP* maptexte2, int number, int state[TAM_MAX], int state2[TAM_MAX]);
void mouvementCollisionEtActionPersonnages(BITMAP *buffer, t_player* joueur, int iJoy, t_case matrice[NB_LIGNES][NB_COLONNES]);
int choixTextureDeDeplacementDuSprite(t_player* joueur);
void calculHitBox(BITMAP *buffer, t_player *joueur,double* previuscoY,double* previuscoX,t_case matrices[NB_LIGNES][NB_COLONNES]);
t_backgrounds backgrounds_maker(t_ressources RESSOURCES, char* name, t_partie* partie);
void afficher_pseudo(t_player* joueur1, t_backgrounds backgrounds,BITMAP* buffer);
int menu_pause_quitter (t_ressources RESSOURCES,t_partie* partie, BITMAP* buffer, File_commandes* file_commandes, int state[TAM_MAX], int state2[TAM_MAX]);
void Intro_level4(t_ressources RESSOURCES, BITMAP *buffer, t_partie *partie, int state[TAM_MAX], int state2[TAM_MAX]);
void Tempete_sable(t_ressources RESSOURCES, BITMAP *buffer, double param);
int fin_temps(t_partie* partie, t_ressources RESSOURCES, File_commandes* commandes, BITMAP* buffer, int state[TAM_MAX], int state2[TAM_MAX]);

/// commandes.c
int alea_type_commande_niv1();
int alea_temps_commande();
void ajout_maillon(File_commandes* tete, t_commande* commande);
void supprimer_maillon(File_commandes* file);
void liberation(File_commandes* tete);
void complete_commande(File_commandes* commandes, t_commande* commande);
t_commande* creerMaillon(File_commandes* fileCommandes);
void afficher_console(File_commandes* File_commande);
void lancer_commandes(File_commandes* commandes, t_ressources RESSOURCES, BITMAP* buffer, t_partie* partie);
void afficher_commandes(File_commandes* commandes, t_ressources RESSOURCES, BITMAP* buffer);
void initialise_recettes(int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]);
int alea_type_commande_niv4();
int alea_type_commande(int niveau);
void supprimer_tous_maillons(File_commandes* file);
void compareCommande(File_commandes* commandes ,const int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS],const short objet[NOMBRE_OBJETS]);
void initialisation_fichiers_commandes();

/// Score
void afficher_score(File_commandes* commandes, t_ressources RESSOURCES, t_partie* partie,BITMAP* buffer);
int meilleur_score(File_commandes* commandes);
void initialisation_fichier_score();

/// buttons.c
//short bouton(BITMAP* buffer, int pos_x, int pos_y, int taille_x, int taille_y, BITMAP* button, BITMAP* button_hover, BITMAP* button_pressed,int etat, int etat2);



/// gestionObjets.c

// Principales
int toucheInterractionJoueur(t_ressources RESSOURCES, t_case *caseMatrice, t_player *joueur, t_partie *partie, File_commandes *commandes, int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]);

// Actions et interractions
void actionTempsMeublesSpecifique(t_ressources RESSOURCES, t_partie *partie);
void toucheActionJoueur(t_ressources RESSOURCES, t_case *caseMatrice, t_player *joueur, t_partie *partie);
void interractionSpecialMeubleSpecifique(t_partie *partie, t_case *caseMatrice, t_player *joueur, File_commandes *commandes, int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]);
void interractionMeubleGenerateur(t_case *caseMatrice, t_player *joueur);

// Tests
int b_objet(short objet[NOMBRE_OBJETS]);
int b_meubleSpecifique(int IDcaseMatrice);

// Autorisations
int b_poserObjetMeubleSpecifique (int MeubleID, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]);
int b_prendreObjetMeubleSpecifique (int MeubleID, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]);
int b_echangerObjetMeubleSpecifique (int MeubleID, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]);
int b_objetCombinable(short objet1[NOMBRE_OBJETS], short objet2[NOMBRE_OBJETS], t_permissionsObjets permissionsObjets);
int b_verrificationPermission(short objet[NOMBRE_OBJETS], short permissionObjet[NOMBRE_OBJETS]);
int b_objetDejaPresent (short objet1[NOMBRE_OBJETS], short objet2[NOMBRE_OBJETS]);
short b_Melange_aliment(t_partie *partie);

// Fonctions
void supprimerObjet(short objet[NOMBRE_OBJETS]);
void echangerObjet(short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]);
int combinaisonObjetPrioritaire(t_partie* partie, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]);
void combinaisonObjets(t_partie* partie, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]);
void incrementationObjetTableau(short objet[NOMBRE_OBJETS]);

// Affichage et déplacement
void afficherStatuObjets(BITMAP *buffer, t_partie *partie);
int bMeubleExiste(int idMeuble);
int bMeubleHaut(int idMeuble);
int bMeubleInfranchissable(int idMeuble);
void dessineMatriceObjets(t_ressources RESSOURCES, BITMAP *buffer, short objetMatrice[NOMBRE_OBJETS], int origX, int origY, int id_meuble, int bJoueur, int orientationJoueur);
void dessineObjetsPlateauSurSol(t_ressources RESSOURCES, BITMAP *buffer, t_case matrice[NB_LIGNES][NB_COLONNES]);
void dessineObjetsPlateauEnHauteur(t_ressources RESSOURCES, BITMAP *buffer, t_case matrice[NB_LIGNES][NB_COLONNES]);
void dessineMarqueCaseInterraction(BITMAP *buffer, t_case matrice[NB_LIGNES][NB_COLONNES], int case_X, int case_Y, int bUniquementMeubleHaut);

// Initialisation
void initialiserObjetMatrice(t_case matrice[NB_LIGNES][NB_COLONNES]);
void initialiserObjetMeublesMatrice(t_case matrice[NB_LIGNES][NB_COLONNES]);
void initialisationPermissionsObjets(t_permissionsObjets *permissionsObjets);

// Debug
void afficherObjetMatriceConsole(t_case matrice[NB_LIGNES][NB_COLONNES]);
void afficherObjetJoueurConsole(t_player joueur, int numeroJoueur);





#endif //PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1_CONFIG_H