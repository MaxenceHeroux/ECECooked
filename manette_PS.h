#ifndef PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1_MANETTE_PS_H
#define PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1_MANETTE_PS_H

#include "ressources.h"
#include <allegro.h>
#include <assert.h>
#define TAILLE_PSEUDO 25
#define CLAVIER_X 22
#define CLAVIER_Y SCREEN_H - 300 //300 taille en y du bitmap clavier
#define VITESSE_MANETTE 2

enum{
    BUTTON_X,
    BUTTON_TRI,
    BUTTON_ROND,
    BUTTON_CARRE,

    /*BUTTON_CROIX_UP,
    BUTTON_CROIX_DOWN,
    BUTTON_CROIX_LEFT,
    BUTTON_CROIX_RIGHT,*/

    GACHETTE_UP_R,
    GACHETTE_UP_L,
    GACHETTE_R,
    GACHETTE_L,

    LSTICK_UP,
    LSTICK_DOWN,
    LSTICK_LEFT,
    LSTICK_RIGHT,

    TAM_MAX
};

void input(int state [TAM_MAX], int state2 [TAM_MAX]);
void affiche_clavier_min(t_ressources RESSOURCES, BITMAP* buffer);
void affiche_clavier_maj(t_ressources RESSOURCES, BITMAP* buffer);
void clavier(t_ressources RESSOURCES, BITMAP* buffer, BITMAP* buffer_texte, BITMAP* maptexte, char string[TAILLE_PSEUDO], int state[TAM_MAX], int state2[TAM_MAX]);
void apparitionClavier(t_ressources RESSOURCES, BITMAP* buffer, BITMAP* buffer_texte, BITMAP* maptexte, char string[TAILLE_PSEUDO]);

#endif //PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1_MANETTE_PS_H
