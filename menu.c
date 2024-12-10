#include "config.h"

///-----------------------------------------------------------------------------------///
///                            BOUTONS MENU PRINCIPALE                                ///
///-----------------------------------------------------------------------------------///

/////////////////////////////////////////////////////////////////////////////////
// Nom : boutonLancerMenuPartie
// Role : Bouton pour lancer le choix des niveau
/////////////////////////////////////////////////////////////////////////////////
int boutonLancerMenuPartie(t_ressources RESSOURCES, BITMAP* buffer, t_partie* partie, File_commandes* file_commandes, int state[TAM_MAX], int state2[TAM_MAX], int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]){

    // On verifier que le bouton est appuyé
    if (bouton(buffer, SCREEN_W -300, 200, 200, 100, RESSOURCES.start_button,RESSOURCES.start_button_hover,RESSOURCES.start_button_pressed,state[BUTTON_X],state2[BUTTON_X])){

        //////////////////////////////////// INITIALISATION PARTIE ////////////////////////////////////
        initialisationPartie(partie,state,state);

        //////////////////////////////// CREATION NIVEAU ET PERSONNAGE ////////////////////////////////
        choixPersonnagesEtNiveau (RESSOURCES, buffer, partie, file_commandes,state,state2);

        //////////////////////////////////////// LANCER LE JEU ////////////////////////////////////////
        if(key[KEY_ESC] || state[BUTTON_ROND]){
            clearESC(state,state2);
            return 0;
        }
        else {
            if (MODE_DEV==0) waitingScreen(RESSOURCES, buffer, partie);
            int i = 0;
            int j = 0;

            // DEBUG : Affiche la matrice dans la console
            for (int k = 0; k < 12; ++k) {
                for (int l = 0; l < 20; ++l) {
                    printf("%d", partie->matrice[k][l].id_meuble);
                }
                printf("\n");
            }

            /// LANCER LE NIVEAU
            lancerNiveau(RESSOURCES, buffer, partie, file_commandes, state,state2, &i, &j, recettes);

            clearESC(state,state2);
        }

    return 0;
    }
}

/////////////////////////////////////////////////////////////////////////////////
// Nom : boutonAfficherAides
// Role : Bouton pour afficher les aides du jeu
/////////////////////////////////////////////////////////////////////////////////
void boutonAfficherAides(t_ressources RESSOURCES, BITMAP* buffer, int state[TAM_MAX], int state2[TAM_MAX]){
    if (bouton(buffer, SCREEN_W -300, 300, 200, 100, RESSOURCES.help_button,RESSOURCES.help_button_hover,RESSOURCES.help_button_pressed,state[BUTTON_X],state2[BUTTON_X])) {
        stretch_blit(RESSOURCES.launcher, screen, 0, 0, RESSOURCES.launcher->w, RESSOURCES.launcher->h, 0, 0, SCREEN_W, SCREEN_H);

        textprintf_ex(screen, font, SCREEN_W - 310, 200, makecol(0, 0, 0), -1, "---------REGLES---------");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+text_height(font)+6, makecol(0, 0, 0), -1, "Objectif : Le but principal");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*2, makecol(0, 0, 0), -1, "d'ECECOOKED est de préparer");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*3, makecol(0, 0, 0), -1, "et de servir des plats dans ");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*4, makecol(0, 0, 0), -1, "un restaurant en coopération ");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*5, makecol(0, 0, 0), -1, "avec d'autres joueurs.");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*7, makecol(0, 0, 0), -1, "Les touches : J1 ZQSD et C/V ");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*8, makecol(0, 0, 0), -1, "J2 flèches haut bas gauche");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*9, makecol(0, 0, 0), -1, "droite et touche L/M. ");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*11, makecol(0, 0, 0), -1, "Gardez un œil sur le feu : ");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*12, makecol(0, 0, 0), -1, "Surveillez constamment les");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*13, makecol(0, 0, 0), -1, "plats pour éviter qu'ils ne");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*14, makecol(0, 0, 0), -1, "brûlent. Assurez-vous de les");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*15, makecol(0, 0, 0), -1, "retirer du feu à temps. ");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*16, makecol(0, 0, 0), -1, "Servez la première commande");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*17, makecol(0, 0, 0), -1, "de la file aux tables avec");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*18, makecol(0, 0, 0), -1, "une flèche. Les commandes");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*19, makecol(0, 0, 0), -1, "s'affichent en haut à gauche");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*20, makecol(0, 0, 0), -1, "le timer et le score en haut");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*21, makecol(0, 0, 0), -1, "à droite.");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*23, makecol(0, 0, 0), -1, "A travers les niveaux, vous");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*24, makecol(0, 0, 0), -1, "cuisinerez des burgers, ");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*25, makecol(0, 0, 0), -1, "des steak-frites, des frites,");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*26, makecol(0, 0, 0), -1, "des salades et bien plus...");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*28, makecol(0, 0, 0), -1, "Bon jeu !");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*30, makecol(0, 0, 0), -1, "Ethan BAUDRILLARD");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*31, makecol(0, 0, 0), -1, "Maxence HEROUX");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*32, makecol(0, 0, 0), -1, "Lucas VALERION");
        textprintf_ex(screen, font, SCREEN_W - 310, 200+(text_height(font)+6)*33, makecol(0, 0, 0), -1, "Olivier YAMMINE");

        textprintf_ex(screen, font, SCREEN_W - 300, 700, makecol(0, 0, 0), -1, "  [ PRESS ENTER ou O]");

        while (!key[KEY_ENTER] && (state[BUTTON_ROND]!=1) && (state2[BUTTON_ROND]!=1)){
            input(state,state2); //manette deconnectée ca marche
        }
    }
}


/////////////////////////////////////////////////////////////////////////////////
// Nom : boutonMusiqueOnOff
// Role : Bouton pour activer ou desactiver la musique
/////////////////////////////////////////////////////////////////////////////////
void boutonMusiqueOnOff(t_ressources RESSOURCES, SAMPLE* music, short speed, BITMAP* buffer, short* mouse_pressed, short* music_active,  int state[TAM_MAX], int state2[TAM_MAX]) {
    if (bouton(buffer, SCREEN_W - 300, 400, 200, 100, RESSOURCES.music_ON_button, RESSOURCES.music_ON_button_hover,RESSOURCES.music_ON_button_pressed,state[BUTTON_X],state2[BUTTON_X])) {
        if ((*mouse_pressed) == 0) { //Si pas de click (gauche) actif
            if (*music_active) { //Si musique active alors on stop
                stop_sample(music);
                *music_active = 0;
            }
            else { //Sinon on la lance
                play_sample(music, 255, 128, speed, TRUE); //Musique
                *music_active = 1;
            }
        }
        *mouse_pressed = 1; //Click actif
    }

    if (!(mouse_b & 1) && !state[BUTTON_X] && !state2[BUTTON_X]) {
        *mouse_pressed = 0; //Click inactif (click gauche)
    }

    if (!(*music_active)) { //Si musique stoppée alors, on affiche le bouton music_OFF par-dessus celui de music_ON
        bouton(buffer, SCREEN_W -300, 400, 200, 100, RESSOURCES.music_OFF_button,RESSOURCES.music_OFF_button_hover,RESSOURCES.music_OFF_button_pressed,state[BUTTON_X],state2[BUTTON_X]);
    }
}


