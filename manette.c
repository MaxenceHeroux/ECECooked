// Created by herou on 30/03/2024.
#include "manette_PS.h"

void input(int state [TAM_MAX], int state2 [TAM_MAX]){

    //Joy 1 (TAM_MAX)///////////////////////////////////////////////////////
    poll_joystick();
    state[BUTTON_CARRE]= joy[0].button[0].b;
    state[BUTTON_X]= joy[0].button[1].b;
    state[BUTTON_ROND]= joy[0].button[2].b;
    state[BUTTON_TRI]= joy[0].button[3].b;

    state[GACHETTE_UP_R]= joy[0].button[5].b;
    state[GACHETTE_UP_L]= joy[0].button[4].b;
    //sate[GACHETTE_L]= joy[0].button[6].b;
    state[GACHETTE_R]= joy[0].button[7].b;

    /*sate[BUTTON_CROIX_UP]= joy[1].button[0].b;  //891011 option sp pt etc
    sate[BUTTON_CROIX_DOWN]= joy[1].button[1].b;
    sate[BUTTON_CROIX_LEFT]= joy[1].button[2].b;
    sate[BUTTON_CROIX_RIGHT]= joy[1].button[3].b;*/

    state[LSTICK_UP]=(joy[0].stick[0].axis[1].pos <0);
    state[LSTICK_DOWN]=(joy[0].stick[0].axis[1].pos >0);
    state[LSTICK_LEFT]=(joy[0].stick[0].axis[0].pos <0);
    state[LSTICK_RIGHT]=(joy[0].stick[0].axis[0].pos >0);

    //Joy 2 (MAX_TAM)///////////////////////////////////////////////////////
    poll_joystick();
    state2[BUTTON_CARRE]= joy[1].button[0].b;
    state2[BUTTON_X]= joy[1].button[1].b;
    state2[BUTTON_ROND]= joy[1].button[2].b;
    state2[BUTTON_TRI]= joy[1].button[3].b;

    state2[GACHETTE_UP_R]= joy[1].button[5].b;
    state2[GACHETTE_UP_L]= joy[1].button[4].b;
    //sate[GACHETTE_L]= joy[0].button[6].b;
    state2[GACHETTE_R]= joy[1].button[7].b;

    state2[LSTICK_UP]=(joy[1].stick[0].axis[1].pos <0);
    state2[LSTICK_DOWN]=(joy[1].stick[0].axis[1].pos >0);
    state2[LSTICK_LEFT]=(joy[1].stick[0].axis[0].pos <0);
    state2[LSTICK_RIGHT]=(joy[1].stick[0].axis[0].pos >0);

}

void affiche_clavier_min(t_ressources RESSOURCES, BITMAP* buffer){
    draw_sprite(buffer,RESSOURCES.clavier_min, CLAVIER_X, CLAVIER_Y);
    draw_sprite(buffer, RESSOURCES.mouse, mouse_x, mouse_y);
}

void affiche_clavier_maj(t_ressources RESSOURCES, BITMAP* buffer){
    draw_sprite(buffer,RESSOURCES.clavier_maj, CLAVIER_X, CLAVIER_Y);
    draw_sprite(buffer, RESSOURCES.mouse, mouse_x, mouse_y);
}

