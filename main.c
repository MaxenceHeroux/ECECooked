// Created by Maxence, Lucas, Ethan, Olivier on 21/03/2024.

#include <allegro.h>
#include "config.h"
#include "manette_PS.h"
#include "_fonctionsAllegro.h"
#define B_MANETTE_START_ON_NOW 0

int main(void) {

    ////////////////////////////////////// Initialisation //////////////////////////////////////
    // Initilisation Allegro
    initialisationAllegro();

    // Initialisation commandes de manette
    if(B_MANETTE_START_ON_NOW){
        install_joystick(JOY_TYPE_AUTODETECT); //pour pouvoir l activer apres le lancement jeux cf define
    }
    // Initialisation tableau controles manettes
    int state[TAM_MAX]={0};
    int state2 [TAM_MAX]={0};

    // Initialisation images et musiques
    t_ressources RESSOURCES = importationAllRessources();

    // Initialisation du buffer
    BITMAP* buffer = create_bitmap(SCREEN_W, SCREEN_H); // Buffer pour un affichage fluide
    clear(buffer);

    // Initialisation partie
    t_partie partie;

    //Initialisation fichiers
    //initialisation_fichier_score();
    //initialisation_fichiers_commandes();

    // Initialisation musique
    partie.music.activated = !MODE_DEV;

    // Initialisation espace mémoire des commandes et des recettes
    int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS] = {{0}};
    initialise_recettes(recettes);
    File_commandes* file_commandes = (File_commandes*)malloc(sizeof(File_commandes));
    file_commandes->nb_commande = 0;
    file_commandes->score = 0;
    file_commandes->first = NULL;

    // Initiaisaltion du temps
    srand(time(NULL));

    // Initialisation manette
    if(B_MANETTE_START_ON_NOW){
        partie.b_controller = 1;
    }
    else {
        partie.b_controller = 0;
    }

    // Variables déplacement menu
    short mouse_pressed = 0;



    ////////////////////////////////////// Menu //////////////////////////////////////
    /// Musique d'intro
    if (partie.music.activated) {
        play_sample(RESSOURCES.musicIntro, 255, 128, 1600, TRUE); //Musique d'intro
    }

    /// Fondu d'intro
    if (MODE_DEV == 0) {
        fonduDuMenu(buffer,RESSOURCES);
    }

    while (!key[KEY_ESC] && (state[GACHETTE_UP_L]!=1)) { // Condition pour quitter le jeu
        clearESC(state,state2);

        /// Affichage image fond du menu
        stretch_blit(RESSOURCES.launcher, buffer, 0, 0, RESSOURCES.launcher->w, RESSOURCES.launcher->h, 0, 0, SCREEN_W, SCREEN_H);

        /// Boutons
        boutonLancerMenuPartie (RESSOURCES, buffer, &partie, file_commandes, state, state2, recettes);
        boutonAfficherAides (RESSOURCES, buffer, state, state2);
        boutonMusiqueOnOff (RESSOURCES, RESSOURCES.musicIntro, 1600, buffer, &mouse_pressed, &partie.music.activated , state,state2);
        boutonManetteOnOff (RESSOURCES, buffer, &mouse_pressed, &partie.b_controller,  state,state2);
        if(boutonQuitterJeu (RESSOURCES, buffer,state,state2)) break;
        /// Affichage du curseur personalisé
        draw_sprite(buffer, RESSOURCES.mouse, mouse_x, mouse_y);

        /// Afficher écran
        afficherScreen(buffer);
    }


    ////////////////////////////////////// Suppression des ressources //////////////////////////////////////
    liberation(file_commandes);
    free(file_commandes);
    file_commandes = NULL;
    destroyAllRessources(RESSOURCES);
    allegro_exit();

    return 0;

} END_OF_MAIN()