/////////////////////////////////////////////////////////////////////////////////
// Nom : boutonManetteOnOff
// Role : Bouton pour activer ou désactiver la manette
/////////////////////////////////////////////////////////////////////////////////
void boutonManetteOnOff(t_ressources RESSOURCES, BITMAP* buffer, short* mouse_pressed, short* controller_active, int state[TAM_MAX], int state2[TAM_MAX]){
    deplacement_cursseur_manette(state,state2); // Limite les mouvements de la manette

    if (bouton(buffer, SCREEN_W -300, 500, 200, 100, RESSOURCES.manette_ON_button,RESSOURCES.manette_ON_button_hover,RESSOURCES.manette_ON_button_pressed,state[BUTTON_X],state2[BUTTON_X])) {
        if (*mouse_pressed == 0) { //Si pas de click (gauche) actif
            if (*controller_active) {
                *controller_active = 0;
            }
            else {
                // Initialisation manette
                install_joystick(JOY_TYPE_AUTODETECT);
                *controller_active = 1;
            }
        }
        *mouse_pressed = 1; //Click actif
    }

    if (!(mouse_b & 1) && !state[BUTTON_X] && !state2[BUTTON_X]) {
        *mouse_pressed = 0; //Click inactif (click gauche)
    }

    if (!(*controller_active)) { // Si manette OFF alors, on affiche le bouton manette_OFF par-dessus celui de manette_ON
        bouton(buffer, SCREEN_W -300, 500, 200, 100, RESSOURCES.manette_OFF_button,RESSOURCES.manette_OFF_button_hover,RESSOURCES.manette_OFF_button_pressed,state[BUTTON_X],state2[BUTTON_X]);
        state[BUTTON_X]=0;  state[BUTTON_ROND]=0;   joy[0].stick[0].axis[0].pos=0;   joy[0].stick[0].axis[1].pos=0;  //supression de l historique de la manette
        state2[BUTTON_X]=0;  state2[BUTTON_ROND]=0;   joy[1].stick[0].axis[0].pos=0;   joy[1].stick[0].axis[1].pos=0;  //supression de l historique de la manette

    }
    else{
        input(state,state2);
    }
}


/////////////////////////////////////////////////////////////////////////////////
// Nom : boutonQuitterJeu
// Role : Bouton pour quitter le jeu
/////////////////////////////////////////////////////////////////////////////////
int boutonQuitterJeu(t_ressources RESSOURCES, BITMAP* buffer, int state[TAM_MAX], int state2[TAM_MAX]){
    return bouton(buffer, SCREEN_W -300, 600, 200, 100, RESSOURCES.exit_button,RESSOURCES.exit_button_hover,RESSOURCES.exit_button_pressed,state[BUTTON_X],state2[BUTTON_X])==1 ? 1 : 0 ;
}



///-----------------------------------------------------------------------------------///
///                            FONCTION INITIALISATION                                ///
///-----------------------------------------------------------------------------------///

