#include "config.h"

//////////////////////////////////////////////////////////
// Fonctions de dessin
//////////////////////////////////////////////////////////

void dessineCercleCase(BITMAP *buffer, int case_X, int case_Y, int couleur, int rayon, int delta) {
    circlefill(buffer,(int)(case_X*NB_PIXELS_CASE+NB_PIXELS_CASE/2),(int)(case_Y*NB_PIXELS_CASE+NB_PIXELS_CASE/2)+delta,rayon, couleur);
}

void dessineCercle(BITMAP *buffer, int x, int y, int couleur, int rayon) {
    circlefill(buffer,x,y,rayon,couleur);
}

void dessineJoueur(t_ressources RESSOURCES, BITMAP *ground, t_player* joueur) {
    int indiceTexture = choixTextureDeDeplacementDuSprite(joueur);
    int deltaX = 0;
    int deltaY = 0;

    switch (indiceTexture) {
        case 0 : { // 0 vers haut
            deltaX = 0;
            deltaY = 0;
            break;
        }
        case 1 : { // 1 vers gauche
            deltaX = -40;
            deltaY = 0;
            break;
        }
        case 2 : { // 2 vers bas
            deltaX = -10;
            deltaY = 0;
            break;
        }
        case 3 : { // 3 vers droite
            deltaX = -10;
            deltaY = 0;
            break;
        }

    }
    stretch_blit(joueur->imagejoueur,joueur->sprite,joueur->avancement_de_marche*64,512+(indiceTexture*64),64,64,0,0,158,158);

    // vers le haut : ojects puis joueur, sinon l'inverse
    if (indiceTexture==0) {
        dessineMatriceObjets(RESSOURCES, ground, joueur->objet, joueur->pos_milieux_X+deltaX,  joueur->pos_milieux_Y+deltaY,0,1,choixTextureDeDeplacementDuSprite(joueur));
        draw_sprite(ground,joueur->sprite,(int)joueur->pos_milieux_X-(joueur->sprite->w/2),(int)joueur->pos_milieux_Y-(joueur->sprite->h/2));
    }
    else {
        draw_sprite(ground,joueur->sprite,(int)joueur->pos_milieux_X-(joueur->sprite->w/2),(int)joueur->pos_milieux_Y-(joueur->sprite->h/2));
        dessineMatriceObjets(RESSOURCES, ground, joueur->objet, joueur->pos_milieux_X+deltaX,  joueur->pos_milieux_Y+deltaY,0,1,choixTextureDeDeplacementDuSprite(joueur));
    }
}

void dessineMarqueCaseInterraction(BITMAP *buffer, t_case matrice[NB_LIGNES][NB_COLONNES], int case_X, int case_Y, int bUniquementMeubleHaut) {
    int x = (int)(case_X*NB_PIXELS_CASE+NB_PIXELS_CASE/2);
    int y = (int)(case_Y*NB_PIXELS_CASE+NB_PIXELS_CASE/2);

    int largX = TAILLE_SELECTION;
    int largY = TAILLE_SELECTION;

    int deltaY = 0;
    int id_meuble = matrice[case_Y][case_X].id_meuble;
    int b_meubleHaut = bMeubleHaut(id_meuble);
    if (b_meubleHaut==1) deltaY = -NB_PIXELS_CASE/2;
    if ((bUniquementMeubleHaut==1) && (b_meubleHaut==0)) return;

    int h = TAILLE_SELECTION / 8;
    int g = TAILLE_SELECTION / 5;
    int c = couleurJaune();

    // coin haut gauche - barre horizontale
    rectfill(buffer,        x-largX/2,      y+deltaY-largY/2,          x-g,            y+deltaY-largY/2+h   ,c);
    // coin haut droit  - barre horizontale
    rectfill(buffer,        x+g,            y+deltaY-largY/2,          x+largX/2,      y+deltaY-largY/2+h   ,c);
    // coin haut gauche - barre verticale
    rectfill(buffer,        x-largX/2,      y+deltaY-largY/2,          x-largX/2+h,    y+deltaY-g           ,c);
    // coin haut droit  - barre verticale
    rectfill(buffer,        x+largX/2-h,    y+deltaY-largY/2,          x+largX/2,      y+deltaY-g           ,c);

    if (0) printf("b_meubleHaut=%d ",b_meubleHaut); // DEBUG
    int bDessineBas = 1;
    if ((b_meubleHaut==0) && (case_Y<NB_LIGNES-1)) {
        // si le croix doit etre au sol,
        // on regarde si la case de la ligne en dessous est un meuble haut,
        // auquel cas on ne dessine pas la partie basse de la croix
        int id_meubleDessous = matrice[case_Y+1][case_X].id_meuble;
        int meubleDessous_haut = bMeubleHaut(id_meubleDessous);
        if (meubleDessous_haut==1) bDessineBas = 0;

        if (0) printf("id_meubleDessous=%d\n",id_meubleDessous); // DEBUG
    }
    if (bDessineBas) {
        // coin bas gauche - barre horizontale
        rectfill(buffer, x - largX / 2, y + deltaY + largY / 2 - h, x - g, y + deltaY + largY / 2, c);
        // coin bas droit  - barre horizontale
        rectfill(buffer, x + g, y + deltaY + largY / 2 - h, x + largX / 2, y + deltaY + largY / 2, c);
        // coin bas gauche - barre verticale
        rectfill(buffer, x - largX / 2, y + deltaY + g, x - largX / 2 + h, y + deltaY + largY / 2, c);
        // coin bas droit  - barre verticale
        rectfill(buffer, x + largX / 2 - h, y + deltaY + g, x + largX / 2, y + deltaY + largY / 2, c);
    }
}

//////////////////////////////////////////////////////////
// Nom du sous-programme : lancerNiveau
// Rôle : boucle de jeu
// Etapes :
//    - VERIFICATION MODE PAUSE
//    - VERIFICATION VICTOIRE ET DEFAITE
//    - MISE A JOUR TEMPS DE JEU
//    - MISE A JOUR DU TICK
//    - DEPLACEMENT
//    - COLLISIONS
//    - MISE A JOUR
//    - AFFICHAGE
//    - TEMPS DE PAUSE
//////////////////////////////////////////////////////////

