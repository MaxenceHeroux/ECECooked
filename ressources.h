#ifndef PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1_RESSOURCES_H
#define PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1_RESSOURCES_H

#include <allegro.h>

typedef struct {

    /////////////////////////////////////////// IMAGES MENU ///////////////////////////////////////////

    // LAUNCHER
    BITMAP *launcher;

    // INTERFACE CHARGEMENT
    BITMAP *interface_chargement;

    // FOND
    BITMAP *fondmenu;
    BITMAP *parchemin_menu;

    // CURSEUR DE LA SOURIS
    BITMAP *mouse;

    // BOUTONS LANCER PARTIE
    BITMAP *start_button;
    BITMAP *start_button_pressed;
    BITMAP *start_button_hover;

    // BOUTON AIDE
    BITMAP *help_button;
    BITMAP *help_button_pressed;
    BITMAP *help_button_hover;

    // BOUTON MUSIQUE
    BITMAP *music_ON_button;
    BITMAP *music_ON_button_pressed;
    BITMAP *music_ON_button_hover;
    BITMAP *music_OFF_button;
    BITMAP *music_OFF_button_pressed;
    BITMAP *music_OFF_button_hover;

    // BOUTON MANETTE
    BITMAP *manette_ON_button;
    BITMAP *manette_ON_button_pressed;
    BITMAP *manette_ON_button_hover;
    BITMAP *manette_OFF_button;
    BITMAP *manette_OFF_button_pressed;
    BITMAP *manette_OFF_button_hover;

    // BOUTON QUITTER
    BITMAP *exit_button;
    BITMAP *exit_button_pressed;
    BITMAP *exit_button_hover;

    // BOUTON AUTRE
    BITMAP *button_other;
    BITMAP *button_other_hover;

    // BOUTONS NIVEAUX
    BITMAP *button_nv1;
    BITMAP *button_nv1_hover;
    BITMAP *button_nv2;
    BITMAP *button_nv2_hover;
    BITMAP *button_nv3;
    BITMAP *button_nv3_hover;
    BITMAP *button_nv4;
    BITMAP *button_nv4_hover;

    /////////////////////////////////////////// CLAVIER VIRTUEL ///////////////////////////////////////////

    BITMAP *clavier_min;
    BITMAP *clavier_maj;

    /////////////////////////////////////////// MUSIQUE ET AUDIO ///////////////////////////////////////////

    SAMPLE* musicIntro;
    SAMPLE* sound_transition;
    SAMPLE* music_background;
    SAMPLE* music_background_lvl4;
    SAMPLE* music_lvl4_intro;
    SAMPLE* music_lvl4_outro;
    SAMPLE* ding;
    SAMPLE* fail_buzzer;
    SAMPLE* alarm;
    SAMPLE* sound_game_over;
    SAMPLE* sound_planche;
    SAMPLE* sound_poele;
    SAMPLE* sound_friteuse;
    SAMPLE* sound_four;

    /////////////////////////////////////////// FONTS ///////////////////////////////////////////

    FONT* font_big;
    FONT* font_small;
    FONT* font_egypt_big;
    FONT* font_egypt_small;

    /////////////////////////////////////////// SKINS ///////////////////////////////////////////

    BITMAP *skin1;
    BITMAP *skin2;
    BITMAP *skin3;
    BITMAP *skin4;
    BITMAP *casquette;
    BITMAP *rond_joueur;
    /////////////////////////////////////////// IMAGES PARTIE ///////////////////////////////////////////

    // MEUBLES
    BITMAP *parquet;
    BITMAP *friteuse;
    BITMAP *boite;
    BITMAP *planche_a_couper;
    BITMAP *plaque_de_cuisson;
    BITMAP *table_grise;
    BITMAP *four_ancien;
    BITMAP *friteuse_ancienne;
    BITMAP *pains_burger;
    BITMAP *table_rendu;
    BITMAP *table_rendu_bois;
    BITMAP *poubelle;
    BITMAP *poubelle_bois;
    BITMAP *evier;
    BITMAP *mur;

    BITMAP *plan_de_travail;
    BITMAP *sac_feves;
    BITMAP *sac_ail;
    BITMAP *sac_oignons;
    BITMAP *sac_epices;
    BITMAP *sac_semoule;
    BITMAP *sac_farine;
    BITMAP *sac_sucre;
    BITMAP *pot_miel;
    BITMAP *sable;
    BITMAP *palmier;
    BITMAP *fresque_egyptienne;

    // LEVEL4 EGYPT
    BITMAP *Egypt1;
    BITMAP *Egypt2;
    BITMAP *parchemin;
    BITMAP *hieroglyphes;
    BITMAP *texte_intro_fr;
    BITMAP *tempete_sable;

    // COMMANDES
    BITMAP *commande_assiette_propre;
    BITMAP *commande_assiette_sale;

    // OBJETS
    BITMAP *assiette_propre;
    BITMAP *poele;
    BITMAP *bac_de_friteuse;
    BITMAP *pain_burger_haut;
    BITMAP *pain_burger_bas;
    BITMAP *steak_cru;
    BITMAP *steak_decoupe;
    BITMAP *steak_cuit;
    BITMAP *steak_crame;
    BITMAP *fromage;
    BITMAP *fromage_coupe;
    BITMAP *salade;
    BITMAP *salade_coupe;
    BITMAP *tomates;
    BITMAP *tomates_coupe;
    BITMAP *patate_crue;
    BITMAP *frites_crue;
    BITMAP *frites_cuite;
    BITMAP *frites_crame;

//    BITMAP *poisson_crue;
//    BITMAP *poisson_coupe;
//    BITMAP *poisson_cuit;
//    BITMAP *poisson_crame;

    BITMAP *falafels_crus;
    BITMAP *falafels_cuits;
    BITMAP *falafels_crames;
    BITMAP *feves;
    BITMAP *feves_coupees;
    BITMAP *oignon;
    BITMAP *oignon_coupe;
    BITMAP *ail;
    BITMAP *ail_coupe;
    BITMAP *epices;
    BITMAP *basboussa_cru;
    BITMAP *basboussa_cuit;
    BITMAP *basboussa_crame;
    BITMAP *semoule;
    BITMAP *farine;
    BITMAP *sucre;
    BITMAP *miel;

    BITMAP *commande_burger_viande;
    BITMAP *commande_salade;
    BITMAP *commande_frites;
    BITMAP *commande_steak_frites;
    BITMAP *commande_falafel;
    BITMAP *commande_basboussa;

    /////////////////////////////////////////// FIN RESSOURCES ///////////////////////////////////////////

} t_ressources;

SAMPLE* load_wav_secured(char* cheminFichierSonWav);
FONT* load_font_secured(char* cheminFichierPolice);
BITMAP* load_bitmap_secured(char* nomDeFichier);

#endif //PROJET_ALLEGRO_ING1_2023_2024_S2_ECECOOKED_ING1_2023_2024_9_1_RESSOURCES_H