/////////////////////////////////////////////////////////////////////////////////
// Nom : initialisationAllegro
// Role : Initialisation de la librairie Allegro
/////////////////////////////////////////////////////////////////////////////////
void initialisationAllegro(void) {
    allegro_init();
    set_color_depth(desktop_color_depth());
    if ((set_gfx_mode(GFX_AUTODETECT_WINDOWED,1400,840,0,0))!=0) {
        allegro_message("Probleme de mode graphique");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    // Initialisation clavier
    install_keyboard(); //attention clavier QWERTY

    // Initialisation souris
    install_mouse();

    // Initialisation son
    install_sound(DIGI_AUTODETECT, MIDI_NONE, NULL);
}


////////////////////////////////////////////////////////// [1 -> 2 -> 3]
// Nom du sous-programme : choixPersonnagesEtNiveau
// Rôle : Permet de choisir les pseudos et le niveau souhaité
// Appel de sous programme : creerJoueur, menuChoixNiveau
//    - creerJoueur
//    - menuChoixNiveau
//    - background_maker
//////////////////////////////////////////////////////////
void choixPersonnagesEtNiveau(t_ressources RESSOURCES, BITMAP* buffer, t_partie* partie, File_commandes* commandes, int state[TAM_MAX], int state2[TAM_MAX]){

    // Initialisation des etats d'avancements des personnages (affichage avancé des déplacements)
    partie->joueur1.avancement_de_marche=0;
    partie->joueur2.avancement_de_marche=0;

    clear_keybuf();

    ///////////////////////////////// CHOIX DES PERSONNAGES /////////////////////////////////
    /// Creation du personnage du joueur1
    partie->joueur1 = creerJoueur(RESSOURCES, buffer, 1100, 600, 1, *partie,state,state2);

    // Clear du buffer
    while(key[KEY_ENTER] || state[BUTTON_X]==1 || state2[BUTTON_X]==1){
        input(state,state2);
    }
    clear_keybuf(); // Evite d avoir le enter precedent qui rendre dans pseudo 2

    /// Creation du personnage du joueur 2
    partie->joueur2 = creerJoueur(RESSOURCES, buffer,200,600,2, *partie,state,state2);

    // Clear du buffer
    while(key[KEY_ENTER] || state[BUTTON_X]==1  || state2[BUTTON_X]==1|| mouse_b&1){
        input(state,state2);
    }

    ///////////////////////////////// CHOIX DU NIVEAU /////////////////////////////////

    // Affichage menu choix des niveau puis importation du niveau choisit et création de ses textures
    switch (menuChoixNiveau(RESSOURCES,buffer,state,state2,commandes)) {
        case 1 :{
            partie->niveau_select = 1;
            partie->backgrounds = backgrounds_maker(RESSOURCES, "../Background_niveau_1.txt", partie);
            break;
        }
        case 2 :{
            partie->niveau_select = 2;
            partie->backgrounds = backgrounds_maker(RESSOURCES, "../Background_niveau_2.txt", partie);
            break;
        }
        case 3 :{
            partie->niveau_select = 3;
            partie->backgrounds = backgrounds_maker(RESSOURCES, "../Background_niveau_3.txt", partie);
            break;
        }
        case 4 :{
            partie->niveau_select = 4;
            partie->backgrounds = backgrounds_maker(RESSOURCES, "../Background_niveau_4.txt", partie);
            break;
        }
        case 5:{
            partie->niveau_select = 5;
            creation_niveau_personel (buffer,RESSOURCES,state,state2);
            partie->backgrounds = backgrounds_maker(RESSOURCES, "../pf_tmp.txt", partie);
            break;
        }
        default:{
            break;
        }
    }
}

void draw_smal_table (BITMAP*table, int i, int j, t_backgrounds Creation){
    stretch_sprite(Creation.background_back,table,j*35,(i*35)+DECALAGE_EFFET_3D/2,NB_PIXELS_CASE/2,((110)/2)/3);
    stretch_sprite(Creation.background_front,table,j*35,(i*35)+DECALAGE_EFFET_3D/2,NB_PIXELS_CASE/2,(110)/2);
}
void draw_smal_table_object (BITMAP*table, BITMAP*object, int i, int j, t_backgrounds Creation){
    draw_smal_table(table,i,j,Creation);
    draw_smal_table(object,i,j,Creation);
}

#define DECALAGE_CONCEPTEUR 10
void creation_niveau_personel (BITMAP* buffer,t_ressources RESSOURCES, int state[TAM_MAX], int state2[TAM_MAX]){
    int matrice_tps[12][20]={0};
    int variable;
    FILE *Fichier_niv_perso = NULL;
    Fichier_niv_perso = fopen("../Background_niveau_5.txt", "r");
    assert(Fichier_niv_perso != NULL);
    for (int i = 0; i < NB_LIGNES; ++i) {
        for (int j=0 ; j < NB_COLONNES; ++j) {
            fscanf(Fichier_niv_perso,"%d",&variable);
            matrice_tps[i][j]=variable;
        }
    }
    fclose(Fichier_niv_perso);
    Fichier_niv_perso=NULL;

    t_backgrounds Creation;
    Creation.background_back = create_bitmap(SCREEN_W,SCREEN_H);
    Creation.background_front = create_bitmap(SCREEN_W,SCREEN_H);
    clear_to_color(Creation.background_back, makecol(124,124,124));
    clear_to_color(Creation.background_front, makecol(255,0,255));

    int id;

    while (!key[KEY_ENTER] && !state[BUTTON_ROND] && !state2[BUTTON_ROND]) {
        for (int i = 0; i < NB_LIGNES; i++) {
            for (int j = DECALAGE_CONCEPTEUR; j < NB_COLONNES+DECALAGE_CONCEPTEUR; j++) {
                //parquet
                stretch_sprite(Creation.background_back,RESSOURCES.parquet,j*35,i*35,NB_PIXELS_CASE/2,(35));
                stretch_sprite(Creation.background_front,RESSOURCES.parquet,j*35,i*35,NB_PIXELS_CASE/2,(35));
            }
        }
        for (int i = 0; i < NB_LIGNES; i++) {
            for (int j = DECALAGE_CONCEPTEUR; j < NB_COLONNES+DECALAGE_CONCEPTEUR; j++) {
                switch (matrice_tps[i][j-DECALAGE_CONCEPTEUR]) {
                    case MEUBLE_SOL_SPAWN_JOUEUR1 : {
                        draw_smal_table(RESSOURCES.rond_joueur,i,j,Creation);
                        break;
                    }
                    case MEUBLE_SOL_SPAWN_JOUEUR2 : {
                        draw_smal_table(RESSOURCES.casquette,i,j,Creation);
                        break;
                    }
                    case MEUBLE_PLAN_DE_TRAVAIL         : {
                        draw_smal_table(RESSOURCES.plan_de_travail,i,j,Creation);
                        break;
                    }
                    case MEUBLE_TABLE_GRISE             : {
                        draw_smal_table(RESSOURCES.table_grise,i,j,Creation);
                        break;
                    }
                    case MEUBLE_PLANCHE_A_COUPER        : {
                        draw_smal_table_object(RESSOURCES.plan_de_travail,RESSOURCES.planche_a_couper,i,j,Creation);
                        break;
                    }
                    case MEUBLE_POUBELLE                : {
                        draw_smal_table(RESSOURCES.poubelle,i,j,Creation);
                        break;
                    }
                    case MEUBLE_PLAQUE_DE_CUISSON       : {
                        draw_smal_table(RESSOURCES.plaque_de_cuisson,i,j,Creation);
                        break;
                    }
                    case MEUBLE_FRITEUSE                : {
                        draw_smal_table(RESSOURCES.friteuse,i,j,Creation);
                        break;
                    }
                    case MEUBLE_RENDU                   : {
                        draw_smal_table(RESSOURCES.table_rendu,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_PAIN_BURGER  : {
                        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.pains_burger,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_SALADE       : {
                        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.salade,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_TOMATE       : {
                        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.tomates,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_FROMAGE      : {
                        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.fromage,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_STEAK        : {
                        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.steak_cru,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_PATATE       : {
                        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.patate_crue,i,j,Creation);
                        break;
                    }
//////////////  case MEUBLE_GENERATEUR_POISSON      : { dessineGenerateurAvecObjet(background,i,j,RESSOURCES.boite,RESSOURCES.tomates);         break;  }
                    case MEUBLE_GENERATEUR_ASSIETTE     : {
                        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.assiette_propre,i,j,Creation);
                        break;
                    }
                    case MEUBLE_PALMIER                 : {
                        draw_smal_table(RESSOURCES.palmier,i,j,Creation);
                        break;
                    }
                    case MEUBLE_FRITEUSE_ANCIENNE       : {
                        draw_smal_table(RESSOURCES.friteuse_ancienne,i,j,Creation);
                        break;
                    }
                    case MEUBLE_FOUR                    : {
                        draw_smal_table(RESSOURCES.four_ancien,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_FEVES        : {
                        draw_smal_table(RESSOURCES.sac_feves,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_OIGNONS      : {
                        draw_smal_table(RESSOURCES.sac_oignons,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_AIL          : {
                        draw_smal_table(RESSOURCES.sac_ail,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_EPICES       : {
                        draw_smal_table(RESSOURCES.sac_epices,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_SEMOULE      : {
                        draw_smal_table(RESSOURCES.sac_semoule,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_FARINE       : {
                        draw_smal_table(RESSOURCES.sac_farine,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_SUCRE        : {
                        draw_smal_table(RESSOURCES.sac_sucre,i,j,Creation);
                        break;
                    }
                    case MEUBLE_GENERATEUR_MIEL         : {
                        draw_smal_table_object(RESSOURCES.plan_de_travail,RESSOURCES.pot_miel,i,j,Creation);
                        break;
                    }
                    default: {
                        break;
                    }
                }
            }

        }

        //liste choix :
        stretch_sprite(Creation.background_back,RESSOURCES.parquet,MEUBLE_SOL*35,(SCREEN_H-35),NB_PIXELS_CASE/2,(35));
        draw_smal_table(RESSOURCES.plan_de_travail,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_PLAN_DE_TRAVAIL,Creation);
        draw_smal_table(RESSOURCES.table_grise,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_TABLE_GRISE,Creation);
        draw_smal_table_object(RESSOURCES.plan_de_travail,RESSOURCES.planche_a_couper,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_PLANCHE_A_COUPER,Creation);
        draw_smal_table(RESSOURCES.poubelle,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_POUBELLE,Creation);
        draw_smal_table(RESSOURCES.plaque_de_cuisson,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_PLAQUE_DE_CUISSON,Creation);
        draw_smal_table(RESSOURCES.friteuse,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_FRITEUSE,Creation);
        draw_smal_table(RESSOURCES.table_rendu,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_RENDU,Creation);
        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.pains_burger,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_PAIN_BURGER,Creation);
        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.salade,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_SALADE,Creation);
        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.tomates,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_TOMATE,Creation);
        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.fromage,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_FROMAGE,Creation);
        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.steak_cru,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_STEAK,Creation);
        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.patate_crue,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_PATATE,Creation);
        draw_smal_table_object(RESSOURCES.boite,RESSOURCES.assiette_propre,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_ASSIETTE,Creation);
        stretch_sprite(Creation.background_back,RESSOURCES.palmier,MEUBLE_PALMIER*35,(SCREEN_H-55),NB_PIXELS_CASE/2,(55));
        stretch_sprite(Creation.background_back,RESSOURCES.friteuse_ancienne,MEUBLE_FRITEUSE_ANCIENNE*35,(SCREEN_H-55),NB_PIXELS_CASE/2,(55));
        stretch_sprite(Creation.background_back,RESSOURCES.four_ancien,MEUBLE_FOUR*35,(SCREEN_H-55),NB_PIXELS_CASE/2,(55));
        //attention sac transparent
        draw_smal_table(RESSOURCES.sac_feves,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_FEVES,Creation);
        draw_smal_table(RESSOURCES.sac_oignons,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_OIGNONS,Creation);
        draw_smal_table(RESSOURCES.sac_ail,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_AIL,Creation);
        draw_smal_table(RESSOURCES.sac_epices,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_EPICES,Creation);
        draw_smal_table(RESSOURCES.sac_semoule,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_SEMOULE,Creation);
        draw_smal_table(RESSOURCES.sac_farine,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_FARINE,Creation);
        draw_smal_table(RESSOURCES.sac_sucre,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_SUCRE,Creation);
        draw_smal_table_object(RESSOURCES.plan_de_travail,RESSOURCES.pot_miel,(int)(SCREEN_H-55-DECALAGE_EFFET_3D)/35,MEUBLE_GENERATEUR_MIEL,Creation);
        //joueurs
        stretch_sprite(Creation.background_back,RESSOURCES.rond_joueur,MEUBLE_SOL_SPAWN_JOUEUR1*NB_PIXELS_CASE/2,(SCREEN_H-55),NB_PIXELS_CASE/2,(55));
        stretch_sprite(Creation.background_back,RESSOURCES.casquette,MEUBLE_SOL_SPAWN_JOUEUR2*NB_PIXELS_CASE/2,(SCREEN_H-55),NB_PIXELS_CASE/2,(55));

        //mouvement manette
        if(state[LSTICK_UP] && mouse_y>0) mouse_y-=VITESSE_MANETTE*2;
        if(state[LSTICK_DOWN]&& mouse_y<SCREEN_H) mouse_y+=VITESSE_MANETTE*2;
        if(state[LSTICK_RIGHT]&& mouse_x<SCREEN_W) mouse_x+=VITESSE_MANETTE*2;
        if(state[LSTICK_LEFT]&& mouse_x>0) mouse_x-=VITESSE_MANETTE*2;
        if(state2[LSTICK_UP] && mouse_y>0) mouse_y-=VITESSE_MANETTE*2;
        if(state2[LSTICK_DOWN]&& mouse_y<SCREEN_H) mouse_y+=VITESSE_MANETTE*2;
        if(state2[LSTICK_RIGHT]&& mouse_x<SCREEN_W) mouse_x+=VITESSE_MANETTE*2;
        if(state2[LSTICK_LEFT]&& mouse_x>0) mouse_x-=VITESSE_MANETTE*2;
        input(state,state2);

        if((mouse_b &1 || state[BUTTON_X] || state2[BUTTON_X]) && mouse_y>SCREEN_H-75){
            id= (int)mouse_x/35;
        }

        if((mouse_b &1 || state[BUTTON_X] || state2[BUTTON_X]) && mouse_y<SCREEN_H-75){
            int i = mouse_y / 35;
            int j = (mouse_x-DECALAGE_CONCEPTEUR*35)/ 35;
            if (i >= 0 && i < NB_LIGNES && j >= 0 && j < NB_COLONNES) {
                matrice_tps[i][j] = id;
            }
        }

        blit(Creation.background_back, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        masked_blit(Creation.background_front, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        draw_sprite(buffer, RESSOURCES.mouse, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        if(key[KEY_S]){
            FILE * pf =NULL;
            pf= fopen("../pf_backup.txt","w");
            assert(pf!=NULL);
            for (int i = 0; i < 12; ++i) {
                for (int j = 0; j < 20; ++j) {
                    fprintf(pf,"%d  ",matrice_tps[i][j]);
                }
                fprintf(pf,"\n");
            }
            fclose(pf);
            pf=NULL;
            allegro_message("fichier sauvegardé");
        }
        rest(10);
    }
    destroy_bitmap(Creation.background_back);
    destroy_bitmap(Creation.background_front);

    FILE * pf_tmp =NULL;
    pf_tmp= fopen("../pf_tmp.txt","w");
    assert(pf_tmp!=NULL);
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 20; ++j) {
            fprintf(pf_tmp,"%d  ",matrice_tps[i][j]);
        }
        fprintf(pf_tmp,"\n");
    }
    fclose(pf_tmp);
    pf_tmp=NULL;

}
////////////////////////////////////////////////////////// [1]
// Nom du sous-programme : creerJoueur
// Rôle : Initialisation des joueurs
// Appel de sous programme :
//    - menuChoixDuPersonnage
//////////////////////////////////////////////////////////
t_player creerJoueur (t_ressources RESSOURCES, BITMAP* buffer, int X, int Y, int number, t_partie partie, int state[TAM_MAX], int state2[TAM_MAX]){

    // Empeche de rentrer dans le pseudo précédent
    while(state[BUTTON_X]==1){
        input(state,state2);
    }

    // Création de l'objet joueur
    t_player joueur;
    BITMAP * maptexte1= create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP * maptexte2= create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP * buferdetexte= create_bitmap(SCREEN_W,SCREEN_H);

    // Affichage choix du pseudo
    stretch_blit(RESSOURCES.launcher, maptexte1, 0, 0, RESSOURCES.launcher->w, RESSOURCES.launcher->h, 0, 0,SCREEN_W, SCREEN_H);
    textprintf_ex(maptexte1, font, SCREEN_W - 300, 200, makecol(0, 0, 0), -1, "---------PSEUDO---------");
    textprintf_ex(maptexte1, font, SCREEN_W - 300, 220, makecol(0, 0, 0), -1, "---------player %d---------",number);
    textprintf_ex(maptexte1, font, SCREEN_W - 310, 240, makecol(0, 0, 0), -1, "Tapez votre nom de personnage");
    textprintf_ex(maptexte1, font, SCREEN_W - 300, 700, makecol(0, 0, 0), -1, "   [ PRESS ENTER ou O]     ");

    // Initialisation du pseudo
    char input_name[25]={0};
    int i=0;
    joueur.taille_du_nom=0;

    // Choix du pseudo par manette
    if (partie.b_controller) {
        apparitionClavier(RESSOURCES, buffer, buferdetexte, maptexte1, input_name);
        clavier(RESSOURCES, buffer, buferdetexte, maptexte1, input_name,state,state2);
        joueur.taille_du_nom = strlen(input_name);
    }
    else {
        while ((!key[KEY_ENTER] && state[BUTTON_ROND] != 1) && i < 24) {

            input(state,state2);
            if (keypressed()) {
                int KEY = readkey();
                if ((KEY >> 8 == KEY_DEL || KEY >> 8 == KEY_BACKSPACE) && i > 0) { //Si backspace ou suppr
                    i--;
                    input_name[i] = ' ';
                    joueur.taille_du_nom--;
                } else if (KEY >> 8) { //Sinon, on écrit la lettre
                    input_name[i] = KEY;
                    i++;
                    joueur.taille_du_nom++;
                }
            }
            blit(maptexte1, buferdetexte, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
            textprintf_ex(buferdetexte, font, SCREEN_W - 300, 260, makecol(0, 0, 0), -1, input_name);
            blit(buferdetexte, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        }

        clear(buferdetexte);
        while(key[KEY_ENTER] || state[BUTTON_ROND]==1){
            input(state,state2);
        }
    }


    // Choix du personnage entre plusieurs propositions
    clear_keybuf(); //évite d'avoir le texte précédent
    stretch_blit(RESSOURCES.launcher, maptexte2, 0, 0, RESSOURCES.launcher->w, RESSOURCES.launcher->h, 0, 0,SCREEN_W, SCREEN_H);
    switch (menuChoixDuPersonnage(RESSOURCES, buffer, maptexte2, number,state,state2)) {
        case 1: {
            joueur.imagejoueur = RESSOURCES.skin1;
            break;
        }
        case 2: {
            joueur.imagejoueur = RESSOURCES.skin2;
            break;
        }
        case 3: {
            joueur.imagejoueur = RESSOURCES.skin3;
            break;
        }
        case 4: {
            joueur.imagejoueur = RESSOURCES.skin4;
            break;
        }
        case 5: {
            textprintf_ex(maptexte2, font, SCREEN_W - 310, 240, makecol(0, 0, 0), -1, " Tapez votre nom de sprite");
            textprintf_ex(maptexte2, font, SCREEN_W - 310, 260, makecol(0, 0, 0), -1, " ..Sprites/");
            textprintf_ex(maptexte2, font, SCREEN_W - 300, 700, makecol(0, 0, 0), -1, "   [ PRESS ENTER ou X]     ");

            char string[50]={0};

            int j=0;
            while ((!key[KEY_ENTER] && state[BUTTON_X]!=1) && j < 50){
                char string_tpm[55]={0};
                input(state, state2);
                if(keypressed()){
                    int KEY = readkey();
                    if((KEY>>8==KEY_DEL || KEY>>8==KEY_BACKSPACE) && j>0){
                        j-=1;
                        string[j]=' ';
                    }else if(KEY>>8){
                        string[j]=KEY;
                        j++;
                    }
                }
                blit(maptexte2,buferdetexte,0,0,0,0,SCREEN_W,SCREEN_H);
                strcat(string_tpm,string);
                strcat(string_tpm, ".bmp");
                textprintf_ex(buferdetexte, font, SCREEN_W - 220, 260, makecol(0, 0, 0), -1,string_tpm );
                blit(buferdetexte,screen,0,0,0,0,SCREEN_W,SCREEN_H);
            }
            char name_sprite[50] = {0};
            strcat(name_sprite, "../Images/Sprites/");
            strcat(name_sprite, string);
            strcat(name_sprite, ".bmp");

            joueur.imagejoueur = load_bitmap(name_sprite,NULL);
            //cas rapide par defaut
            if (joueur.imagejoueur == NULL) {
                allegro_message("skin ou chemin non disposnible (chargement skin1)");
                joueur.imagejoueur = RESSOURCES.skin1;
            }
            break;
        }
        default: {
            break;
        }
    }
    destroy_bitmap(maptexte1);
    destroy_bitmap(maptexte2);
    destroy_bitmap(buferdetexte);

    // Initialisation des variables du joueur
    strcpy(joueur.username, input_name);

    joueur.sprite= create_bitmap(152,152);
    joueur.pos_milieux_X = X;
    joueur.pos_milieux_Y = Y;
    joueur.direction_angle =0;
    supprimerObjet(joueur.objet);
    joueur.score = 0;

    return joueur;
}


////////////////////////////////////////////////////////// [1]
// Nom du sous-programme : menuChoixDuPersonnage
// Rôle : Menu de choix du personnage
//////////////////////////////////////////////////////////
short menuChoixDuPersonnage(t_ressources RESSOURCES, BITMAP *buffer, BITMAP *maptexte2, int number, int state[TAM_MAX], int state2[TAM_MAX]) {

    while (1) {
        clear_bitmap(buffer);
        deplacement_cursseur_manette(state,state2);
        input(state,state2);

        blit(RESSOURCES.launcher, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        textprintf_ex(maptexte2, font, SCREEN_W - 300, 200, makecol(0, 0, 0), -1, "----------PERSO---------");
        textprintf_ex(maptexte2, font, SCREEN_W - 300, 220, makecol(0, 0, 0), -1, "---------player %d---------",
                      number);
        blit(maptexte2, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        masked_stretch_blit(RESSOURCES.skin1, buffer, 16, 642, 31, 60, SPRITE_X, SPRITE_Y,       54, 105);
        masked_stretch_blit(RESSOURCES.skin2, buffer, 16, 642, 31, 60, SPRITE_X, SPRITE_Y + 105, 54, 105);
        masked_stretch_blit(RESSOURCES.skin3, buffer, 16, 642, 31, 60, SPRITE_X, SPRITE_Y + 205, 54, 105);
        masked_stretch_blit(RESSOURCES.skin4, buffer, 16, 642, 31, 60, SPRITE_X, SPRITE_Y + 315, 54, 105);
        short other = bouton(buffer, SCREEN_W - 250, SPRITE_Y + 430, 100, 50, RESSOURCES.button_other,RESSOURCES.button_other_hover, RESSOURCES.button_other_hover, state[BUTTON_X],state2[BUTTON_X]);

        if ((mouse_x >= SPRITE_X - 5) && (mouse_x <= SPRITE_X + 62) && (mouse_y >= SPRITE_Y + 10) && (mouse_y <= SPRITE_Y + 110)) {
            coloration_selection_personnage(buffer, RESSOURCES.launcher, 10, 110);
            if ((mouse_b & 1) || state[BUTTON_X] || state2[BUTTON_X]) {
                return 1;
            }
        } else if ((mouse_x >= SPRITE_X - 5) && (mouse_x <= SPRITE_X + 62) && (mouse_y >= SPRITE_Y + 110) && (mouse_y <= SPRITE_Y + 110 + 105)) {
            coloration_selection_personnage(buffer, RESSOURCES.launcher, 110, 215);
            if ((mouse_b & 1) || state[BUTTON_X] || state2[BUTTON_X]) {
                return 2;
            }
        } else if ((mouse_x >= SPRITE_X - 5) && (mouse_x <= SPRITE_X + 62) && (mouse_y >= SPRITE_Y + 215) && (mouse_y <= SPRITE_Y + 215 + 100)) {
            coloration_selection_personnage(buffer, RESSOURCES.launcher, 215, 315);
            if ((mouse_b & 1) || state[BUTTON_X] || state2[BUTTON_X]) {
                return 3;
            }
        } else if ((mouse_x >= SPRITE_X - 5) && (mouse_x <= SPRITE_X + 62) && (mouse_y >= SPRITE_Y + 315) && (mouse_y <= SPRITE_Y + 315 + 110)) {
            coloration_selection_personnage(buffer, RESSOURCES.launcher, 315, 425);
            if ((mouse_b & 1) || state[BUTTON_X] || state2[BUTTON_X]) {
                return 4;
            }
        } else if (other) {
            return 5;
        }
        draw_sprite(buffer, RESSOURCES.mouse, mouse_x, mouse_y);
        afficherScreen(buffer);
    }
}


///////////////////////////////////////////////////////////////////////////////// [2]
// Nom : menuChoixNiveau
// Role : Menu de choix du niveau
// Return : le numéro du niveau choisi
/////////////////////////////////////////////////////////////////////////////////
int menuChoixNiveau (t_ressources RESSOURCES, BITMAP* buffer, int state[TAM_MAX], int state2[TAM_MAX], File_commandes* commandes) {
    while(1) {

        // On regarde le mode d'entrée
        deplacement_cursseur_manette(state,state2);
        input(state,state2);
        stretch_blit(RESSOURCES.launcher, buffer, 0, 0, RESSOURCES.launcher->w, RESSOURCES.launcher->h, 0, 0, SCREEN_W, SCREEN_H);

        // Affichage
        textprintf_ex(buffer, font, SCREEN_W - 300, 200, makecol(0, 0, 0), -1, "----CHOIX DU NIVEAUX----");
        textprintf_ex(buffer, font, SCREEN_W - 300, 700, makecol(0, 0, 0), -1, "   [ PRESS ESC ou O ]   ");

        // Choix du niveau par des boutons
        if(key[KEY_ESC] || state[BUTTON_ROND]==1 || state2[BUTTON_ROND]==1){
            return 0;
        }
        if (bouton(buffer, SCREEN_W - 300+9, 230, 200, 100, RESSOURCES.button_nv1, RESSOURCES.button_nv1_hover,
                   RESSOURCES.button_nv1_hover, state[BUTTON_X],state2[BUTTON_X])) {
            commandes->niveau = 1; //Indique dans quel niveau on est
            return 1;
        }
        if (bouton(buffer, SCREEN_W - 300+9, 330, 200, 100, RESSOURCES.button_nv2, RESSOURCES.button_nv2_hover,
                   RESSOURCES.button_nv2_hover, state[BUTTON_X],state2[BUTTON_X])) {
            commandes->niveau = 2; //Indique dans quel niveau on est
            return 2;
        }
        if (bouton(buffer, SCREEN_W - 300+9, 430, 200, 100, RESSOURCES.button_nv3, RESSOURCES.button_nv3_hover,
                   RESSOURCES.button_nv3_hover, state[BUTTON_X],state2[BUTTON_X])) {
            commandes->niveau = 3; //Indique dans quel niveau on est
            return 3;
        }
        if (bouton(buffer, SCREEN_W - 300+9, 530, 200, 100, RESSOURCES.button_nv4, RESSOURCES.button_nv4_hover,
                   RESSOURCES.button_nv4_hover, state[BUTTON_X],state2[BUTTON_X])) {
            commandes->niveau = 4; //Indique dans quel niveau on est
            return 4;
        }

        if (bouton(buffer, SCREEN_W - 250, 630, 200, 100, RESSOURCES.button_other, RESSOURCES.button_other_hover,
                   RESSOURCES.button_other, state[BUTTON_X],state2[BUTTON_X])) {
            commandes->niveau = 5;
            return 5;
        }

        // Affichage de la sourie et clear buffer
        draw_sprite(buffer, RESSOURCES.mouse, mouse_x, mouse_y);
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}


void dessineGenerateurAvecObjetEcart(t_backgrounds backgrounds, int i, int j, BITMAP *generateur, BITMAP *objet, int dx, int dy) {
    // Dessin d'une boite générateur
    masked_blit(generateur, backgrounds.background_back, 0,0,j*NB_PIXELS_CASE,i*NB_PIXELS_CASE+DECALAGE_EFFET_3D,generateur->w,generateur->h);
    masked_blit(generateur, backgrounds.background_front,0,0,j*NB_PIXELS_CASE,i*NB_PIXELS_CASE+DECALAGE_EFFET_3D,generateur->w,HAUTEUR_DECOUPE_FRONT);
    // Dessin de l'objet
    masked_blit(objet,      backgrounds.background_back, 0,0,j*NB_PIXELS_CASE+dx,i*NB_PIXELS_CASE+dy+DECALAGE_EFFET_3D,objet->w,objet->h);
    masked_blit(objet,      backgrounds.background_front,0,0,j*NB_PIXELS_CASE+dx,i*NB_PIXELS_CASE+dy+DECALAGE_EFFET_3D,objet->w,HAUTEUR_DECOUPE_FRONT);
}

void dessineGenerateurAvecObjet(t_backgrounds backgrounds, int i, int j, BITMAP *generateur, BITMAP *objet) {
    dessineGenerateurAvecObjetEcart(backgrounds, i, j, generateur, objet, 0,0);
}

void dessineMeubleSeulEcart(t_backgrounds backgrounds, int i, int j, BITMAP *meuble, int dx, int dy, int bDessineHaut) {
    // Dessin du meu ble seul
    masked_blit(meuble,     backgrounds.background_back, 0,0,j*NB_PIXELS_CASE+dx,i*NB_PIXELS_CASE+dy+DECALAGE_EFFET_3D,meuble->w,meuble->h);
    if (bDessineHaut==1)
        masked_blit(meuble,     backgrounds.background_front,0,0,j*NB_PIXELS_CASE+dx,i*NB_PIXELS_CASE+dy+DECALAGE_EFFET_3D,meuble->w,HAUTEUR_DECOUPE_FRONT);
}

void dessineMeubleSeul(t_backgrounds backgrounds, int i, int j, BITMAP *meuble) {
    dessineMeubleSeulEcart(backgrounds, i, j, meuble, 0,0,1);
}

///////////////////////////////////////////////////////////////////////////////// [3]
// Nom : Backgroud_maker
// Role : Importation du niveau et création des textures
///////////////////////////////////////////////////////////////////
t_backgrounds backgrounds_maker(t_ressources RESSOURCES, char* name, t_partie* partie) {

    // Création bitmaps arrière-plan
    t_backgrounds backgrounds;
    backgrounds.background_back  = create_bitmap(SCREEN_W,SCREEN_H);
    backgrounds.background_front = create_bitmap(SCREEN_W,SCREEN_H);

    // Initialisation arrière-plan transparent
    clear_to_color(backgrounds.background_front, couleurMagenta());

    // Ouverture fichier meubles
    FILE * fichier = fopen(name, "r");
    assert(fichier != NULL);

    int id_meuble_du_fichier;

    // Boucle initialiser sol et matrice meubles
    for (int i = 0; i < NB_LIGNES; ++i) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            // Pose du sol sur background_back
            if (partie->niveau_select != 4) {
                blit(RESSOURCES.parquet, backgrounds.background_back, 0, 0, j * NB_PIXELS_CASE, i * NB_PIXELS_CASE, RESSOURCES.parquet->w, RESSOURCES.parquet->h);
            }
            else {
                blit(RESSOURCES.sable, backgrounds.background_back, 0, 0, j * NB_PIXELS_CASE, i * NB_PIXELS_CASE, RESSOURCES.sable->w, RESSOURCES.sable->h);
            }

            // Initialisation de la matrice de meubles
            partie->matrice[i][j].b_infranchissable = 0;
            partie->matrice[i][j].id_meuble = MEUBLE_SOL;
        }
    }

    // Boucle pour lire le fichier et ajouter les meubles à l'arrière-plan
    for (int i = 0; i < NB_LIGNES ; i++) {
        for (int j = 0; j < NB_COLONNES; j++) {
            fscanf(fichier,"%d",&id_meuble_du_fichier);
            
            if (bMeubleExiste(id_meuble_du_fichier)==0) {exit(-1);} // on quitte le programme, erreur dans le fichier de description du niveau
            partie->matrice[i][j].id_meuble = id_meuble_du_fichier;
            if (partie->matrice[i][j].b_infranchissable ==0 ) { // test pour le cas particulier de la fresque où les case ont été lue en avance en infranchissable
                partie->matrice[i][j].b_infranchissable = bMeubleInfranchissable(id_meuble_du_fichier);
            }

            switch (id_meuble_du_fichier) {
                case MEUBLE_SOL_SPAWN_JOUEUR1       : { partie->matrice[i][j].b_infranchissable =0;     partie->joueur1.pos_milieux_X=j*NB_PIXELS_CASE;     partie->joueur1.pos_milieux_Y=i*NB_PIXELS_CASE; break; }
                case MEUBLE_SOL_SPAWN_JOUEUR2       : { partie->matrice[i][j].b_infranchissable =0;     partie->joueur2.pos_milieux_X=j*NB_PIXELS_CASE;     partie->joueur2.pos_milieux_Y=i*NB_PIXELS_CASE; break; }
                case MEUBLE_SOL 					: { break; }
                case MEUBLE_PLAN_DE_TRAVAIL         : { dessineMeubleSeul(backgrounds,i,j,RESSOURCES.plan_de_travail);   break;  }
                case MEUBLE_TABLE_GRISE             : { dessineMeubleSeul(backgrounds,i,j,RESSOURCES.table_grise);       break;  }
                case MEUBLE_PLANCHE_A_COUPER        : {
                    if (partie->niveau_select != 4) {
                        dessineGenerateurAvecObjet(backgrounds, i, j, RESSOURCES.plan_de_travail, RESSOURCES.planche_a_couper);
                    }
                    else {
                        dessineGenerateurAvecObjet(backgrounds, i, j, RESSOURCES.plan_de_travail, RESSOURCES.planche_a_couper);
                    }
                    break;  }
                case MEUBLE_POUBELLE                : {
                    if (partie->niveau_select != 4) {
                        dessineMeubleSeul(backgrounds,i,j,RESSOURCES.poubelle);}
                    else {
                        dessineMeubleSeul(backgrounds,i,j,RESSOURCES.poubelle_bois);}
                    break;  }
                case MEUBLE_PLAQUE_DE_CUISSON       : { dessineMeubleSeul(backgrounds,i,j,RESSOURCES.plaque_de_cuisson); break;  }
                case MEUBLE_FRITEUSE                : { dessineMeubleSeul(backgrounds,i,j,RESSOURCES.friteuse);          break;  }
                case MEUBLE_RENDU                   : {
                    if (partie->niveau_select != 4) {
                        dessineMeubleSeul(backgrounds, i, j, RESSOURCES.table_rendu);
                    }
                    else {
                        dessineMeubleSeul(backgrounds, i, j, RESSOURCES.table_rendu_bois);}
                    break;  }
                case MEUBLE_GENERATEUR_PAIN_BURGER  : { dessineGenerateurAvecObjet(backgrounds,i,j,RESSOURCES.boite,RESSOURCES.pains_burger);    break;  }
                case MEUBLE_GENERATEUR_SALADE       : { dessineGenerateurAvecObjet(backgrounds,i,j,RESSOURCES.boite,RESSOURCES.salade);          break;  }
                case MEUBLE_GENERATEUR_TOMATE       : { dessineGenerateurAvecObjet(backgrounds,i,j,RESSOURCES.boite,RESSOURCES.tomates);         break;  }
                case MEUBLE_GENERATEUR_FROMAGE      : { dessineGenerateurAvecObjet(backgrounds,i,j,RESSOURCES.boite,RESSOURCES.fromage);         break;  }
                case MEUBLE_GENERATEUR_STEAK        : { dessineGenerateurAvecObjet(backgrounds,i,j,RESSOURCES.boite,RESSOURCES.steak_cru);       break;  }
                case MEUBLE_GENERATEUR_PATATE       : { dessineGenerateurAvecObjet(backgrounds,i,j,RESSOURCES.boite,RESSOURCES.patate_crue);     break;  }
//////////////  case MEUBLE_GENERATEUR_POISSON      : { dessineGenerateurAvecObjet(backgrounds,i,j,RESSOURCES.boite,RESSOURCES.tomates);         break;  }
                case MEUBLE_GENERATEUR_ASSIETTE     : { dessineGenerateurAvecObjet(backgrounds,i,j,RESSOURCES.boite,RESSOURCES.assiette_propre); break;  }

                //////////////////// Meubles niveau 4

                case MEUBLE_FRESQUE_EGYPTIENNE :{                                                                                                 // fait
                    masked_blit(RESSOURCES.fresque_egyptienne,backgrounds.background_back,0,0,0,0,RESSOURCES.fresque_egyptienne->w,RESSOURCES.fresque_egyptienne->h);
                    // cas particulier !
                    if ((j+10)<NB_COLONNES) {
                        for (int k=0; k<NB_COLONNES; k++) {
                            partie->matrice[i][k].b_infranchissable = 1;
                        }
                        partie->matrice[i+1][j+9].b_infranchissable = 1;
                        partie->matrice[i+1][j+10].b_infranchissable = 1;
                    }break;
                }
                case MEUBLE_PALMIER                 : { dessineMeubleSeul(backgrounds,i,j,RESSOURCES.palmier);                                       break;  }

                case MEUBLE_FRITEUSE_ANCIENNE       : { dessineMeubleSeul(backgrounds,i,j,RESSOURCES.friteuse_ancienne); break;  }
                case MEUBLE_FOUR                    : { dessineMeubleSeul(backgrounds,i,j,RESSOURCES.four_ancien);       break;  }
                case MEUBLE_GENERATEUR_FEVES        : { dessineMeubleSeulEcart(backgrounds,i,j,RESSOURCES.sac_feves,-2,30,0);                          break;  }
                case MEUBLE_GENERATEUR_OIGNONS      : { dessineMeubleSeulEcart(backgrounds,i,j,RESSOURCES.sac_oignons,-2,30,0);                        break;  }
                case MEUBLE_GENERATEUR_AIL          : { dessineMeubleSeulEcart(backgrounds,i,j,RESSOURCES.sac_ail,-2,30,0);                            break;  }
                case MEUBLE_GENERATEUR_EPICES       : { dessineMeubleSeulEcart(backgrounds,i,j,RESSOURCES.sac_epices,-2,30,0);                         break;  }
                case MEUBLE_GENERATEUR_SEMOULE      : { dessineMeubleSeulEcart(backgrounds,i,j,RESSOURCES.sac_semoule,0,30,0);                         break;  }
                case MEUBLE_GENERATEUR_FARINE       : { dessineMeubleSeulEcart(backgrounds,i,j,RESSOURCES.sac_farine,0,30,0);                          break;  }
                case MEUBLE_GENERATEUR_SUCRE        : { dessineMeubleSeulEcart(backgrounds,i,j,RESSOURCES.sac_sucre,0,30,0);                           break;  }
                case MEUBLE_GENERATEUR_MIEL         : { dessineGenerateurAvecObjetEcart(backgrounds,i,j,RESSOURCES.plan_de_travail,RESSOURCES.pot_miel, 6,6);  break;  }

                default: {
                    // Si un meuble n'a pas été reconnu dans le switch case
                    partie->matrice[i][j].b_infranchissable = 0;
                    partie->matrice[i][j].id_meuble = MEUBLE_SOL;
                    break;
                }
            }
        }
    }
    fclose(fichier);
    // Retour de l'arrière-plan créé
    return backgrounds;
}


///////////////////////////////////////////////////////////////////////////////// [4]
// Nom : initialisationMatrice
// Role : Initialisation de la matrice de meubles
///////////////////////////////////////////////////////////////////

void initialisationMatrice (t_partie* partie){
    for (int i = 0; i < NB_LIGNES; ++i) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            partie->matrice[i][j].b_infranchissable = 0;
            partie->matrice[i][j].id_meuble = 3;
            supprimerObjet(partie->matrice[i][j].objet);
        }
    }
}



///-----------------------------------------------------------------------------------///
///                              FONCTION UTILITAIRE                                  ///
///-----------------------------------------------------------------------------------///

/////////////////////////////////////////////////////////////////////////////////
// Nom : fondueImage
// Role : Créee un fondu entre deux BITMAP
/////////////////////////////////////////////////////////////////////////////////
void fondueImage (double param, BITMAP* fond, BITMAP*bitmap, BITMAP*buffer,int X,int Y, int i ,int j){
    int  r, g, b;
    int pixelfond1 = getpixel(fond, i+X, j+Y);
    int pixelimage1= getpixel(bitmap, i, j);

    r = (1.0 - param) * getr(pixelfond1) + param * getr(pixelimage1);
    g = (1.0 - param) * getg(pixelfond1) + param * getg(pixelimage1);
    b = (1.0 - param) * getb(pixelfond1) + param * getb(pixelimage1);

    if(makecol(255,0,255) != getpixel(bitmap, i, j) && i<bitmap->w){
        putpixel(buffer, i+X, j+Y, makecol(r, g, b));
    }
}


/////////////////////////////////////////////////////////////////////////////////
// Nom : deplacement_cursseur_manette
// Role : Limite les mouvements de la manette
/////////////////////////////////////////////////////////////////////////////////
void deplacement_cursseur_manette( int state[TAM_MAX] ,int state2[TAM_MAX]) {
    if ((mouse_y > 50) && (mouse_y < SCREEN_H - 50)) {
        if (state[LSTICK_DOWN] ||state2[LSTICK_DOWN]) {
            mouse_x = SCREEN_W - 200;
            mouse_y += 2;
        }

        if (state[LSTICK_UP] || state2[LSTICK_UP]) {
            mouse_x = SCREEN_W - 200;
            mouse_y -= 2;
        }
    }
    else {
        mouse_x = SCREEN_W - 200;
        mouse_y = 200;
    }
}


/////////////////////////////////////////////////////////////////////////////////
// Nom : fonduDuMenu
// Role : Créee un fondu d'entree du menu
/////////////////////////////////////////////////////////////////////////////////
void fonduDuMenu (BITMAP * buffer ,t_ressources RESSOURCES){
    blit(RESSOURCES.launcher,screen,0,0,0,0,SCREEN_W,SCREEN_W); // affichage de l'image de fond
    blit(RESSOURCES.launcher,buffer,0,0,0,0,SCREEN_W,SCREEN_H); // copie de l'image de fond dans le buffer
    rest(1000);
    double param = 0;
    for (int k = 0; k < VARIABLE_TEMPORELLE; ++k) { // fondu du menu pour chaques elements, varie avec le temps
        for (int i = 0; i < RESSOURCES.start_button->w; ++i) {
            for (int j = 0; j < RESSOURCES.start_button->h; ++j) {
                fondueImage(param,RESSOURCES.launcher,RESSOURCES.start_button,buffer,SCREEN_W -300,200,i,j);
                fondueImage(param,RESSOURCES.launcher,RESSOURCES.help_button,buffer,SCREEN_W -300,300,i,j);
                fondueImage(param,RESSOURCES.launcher,RESSOURCES.music_ON_button,buffer,SCREEN_W -300,400,i,j);
                fondueImage(param,RESSOURCES.launcher,RESSOURCES.manette_OFF_button,buffer,SCREEN_W -300,500,i,j);
                fondueImage(param,RESSOURCES.launcher,RESSOURCES.exit_button,buffer,SCREEN_W -300,600,i,j);
            }
        }
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        param += pow(VARIABLE_TEMPORELLE,-1); // variation du parametre du temps
    }
}


/////////////////////////////////////////////////////////////////////////////////
// Nom : waitingScreen
// Role : Ecran de chargement
/////////////////////////////////////////////////////////////////////////////////

void waitingScreen(t_ressources RESSOURCES, BITMAP* buffer,t_partie* partie){
    if(partie->music.activated==1){
        stop_sample(RESSOURCES.musicIntro);
        play_sample(RESSOURCES.sound_transition, 255, 128, 1000, FALSE);
    }
    for (int i = 20; i <SCREEN_W-20 ; i++){
        blit(RESSOURCES.interface_chargement,buffer,0,0,0,0,SCREEN_W,SCREEN_H);
        rect(buffer, 19, SCREEN_H - 101, SCREEN_W - 19, SCREEN_H - 49, makecol(0, 0, 0));
        rectfill(buffer,20, SCREEN_H - 100,i,SCREEN_H-50, makecol(0,0,22));
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}


/////////////////////////////////////////////////////////////////////////////////
// Nom : initiliserJoueursNEW manuelle
// Role : Initialisation du joueur
/////////////////////////////////////////////////////////////////////////////////

void creerJoueursNEW(t_partie* partie, int state[TAM_MAX], int state2[TAM_MAX]) {

    partie->joueur1.taille_du_nom = 0;
    partie->joueur1.score = 0;
    partie->joueur1.avancement_de_marche = 0;
    supprimerObjet(partie->joueur1.objet);
    partie->joueur1.imagejoueur = NULL;
    partie->joueur1.sprite = create_bitmap(152, 152);
    partie->joueur1.pos_milieux_X = 0;
    partie->joueur1.pos_milieux_Y = 0;
    partie->joueur1.pos_case_X = 0;
    partie->joueur1.pos_case_Y = 0;
    partie->joueur1.pos_interaction_case_X = 0;
    partie->joueur1.pos_interaction_case_Y = 0;
    partie->joueur1.direction_angle = 0;

    partie->joueur2.taille_du_nom = 0;
    partie->joueur2.score = 0;
    partie->joueur2.avancement_de_marche = 0;
    supprimerObjet(partie->joueur2.objet);
    partie->joueur2.imagejoueur = NULL;
    partie->joueur2.sprite = create_bitmap(152, 152);
    partie->joueur2.pos_milieux_X = 0;
    partie->joueur2.pos_milieux_Y = 0;
    partie->joueur2.pos_case_X = 0;
    partie->joueur2.pos_case_Y = 0;
    partie->joueur2.pos_interaction_case_X = 0;
    partie->joueur2.pos_interaction_case_Y = 0;
    partie->joueur2.direction_angle = 0;
}



/////////////////////////////////////////////////////////////////////////////////
// Nom : initiliserPartie
// Role : Initialisation de la partie
/////////////////////////////////////////////////////////////////////////////////

void initialisationPartie (t_partie* partie, int state[TAM_MAX], int state2[TAM_MAX]) {
    creerJoueursNEW(partie,state,state2);
    partie->niveau_select = 1;
    partie->time.timer = 120;
    partie->time.temps_pro_commande = 0;
    partie->time.temps = maintenantEnMs();
    partie->time.temps_prec_commande = maintenantEnSec();
    partie->time.temps_seconde = maintenantEnMs();
    partie->time.decalage = maintenantEnSec();
    partie->time.seconde = 0;
    partie->time.seconde_prec = partie->time.seconde;
    partie->time.decalage_pause = 0;
    partie->time.pause = 0;
    partie->time.temps_pause_ON = 0;
    partie->time.duree_totale_pause = 0;
    initialiserObjetMatrice(partie->matrice);
}