int lancerNiveau(t_ressources RESSOURCES, BITMAP *buffer, t_partie *partie, File_commandes* file_commandes, int state[TAM_MAX], int state2[TAM_MAX], int *i, int *j, int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]) {

    BITMAP* foreground_back  = create_bitmap(SCREEN_W,SCREEN_H);
    BITMAP* foreground_front = create_bitmap(SCREEN_W,SCREEN_H);

    ///////////////////////////////////////// INITIALISATION DU NIVEAU /////////////////////////////////////////
    /// GESTION DU TICK
    clock_t heureActuelleEnMs = maintenantEnMs();
    clock_t heureDernierTickEnMs = maintenantEnMs();
    int bNouveauTick = 0;
    int nombreTotalDeTick = 0;
    double param_tempete = 0;
    short coeff = 1;

    ///LEVEL 4 ONLY
    if (partie->niveau_select == 4) {
        if (MODE_DEV==0) Intro_level4(RESSOURCES, buffer, partie, state, state2);
        partie->lvl4_succes = 1;
    }
    if (partie->niveau_select == 5) {
        if (MODE_DEV==1) printf("niveau personnel");
    }

    if (partie->music.activated==1){
        if (partie->niveau_select != 4) {
            play_sample(RESSOURCES.music_background, 255, 128, 1000, TRUE);
        }
        else {
            play_sample(RESSOURCES.music_background_lvl4, 255, 128, 1000, TRUE);
        }
    }
    /// MISE à 0 DU SCORE
    file_commandes->score = 0;

    /// GESTION DU TEMPS
    partie->time.timer = TIMER_PARTIE;
    partie->time.temps_pro_commande = 0;
    partie->time.temps = maintenantEnMs();
    partie->time.temps_prec_commande = 0;
    partie->time.temps_seconde = maintenantEnMs();
    partie->time.decalage = maintenantEnSec();
    partie->time.seconde = 0;
    partie->time.seconde_prec = partie->time.seconde;
    partie->time.decalage_pause = 0;
    partie->time.pause = 0;
    partie->time.temps_pause_ON = 0;
    partie->time.duree_totale_pause = 0;

    /// GESTION DES OBJETS
    initialisationPermissionsObjets(&partie->permissionsObjets);
    initialiserObjetMeublesMatrice(partie->matrice);
    partie->nombre_assiettes_restante = NOMBRE_ASSIETTES_MAX;
    partie->music.alarm_playing = 0;
    partie->music.alarm_played = 0;
    partie->music.alarm_must_play = 0;
    partie->music.nbr_alarm_playing = 0;
    partie->music.nbr_pan_playing = 0;
    partie->music.nbr_fryer_playing = 0;
    partie->music.nbr_oven_playing = 0;


    ///////////////////////////////////////// BOUCLE /////////////////////////////////////////

    while (1) {

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // PREPARATON AFFICHAGE
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ///////// Clear du buffer /////////
        clear_bitmap(buffer);

        ///////// Clear des plans transparents /////////
        clear_to_color(foreground_back,  couleurMagenta());
        clear_to_color(foreground_front, couleurMagenta());

        ///////// Calcul des déplacement et du pointeur interraction de chaques personnages /////////
        mouvementCollisionEtActionPersonnages(foreground_front, &partie->joueur1, 0, partie->matrice);
        mouvementCollisionEtActionPersonnages(foreground_front, &partie->joueur2, 1, partie->matrice);
        // DEBUG : printf("X:%f Y:%f\n ActionX:%d ActionY:%d\n CaseX:%d CaseY:%d\n", partie->joueur1.pos_milieux_X, partie->joueur1.pos_milieux_Y, partie->joueur1.pos_interaction_X, partie->joueur1.pos_interaction_Y, partie->joueur1.pos_case_X, partie->joueur1.pos_case_Y);

        ///////// ON MET A JOUR LA MANETTE /////////
        if (partie->b_controller) {
            input(state,state2);
        }

        ////// Calcul du tick //////
        heureActuelleEnMs = maintenantEnMs();
        bNouveauTick = 0;

        // On regarde si on doit actualiser le tick
        if(heureActuelleEnMs > (heureDernierTickEnMs + DUREE_TICK_EN_MS)) {
            heureDernierTickEnMs = heureActuelleEnMs;
            bNouveauTick = 1;
            nombreTotalDeTick++;
        }

        //////////// GESTION OBJETS ////////////

        if (bNouveauTick == 1) {

            // afficher objet joueur 2
            if (0) { // DEBUG
                afficherObjetMatriceConsole(partie->matrice);
                afficherObjetJoueurConsole(partie->joueur1, 1);
                afficherObjetJoueurConsole(partie->joueur2, 2);
            }

            if(0) { // DEBUG
                printf("\n\nDEBUG\n");
                printf("Time : %d\n",nombreTotalDeTick);

                printf("Position milieux X   : %f\n", partie->joueur1.pos_milieux_X);
                printf("Position milieux Y   : %f\n", partie->joueur1.pos_milieux_Y);
                printf("Pos case joueur X    : %d\n", partie->joueur1.pos_case_X);
                printf("Pos case joueur Y    : %d\n", partie->joueur1.pos_case_Y);
                printf("Direction Angle      : %d\n", partie->joueur1.direction_angle);
                printf("id_meuble case       : %d\n", partie->matrice[partie->joueur1.pos_case_Y][partie->joueur1.pos_case_X].id_meuble);
                printf("case infranchissable : %d\n", partie->matrice[partie->joueur1.pos_case_Y][partie->joueur1.pos_case_X].b_infranchissable);
                printf("\n");

                printf("Pos case interaction X : %d\n", partie->joueur1.pos_interaction_case_X);
                printf("Pos case interaction Y : %d\n", partie->joueur1.pos_interaction_case_Y);
                printf("id_meuble case : %d\n", partie->matrice[partie->joueur1.pos_interaction_case_Y][partie->joueur1.pos_interaction_case_X].id_meuble);
            }

        }

        ////// Interraction entre les objets

        if (bNouveauTick == 1) {
            actionTempsMeublesSpecifique(RESSOURCES, partie);
        }

        // Action joueur 1
        if (key[TOUCHE_INTERRACTION_JOUEUR1] || state[BUTTON_ROND]==1) {
            toucheInterractionJoueur(RESSOURCES, &partie->matrice[partie->joueur1.pos_interaction_case_Y][partie->joueur1.pos_interaction_case_X], &partie->joueur1, partie, file_commandes, recettes);
            while (key[TOUCHE_INTERRACTION_JOUEUR1] || (state[BUTTON_ROND]==1)){ // Clear touche
                input(state,state2);
            }
        }
        if (key[TOUCHE_ACTION_JOUEUR1] || state[BUTTON_X]==1) {
            toucheActionJoueur(RESSOURCES, &partie->matrice[partie->joueur1.pos_interaction_case_Y][partie->joueur1.pos_interaction_case_X], &partie->joueur1, partie);
            while (key[TOUCHE_ACTION_JOUEUR1] || (state[BUTTON_X]==1)){ // Clear touche
                input(state,state2);
            }
        }

        // Action joueur 2
        if (key[TOUCHE_INTERRACTION_JOUEUR2] || (state2[BUTTON_ROND]==1)) {
            toucheInterractionJoueur(RESSOURCES, &partie->matrice[partie->joueur2.pos_interaction_case_Y][partie->joueur2.pos_interaction_case_X], &partie->joueur2, partie, file_commandes, recettes);
            while (key[TOUCHE_INTERRACTION_JOUEUR2] || (state2[BUTTON_ROND]==1)){ // Clear touche
                input(state,state2);
            }
        }
        if (key[TOUCHE_ACTION_JOUEUR2] || (state2[BUTTON_X]==1)) {
            toucheActionJoueur(RESSOURCES, &partie->matrice[partie->joueur2.pos_interaction_case_Y][partie->joueur2.pos_interaction_case_X], &partie->joueur2, partie);
            while (key[TOUCHE_ACTION_JOUEUR2] || (state2[BUTTON_X]==1)){ // Clear touche
                input(state,state2);
            }
        }
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


        //////////// AFFICHAGE DES CASES D'INTERRACTION /////////

        if (0 && (MODE_DEV==1)) {
            dessineCercleCase(buffer, partie->joueur1.pos_case_X, partie->joueur1.pos_case_Y, couleurRouge(),20,0);
            dessineCercleCase(buffer, partie->joueur2.pos_case_X, partie->joueur2.pos_case_Y, couleurRouge(),20,0);
        }
        dessineMarqueCaseInterraction(foreground_back, partie->matrice, partie->joueur1.pos_interaction_case_X, partie->joueur1.pos_interaction_case_Y,0);
        dessineMarqueCaseInterraction(foreground_back, partie->matrice, partie->joueur2.pos_interaction_case_X, partie->joueur2.pos_interaction_case_Y,0);

        ///////// AFFICHAGE DES OBJETS SUR LE PLATEAU AU SOL /////////
        dessineObjetsPlateauSurSol(RESSOURCES, foreground_back, partie->matrice);

        ///////// AFFICHAGE DES 2 PERSONNAGES /////////
        if (partie->joueur2.pos_milieux_Y < partie->joueur1.pos_milieux_Y) {
            dessineJoueur(RESSOURCES, foreground_back, &partie->joueur2);
            dessineJoueur(RESSOURCES, foreground_back, &partie->joueur1);
        }
        else {
            dessineJoueur(RESSOURCES, foreground_back, &partie->joueur1);
            dessineJoueur(RESSOURCES, foreground_back, &partie->joueur2);
        }

        ///////// AFFICHAGE DES OBJETS SUR LE PLATEAU EN HAUT /////////
        dessineObjetsPlateauEnHauteur(RESSOURCES, foreground_front, partie->matrice);


        ///////// DEPLACEMENT PERSONNAGE 1 /////////
        (*i)+=1;
        if(*i>15){
            partie->joueur1.avancement_de_marche=(partie->joueur1.avancement_de_marche+1)%9;
            *i=0;
        }

        ///////// DEPLACEMENT PERSONNAGE 2 /////////
        (*j)+=1;
        if(*j>15){
            partie->joueur2.avancement_de_marche=(partie->joueur2.avancement_de_marche+1)%9;
            *j=0;
        }

        //////////// AFFICHAGE DES PSEUDOS /////////
        if(partie->joueur2.pos_milieux_Y<partie->joueur1.pos_milieux_Y){
            afficher_pseudo(&partie->joueur2,partie->backgrounds,foreground_front);
            afficher_pseudo(&partie->joueur1,partie->backgrounds,foreground_front);
        }
        else {
            afficher_pseudo(&partie->joueur1,partie->backgrounds,foreground_front);
            afficher_pseudo(&partie->joueur2,partie->backgrounds,foreground_front);
        }

        //////////// AFFICHAGE DES CASES D'INTERRACTION /////////

        // redessinne que pour les meubles haut => niveau le plus haut
        dessineMarqueCaseInterraction(foreground_front, partie->matrice, partie->joueur1.pos_interaction_case_X, partie->joueur1.pos_interaction_case_Y,1);
        dessineMarqueCaseInterraction(foreground_front, partie->matrice, partie->joueur2.pos_interaction_case_X, partie->joueur2.pos_interaction_case_Y,1);

        //////////// AFFICHAGE BARRE D'AVANCEMENT /////////
        afficherStatuObjets(foreground_front, partie);

        //////////// AFFICHAGE FINAL : ON APPLATI TOUTES LES COUCHES /////////

        masked_blit(partie->backgrounds.background_back, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        masked_blit(foreground_back, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        masked_blit(partie->backgrounds.background_front, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        masked_blit(foreground_front, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);



        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // AFFICHAGE PAR DESSIN LE PLATEAU, ne plus utiliser que buffer
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        //////////// GESTION DES COMMANDES /////////
        lancer_commandes(file_commandes, RESSOURCES, buffer, partie);
        if (partie->niveau_select != 4) {
            textprintf_ex(buffer, RESSOURCES.font_big, SCREEN_W-170, 40, makecol(0, 0, 0), -1, "%d", partie->time.timer); //affiche le timer
        }
        else {
            textprintf_ex(buffer, RESSOURCES.font_egypt_big, SCREEN_W-170, 40, makecol(0, 0, 0), -1, "%d", partie->time.timer); //affiche le timer
        }

        afficher_score(file_commandes, RESSOURCES, partie, buffer);

        /////////// AFFICHAGE TEMPETE DE SABLE NIVEAU 4 ONLY ///////////
        if (partie->time.timer == 140 || partie->time.timer == 100 || partie->time.timer == 60 || partie->time.timer == 20) { //Déclenchement de l'event si timer == 100 ou si timer == 60 ou si timer == 20
            if (partie->niveau_select == 4) {
                partie->tempete_active = 1;
            }
        }
        if (partie->tempete_active == 1) {
            Tempete_sable(RESSOURCES, buffer, param_tempete);
            param_tempete += (0.05*coeff);
            if (param_tempete >= 1) {
                coeff *= -1;
            }
            else if (param_tempete <= 0) {
                param_tempete = 0;
                coeff *= -1;
                partie->tempete_active = 0;
            }
        }

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // AFFICHAGE FINAL SUR L ECRAN
        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        blit(buffer,screen,0, 0, 0, 0, SCREEN_W, SCREEN_H);

        ////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        if (key[KEY_PRTSCR]) {
            Screenshot(buffer);
        }

        int bQuit = 0;
        if (menu_pause_quitter (RESSOURCES,partie,buffer, file_commandes, state,state2) == 1 ) {
            // on quitte la partie en cours
            bQuit = 1;
        }

        if (fin_temps(partie,RESSOURCES,file_commandes,buffer,state,state2) == 1){
            bQuit = 1;
        }

        if (bQuit == 1) {
            destroy_bitmap(partie->backgrounds.background_back);
            destroy_bitmap(partie->backgrounds.background_front);
            destroy_bitmap(foreground_back);
            destroy_bitmap(foreground_front);
            return 1;
        }
    }
}


////////////////////////////////////////////////////////// [1 -> 2]
// Nom du sous-programme : mouvementCollisionEtActionPersonnages
// Rôle : Gestion des déplacements des joueurs, des collisions et des pointeurs d'actions.
// Sous-programmes appelés :
//    - calculPointeurActionPersonnage
//    - calculHitBox
//////////////////////////////////////////////////////////



void mouvementCollisionEtActionPersonnages(BITMAP *buffer, t_player* joueur, int iJoy, t_case matrice[NB_LIGNES][NB_COLONNES]){

    int kUp    = KEY_UP;
    int kDown  = KEY_DOWN;
    int kLeft  = KEY_LEFT;
    int kRight = KEY_RIGHT;

    if (iJoy==1) { //joy1 = joueur2
        kUp    = KEY_W;
        kDown  = KEY_S;
        kLeft  = KEY_A;
        kRight = KEY_D;
    }

    ///////////////////////////// JOUEUR 1 /////////////////////////////
    // Deplacement du joueur en fonction de l'action précédente et on calcule la direction
    double previousPosX = joueur->pos_milieux_X;
    double previousPosY = joueur->pos_milieux_Y;

    // On regarde si le joueur appuie sur une touche clavier ou manette
    if((key[kUp]||(joy[iJoy].stick[0].axis[1].pos)<0) && joueur->pos_milieux_Y+DELTA_VERS_PIED > LIMITE_Y_MIN){
        if(key[kUp]){
            joueur->pos_milieux_Y-=1*VITESSE_MOUVEMENT;
        }
        else {
            joueur->pos_milieux_Y+=(joy[iJoy].stick[0].axis[1].pos/128.0)*VITESSE_MOUVEMENT;
        }
    }
    if((key[kDown]||(joy[iJoy].stick[0].axis[1].pos)>0) && joueur->pos_milieux_Y+DELTA_VERS_PIED < LIMITE_Y_MAX){
        if(key[kDown]){
            joueur->pos_milieux_Y+=1*VITESSE_MOUVEMENT;
        }
        else {
            joueur->pos_milieux_Y+=(joy[iJoy].stick[0].axis[1].pos/128.0)*VITESSE_MOUVEMENT;
        }
    }
    if((key[kLeft]||(joy[iJoy].stick[0].axis[0].pos)<0) && joueur->pos_milieux_X > LIMITE_X_MIN){
        if(key[kLeft]){
            joueur->pos_milieux_X-=1*VITESSE_MOUVEMENT;
        }
        else {
            joueur->pos_milieux_X+=(joy[iJoy].stick[0].axis[0].pos/128.0)*VITESSE_MOUVEMENT;
        }
    }
    if((key[kRight]||(joy[iJoy].stick[0].axis[0].pos)>0) && joueur->pos_milieux_X < LIMITE_X_MAX){
        if(key[kRight]){
            joueur->pos_milieux_X+=1*VITESSE_MOUVEMENT;
        }
        else {
            joueur->pos_milieux_X+=(joy[iJoy].stick[0].axis[0].pos/128.0)*VITESSE_MOUVEMENT;
        }
    }

    // sous programme de restriction mouvement
    // condition d' 'annulation = plan de travail etc joueur->pos_milieux_Y= previousPosY
    // si pointeur collision (taille du bonhomme)= table

    //ATTENTION plus rapide en diago avec les fleches car 1+1 et a la manette 0.5 +0.5 !
    // Vérifier si le mouvement est diagonal

    // On regarde si le joueur a appuyé sur une touche manette
    if(joy[iJoy].stick[0].axis[0].pos ==0 && joy[iJoy].stick[0].axis[1].pos ==0){
        if (joueur->pos_milieux_Y - previousPosY != 0 && joueur->pos_milieux_X - previousPosX != 0) {
            joueur->pos_milieux_Y = previousPosY + (int)((joueur->pos_milieux_Y - previousPosY)) * 0.7; // coeff de la manette
            joueur->pos_milieux_X = previousPosX + (int)((joueur->pos_milieux_X - previousPosX)) * 0.7;
        }
    }

    // On regarde si le joueur a changé de direction et on calcule sa position en fonction
    if (previousPosY != joueur->pos_milieux_Y || previousPosX != joueur->pos_milieux_X) {
        double deltaY = joueur->pos_milieux_Y - previousPosY;
        double deltaX = joueur->pos_milieux_X - previousPosX;
        // fonction de maths.h permettant le calcul d'un angle (en radians) entre les deux vecteurs et pas division par 0 !
        double angle = atan2(deltaY, deltaX);
        joueur->direction_angle =(int)(angle * 180.0 / M_PI)+90;
    }
    else {
        joueur->avancement_de_marche=0;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    // On le rayon de collision du joueur pour après

    calculHitBox(buffer, joueur,&previousPosY,&previousPosX,matrice);

    /////////////////////////////////////////////////////////////////////////////////////////


    joueur->pos_case_X = (int)(joueur->pos_milieux_X/NB_PIXELS_CASE);
    joueur->pos_case_Y = (int)((joueur->pos_milieux_Y+DELTA_VERS_PIED)/NB_PIXELS_CASE);

    /////////////////////////////////////////////////////////////////////////////////////////
    // calcul Pointeur Action Personnage

    int dX = 0;
    int dY = 0;
    switch (joueur->direction_angle) {
        case -40 ...  40 : { dX= 0; dY=-1; break; }
        case  41 ... 140 : { dX= 1; dY= 0; break; }
        case 141 ... 224 : { dX= 0; dY= 1; break; }
        case 225 ... 270 : { dX=-1; dY= 0; break; }
        case -90 ... -41 : { dX=-1; dY= 0; break; }
    }

    joueur->pos_interaction_case_X = (int)joueur->pos_case_X+dX;
    joueur->pos_interaction_case_Y = (int)joueur->pos_case_Y+dY;

    if ( joueur->pos_interaction_case_X < 0 )                joueur->pos_interaction_case_X = 0;
    if ( joueur->pos_interaction_case_X > (NB_COLONNES-1) )  joueur->pos_interaction_case_X = (NB_COLONNES-1);
    if ( joueur->pos_interaction_case_Y < 0 )                joueur->pos_interaction_case_Y = 0;
    if ( joueur->pos_interaction_case_Y > (NB_LIGNES-1) )    joueur->pos_interaction_case_Y = (NB_LIGNES-1);
}


////////////////////////////////////////////////////////// [2]
// Nom du sous-programme : calculHitBox
// Rôle : Gestion des collisions
//////////////////////////////////////////////////////////
void calculHitBox(BITMAP *buffer, t_player *joueur,double* previousPosY,double* previousPosX , t_case matrice[NB_LIGNES][NB_COLONNES]){ //pris sur un salon sur l analyse des hit box et la creation des cercle methode Bresenham

    double deltaY = joueur->pos_milieux_Y - *previousPosY;
    double deltaX = joueur->pos_milieux_X - *previousPosX;

    int x0 = (int) joueur->pos_milieux_X;
    //int y0 = (int) joueur->pos_milieux_Y + 10;
    int y0 = (int) (joueur->pos_milieux_Y+DELTA_VERS_PIED-7);

    int x = (NB_PIXELS_CASE - 7) / 2;
    int y = 0;
    int err = 0;
    // 1 = obstacles structure type obj = 2 6 etc table etc et blocage = 1 ou 0
    while (x >= y) {
        // a 100 détailler pour faire des slides en désynchronisant les coordonnées x et y

        int p1y = y0+x;
        int p1x = x0+y;
        int p2y = y0+x;
        int p2x = x0-y;
        int p3y = y0-x;
        int p3x = x0-y;
        int p4y = y0-x;
        int p4x = x0+y;
        if (INTERRACTION_HITBOX_CERCLE) {
            dessineCercle(buffer, p1x, p1y, couleurRouge(), 1);     //bas droite
            dessineCercle(buffer, p2x, p2y, couleurVert(), 1);      //bas gauche
            dessineCercle(buffer, p3x, p3y, couleurBleu(), 1);      //haut gauche
            dessineCercle(buffer, p4x, p4y, couleurJaune(), 1);     //haut droite
        }
        //restriction y
        int i1 = p1y/NB_PIXELS_CASE;
        int j1 = p1x/NB_PIXELS_CASE;
        int i2 = p2y/NB_PIXELS_CASE;
        int j2 = p2x/NB_PIXELS_CASE;
        int i3 = p3y/NB_PIXELS_CASE;
        int j3 = p3x/NB_PIXELS_CASE;
        int i4 = p4y/NB_PIXELS_CASE;
        int j4 = p4x/NB_PIXELS_CASE;
        if (INTERRACTION_HITBOX_CERCLE_CASE) {
            dessineCercleCase(buffer, j1, i1, couleurRouge(), 20, -10);
            dessineCercleCase(buffer, j2, i2, couleurVert(), 20, -10);
            dessineCercleCase(buffer, j3, i3, couleurBleu(), 20, -10);
            dessineCercleCase(buffer, j4, i4, couleurJaune(), 20, -10);
        }

        if (deltaY<0) {
            // on ne regarde que les blocage en haut
            if (matrice[i3][j3].b_infranchissable == 1) joueur->pos_milieux_Y = *previousPosY;       // Bleu(   haut gauche
            if (matrice[i4][j4].b_infranchissable == 1) joueur->pos_milieux_Y = *previousPosY;       // Jaune   haut droite
        }
        else {
            // on ne regarde que les blocage en bas
            if (matrice[i1][j1].b_infranchissable == 1) joueur->pos_milieux_Y = *previousPosY;       // Rouge   bas droite
            if (matrice[i2][j2].b_infranchissable == 1) joueur->pos_milieux_Y = *previousPosY;       // Vert    bas gauche
        }

        int p5y = y0+y;
        int p5x = x0+x;
        int p6y = y0+y;
        int p6x = x0-x;
        int p7y = y0-y;
        int p7x = x0-x;
        int p8y = y0-y;
        int p8x = x0+x;
        if (INTERRACTION_HITBOX_CERCLE) {
            dessineCercle(buffer, p5x, p5y, couleurMarron(), 1);        //droite bas
            dessineCercle(buffer, p6x, p6y, couleurGrisMoyen(), 1);     //gauche bas
            dessineCercle(buffer, p7x, p7y, couleurOrange(), 1);        //gauche haut
            dessineCercle(buffer, p8x, p8y, couleurNoir(), 1);          //droite haut
        }
        //restriction y
        int i5 = p5y/NB_PIXELS_CASE;
        int j5 = p5x/NB_PIXELS_CASE;
        int i6 = p6y/NB_PIXELS_CASE;
        int j6 = p6x/NB_PIXELS_CASE;
        int i7 = p7y/NB_PIXELS_CASE;
        int j7 = p7x/NB_PIXELS_CASE;
        int i8 = p8y/NB_PIXELS_CASE;
        int j8 = p8x/NB_PIXELS_CASE;
        if (INTERRACTION_HITBOX_CERCLE_CASE) {
            dessineCercleCase(buffer, j5, i5, couleurMarron(), 20, 10);
            dessineCercleCase(buffer, j6, i6, couleurGrisMoyen(), 20, 10);
            dessineCercleCase(buffer, j7, i7, couleurOrange(), 20, 10);
            dessineCercleCase(buffer, j8, i8, couleurNoir(), 20, 10);
        }
        // test droite et gauche

        if (deltaX<0) {
            // on ne regarde que les blocage à gauche
            if (matrice[i6][j6].b_infranchissable == 1) joueur->pos_milieux_X = *previousPosX;   // GrisMoyen   gauche bas
            if (matrice[i7][j7].b_infranchissable == 1) joueur->pos_milieux_X = *previousPosX;   // Orange      gauche haut
        }
        else {
            // on ne regarde que les blocage à droite
            if (matrice[i5][j5].b_infranchissable == 1) joueur->pos_milieux_X = *previousPosX;   // Marron      droite bas
            if (matrice[i8][j8].b_infranchissable == 1) joueur->pos_milieux_X = *previousPosX;   // Noir(       droite haut
        }

        if (err <= 0) {
            y += 1;
            err += 2 * y + 1;
        }
        if (err > 0) {
            x -= 1;
            err -= 2 * x + 1;
        }
    }
}




///-----------------------------------------------------------------------------------///
///                             FONTIONS UTILITAIRES                                 ///
///-----------------------------------------------------------------------------------///

//////////////////////////////////////////////////////////
// Nom du sous-programme : menu_pause_quitter
// Rôle : Menu pause in-game
//////////////////////////////////////////////////////////
int menu_pause_quitter(t_ressources RESSOURCES, t_partie *partie, BITMAP *buffer, File_commandes* file_commandes, int state[TAM_MAX], int state2[TAM_MAX]) {
    if (key[KEY_ESC] || state[GACHETTE_UP_L] || state2[GACHETTE_UP_L] ) {
        partie->time.pause = 1;

        BITMAP *fond_et_joueur = create_bitmap(SCREEN_W, SCREEN_H);
        blit(buffer, fond_et_joueur, 0, 0, 0, 0, SCREEN_W, SCREEN_H);

        BITMAP * buffer2 = create_bitmap(SCREEN_W,SCREEN_H);
        for (int j =0; j <370/2 ; j++) {
            clear_bitmap(buffer2);
            blit(fond_et_joueur,buffer2,0,0,0,0,SCREEN_W,SCREEN_H);
            masked_blit(RESSOURCES.fondmenu,buffer2,SCREEN_W-370,0,SCREEN_W-j*2,0,j*2,SCREEN_H);
            blit(buffer2,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
        short done=0;
        short mouse_pressed2=0;

        while(!done){
            lancer_commandes(file_commandes, RESSOURCES, buffer, partie);

            clear_bitmap(buffer2);
            blit(fond_et_joueur,buffer2,0,0,0,0,SCREEN_W,SCREEN_H);
            masked_blit(RESSOURCES.fondmenu,buffer2,SCREEN_W-370,0,SCREEN_W-370,0,370,SCREEN_H);

            //start retour en jeux
            if(bouton(buffer2, SCREEN_W -300, 200, 200, 100, RESSOURCES.start_button,RESSOURCES.start_button_hover,RESSOURCES.start_button_pressed,state[BUTTON_X],state2[BUTTON_X])){
                partie->time.pause = 0;
                return 0;
            }
            //help pour revoir les regles
            if(bouton(buffer2, SCREEN_W -300, 300, 200, 100, RESSOURCES.help_button,RESSOURCES.help_button_hover,RESSOURCES.help_button_pressed,state[BUTTON_X],state2[BUTTON_X])){
                clear_bitmap(screen);
                blit(fond_et_joueur,screen,0,0,0,0,SCREEN_W,SCREEN_H);
                masked_blit(RESSOURCES.fondmenu,screen,SCREEN_W-370,0,SCREEN_W-370,0,370,SCREEN_H);

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

                while (!key[KEY_ENTER] && state[BUTTON_ROND]!=1 && state2[BUTTON_ROND]!=1){
                    input(state,state2); //manette deconnecteé ca marche
                }
            }
            //bouton musique
            if (partie->niveau_select != 4) {
                boutonMusiqueOnOff(RESSOURCES, RESSOURCES.music_background, 1000, buffer2, &mouse_pressed2,&partie->music.activated, state,state2);
            }
            else {
                boutonMusiqueOnOff(RESSOURCES, RESSOURCES.music_background_lvl4, 1000, buffer2, &mouse_pressed2,&partie->music.activated, state,state2);
            }
            //bouton pour activer la manette en pleine partie
            boutonManetteOnOff(RESSOURCES, buffer2, &mouse_pressed2, &partie->b_controller, state,state2);
            //bouton exit retour au menu
            done = bouton(buffer2, SCREEN_W -300, 600, 200, 100, RESSOURCES.exit_button,RESSOURCES.exit_button_hover,RESSOURCES.exit_button_pressed,state[BUTTON_X],state2[BUTTON_X]);

            draw_sprite(buffer2, RESSOURCES.mouse, mouse_x, mouse_y);
            blit(buffer2,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        }
        partie->time.pause = 0;
        supprimer_tous_maillons(file_commandes); // vide la file dynamique de toutes les commandes stockées

        stop_sample(RESSOURCES.ding);
        stop_sample(RESSOURCES.fail_buzzer);
        stop_sample(RESSOURCES.alarm);
        stop_sample(RESSOURCES.sound_planche);
        stop_sample(RESSOURCES.sound_poele);
        stop_sample(RESSOURCES.sound_friteuse);
        stop_sample(RESSOURCES.sound_four);

        clearESC(state,state2);
        while (mouse_b&1 || state[BUTTON_X] || state2[BUTTON_X]){
            input(state,state2);
        }
        if(partie->music.activated==1){
            stop_sample(RESSOURCES.music_background);
            stop_sample(RESSOURCES.music_background_lvl4);
            play_sample(RESSOURCES.musicIntro, 255, 128, 1600, TRUE);
        }
        destroy_bitmap(fond_et_joueur);
        destroy_bitmap(buffer2);
        return 1;
    }

    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : choixTextureDeDeplacementDuSprite
// Rôle : selectionne la bonne texture du sprite en fonction de la direction du joueur
////////////////////////////////////////////////////////////////////////////////

int choixTextureDeDeplacementDuSprite(t_player* joueur){
    switch (joueur->direction_angle){
        case -40 ...  40 :{ return 0; }
        case  41 ... 140 :{ return 3; }
        case 141 ... 224 :{ return 2; }
        case 225 ... 270 :{ return 1; }
        case -90 ... -41 :{ return 1; }
    }
    return 0;
}


////////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : coloration_selection_personnage
// Rôle : Cree un rectangle gris de fond pour le pseudo
////////////////////////////////////////////////////////////////////////////////


void coloration_selection_personnage(BITMAP *buffer,BITMAP *launcher, short V1, short V2) {
    for (int i = SPRITE_X-5; i < SPRITE_X+62; ++i) {
        for (int j = SPRITE_Y+V1; j < SPRITE_Y+V2; ++j) {
            int pixelfond = getpixel(buffer, i, j);
            if (getpixel(launcher, i, j) != pixelfond) {
                int r = getr(pixelfond) - ASSOMBRISSEMENT;
                if (r < 0) r = 0;
                int g = getg(pixelfond) - ASSOMBRISSEMENT;
                if (g < 0) g = 0;
                int b = getb(pixelfond) - ASSOMBRISSEMENT;
                if (b < 0) b = 0;
                putpixel(buffer, i, j, makecol(r, g, b));
            }
        }
    }
}


////////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : afficher_pseudo
// Rôle : Affiche le pseudo du joueur sur l'ecran au dessus du personnage
////////////////////////////////////////////////////////////////////////////////

void afficher_pseudo (t_player* joueur1,t_backgrounds backgrounds,BITMAP* buffer){
    // Rectangle transparent sous le pseudo
    // Fonction: draw_trans_sprite ou set_trans_blender makeacol() etc
    // rect(buffer,(int)joueur1->pos_milieux_X -(joueur1->taille_du_nom*8/2)-2,(int) joueur1->pos_milieux_Y - (joueur1->sprite->h / 2) +20,(int)joueur1->pos_milieux_X +(joueur1->taille_du_nom*8/2)-2,(int) joueur1->pos_milieux_Y - (joueur1->sprite->h / 2) + 11-5,makecol(0,0,0));
    for (int i = 0; i < 15; ++i) {
        for (int j =(int)joueur1->pos_milieux_X-(joueur1->taille_du_nom*8/2)-2 ; j < (int)joueur1->pos_milieux_X+(joueur1->taille_du_nom*8/2)+2 ; ++j) {
            int pixelfond = getpixel(backgrounds.background_back,j, (int) joueur1->pos_milieux_Y -(joueur1->sprite->h / 2)+4 +i);
            int r= getr(pixelfond) - ASSOMBRISSEMENT;
            if(r<0) r=0;
            int g= getg(pixelfond) - ASSOMBRISSEMENT;
            if(g<0) g=0;
            int b= getb(pixelfond) - ASSOMBRISSEMENT;
            if(b<0) b=0;
            putpixel(buffer,j,(int) joueur1->pos_milieux_Y - (joueur1->sprite->h / 2)+4 +i,makecol(r,g,b));
        }
    }
    textout_centre_ex(buffer, font, joueur1->username, (int) joueur1->pos_milieux_X,(int) joueur1->pos_milieux_Y - (joueur1->sprite->h / 2) + 10, makecol(255, 255, 255), -1);
}

void Intro_level4(t_ressources RESSOURCES, BITMAP *buffer, t_partie *partie, int state[TAM_MAX], int state2[TAM_MAX]) {
    BITMAP* fond_noir = create_bitmap(SCREEN_W, SCREEN_H);
    clear_bitmap(fond_noir);
    blit(fond_noir, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    afficherScreen(buffer);
    if (partie->music.activated) {
        play_sample(RESSOURCES.music_lvl4_intro, 255, 128, 1000, FALSE);
    }
    rest(100);

    //1ère image de fond avec fondue sur fond noir
    double param = 0;
    do {
        for (int i=0; i < SCREEN_W; i++) {
            for (int j=0; j < SCREEN_H; j++) {
                fondueImage(param, fond_noir, RESSOURCES.Egypt1, buffer, 0, 0, i, j);
            }
        }
        afficherScreen(buffer);
        param += 0.025;
    }
    while (param < 1);
    rest(2000);

    //2e image de fond avec fondue sur la 1ere image
    param = 0;
    do {
        for (int i=0; i < SCREEN_W; i++) {
            for (int j=0; j < SCREEN_H; j++) {
                fondueImage(param, RESSOURCES.Egypt1, RESSOURCES.Egypt2, buffer, 0, 0, i, j);
            }
        }
        afficherScreen(buffer);
        param += 0.025;
    }
    while (param < 1);
    rest(2000);

    //parchemin + hieroglyphes avec fondue sur la 2e image
    param = 0;
    do {
        for (int i=0; i < RESSOURCES.parchemin->w; i++) {
            for (int j=0; j < RESSOURCES.parchemin->h; j++) {
                fondueImage(param, RESSOURCES.Egypt2, RESSOURCES.parchemin, buffer, SCREEN_W/2-RESSOURCES.parchemin->w/2, SCREEN_H/2-RESSOURCES.parchemin->h/2, i, j);
            }
        }
        for (int k=0; k < RESSOURCES.hieroglyphes->w; k++) {
            for (int l=0; l < RESSOURCES.hieroglyphes->h; l++) {
                fondueImage(param, RESSOURCES.Egypt2, RESSOURCES.hieroglyphes, buffer, SCREEN_W/2-RESSOURCES.hieroglyphes->w/2, SCREEN_H/2-RESSOURCES.hieroglyphes->h/2, k, l);
            }
        }
        afficherScreen(buffer);
        param += 0.025;
    }
    while (param < 1);
    rest(2000);

    //parchemin + texte fr avec fondue
    BITMAP *fond_actuel = buffer;
    param = 0;
    do {
        for (int i=0; i < RESSOURCES.parchemin->w; i++) {
            for (int j=0; j < RESSOURCES.parchemin->h; j++) {
                fondueImage(param, fond_actuel, RESSOURCES.parchemin, buffer, SCREEN_W/2-RESSOURCES.parchemin->w/2, SCREEN_H/2-RESSOURCES.parchemin->h/2, i, j);
            }
        }
        for (int k=0; k < RESSOURCES.texte_intro_fr->w; k++) {
            for (int l=0; l < RESSOURCES.texte_intro_fr->h; l++) {
                fondueImage(param, fond_actuel, RESSOURCES.texte_intro_fr, buffer, SCREEN_W/2-RESSOURCES.texte_intro_fr->w/2, SCREEN_H/2-RESSOURCES.texte_intro_fr->h/2, k, l);
            }
        }
        afficherScreen(buffer);
        param += 0.05;
    }
    while (param < 1);

    textprintf_centre_ex(screen, font, SCREEN_W/2, SCREEN_H-120, makecol(0, 0, 0), -1, "Press [ENTER] to skip");
    double begin = maintenantEnSec();
    double now = begin;
    while (!key[KEY_ENTER] && !state[BUTTON_X] && !state2[BUTTON_X] && now-begin < 35){
        input(state, state2);
        now = maintenantEnSec();
    }

    //fondu noir de fin d'intro
    param = 0;
    do {
        for (int i=0; i < SCREEN_W; i++) {
            for (int j=0; j < SCREEN_H; j++) {
                fondueImage(param, RESSOURCES.Egypt2, fond_noir, buffer, 0, 0, i, j);
            }
        }
        afficherScreen(buffer);
        param += 0.05;
    }
    while (param < 1);

    stop_sample(RESSOURCES.music_lvl4_intro);
    fond_actuel = NULL;
    destroy_bitmap(fond_actuel);
    fond_noir = NULL;
    destroy_bitmap(fond_noir);
}


// Evènement pendant niveau 4
void Tempete_sable(t_ressources RESSOURCES, BITMAP *buffer, double param) {
    for (int i=0; i < SCREEN_W; i++) {
        for (int j=0; j < SCREEN_H; j++) {
            fondueImage(param, buffer, RESSOURCES.tempete_sable, buffer, 0, 0, i, j);
        }
    }
}

void afficher_score(File_commandes* commandes,t_ressources RESSOURCES, t_partie* partie,BITMAP* buffer){
    //commandes->score = partie->joueur1.score + partie->joueur2.score;
    if (partie->niveau_select != 4) {
        textprintf_ex(buffer, RESSOURCES.font_small, SCREEN_W-200, 100, makecol(0,0,0), -1, "SCORE : %d", commandes->score);
    }
    else {
        textprintf_ex(buffer, RESSOURCES.font_egypt_small, SCREEN_W-200, 100, makecol(0,0,0), -1, "SCORE : %d", commandes->score);
    }
}

int fin_temps(t_partie* partie, t_ressources RESSOURCES, File_commandes* commandes, BITMAP* buffer, int state[TAM_MAX], int state2[TAM_MAX]){
    if(partie->time.timer <= 0){
        int sortie = 0;
        commandes->score = partie->joueur1.score + partie->joueur2.score;
        int ancien_score = meilleur_score(commandes);

        //Affichage des scores et game over avec un support

        //assombrissement du fond
        for (int i = 0; i < SCREEN_W; ++i) {
            for (int j = 0; j < SCREEN_H; ++j) {
                int pixelfond = getpixel(buffer, i, j);
                int r = getr(pixelfond) - ASSOMBRISSEMENTGAMEOVER;
                if (r < 0) r = 0;
                int g = getg(pixelfond) - ASSOMBRISSEMENTGAMEOVER;
                if (g < 0) g = 0;
                int b = getb(pixelfond) - ASSOMBRISSEMENTGAMEOVER;
                if (b < 0) b = 0;
                putpixel(buffer, i, j, makecol(r, g, b));
            }
        }

        // Sons end game
        stop_sample(RESSOURCES.music_background);
        stop_sample(RESSOURCES.music_background_lvl4);
        stop_sample(RESSOURCES.ding);
        stop_sample(RESSOURCES.fail_buzzer);
        stop_sample(RESSOURCES.alarm);
        stop_sample(RESSOURCES.sound_planche);
        stop_sample(RESSOURCES.sound_poele);
        stop_sample(RESSOURCES.sound_friteuse);
        stop_sample(RESSOURCES.sound_four);
        if (partie->music.activated == 1) {
            if (partie->lvl4_succes == 1) {
                play_sample(RESSOURCES.music_lvl4_outro, 255, 128, 1000, FALSE);
            }
            else {
                play_sample(RESSOURCES.sound_game_over, 255, 128, 1000, FALSE);
            }
        }

        masked_blit(RESSOURCES.parchemin_menu,buffer,0,0,200, 50, RESSOURCES.parchemin->w, RESSOURCES.parchemin->h);
        if (partie->niveau_select != 4) {
            textout_centre_ex(buffer, RESSOURCES.font_big,  "GAME OVER", SCREEN_W/2, SCREEN_H/2 - 210, makecol(0,0,0), -1);
            textprintf_centre_ex(buffer, RESSOURCES.font_big, SCREEN_W/2, SCREEN_H/2 - 122, makecol(0,0,0), -1,"MEILLEUR SCORE : %d", ancien_score);
            textprintf_centre_ex(buffer, RESSOURCES.font_big, SCREEN_W/2, SCREEN_H/2 - 34, makecol(0,0,0), -1,"SCORE : %d", commandes->score);
            textprintf_centre_ex(buffer, RESSOURCES.font_big, SCREEN_W/2, SCREEN_H/2 + 54, makecol(0,0,0), -1,"SCORE %s : %d", partie->joueur1.username, partie->joueur1.score);
            textprintf_centre_ex(buffer, RESSOURCES.font_big, SCREEN_W/2, SCREEN_H/2  + 142, makecol(0,0,0), -1,"SCORE %s : %d", partie->joueur2.username, partie->joueur2.score);
        }
        else { // Niveau 4
            if (partie->lvl4_succes == 1) { // Si niveau 4 réussi
                BITMAP* fond_noir = create_bitmap(SCREEN_W, SCREEN_H);
                clear_bitmap(fond_noir);
                blit(fond_noir, buffer, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
                afficherScreen(buffer);

                float param = 0;
                do {
                    for (int i=0; i < SCREEN_W; i++) {
                        for (int j=0; j < SCREEN_H; j++) {
                            fondueImage(param, fond_noir, RESSOURCES.Egypt2, buffer, 0, 0, i, j);
                        }
                    }
                    afficherScreen(buffer);
                    param += 0.02;
                }
                while (param < 1);
                rest(2000);

                param = 0;
                do {
                    for (int i=0; i < RESSOURCES.parchemin->w; i++) {
                        for (int j=0; j < RESSOURCES.parchemin->h; j++) {
                            fondueImage(param, RESSOURCES.Egypt2, RESSOURCES.parchemin, buffer, SCREEN_W/2-RESSOURCES.parchemin->w/2, SCREEN_H/2-RESSOURCES.parchemin->h/2, i, j);
                        }
                    }
                    afficherScreen(buffer);
                    param += 0.02;
                }
                while (param < 1);
                textout_centre_ex(buffer, RESSOURCES.font_egypt_big,  "BRAVO !", SCREEN_W/2, SCREEN_H/2 - 300, makecol(0,0,0), -1);
                textout_centre_ex(buffer, RESSOURCES.font_egypt_big,  "LA MALEDICTION EST LEVEE !", SCREEN_W/2, SCREEN_H/2 - 220, makecol(0,0,0), -1);
            }
            else { // Sinon simple texte GAME OVER
                textout_centre_ex(buffer, RESSOURCES.font_egypt_big,  "GAME OVER", SCREEN_W/2, SCREEN_H/2 - 210, makecol(0,0,0), -1);
            }
            // Affichage scores
            textprintf_centre_ex(buffer, RESSOURCES.font_egypt_big, SCREEN_W/2, SCREEN_H/2 - 122, makecol(0,0,0), -1,"MEILLEUR SCORE : %d", ancien_score);
            textprintf_centre_ex(buffer, RESSOURCES.font_egypt_big, SCREEN_W/2, SCREEN_H/2 - 34, makecol(0,0,0), -1,"SCORE : %d", commandes->score);
            textprintf_centre_ex(buffer, RESSOURCES.font_egypt_big, SCREEN_W/2, SCREEN_H/2 + 54, makecol(0,0,0), -1,"SCORE %s : %d", partie->joueur1.username, partie->joueur1.score);
            textprintf_centre_ex(buffer, RESSOURCES.font_egypt_big, SCREEN_W/2, SCREEN_H/2  + 142, makecol(0,0,0), -1,"SCORE %s : %d", partie->joueur2.username, partie->joueur2.score);
        }


        BITMAP* tmp = create_bitmap(SCREEN_W, SCREEN_H);
        draw_sprite(tmp,buffer,0,0);


        while(sortie == 0){
            //Mettre le background
            draw_sprite(buffer, tmp, 0, 0);

            //Bouton pour continuer
            sortie = bouton(buffer, SCREEN_W/2 -100, SCREEN_H/2 + 230, 200, 100, RESSOURCES.exit_button,RESSOURCES.exit_button_hover,RESSOURCES.exit_button_pressed,state[BUTTON_X],state2[BUTTON_X]);

            //Affichage souris
            draw_sprite(buffer, RESSOURCES.mouse, mouse_x, mouse_y);

            //Mise à jour de l'affichage
            draw_sprite(screen,buffer,0,0);
        }
        supprimer_tous_maillons(commandes); // vide la file dynamique de toutes les commandes stockées

        clearESC(state,state2);
        while (mouse_b&1 || state[BUTTON_X]){
            input(state,state2);
        }
        if(partie->music.activated==1){
            stop_sample(RESSOURCES.music_lvl4_outro);
            stop_sample(RESSOURCES.sound_game_over);
            play_sample(RESSOURCES.musicIntro, 255, 128, 1600, TRUE);
        }
        destroy_bitmap(tmp);
        return 1; //Le temps est fini et on a appuyé sur le bouton sorti
    }
    return 0; //Le temps n'est pas fini rien ne se passe
}
