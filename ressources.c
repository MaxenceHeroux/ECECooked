#include "config.h"

//////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : chargeImageSecurise
// Rôle : charger une image, quitte le jeu en cas d'erreur
//////////////////////////////////////////////////////////////////////////////

BITMAP* chargeImageSecurise(char* nomDeFichier)
{
    BITMAP *image;

    // Chargement de l'image (l'allocation a lieu en même temps)
    image = load_bitmap(nomDeFichier,NULL);

    // Vérification que l'image est bien chargée (dans le cas contraire image vaut NULL)
    // TOUJOURS LE FAIRE CAR ON N'EST JAMAIS CERTAIN DE BIEN TROUVER L'IMAGE
    if (!image)
    {
        allegro_message("ERREUR : échec lecture de l'image: %s",nomDeFichier);
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    return image;
}

//////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : load_wav_secured
// Rôle : charger un fichier son wav, quitte le jeu en cas d'erreur
//////////////////////////////////////////////////////////////////////////////

SAMPLE* load_wav_secured(char* cheminFichierSonWav)
{
    SAMPLE *son = load_wav(cheminFichierSonWav);
    if (!son)
    {
        allegro_message("ERREUR : échec lecture du son wav: %s",cheminFichierSonWav);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    return son;
}

//////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : load_font_secured
// Rôle : charger un fichier police de caractères, quitte le jeu en cas d'erreur
//////////////////////////////////////////////////////////////////////////////

FONT* load_font_secured(char* cheminFichierPolice)
{
    FONT *police = load_font(cheminFichierPolice, NULL, NULL);
    if (!police)
    {
        allegro_message("ERREUR : échec lecture de la police de caractères: %s",cheminFichierPolice);
        allegro_exit();
        exit(EXIT_FAILURE);
    }
    return police;
}

//////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : load_bitmap_secured
// Rôle : charger une image, quitte le jeu en cas d'erreur
//////////////////////////////////////////////////////////////////////////////

BITMAP* load_bitmap_secured(char* nomDeFichier)
{
    BITMAP *image;
    // Chargement de l'image (l'allocation a lieu en même temps)
    image = load_bitmap(nomDeFichier,NULL);
    // Vérification que l'image est bien chargée (dans le cas contraire image vaut NULL)
    // TOUJOURS LE FAIRE CAR ON N'EST JAMAIS CERTAIN DE BIEN TROUVER L'IMAGE
    if (!image)
    {
        allegro_message("ERREUR : échec lecture de l'image: %s",nomDeFichier);
        allegro_exit();
        exit(EXIT_FAILURE);
    }

    return image;
}


/////////////////////////////////////////////////////////////////////////////////
// Nom : importationAllRessources
// Role : importer toutes les ressources visuel et audio du jeu
/////////////////////////////////////////////////////////////////////////////////
t_ressources importationAllRessources (void) {
    t_ressources RESSOURCES;

    /////////////////////////////////////////// IMAGES MENU ///////////////////////////////////////////

    // LAUNCHER
    RESSOURCES.launcher                     = load_bitmap_secured("../Images/launcher.bmp");

    // INTERFACE CHARGEMENT
    RESSOURCES.interface_chargement         = load_bitmap_secured("../Images/interface_chargement.bmp");

    // FOND
    RESSOURCES.fondmenu                     = load_bitmap_secured("../Images/fondmenu.bmp");
    RESSOURCES.parchemin_menu               = load_bitmap_secured("../Images/parchemin_menu.bmp");

    // CURSEUR DE LA SOURIS
    RESSOURCES.mouse                        = load_bitmap_secured("../Images/mouse.bmp");

    // BOUTONS LANCER PARTIE
    RESSOURCES.start_button                 = load_bitmap_secured("../Images/Buttons/Button_Play_Gris.bmp");
    RESSOURCES.start_button_hover           = load_bitmap_secured("../Images/Buttons/Button_Play_Hover.bmp");
    RESSOURCES.start_button_pressed         = load_bitmap_secured("../Images/Buttons/Button_Play_Pressed.bmp");

    // BOUTON AIDE
    RESSOURCES.help_button                  = load_bitmap_secured("../Images/Buttons/Button_Help_Gris.bmp");
    RESSOURCES.help_button_hover            = load_bitmap_secured("../Images/Buttons/Button_Help_Hover.bmp");
    RESSOURCES.help_button_pressed          = load_bitmap_secured("../Images/Buttons/Button_Help_Pressed.bmp");

    // BOUTON MUSIQUE
    RESSOURCES.music_ON_button              = load_bitmap_secured("../Images/Buttons/Button_Music_ON_Gris.bmp");
    RESSOURCES.music_ON_button_hover        = load_bitmap_secured("../Images/Buttons/Button_Music_ON_Hover.bmp");
    RESSOURCES.music_ON_button_pressed      = load_bitmap_secured("../Images/Buttons/Button_Music_ON_Pressed.bmp");
    RESSOURCES.music_OFF_button             = load_bitmap_secured("../Images/Buttons/Button_Music_OFF_Gris.bmp");
    RESSOURCES.music_OFF_button_hover       = load_bitmap_secured("../Images/Buttons/Button_Music_OFF_Hover.bmp");
    RESSOURCES.music_OFF_button_pressed     = load_bitmap_secured("../Images/Buttons/Button_Music_OFF_Pressed.bmp");

    // BOUTON MANETTE
    RESSOURCES.manette_ON_button            = load_bitmap_secured("../Images/Buttons/Button_Controller_ON_Gris.bmp");
    RESSOURCES.manette_ON_button_hover      = load_bitmap_secured("../Images/Buttons/Button_Controller_ON_Hover.bmp");
    RESSOURCES.manette_ON_button_pressed    = load_bitmap_secured("../Images/Buttons/Button_Controller_ON_Pressed.bmp");
    RESSOURCES.manette_OFF_button           = load_bitmap_secured("../Images/Buttons/Button_Controller_OFF_Gris.bmp");
    RESSOURCES.manette_OFF_button_hover     = load_bitmap_secured("../Images/Buttons/Button_Controller_OFF_Hover.bmp");
    RESSOURCES.manette_OFF_button_pressed   = load_bitmap_secured("../Images/Buttons/Button_Controller_OFF_Pressed.bmp");

    // BOUTON QUITTER
    RESSOURCES.exit_button                  = load_bitmap_secured("../Images/Buttons/Button_Exit_Gris.bmp");
    RESSOURCES.exit_button_hover            = load_bitmap_secured("../Images/Buttons/Button_Exit_Hover.bmp");
    RESSOURCES.exit_button_pressed          = load_bitmap_secured("../Images/Buttons/Button_Exit_Pressed.bmp");

    // BOUTONS AUTRE
    RESSOURCES.button_other                 = load_bitmap_secured("../Images/Buttons/button_other.bmp");
    RESSOURCES.button_other_hover           = load_bitmap_secured("../Images/Buttons/button_other_hover.bmp");

    // BOUTONS NIVEAUX
    RESSOURCES.button_nv1                   = load_bitmap_secured("../Images/Buttons/button_nv1.bmp");
    RESSOURCES.button_nv1_hover             = load_bitmap_secured("../Images/Buttons/button_nv1_hover.bmp");
    RESSOURCES.button_nv2                   = load_bitmap_secured("../Images/Buttons/button_nv2.bmp");
    RESSOURCES.button_nv2_hover             = load_bitmap_secured("../Images/Buttons/button_nv2_hover.bmp");
    RESSOURCES.button_nv3                   = load_bitmap_secured("../Images/Buttons/button_nv3.bmp");
    RESSOURCES.button_nv3_hover             = load_bitmap_secured("../Images/Buttons/button_nv3_hover.bmp");
    RESSOURCES.button_nv4                   = load_bitmap_secured("../Images/Buttons/button_nv_final.bmp");
    RESSOURCES.button_nv4_hover             = load_bitmap_secured("../Images/Buttons/button_nv_final_hover.bmp");

    /////////////////////////////////////////// CLAVIER VIRTUEL ///////////////////////////////////////////

    RESSOURCES.clavier_min                  = load_bitmap_secured("../Images/clavier_min.bmp");
    RESSOURCES.clavier_maj                  = load_bitmap_secured("../Images/clavier_maj.bmp");

    /////////////////////////////////////////// MUSIQUE ET AUDIO ///////////////////////////////////////////

    RESSOURCES.musicIntro                   = load_wav_secured("../Sounds/epic-emotional_long.wav");
    RESSOURCES.sound_transition             = load_wav_secured("../Sounds/transition.wav");
    RESSOURCES.music_background             = load_wav_secured("../Sounds/background_music.wav");
    RESSOURCES.music_background_lvl4        = load_wav_secured("../Sounds/Temple of Endless Sands.wav");
    RESSOURCES.music_lvl4_intro             = load_wav_secured("../Sounds/Osiris - God of Egypt Powerful Ritual Epic Music.wav");
    RESSOURCES.music_lvl4_outro             = load_wav_secured("../Sounds/Isis - Most Powerful Goddess of Ancient Egypt Epic Cinematic Music.wav");
    RESSOURCES.ding                         = load_wav_secured("../Sounds/service-bell-ring.wav");
    RESSOURCES.fail_buzzer                  = load_wav_secured("../Sounds/wrong-buzzer.wav");
    RESSOURCES.alarm                        = load_wav_secured("../Sounds/alarm-clock.wav");
    RESSOURCES.sound_game_over              = load_wav_secured("../Sounds/game_over.wav");
    RESSOURCES.sound_planche                = load_wav_secured("../Sounds/slicing.wav");
    RESSOURCES.sound_poele                  = load_wav_secured("../Sounds/cooking-pan.wav");
    RESSOURCES.sound_friteuse               = load_wav_secured("../Sounds/deep-fryer-sizzle.wav");
    RESSOURCES.sound_four                   = load_wav_secured("../Sounds/bonfire.wav");

    /////////////////////////////////////////// FONTS ///////////////////////////////////////////

    RESSOURCES.font_big                     = load_font_secured("../Images/RebellionSquadPolice.pcx");
    RESSOURCES.font_small                   = load_font_secured("../Images/RebellionSquadPolice_small.pcx");
    RESSOURCES.font_egypt_big               = load_font_secured("../Images/EgyptAxeBig.pcx");
    RESSOURCES.font_egypt_small             = load_font_secured("../Images/EgyptAxeSmall.pcx");

    /////////////////////////////////////////// SKINS ///////////////////////////////////////////

    RESSOURCES.skin1                        = load_bitmap_secured("../Images/Sprites/sprite1.bmp");
    RESSOURCES.skin2                        = load_bitmap_secured("../Images/Sprites/sprite2.bmp");
    RESSOURCES.skin3                        = load_bitmap_secured("../Images/Sprites/sprite3.bmp");
    RESSOURCES.skin4                        = load_bitmap_secured("../Images/Sprites/egyptian.bmp");
    RESSOURCES.casquette                    = load_bitmap_secured("../Images/Sprites/casquette.bmp");
    RESSOURCES.rond_joueur                  = load_bitmap_secured("../Images/Sprites/joueur1.bmp");
    /////////////////////////////////////////// IMAGES PARTIE ///////////////////////////////////////////

    // MEUBLES
    //RESSOURCES.parquet                      = load_bitmap_secured("../Images/parquetDEBUG.bmp");  // parquet DEBUG
    RESSOURCES.parquet                      = load_bitmap_secured("../Images/Meubles/Parquet1.bmp");

    RESSOURCES.friteuse                     = load_bitmap_secured("../Images/Meubles/friteuse.bmp");
    RESSOURCES.boite                        = load_bitmap_secured("../Images/Meubles/Boite.bmp");
    RESSOURCES.planche_a_couper             = load_bitmap_secured("../Images/Meubles/PlancheACouper.bmp");
    RESSOURCES.plaque_de_cuisson            = load_bitmap_secured("../Images/Meubles/PlaqueDeCuisson_2.bmp");
    RESSOURCES.table_grise                  = load_bitmap_secured("../Images/Meubles/TableGrise.bmp");
    RESSOURCES.four_ancien                  = load_bitmap_secured("../Images/Meubles/four_pierres.bmp");
    RESSOURCES.friteuse_ancienne            = load_bitmap_secured("../Images/Meubles/friteuse_ancienne.bmp");
    RESSOURCES.pains_burger                 = load_bitmap_secured("../Images/Objets/pains_burger.bmp");
    RESSOURCES.table_rendu                  = load_bitmap_secured("../Images/Meubles/TableRenduDroite.bmp");
    RESSOURCES.table_rendu_bois             = load_bitmap_secured("../Images/Meubles/TableRendu_bois.bmp");
    RESSOURCES.poubelle                     = load_bitmap_secured("../Images/Meubles/Poubelle.bmp");
    RESSOURCES.poubelle_bois                = load_bitmap_secured("../Images/Meubles/poubelle_bois_2.bmp");
    RESSOURCES.plan_de_travail              = load_bitmap_secured("../Images/Meubles/plan_de_travail_2.bmp");
    RESSOURCES.evier                        = load_bitmap_secured("../Images/Meubles/evier.bmp");
    RESSOURCES.mur                          = load_bitmap_secured("../Images/Meubles/evier.bmp"); // changer

    RESSOURCES.sac_feves                    = load_bitmap_secured("../Images/Meubles/sac_feves.bmp");
    RESSOURCES.sac_ail                      = load_bitmap_secured("../Images/Meubles/sac_ail.bmp");
    RESSOURCES.sac_oignons                  = load_bitmap_secured("../Images/Meubles/sac_oignons.bmp");
    RESSOURCES.sac_epices                   = load_bitmap_secured("../Images/Meubles/sac_epices.bmp");
    RESSOURCES.sac_semoule                  = load_bitmap_secured("../Images/Meubles/sac_semoule.bmp");
    RESSOURCES.sac_farine                   = load_bitmap_secured("../Images/Meubles/sac_farine.bmp");
    RESSOURCES.sac_sucre                    = load_bitmap_secured("../Images/Meubles/sac_sucre.bmp");
    RESSOURCES.pot_miel                     = load_bitmap_secured("../Images/Meubles/pot_miel.bmp");
    RESSOURCES.sable                        = load_bitmap_secured("../Images/sable.bmp");
    RESSOURCES.palmier                      = load_bitmap_secured("../Images/palmier.bmp");
    RESSOURCES.fresque_egyptienne           = load_bitmap_secured("../Images/fresque.bmp");

    // LEVEL4 EGYPT
    RESSOURCES.Egypt1                       = load_bitmap_secured("../Images/Egypt1.bmp");
    RESSOURCES.Egypt2                       = load_bitmap_secured("../Images/Egypt2.bmp");
    RESSOURCES.parchemin                    = load_bitmap_secured("../Images/parchemin.bmp");
    RESSOURCES.hieroglyphes                 = load_bitmap_secured("../Images/hieroglyphes.bmp");
    RESSOURCES.texte_intro_fr               = load_bitmap_secured("../Images/texte_intro_fr.bmp");
    RESSOURCES.tempete_sable                = load_bitmap_secured("../Images/tempete_sable.bmp");

    // COMMANDES
    RESSOURCES.commande_assiette_propre     = load_bitmap_secured("../Images/assiette_propre.bmp"); //1
    RESSOURCES.commande_assiette_sale       = load_bitmap_secured("../Images/assiette_sale.bmp");     //2

    // OBJETS
    RESSOURCES.assiette_propre              = load_bitmap_secured("../Images/Objets/assiette_propre.bmp"); //1
    RESSOURCES.poele                        = load_bitmap_secured("../Images/Objets/poele.bmp");
    RESSOURCES.bac_de_friteuse              = load_bitmap_secured("../Images/Objets/bac_de_friteuse.bmp");
    RESSOURCES.pain_burger_haut             = load_bitmap_secured("../Images/Objets/pain_burger_haut.bmp");
    RESSOURCES.pain_burger_bas              = load_bitmap_secured("../Images/Objets/pain_burger_bas.bmp");
    RESSOURCES.steak_cru                    = load_bitmap_secured("../Images/Objets/steak_cru.bmp");
    RESSOURCES.steak_decoupe                = load_bitmap_secured("../Images/Objets/steak_decoupe.bmp");
    RESSOURCES.steak_cuit                   = load_bitmap_secured("../Images/Objets/steak_cuit.bmp");
    RESSOURCES.steak_crame                  = load_bitmap_secured("../Images/Objets/steak_crame.bmp");
    RESSOURCES.fromage                      = load_bitmap_secured("../Images/Objets/fromage.bmp");
    RESSOURCES.fromage_coupe                = load_bitmap_secured("../Images/Objets/fromage_coupe.bmp");
    RESSOURCES.salade                       = load_bitmap_secured("../Images/Objets/salade.bmp");
    RESSOURCES.salade_coupe                 = load_bitmap_secured("../Images/Objets/salade_coupe.bmp");
    RESSOURCES.tomates                      = load_bitmap_secured("../Images/Objets/tomates.bmp");
    RESSOURCES.tomates_coupe                = load_bitmap_secured("../Images/Objets/tomates_coupe.bmp");
    RESSOURCES.patate_crue                  = load_bitmap_secured("../Images/Objets/patate_crue.bmp");
    RESSOURCES.frites_crue                  = load_bitmap_secured("../Images/Objets/frites_crue.bmp");
    RESSOURCES.frites_cuite                 = load_bitmap_secured("../Images/Objets/frites_cuite.bmp");
    RESSOURCES.frites_crame                 = load_bitmap_secured("../Images/Objets/frites_crame.bmp");

//  RESSOURCES.poisson_crue                 = load_bitmap_secured("../Images/poisson_crue.bmp");
//  RESSOURCES.poisson_coupe                = load_bitmap_secured("../Images/poisson_coupe.bmp");
//  RESSOURCES.poisson_cuit                 = load_bitmap_secured("../Images/poisson_cuit.bmp");
//  RESSOURCES.poisson_crame                = load_bitmap_secured("../Images/poisson_crame.bmp");

    RESSOURCES.falafels_crus                = load_bitmap_secured("../Images/Objets/falafels_crus.bmp");
    RESSOURCES.falafels_cuits               = load_bitmap_secured("../Images/Objets/falafels_cuits.bmp");
    RESSOURCES.falafels_crames              = load_bitmap_secured("../Images/Objets/falafels_crames.bmp");
    RESSOURCES.feves                        = load_bitmap_secured("../Images/Objets/feves.bmp");
    RESSOURCES.feves_coupees                = load_bitmap_secured("../Images/Objets/feves_coupees.bmp");
    RESSOURCES.oignon                       = load_bitmap_secured("../Images/Objets/oignon.bmp");
    RESSOURCES.oignon_coupe                 = load_bitmap_secured("../Images/Objets/oignon_coupe.bmp");
    RESSOURCES.ail                          = load_bitmap_secured("../Images/Objets/ail.bmp");
    RESSOURCES.ail_coupe                    = load_bitmap_secured("../Images/Objets/ail_coupe.bmp");
    RESSOURCES.epices                       = load_bitmap_secured("../Images/Objets/epices.bmp");
    RESSOURCES.basboussa_cru                = load_bitmap_secured("../Images/Objets/basboussa_cru.bmp");
    RESSOURCES.basboussa_cuit               = load_bitmap_secured("../Images/Objets/basboussa_cuit.bmp");
    RESSOURCES.basboussa_crame              = load_bitmap_secured("../Images/Objets/basboussa_crame.bmp");
    RESSOURCES.semoule                      = load_bitmap_secured("../Images/Objets/semoule.bmp");
    RESSOURCES.farine                       = load_bitmap_secured("../Images/Objets/farine.bmp");
    RESSOURCES.sucre                        = load_bitmap_secured("../Images/Objets/sucre.bmp");
    RESSOURCES.miel                         = load_bitmap_secured("../Images/Objets/miel.bmp");

    RESSOURCES.commande_burger_viande       = load_bitmap_secured("../Images/commande_burger_viande.bmp");
    RESSOURCES.commande_salade              = load_bitmap_secured("../Images/commande_salade.bmp");
    RESSOURCES.commande_frites              = load_bitmap_secured("../Images/commande_frites.bmp");
    RESSOURCES.commande_steak_frites        = load_bitmap_secured("../Images/commande_steak_frites.bmp");
    RESSOURCES.commande_falafel             = load_bitmap_secured("../Images/commande_falafel.bmp");
    RESSOURCES.commande_basboussa           = load_bitmap_secured("../Images/commande_basboussa.bmp");

    /////////////////////////////////////////// FIN RESSOURCES ///////////////////////////////////////////

    return RESSOURCES;
}


/////////////////////////////////////////////////////////////////////////////////
// Nom : destroyAllRessources
// Role : detruire toutes les ressources visuel et audio du jeu
/////////////////////////////////////////////////////////////////////////////////

void destroyAllRessources(t_ressources RESSOURCES){

    // LAUNCHER
    destroy_bitmap(RESSOURCES.launcher);

    // INTERFACE CHARGEMENT
    destroy_bitmap(RESSOURCES.interface_chargement);

    // FOND
    destroy_bitmap(RESSOURCES.fondmenu);
    destroy_bitmap(RESSOURCES.parchemin_menu);

    // CURSEUR DE LA SOURIS
    destroy_bitmap(RESSOURCES.mouse);

    // BOUTONS LANCER PARTIE
    destroy_bitmap(RESSOURCES.start_button);
    destroy_bitmap(RESSOURCES.start_button_hover);
    destroy_bitmap(RESSOURCES.start_button_pressed);

    // BOUTON AIDE
    destroy_bitmap(RESSOURCES.help_button);
    destroy_bitmap(RESSOURCES.help_button_hover);
    destroy_bitmap(RESSOURCES.help_button_pressed);

    // BOUTON MUSIQUE
    destroy_bitmap(RESSOURCES.music_ON_button);
    destroy_bitmap(RESSOURCES.music_ON_button_hover);
    destroy_bitmap(RESSOURCES.music_ON_button_pressed);
    destroy_bitmap(RESSOURCES.music_OFF_button);
    destroy_bitmap(RESSOURCES.music_OFF_button_hover);
    destroy_bitmap(RESSOURCES.music_OFF_button_pressed);

    // BOUTON MANETTE
    destroy_bitmap(RESSOURCES.manette_ON_button);
    destroy_bitmap(RESSOURCES.manette_ON_button_hover);
    destroy_bitmap(RESSOURCES.manette_ON_button_pressed);
    destroy_bitmap(RESSOURCES.manette_OFF_button);
    destroy_bitmap(RESSOURCES.manette_OFF_button_hover);
    destroy_bitmap(RESSOURCES.manette_OFF_button_pressed);

    // BOUTON QUITTER
    destroy_bitmap(RESSOURCES.exit_button);
    destroy_bitmap(RESSOURCES.exit_button_hover);
    destroy_bitmap(RESSOURCES.exit_button_pressed);

    // BOUTON AUTRE
    destroy_bitmap(RESSOURCES.button_nv1);
    destroy_bitmap(RESSOURCES.button_nv1_hover);
    destroy_bitmap(RESSOURCES.button_nv2);
    destroy_bitmap(RESSOURCES.button_nv2_hover);
    destroy_bitmap(RESSOURCES.button_nv3);
    destroy_bitmap(RESSOURCES.button_nv3_hover);
    destroy_bitmap(RESSOURCES.button_nv4);
    destroy_bitmap(RESSOURCES.button_nv4_hover);

    /////////////////////////////////////////// CLAVIER VIRTUEL ///////////////////////////////////////////

    destroy_bitmap(RESSOURCES.clavier_min);
    destroy_bitmap(RESSOURCES.clavier_maj);

    /////////////////////////////////////////// MUSIQUE ET AUDIO ///////////////////////////////////////////

    destroy_sample(RESSOURCES.musicIntro);
    destroy_sample(RESSOURCES.sound_transition);
    destroy_sample(RESSOURCES.music_background);
    destroy_sample(RESSOURCES.music_background_lvl4);
    destroy_sample(RESSOURCES.music_lvl4_intro);
    destroy_sample(RESSOURCES.music_lvl4_outro);
    destroy_sample(RESSOURCES.ding);
    destroy_sample(RESSOURCES.fail_buzzer);
    destroy_sample(RESSOURCES.alarm);
    destroy_sample(RESSOURCES.sound_game_over);
    destroy_sample(RESSOURCES.sound_planche);
    destroy_sample(RESSOURCES.sound_poele);
    destroy_sample(RESSOURCES.sound_friteuse);
    destroy_sample(RESSOURCES.sound_four);

    /////////////////////////////////////////// FONTS ///////////////////////////////////////////

    destroy_font(RESSOURCES.font_big);
    destroy_font(RESSOURCES.font_small);
    destroy_font(RESSOURCES.font_egypt_big);
    destroy_font(RESSOURCES.font_egypt_small);

    /////////////////////////////////////////// SKINS ///////////////////////////////////////////

    destroy_bitmap(RESSOURCES.skin1);
    destroy_bitmap(RESSOURCES.skin2);
    destroy_bitmap(RESSOURCES.skin3);
    destroy_bitmap(RESSOURCES.skin4);

    /////////////////////////////////////////// IMAGES PARTIE ///////////////////////////////////////////

    // MEUBLES
    destroy_bitmap(RESSOURCES.parquet);
    destroy_bitmap(RESSOURCES.friteuse);
    destroy_bitmap(RESSOURCES.boite);
    destroy_bitmap(RESSOURCES.planche_a_couper);
    destroy_bitmap(RESSOURCES.plaque_de_cuisson);
    destroy_bitmap(RESSOURCES.table_grise);
    destroy_bitmap(RESSOURCES.four_ancien);
    destroy_bitmap(RESSOURCES.friteuse_ancienne);
    destroy_bitmap(RESSOURCES.pains_burger);
    destroy_bitmap(RESSOURCES.table_rendu);
    destroy_bitmap(RESSOURCES.table_rendu_bois);
    destroy_bitmap(RESSOURCES.poubelle);
    destroy_bitmap(RESSOURCES.poubelle_bois);
    destroy_bitmap(RESSOURCES.evier);
    destroy_bitmap(RESSOURCES.evier);

    destroy_bitmap(RESSOURCES.plan_de_travail);
    destroy_bitmap(RESSOURCES.sac_feves);
    destroy_bitmap(RESSOURCES.sac_ail);
    destroy_bitmap(RESSOURCES.sac_oignons);
    destroy_bitmap(RESSOURCES.sac_epices);
    destroy_bitmap(RESSOURCES.sac_semoule);
    destroy_bitmap(RESSOURCES.sac_farine);
    destroy_bitmap(RESSOURCES.sac_sucre);
    destroy_bitmap(RESSOURCES.pot_miel);
    destroy_bitmap(RESSOURCES.sable);
    destroy_bitmap(RESSOURCES.palmier);
    destroy_bitmap(RESSOURCES.fresque_egyptienne);

    // LEVEL4 EGYPT
    destroy_bitmap(RESSOURCES.Egypt1);
    destroy_bitmap(RESSOURCES.Egypt2);
    destroy_bitmap(RESSOURCES.parchemin);
    destroy_bitmap(RESSOURCES.hieroglyphes);
    destroy_bitmap(RESSOURCES.texte_intro_fr);
    destroy_bitmap(RESSOURCES.tempete_sable);

    // COMMANDES
    destroy_bitmap(RESSOURCES.commande_assiette_propre);
    destroy_bitmap(RESSOURCES.commande_assiette_sale);

    // OBJETS
    destroy_bitmap(RESSOURCES.assiette_propre);
    destroy_bitmap(RESSOURCES.poele);
    destroy_bitmap(RESSOURCES.bac_de_friteuse);
    destroy_bitmap(RESSOURCES.pain_burger_haut);
    destroy_bitmap(RESSOURCES.pain_burger_bas);
    destroy_bitmap(RESSOURCES.steak_cru);
    destroy_bitmap(RESSOURCES.steak_decoupe);
    destroy_bitmap(RESSOURCES.steak_cuit);
    destroy_bitmap(RESSOURCES.steak_crame);
    destroy_bitmap(RESSOURCES.fromage);
    destroy_bitmap(RESSOURCES.fromage_coupe);
    destroy_bitmap(RESSOURCES.salade);
    destroy_bitmap(RESSOURCES.salade_coupe);
    destroy_bitmap(RESSOURCES.tomates);
    destroy_bitmap(RESSOURCES.tomates_coupe);
    destroy_bitmap(RESSOURCES.patate_crue);
    destroy_bitmap(RESSOURCES.frites_crue);
    destroy_bitmap(RESSOURCES.frites_cuite);
    destroy_bitmap(RESSOURCES.frites_crame);
/*
    destroy_bitmap(RESSOURCES.poisson_crue);
    destroy_bitmap(RESSOURCES.poisson_coupe);
    destroy_bitmap(RESSOURCES.poisson_cuit);
    destroy_bitmap(RESSOURCES.poisson_crame);
*/
    destroy_bitmap(RESSOURCES.falafels_crus);
    destroy_bitmap(RESSOURCES.falafels_cuits);
    destroy_bitmap(RESSOURCES.falafels_crames);
    destroy_bitmap(RESSOURCES.feves);
    destroy_bitmap(RESSOURCES.feves_coupees);
    destroy_bitmap(RESSOURCES.oignon);
    destroy_bitmap(RESSOURCES.oignon_coupe);
    destroy_bitmap(RESSOURCES.ail);
    destroy_bitmap(RESSOURCES.ail_coupe);
    destroy_bitmap(RESSOURCES.epices);
    destroy_bitmap(RESSOURCES.basboussa_cru);
    destroy_bitmap(RESSOURCES.basboussa_cuit);
    destroy_bitmap(RESSOURCES.basboussa_crame);
    destroy_bitmap(RESSOURCES.semoule);
    destroy_bitmap(RESSOURCES.farine);
    destroy_bitmap(RESSOURCES.sucre);
    destroy_bitmap(RESSOURCES.miel);


    destroy_bitmap(RESSOURCES.commande_burger_viande);
    destroy_bitmap(RESSOURCES.commande_salade);
    destroy_bitmap(RESSOURCES.commande_frites);
    destroy_bitmap(RESSOURCES.commande_steak_frites);
    destroy_bitmap(RESSOURCES.commande_falafel);
    destroy_bitmap(RESSOURCES.commande_basboussa);


}