void apparitionClavier(t_ressources RESSOURCES, BITMAP* buffer, BITMAP* buffer_texte, BITMAP* maptexte, char string[TAILLE_PSEUDO]){
    ///////////////////////////////////Animation 1 : De bas à haut///////////////////////////////////
    int y = SCREEN_H;
    //Copie du buffer dans un bitmap temporaire
    BITMAP* tmp = create_bitmap(SCREEN_W, SCREEN_H);
    assert(tmp != NULL);
    draw_sprite(tmp, buffer, 0, 0);

    //Affichage du texte
    blit(maptexte,buffer_texte,0,0,0,0,SCREEN_W,SCREEN_H);
    textprintf_ex(buffer_texte, font, SCREEN_W - 300, 260, makecol(0, 0, 0), -1, string);
    blit(buffer_texte,tmp,0,0,0,0,SCREEN_W,SCREEN_H);

    while(1) {
        y--;
        if(y <= CLAVIER_Y){ //Condition pour sortir de la boucle
            destroy_bitmap(tmp); //libération mémoire
            return;
        }

        //Mise à jour du buffer
        draw_sprite(buffer, tmp, 0, 0);
        //Affichage du clavier
        draw_sprite(buffer, RESSOURCES.clavier_min, CLAVIER_X, y);
        //Affichage de la souris
        draw_sprite(buffer, RESSOURCES.mouse, mouse_x, mouse_y);
        //Mise à jour de l'écran
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }

    ///////////////////////////////////Animation 2 : De gauche à droite///////////////////////////////////
    /*float x = 0;
    float bitmap_x = 1000;
    //Copie du buffer dans un bitmap temporaire
    BITMAP* tmp = create_bitmap(SCREEN_W, SCREEN_H);
    assert(tmp != NULL);
    draw_sprite(tmp, buffer, 0, 0);

    //Affichage du texte
    blit(maptexte,buffer_texte,0,0,0,0,SCREEN_W,SCREEN_H);
    textprintf_ex(buffer_texte, font, SCREEN_W - 300, 260, makecol(0, 0, 0), -1, string);
    blit(buffer_texte,tmp,0,0,0,0,SCREEN_W,SCREEN_H);

    while(1) {
        x += 0.22; //vitesse de déplacement du clavier, doit correspondre avec l'incrémentation de bitmap_x
        if(x >= CLAVIER_X){ //Condition d'arrêt
            destroy_bitmap(tmp); //libération mémoire
            return;
        }
        bitmap_x -= 10; //vitesse de déroulement du clavier, doit correspondre avec l'incrémentation de x
        if(bitmap_x <= 0){ //Condition d'arrêt
            bitmap_x = 0;
        }

        //Mise à jour du buffer
        draw_sprite(buffer, tmp, 0, 0);
        //Affichage du clavier
        //draw_sprite(buffer, RESSOURCES.clavier_min, x, CLAVIER_Y);
        blit(RESSOURCES.clavier_min, buffer,bitmap_x , 0, x, CLAVIER_Y, SCREEN_W, SCREEN_H);
        //Affichage de la souris
        draw_sprite(buffer, RESSOURCES.mouse, mouse_x, mouse_y);
        //Mise à jour de l'écran
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
        rest(5); //Pour régler la vitesse de l'animation
    }*/
}

