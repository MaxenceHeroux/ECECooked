#ifndef PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1__FONCTIONSALLEGRO_H
#define PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1__FONCTIONSALLEGRO_H

#include <allegro.h>
#include "config.h"
#include "manette_PS.h"
#include "_fonctionsAllegro.h"

int attenteToucheBloquantAllegro();
int attenteToucheNonBloquantAllero();
void printErreurAllegro(char *message);
void printCharCouleurAllegro(char c, int couleurDuTexte);
void printOkAllegro(char *message);
void printKoAllegro(char *message);
void afficheCurseurAllegro(int bAffiche);

void afficheErreurEtQuitte(char* message);
void clearESC(int state[TAM_MAX],int state2[TAM_MAX]);
void clearScreen();
void afficherScreen(BITMAP* buffer);
int lireChaineAllegro(char *chaine, int longueur);
int lireIntAllegro();
char lireCharAllegro();
void retirerRetourLigneAllegro(char* mot);
void viderBufferAllegro();

void clearESC();
void afficherScreen(BITMAP* buffer);
short bouton (BITMAP* buffer, int pos_x, int pos_y, int taille_x, int taille_y, BITMAP*button, BITMAP*button_hover, BITMAP* button_pressed,int etat, int etat2);

int couleurGrisTresClair();
int couleurGrisMoyen();
int couleurGrisFonce();
int couleurNoir();
int couleurBlanc();
int couleurRouge();
int couleurVert();
int couleurPioche();
int couleurDefausse();
int couleurBleu();
int couleurJaune();
int couleurOrange();
int couleurMagenta();
int couleurMarron();
int couleurTransparence();

/// Screenshot
void Screenshot(BITMAP* buffer);

#endif //PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1__FONCTIONSALLEGRO_H
