#include "_fonctionsAllegro.h"

//////////////////////////////////////////////////////////
/// Nom du sous-programme : afficheErreurEtQuitte
/// Rôle : affiche le message et quitte complètement le programme
/// @param message
//////////////////////////////////////////////////////////

void afficheErreurEtQuitte(char* message)
{
    allegro_message(message);
    allegro_exit();
    exit(EXIT_FAILURE);
}

//////////////////////////////////////////////////////////
/// Nom du sous-programme : clearESC
/// Rôle : Attend que la touche ESC soit relâchée
//////////////////////////////////////////////////////////

void clearESC(int state[TAM_MAX], int state2[TAM_MAX]){
    while (key[KEY_ESC] || (state[GACHETTE_UP_L]==1) || (state2[GACHETTE_UP_L]==1)){ //si echappe reste appuyer bloquer ici
        input(state,state2);
    }
}

//////////////////////////////////////////////////////////
/// Nom du sous-programme : afficherScreen
/// Rôle : Affiche le buffer à l'écran
/// @param buffer
//////////////////////////////////////////////////////////

void afficherScreen(BITMAP* buffer) {
    blit(buffer, screen, 0, 0, 0, 0, SCREEN_W, SCREEN_H);
}

//////////////////////////////////////////////////////////
/// Nom du sous-programme : Button
/// Rôle : Affiche un bouton à l'écran
/// @param buffer
/// @param pos_x
/// @param pos_y
/// @param taille_x
/// @param taille_y
/// @param button
/// @param button_hover
/// @param button_pressed
/// @param state
/// @return
//////////////////////////////////////////////////////////

short bouton (BITMAP* buffer, int pos_x, int pos_y, int taille_x, int taille_y, BITMAP*button, BITMAP*button_hover, BITMAP* button_pressed,int etat, int etat2){
    if (((etat || etat2)||(mouse_b & 1)) && (mouse_x <= pos_x + taille_x) && (mouse_x >= pos_x) && (mouse_y <= pos_y + taille_y) && (mouse_y >= pos_y)){
        draw_sprite(buffer, button_pressed, pos_x, pos_y);
        return 1; // bouton appuyé
    }
    else if((mouse_x <= pos_x + taille_x) && (mouse_x >= pos_x) && (mouse_y <= pos_y + taille_y) && (mouse_y >= pos_y)){
        draw_sprite(buffer, button_hover, pos_x, pos_y);
        return 0; // bouton survolé
    }
    else {
        draw_sprite(buffer, button, pos_x, pos_y);
        return 0; // bouton non appuyé
    }
}

//////////////////////////////////////////////////////////
/// Fonctions pratiques pour utiliser des couleurs
//////////////////////////////////////////////////////////

int couleurGrisTresClair()      { return makecol(230,230,230);  }
int couleurGrisMoyen()          { return makecol(127,127,127);  }
int couleurGrisFonce()          { return makecol(70,70,70);     }
int couleurNoir()               { return makecol(0,0,0);        }
int couleurBlanc()              { return makecol(255,255,255);  }
int couleurRouge()              { return makecol(255,0,0);      }
int couleurVert()               { return makecol(0,255,0);      }
int couleurBleu()               { return makecol(0,0,255);      }
int couleurJaune()              { return makecol(255,255,0);    }
int couleurOrange()             { return makecol(250,150,50);   }
int couleurMagenta()            { return makecol(255,0,255);    }
int couleurMarron()             { return makecol(88,41,0);      }
int couleurTransparence()       { return couleurMagenta();      }

//////////////////////////////////////////////////////////
/// Nom du sous-programme :
/// Rôle :
/// @param buffer
//////////////////////////////////////////////////////////

void Screenshot(BITMAP* buffer) {
    time_t now;
    time(&now);
    char screen_time[64] = "../Screenshots/Screenshot";

    struct tm *local = localtime(&now);
    char h[8];
    char min[8];
    char s[8];
    char day[8];
    char month[8];
    char year[8];

    sprintf(h, "-%d", local->tm_hour);
    sprintf(min, "-%d", local->tm_min);
    sprintf(s, "-%d", local->tm_sec);
    sprintf(day, "-%d", local->tm_mday);
    sprintf(month, "-%d", local->tm_mon+1);
    sprintf(year, "-%d", local->tm_year+1900);

    strcat(screen_time, year);
    strcat(screen_time, month);
    strcat(screen_time, day);
    strcat(screen_time, h);
    strcat(screen_time, min);
    strcat(screen_time, s);
    strcat(screen_time, ".bmp");

    save_bmp(screen_time, buffer, NULL);
    printf("\nScreenshot saved ! \n%s", screen_time);
}