void clavier(t_ressources RESSOURCES, BITMAP* buffer, BITMAP* buffer_texte, BITMAP* maptexte, char string[TAILLE_PSEUDO], int state[TAM_MAX], int state2[TAM_MAX]){

    int touche; //Pour savoir quelle est la touche pressée
    int nb_caractere = 0; //Compte le nombre de caractères pour ne pas dépasser la limite de caractères des chaines
    int touche_pressed = 0; //pour savoir si la touche est appuyée
    int pixel, r, g, b;
    int mode = 0; //0 : minuscule ; 1 : majuscule
    int maj = 0; //1 : maj activé; 0 : maj désactiver

    while(!key[KEY_ENTER]){
        //mouvement manette
        if(state[LSTICK_UP] && mouse_y>0) mouse_y-=VITESSE_MANETTE;
        if(state[LSTICK_DOWN]&& mouse_y<SCREEN_H) mouse_y+=VITESSE_MANETTE;
        if(state[LSTICK_RIGHT]&& mouse_x<SCREEN_W) mouse_x+=VITESSE_MANETTE;
        if(state[LSTICK_LEFT]&& mouse_x>0) mouse_x-=VITESSE_MANETTE;
        if(state2[LSTICK_UP] && mouse_y>0) mouse_y-=VITESSE_MANETTE;
        if(state2[LSTICK_DOWN]&& mouse_y<SCREEN_H) mouse_y+=VITESSE_MANETTE;
        if(state2[LSTICK_RIGHT]&& mouse_x<SCREEN_W) mouse_x+=VITESSE_MANETTE;
        if(state2[LSTICK_LEFT]&& mouse_x>0) mouse_x-=VITESSE_MANETTE;
        input(state,state2);

        //Affiche
        //Texte
        blit(maptexte,buffer_texte,0,0,0,0,SCREEN_W,SCREEN_H);
        textprintf_ex(buffer_texte, font, SCREEN_W - 300, 260, makecol(0, 0, 0), -1, string);
        blit(buffer_texte,buffer,0,0,0,0,SCREEN_W,SCREEN_H);

        //Clavier et souris
        if ((mode == 0) || (maj == 0)) {
            affiche_clavier_min(RESSOURCES, buffer);
        }
        if ((mode == 1) || (maj == 1)){
            affiche_clavier_maj(RESSOURCES, buffer);
        }

        //14 touches : de échape à égale
        if ((4 + CLAVIER_Y <= mouse_y) && (mouse_y <= 60 + CLAVIER_Y)) { //coordonnées y des touches
            for (int i = 4 + CLAVIER_X; i <= 897 + CLAVIER_X; i += 64) { //coordonnées en x du coin en haut à gauche de chaque touche

                if ((i <= mouse_x) && (mouse_x <= (i + 60))) { //i + 60 = coordonnées en x du coin en haut à droite de chaque touche

                    //Gérer le click
                    touche = (i - 4 - CLAVIER_X + 64) / 64; //pour savoir quelle touche est pressée
                    //Clavier minuscule
                    if (((mouse_b & 1) || state[BUTTON_X] || state2[BUTTON_X]) && (mode == 0 && maj == 0) && (touche_pressed == 0)) { //si le bouton x est appuyé
                        touche_pressed = 1;
                        switch (touche){
                            case 1: //Echape
                            {
                                return;
                            }
                            case 2:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "²");
                                    nb_caractere++;

                                }
                                break;
                            }
                            case 3:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "&");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 4:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "é");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 5:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "#");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 6:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "'");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 7:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "(");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 8:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "-");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 9:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "è");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 10:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "_");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 11:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "ç");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 12:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "à");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 13:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, ")");
                                nb_caractere++;
                                }
                                break;
                            }
                            case 14:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "=");
                                nb_caractere++;
                                }
                                break;
                            }
                        }
                    }
                    //Clavier majuscule
                    if (((mouse_b & 1) || state[BUTTON_X] || state2[BUTTON_X]) && (mode == 1 || maj == 1) && (touche_pressed == 0)){
                        touche_pressed = 1;
                        maj = 0;
                        switch (touche){
                            case 1: //Echape
                            {
                                return;
                            }
                            case 2:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "");
                                break;
                                }
                            }
                            case 3:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "1");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 4:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "2");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 5:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "3");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 6:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "4");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 7:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "5");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 8:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "6");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 9:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "7");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 10:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "8");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 11:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "9");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 12:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "0");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 13:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "°");
                                nb_caractere++;
                                break;
                                }
                            }
                            case 14:
                            {
                                if(nb_caractere < TAILLE_PSEUDO - 1) {
                                strcat(string, "+");
                                nb_caractere++;
                                break;
                                }
                            }
                        }
                    }

                    //Coloration de la touche survolée
                    //floodfill(buffer, i + 30, CLAVIER_Y + 30,makecol(250, 250, 250)); //old
                    for(int j = 4 + CLAVIER_Y; j <= 60 + CLAVIER_Y; j++){
                        for(int k = i; k <= i + 60; k++){

                            pixel = getpixel(buffer, k, j);
                            r = getr(pixel);
                            g = getg(pixel);
                            b = getb(pixel);

                            if ((r == 51) && (g == 51) && (b == 51)){
                                putpixel(buffer, k, j, makecol(250, 250, 250));
                            }
                        }
                    }
                }
            }
        }

        //touche entrer
        if (((((mouse_x >= 869 + CLAVIER_X) && (mouse_x <= 996 + CLAVIER_X))) && ((mouse_y >= 64 + CLAVIER_Y) && (mouse_y <= 119 + CLAVIER_Y))) || ((((mouse_x >= 893 + CLAVIER_X) && (mouse_x <= 996 + CLAVIER_X))) && ((mouse_y >= 120 + CLAVIER_Y) && (mouse_y <= 178 + CLAVIER_Y)))){

            if ((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) { //si le bouton x est appuyé ou click gauche
                return; //si entrer est appuyé
            }

            //Coloration de la touche survolée
            for(int j = 64 + CLAVIER_Y; j <= 119 + CLAVIER_Y; j++){
                for(int k = 869 + CLAVIER_X; k <=  996+ CLAVIER_X; k++){

                    pixel = getpixel(buffer, k, j);
                    r = getr(pixel);
                    g = getg(pixel);
                    b = getb(pixel);

                    if ((r == 51) && (g == 51) && (b == 51)){
                        putpixel(buffer, k, j, makecol(250, 250, 250));
                    }
                }
            }
            for(int j = 120 + CLAVIER_Y; j <= 178 + CLAVIER_Y; j++){
                for(int k = 893 + CLAVIER_X; k <= 996 + CLAVIER_X; k++){

                    pixel = getpixel(buffer, k, j);
                    r = getr(pixel);
                    g = getg(pixel);
                    b = getb(pixel);

                    if ((r == 51) && (g == 51) && (b == 51)){
                        putpixel(buffer, k, j, makecol(250, 250, 250));
                    }
                }
            }
            //old
            /*floodfill(buffer, 900 + CLAVIER_X, 100 + CLAVIER_Y,makecol(250, 250, 250)); //x = 900 + CLAVIER_X et y = 100 + CLAVIER_Y : coordonnées de la touche entrer
            floodfill(buffer, 950 + CLAVIER_X, 150 + CLAVIER_Y,makecol(250, 250, 250));*/
        }

        //touche espace
        if ((((mouse_x >= 260 + CLAVIER_X) && (mouse_x <= 609 + CLAVIER_X))) && ((mouse_y >= 241 + CLAVIER_Y) && (mouse_y <= 296 + CLAVIER_Y))){

            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0)) { //si le bouton x est appuyé ou click gauche
                touche_pressed = 1;
                nb_caractere++;
                strcat(string, " "); //si espace est appuyé
            }

            //Coloration de la touche survolée
            for(int j = 260 + CLAVIER_X; j <= 609 + CLAVIER_X; j++){
                for(int k = 241 + CLAVIER_Y; k <= 296 + CLAVIER_Y; k++){

                    pixel = getpixel(buffer, j, k);
                    r = getr(pixel);
                    g = getg(pixel);
                    b = getb(pixel);

                    if ((r == 51) && (g == 51) && (b == 51)){
                        putpixel(buffer, j, k, makecol(250, 250, 250));
                    }
                }
            }
        }

        //touche retour
        if ((((mouse_x >= 901 + CLAVIER_X) && (mouse_x <= 996 + CLAVIER_X))) && ((mouse_y >= 4 + CLAVIER_Y) && (mouse_y <= 60 + CLAVIER_Y))){

            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0)) { //si le bouton x est appuyé ou click gauche
                touche_pressed = 1;

                if(string[strlen(string) - 1] == '^'){ //problème car certains caractères se font remplacer par ^ quand on les efface
                    string[strlen(string) - 1] = '\0';
                }
                else if (string != NULL && strlen(string) > 0){
                    nb_caractere--;
                    string[strlen(string) - 1] = '\0';
                }
            }

            //Coloration de la touche survolée
            for(int j = 901 + CLAVIER_X; j <= 996 + CLAVIER_X; j++){
                for(int k = 4 + CLAVIER_Y; k <= 60 + CLAVIER_Y; k++){

                    pixel = getpixel(buffer, j, k);
                    r = getr(pixel);
                    g = getg(pixel);
                    b = getb(pixel);

                    if ((r == 51) && (g == 51) && (b == 51)){
                        putpixel(buffer, j, k, makecol(250, 250, 250));
                    }
                }
            }
        }

        //touche supprimée
        if ((((mouse_x >= 933 + CLAVIER_X) && (mouse_x <= 996 + CLAVIER_X))) && ((mouse_y >= 182 + CLAVIER_Y) && (mouse_y <= 237 + CLAVIER_Y))){

            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0)) { //si le bouton x est appuyé ou click gauche
                touche_pressed = 1;

                if(string[strlen(string) - 1] == '^'){ //problème car certains caractères se font remplacer par ^ quand on les efface
                    string[strlen(string) - 1] = '\0';
                }
                else if (string != NULL && strlen(string) > 0){
                    nb_caractere--;
                    string[strlen(string) - 1] = '\0';
                }
            }

            //Coloration de la touche survolée
            for(int j = 933 + CLAVIER_X; j <= 996 + CLAVIER_X; j++){
                for(int k = 182 + CLAVIER_Y; k <= 237 + CLAVIER_Y; k++){

                    pixel = getpixel(buffer, j, k);
                    r = getr(pixel);
                    g = getg(pixel);
                    b = getb(pixel);

                    if ((r == 51) && (g == 51) && (b == 51)){
                        putpixel(buffer, j, k, makecol(250, 250, 250));
                    }
                }
            }
        }

        //touche tab
        if ((((mouse_x >= 4 + CLAVIER_X) && (mouse_x <= 96 + CLAVIER_X))) && ((mouse_y >= 64 + CLAVIER_Y) && (mouse_y <= 119 + CLAVIER_Y))){

            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0)) { //si le bouton x est appuyé ou click gauche
                touche_pressed = 1;
                nb_caractere += 4;
                strcat(string, "    "); //si tab est appuyé
            }

            //Coloration de la touche survolée
            for(int j = 4 + CLAVIER_X; j <= 96 + CLAVIER_X; j++){
                for(int k = 64 + CLAVIER_Y; k <= 119 + CLAVIER_Y; k++){

                    pixel = getpixel(buffer, j, k);
                    r = getr(pixel);
                    g = getg(pixel);
                    b = getb(pixel);

                    if ((r == 51) && (g == 51) && (b == 51)){
                        putpixel(buffer, j, k, makecol(250, 250, 250));
                    }
                }
            }
        }

        //touche ver_maj
        if ((((mouse_x >= 4 + CLAVIER_X) && (mouse_x <= 119 + CLAVIER_X))) && ((mouse_y >= 123 + CLAVIER_Y) && (mouse_y <= 178 + CLAVIER_Y))){

            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0) && mode == 0) { //si le bouton x est appuyé ou click gauche
                touche_pressed = 1; //si tab est appuyé et le clavier est minuscule
                mode = 1;
            }
            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0) && mode == 1){ //si le bouton x est appuyé ou click gauche
                touche_pressed = 1; //si tab est appuyé et le clavier est majuscule
                mode = 0;
            }

            //Coloration de la touche survolée
            for (int j = 4 + CLAVIER_X; j <= 119 + CLAVIER_X; j++) {
                for (int k = 123 + CLAVIER_Y; k <= 178 + CLAVIER_Y; k++) {

                    pixel = getpixel(buffer, j, k);
                    r = getr(pixel);
                    g = getg(pixel);
                    b = getb(pixel);

                    if ((r == 51) && (g == 51) && (b == 51)) {
                        putpixel(buffer, j, k, makecol(250, 250, 250));
                    }
                }
            }
        }

        //touche maj gauche
        if ((((mouse_x >= 4 + CLAVIER_X) && (mouse_x <= 96 + CLAVIER_X))) && ((mouse_y >= 182 + CLAVIER_Y) && (mouse_y <= 237 + CLAVIER_Y))){

            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0) && maj == 0) { //si le bouton x est appuyé ou click gauche
                touche_pressed = 1; //si maj gauche est appuyé et le clavier est minuscule
                maj = 1;
            }
            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0) && maj == 1){ //si le bouton x est appuyé ou click gauche
                touche_pressed = 1; //si maj gauche est appuyé et le clavier est majuscule
                maj = 0;
            }

            //Coloration de la touche survolée
            for (int j = 4 + CLAVIER_X; j <= 96 + CLAVIER_X; j++) {
                for (int k = 182 + CLAVIER_Y; k <= 237 + CLAVIER_Y; k++) {

                    pixel = getpixel(buffer, j, k);
                    r = getr(pixel);
                    g = getg(pixel);
                    b = getb(pixel);

                    if ((r == 51) && (g == 51) && (b == 51)) {
                        putpixel(buffer, j, k, makecol(250, 250, 250));
                    }
                }
            }
        }

        //touche maj droite
        if ((((mouse_x >= 869 + CLAVIER_X) && (mouse_x <= 929 + CLAVIER_X))) && ((mouse_y >= 182 + CLAVIER_Y) && (mouse_y <= 237 + CLAVIER_Y))){

            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0) && maj == 0) { //si le bouton x est appuyé ou click gauche
                touche_pressed = 1; //si maj gauche est appuyé et le clavier est minuscule
                maj = 1;
            }
            if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (touche_pressed == 0) && maj == 1){ //si le bouton x est appuyé ou click gauche
                touche_pressed = 1; //si maj gauche est appuyé et le clavier est majuscule
                maj = 0;
            }

            //Coloration de la touche survolée
            for (int j = 869 + CLAVIER_X; j <= 929 + CLAVIER_X; j++) {
                for (int k = 182 + CLAVIER_Y; k <= 237 + CLAVIER_Y; k++) {

                    pixel = getpixel(buffer, j, k);
                    r = getr(pixel);
                    g = getg(pixel);
                    b = getb(pixel);

                    if ((r == 51) && (g == 51) && (b == 51)) {
                        putpixel(buffer, j, k, makecol(250, 250, 250));
                    }
                }
            }
        }

        //12 touches : de flêche (<) à flêche vers le haut
        if ((182 + CLAVIER_Y <= mouse_y) && (mouse_y <= 237 + CLAVIER_Y)) { //coordonnées y des touches
            for (int i = 100 + CLAVIER_X; i <= 865 + CLAVIER_X; i += 64) { //coordonnées en x du coin en haut à gauche de chaque touche

                if ((i <= mouse_x) && (mouse_x <= (i + 60))) { //i + 60 = coordonnées en x du coin en haut à droite de chaque touche

                    //Gérer le click
                    touche = (i - 100 - CLAVIER_X + 64) / 64; //pour savoir quelle touche est pressée
                    //Clavier minuscule
                    if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (mode == 0 && maj == 0) && (touche_pressed == 0)) { //si le bouton x est appuyé
                        touche_pressed = 1;
                        switch (touche) {
                            case 1:
                            {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "<");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 2: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "w");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 3: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "x");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 4: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "c");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 5: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "v");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 6: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "b");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 7: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "n");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 8: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, ",");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 9: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, ";");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 10: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, ":");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 11: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "!");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 12: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "");
                                }
                                break;
                            }
                        }
                    }

                    //Clavier majuscule
                    if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (mode == 1 || maj == 1) && (touche_pressed == 0)) {
                        touche_pressed = 1;
                        maj = 0; //désactive la majuscule
                        switch (touche) {
                            case 1: //Echape
                            {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, ">");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 2: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "W");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 3: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "X");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 4: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "C");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 5: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "V");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 6: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "B");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 7: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "N");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 8: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "?");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 9: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, ".");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 10: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "/");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 11: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "§");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 12: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "");
                                    break;
                                }
                            }
                        }
                    }

                    //Coloration de la touche survolée
                    //floodfill(buffer, i + 30, CLAVIER_Y + 30,makecol(250, 250, 250)); //old
                    for (int j = 182 + CLAVIER_Y; j <= 237 + CLAVIER_Y; j++) {
                        for (int k = i; k <= i + 60; k++) {

                            pixel = getpixel(buffer, k, j);
                            r = getr(pixel);
                            g = getg(pixel);
                            b = getb(pixel);

                            if ((r == 51) && (g == 51) && (b == 51)) {
                                putpixel(buffer, k, j, makecol(250, 250, 250));
                            }
                        }
                    }
                }
            }
        }

        //12 touches : de a à $
        if ((64 + CLAVIER_Y <= mouse_y) && (mouse_y <= 119 + CLAVIER_Y)) { //coordonnées y des touches
            for (int i = 100 + CLAVIER_X; i <= 865 + CLAVIER_X; i += 64) { //coordonnées en x du coin en haut à gauche de chaque touche

                if ((i <= mouse_x) && (mouse_x <= (i + 60))) { //i + 60 = coordonnées en x du coin en haut à droite de chaque touche

                    //Gérer le click
                    touche = (i - 100 - CLAVIER_X + 64) / 64; //pour savoir quelle touche est pressée
                    //Clavier minuscule
                    if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (mode == 0 && maj == 0) && (touche_pressed == 0)) { //si le bouton x est appuyé
                        touche_pressed = 1;
                        switch (touche) {
                            case 1:
                            {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "a");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 2: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "z");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 3: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "e");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 4: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "r");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 5: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "t");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 6: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "y");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 7: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "u");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 8: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "i");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 9: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "o");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 10: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "p");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 11: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "€"); //pas d'accent circonflexe car il bug
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 12: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "$");
                                    nb_caractere++;
                                }
                                break;
                            }
                        }
                    }

                    //Clavier majuscule
                    if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (mode == 1 || maj == 1) && (touche_pressed == 0)) {
                        touche_pressed = 1;
                        maj = 0;
                        switch (touche) {
                            case 1: //Echape
                            {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "A");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 2: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "Z");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 3: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "E");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 4: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "R");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 5: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "T");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 6: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "Y");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 7: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "U");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 8: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "I");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 9: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "O");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 10: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "P");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 11: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "¨");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 12: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "£");
                                    nb_caractere++;
                                    break;
                                }
                            }
                        }
                    }

                    //Coloration de la touche survolée
                    //floodfill(buffer, i + 30, CLAVIER_Y + 30,makecol(250, 250, 250)); //old
                    for (int j = 64 + CLAVIER_Y; j <= 119 + CLAVIER_Y; j++) {
                        for (int k = i; k <= i + 60; k++) {

                            pixel = getpixel(buffer, k, j);
                            r = getr(pixel);
                            g = getg(pixel);
                            b = getb(pixel);

                            if ((r == 51) && (g == 51) && (b == 51)) {
                                putpixel(buffer, k, j, makecol(250, 250, 250));
                            }
                        }
                    }
                }
            }
        }


        //12 touches : de q à *
        if ((123 + CLAVIER_Y <= mouse_y) && (mouse_y <= 178 + CLAVIER_Y)) { //coordonnées y des touches
            for (int i = 123 + CLAVIER_X; i <= 889 + CLAVIER_X; i += 64) { //coordonnées en x du coin en haut à gauche de chaque touche

                if ((i <= mouse_x) && (mouse_x <= (i + 60))) { //i + 60 = coordonnées en x du coin en haut à droite de chaque touche

                    //Gérer le click
                    touche = (i - 123 - CLAVIER_X + 64) / 64; //pour savoir quelle touche est pressée
                    //Clavier minuscule
                    if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (mode == 0 && maj == 0) && (touche_pressed == 0)) { //si le bouton x est appuyé
                        touche_pressed = 1;
                        switch (touche) {
                            case 1:
                            {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "q");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 2: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "s");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 3: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "d");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 4: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "f");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 5: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "g");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 6: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "h");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 7: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "j");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 8: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "k");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 9: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "l");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 10: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "m");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 11: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "ù");
                                    nb_caractere++;
                                }
                                break;
                            }
                            case 12: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "*");
                                    nb_caractere++;
                                }
                                break;
                            }
                        }
                    }

                    //Clavier majuscule
                    if (((mouse_b & 1) || state[BUTTON_X]|| state2[BUTTON_X]) && (mode == 1 || maj == 1) && (touche_pressed == 0)) {
                        touche_pressed = 1;
                        maj = 0;
                        switch (touche) {
                            case 1: //Echape
                            {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "Q");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 2: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "S");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 3: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "D");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 4: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "F");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 5: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "G");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 6: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "H");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 7: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "J");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 8: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "K");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 9: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "L");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 10: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "M");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 11: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "%%");
                                    nb_caractere++;
                                    break;
                                }
                            }
                            case 12: {
                                if (nb_caractere < TAILLE_PSEUDO - 1) {
                                    strcat(string, "µ");
                                    nb_caractere++;
                                    break;
                                }
                            }
                        }
                    }

                    //Coloration de la touche survolée
                    //floodfill(buffer, i + 30, CLAVIER_Y + 30,makecol(250, 250, 250)); //old
                    for (int j = 123 + CLAVIER_Y; j <= 178 + CLAVIER_Y; j++) {
                        for (int k = i; k <= i + 60; k++) {

                            pixel = getpixel(buffer, k, j);
                            r = getr(pixel);
                            g = getg(pixel);
                            b = getb(pixel);

                            if ((r == 51) && (g == 51) && (b == 51)) {
                                putpixel(buffer, k, j, makecol(250, 250, 250));
                            }
                        }
                    }
                }
            }
        }

        //3 touches : de flèche de gauche à flêche de doite
        if ((241 + CLAVIER_Y <= mouse_y) && (mouse_y <= 296 + CLAVIER_Y)) { //coordonnées y des touches
            for (int i = 741 + CLAVIER_X; i <= 930 + CLAVIER_X; i += 64) { //coordonnées en x du coin en haut à gauche de chaque touche

                if ((i <= mouse_x) && (mouse_x <= (i + 60))) { //i + 60 = coordonnées en x du coin en haut à droite de chaque touche

                    //Coloration de la touche survolée
                    //floodfill(buffer, i + 30, CLAVIER_Y + 30,makecol(250, 250, 250)); //old
                    for (int j = 241 + CLAVIER_Y; j <= 296 + CLAVIER_Y; j++) {
                        for (int k = i; k <= i + 60; k++) {

                            pixel = getpixel(buffer, k, j);
                            r = getr(pixel);
                            g = getg(pixel);
                            b = getb(pixel);

                            if ((r == 51) && (g == 51) && (b == 51)) {
                                putpixel(buffer, k, j, makecol(250, 250, 250));
                            }
                        }
                    }
                }
            }
        }


        if (!(mouse_b & 1) && !(state[BUTTON_X] || state2[BUTTON_X])) {
            touche_pressed = 0; //Click inactif (bouton x ou click gauche souris)
        }

        //Met à jour l'affichage
        blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
    }
}
