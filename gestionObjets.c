#include "config.h"

/* Explications :
 *  -> INTERRACTION : Quand on appuie sur espace pour prendre, poser, ecahnger ou combiner un objet
 *  -> ACTION : Quand oon appuie sur V pour découper un ingrédient sur une planche a coupé ou autre
 *  -> TEMPS : Quand on doit gérer le temps de cuisson des objets sur les meubles
 *  -> MEUBLE SPECIFIQUE : Meuble qui a des conditions spécifiques pour poser ou prendre un objet
 *  -> COMBINAISON : Quand on combine deux objets pour en faire un autre
 *  -> PRIORITAIRE : Quand on a une action prioritaire sur un meuble spécifique
 *  -> VERIFICATION : Quand on vérifie si on peut poser, prendre ou combiner des objets
 *  -> OBJET : Tableau d'objet qui contient les objets du joueur ou du meuble
 *  -> PERMISSIONS : Tableau de permissions qui contient les permissions des objets pour les combiner, les couper, les cuires, etc...
 */


//////////////////////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : toucheInterractionJoueur
// Rôle : Gestion de l'interraction (espace) des objets entre le joueur et les meubles,
//////////////////////////////////////////////////////////////////////////////////////////////

int toucheInterractionJoueur(t_ressources RESSOURCES, t_case *caseMatrice, t_player *joueur, t_partie *partie, File_commandes *commandes, int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]) {
    // printf("[ACTION] IDcase %d\n", caseMatrice->id_meuble); // DEBUG

    /// On vérifie si on a une interaction prioritaire avec un meuble spécifique.
    if(b_meubleSpecifique(caseMatrice->id_meuble) == 1) {
        interractionSpecialMeubleSpecifique(partie, caseMatrice, joueur, commandes, recettes);
        if(caseMatrice->id_meuble == MEUBLE_GENERATEUR_ASSIETTE) {
            return 1;
        }
    }

    /// MEUBLE VIDE - MAIN VIDE --> Générateur OU rien
    if (b_objet(caseMatrice->objet) == 0 && b_objet(joueur->objet) == 0) {
        // Si on a un générateur, on prend un objet
        if (caseMatrice->id_meuble != 0) {
            printf("[INTERRACTION] Generateur - prendre un objet\n");
            interractionMeubleGenerateur(caseMatrice, joueur);
        }
        // Sinon on ne fait rien
        else {
            printf("[INTERRACTION] Vide - aucune action\n");
        }
    }

    /// MEUBLE VIDE - MAIN OBJET --> Poser l'objet si possible
    else if (b_objet(caseMatrice->objet) == 0 && b_objet(joueur->objet) == 1) {
        // Demande d'autorisation de poser pour les meubles spécifiques
        if (b_meubleSpecifique(caseMatrice->id_meuble) == 1) {
            if(b_poserObjetMeubleSpecifique(caseMatrice->id_meuble, caseMatrice->objet, joueur->objet)==1) {
                printf("[INTERRACTION] Meuble spe - Poser objet\n");
                echangerObjet(caseMatrice->objet, joueur->objet);
            }
            else {
                printf("[INTERRACTION] Meuble spe - INTERDIT poser objet\n");
            }
        }
        // Sinon on pose l'objet
        else {
            if(caseMatrice->id_meuble == MEUBLE_SOL && B_AUTORISATION_POSER_OBJET_SOL) {
                printf("[INTERRACTION] Main - Poser objet sol\n");
                echangerObjet(caseMatrice->objet, joueur->objet);
            }
            if (caseMatrice->id_meuble != MEUBLE_SOL) {
                printf("[INTERRACTION] Main - Poser objet\n");
                echangerObjet(caseMatrice->objet, joueur->objet);
            }
            else {
                printf("[INTERRACTION] Main - INTERDIT de poser objet\n");
            }

        }
    }

    /// MEUBLE OBJET - MAIN VIDE --> Prendre l'objet si possible
    else if (b_objet(caseMatrice->objet) == 1 && b_objet(joueur->objet) == 0) {
        // Demande d'autorisation de prendre pour les meubles spécifiques
        if (b_meubleSpecifique(caseMatrice->id_meuble) == 1) {
            if(b_prendreObjetMeubleSpecifique(caseMatrice->id_meuble, caseMatrice->objet, joueur->objet) == 1) {
                printf("[ACTION] Meuble sep - Prendre objet\n");
                echangerObjet(caseMatrice->objet, joueur->objet);
                switch (caseMatrice->id_meuble) {

                    case MEUBLE_PLAQUE_DE_CUISSON:
                        partie->music.alarm_playing = 0;
                        partie->music.nbr_alarm_playing--;
                        partie->music.nbr_pan_playing--;
                        if (partie->music.nbr_alarm_playing <= 0) {
                            stop_sample(RESSOURCES.alarm);
                        }
                        if (partie->music.nbr_pan_playing <= 0) {
                            stop_sample(RESSOURCES.sound_poele);
                        }
                        break;

                    case MEUBLE_FRITEUSE:
                        partie->music.alarm_playing = 0;
                        partie->music.nbr_alarm_playing--;
                        partie->music.nbr_fryer_playing--;
                        if (partie->music.nbr_alarm_playing <= 0) {
                            stop_sample(RESSOURCES.alarm);
                        }
                        if (partie->music.nbr_fryer_playing <= 0) {
                            stop_sample(RESSOURCES.sound_friteuse);
                        }
                        break;

                    case MEUBLE_FRITEUSE_ANCIENNE:
                        partie->music.nbr_fryer_playing--;
                        if (partie->music.nbr_fryer_playing <= 0) {
                            stop_sample(RESSOURCES.sound_friteuse);
                        }
                        break;

                    case MEUBLE_FOUR:
                        partie->music.nbr_oven_playing--;
                        if (partie->music.nbr_oven_playing <= 0) {
                            stop_sample(RESSOURCES.sound_four);
                        }
                        break;
                }
            }
            else {
                printf("[ACTION] Meuble spe - INTERDIT prendre objet\n");
            }
        }
        else {
            printf("[ACTION] Main - Prendre objet\n");
            echangerObjet(caseMatrice->objet, joueur->objet);
        }
    }

    /// MEUBLE OBJET - MAIN OBJET --> Combinaison OU echange des objets
    else {
        // Cas particulier très spécifiques de combinaison
        if (combinaisonObjetPrioritaire(partie, caseMatrice->objet, joueur->objet) == 1) {
            printf("[ACTION] Combinaison specifique\n");
            switch (caseMatrice->id_meuble) {

                case MEUBLE_PLAQUE_DE_CUISSON:
                    partie->music.alarm_played = 0;
                    play_sample(RESSOURCES.sound_poele, 128, 128, 1000, FALSE);
                    partie->music.nbr_pan_playing++;
                    break;

                case MEUBLE_FRITEUSE:
                    partie->music.alarm_played = 0;
                    play_sample(RESSOURCES.sound_friteuse, 128, 128, 1000, FALSE);
                    partie->music.nbr_fryer_playing++;
                    break;

                case MEUBLE_FRITEUSE_ANCIENNE:
                    play_sample(RESSOURCES.sound_friteuse, 128, 128, 1000, FALSE);
                    partie->music.nbr_fryer_playing++;
                    break;

                case MEUBLE_FOUR:
                    play_sample(RESSOURCES.sound_four, 128, 128, 1000, FALSE);
                    partie->music.nbr_oven_playing++;

                case MEUBLE_PLAN_DE_TRAVAIL:
                    if (b_Melange_aliment(partie) == 1) {
                        for (short i = 0; i < NOMBRE_OBJETS; i++) {
                            caseMatrice->objet[i] = 0;
                        }
                        caseMatrice->objet[FALAFELS_CRUS] = 1;
                    } else if (b_Melange_aliment(partie) == 2) {
                        for (short i = 0; i < NOMBRE_OBJETS; i++) {
                            caseMatrice->objet[i] = 0;
                        }
                        caseMatrice->objet[BASBOUSSA_CRU] = 1;
                    }
            }
            return 1;
        }

        // On teste la combinaison des objets du meuble vers le joueur
        if (b_objetCombinable(caseMatrice->objet, joueur->objet, partie->permissionsObjets) == 1) {
            // Si on a un meuble spécifique, on vérifie qu'on a le droit de poser l'objet sur le meuble et de récuperer l'objet du meuble
            if (b_meubleSpecifique(caseMatrice->id_meuble) == 1) {
                if (b_echangerObjetMeubleSpecifique(caseMatrice->id_meuble, caseMatrice->objet, joueur->objet) == 1) {
                    printf("[ACTION] Meuble spe - Echanger objet (1)\n");
                    combinaisonObjets(partie, caseMatrice->objet, joueur->objet);
                }
                else {
                    printf("[ACTION] Meuble spe - INTERDIT Echanger objet (1)\n");
                }
            }
            else {
                printf("[ACTION] Meuble spe - Combinaison (1)\n");
                combinaisonObjets(partie, caseMatrice->objet, joueur->objet);
            }
        }
        // On test la combiniaison des objets du joueur vers le meuble
        else if (b_objetCombinable(joueur->objet, caseMatrice->objet, partie->permissionsObjets) == 1) {
            // Si on a un meuble spécifique, on vérifie qu'on a le droit de poser l'objet sur le meuble et de récuperer l'objet du meuble
            if (b_meubleSpecifique(caseMatrice->id_meuble) == 1) {
                if (b_echangerObjetMeubleSpecifique(caseMatrice->id_meuble, caseMatrice->objet, joueur->objet) == 1) {
                    printf("[ACTION] Meuble spe - Echanger objet (2)\n");
                    combinaisonObjets(partie, joueur->objet, caseMatrice->objet);
                }
                else {
                    printf("[ACTION] Meuble spe - INTERDIT Echanger objet (2)\n");
                }
            }
            else {
                printf("[ACTION] Meuble spe - Combinaison (2)\n");
                combinaisonObjets(partie, joueur->objet, caseMatrice->objet);
            }
        }
        // Si aucun test est bon, on test l'échange l'objet.
        else {
            // Si on a un meuble spécifique, on vérifie qu'on a le droit de poser l'objet sur le meuble et de récuperer l'objet du meuble
            if (b_meubleSpecifique(caseMatrice->id_meuble) == 1) {
                if (b_echangerObjetMeubleSpecifique(caseMatrice->id_meuble, caseMatrice->objet, joueur->objet) == 1) {
                    printf("[ACTION] Meuble spe - Echanger objet\n");
                    echangerObjet(caseMatrice->objet, joueur->objet);
                } else {
                    printf("[ACTION] Meuble spe - INTERDIT Echanger objet\n");
                }
            } else {
                printf("[ACTION] Meuble et main - Echanger objet\n");
                echangerObjet(caseMatrice->objet, joueur->objet);
            }
        }
    }
    return 1;
}



//////////////////////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : actionTempsMeublesSpecifique
// Rôle : Gestion des objets sur les meubles ayant une interaction temporelle
//////////////////////////////////////////////////////////////////////////////////////////////

void actionTempsMeublesSpecifique(t_ressources RESSOURCES, t_partie *partie) {
    // printf("[TEMPS] Action temps update !\n"); // DEBUG
    int remettreObjet = 0;

    for (int i = 0; i < NB_LIGNES; ++i) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            // On regarde toutes les cases du niveau et selon le meuble on fait l'action qui suit.

            switch (partie->matrice[i][j].id_meuble) {

                case MEUBLE_PLAQUE_DE_CUISSON:
                    // Si on a une poele sur la plaque, on l'enlève temporairement pour vérifier les conditions de cuisson
                    if (partie->matrice[i][j].objet[POELE] == 1) {
                        remettreObjet = 1;
                        partie->matrice[i][j].objet[POELE] = 0;
                    }
                    // Si on a un objet sur la plaque et c'est un objet qui peut cuire
                    if (b_objet(partie->matrice[i][j].objet) == 1 && b_verrificationPermission(partie->matrice[i][j].objet, partie->permissionsObjets.cuisson) == 1) {
                        printf("[CUISSON] Objet poel cuit\n");
                        if (partie->matrice[i][j].objet[STATU_OBJET] == TICK_CUISSON_PLAQUE_MAX) {
                            partie->matrice[i][j].objet[STATU_OBJET] = 0;
                            incrementationObjetTableau(partie->matrice[i][j].objet);
                            partie->matrice[i][j].objet[POELE + 1] = 0;
                        }
                        else {
                            partie->matrice[i][j].objet[STATU_OBJET]++;
                            printf("[CUISSON] Statu objet plaque de cuisson = %d\n",partie->matrice[i][j].objet[STATU_OBJET]);
                        }
                        if (!partie->music.alarm_playing && !partie->music.alarm_played && partie->music.alarm_must_play) {
                            play_sample(RESSOURCES.alarm, 128, 128, 1000, FALSE);
                            partie->music.nbr_alarm_playing++;
                            partie->music.alarm_playing = 1;
                            partie->music.alarm_played = 1;
                            partie->music.alarm_must_play = 0;
                        }
                    }
                    // On remet la poele si il y en avait une
                    if (remettreObjet == 1) {
                        partie->matrice[i][j].objet[POELE] = 1;
                        remettreObjet = 0;
                    }
                    break;

                case MEUBLE_FRITEUSE:
                    // Si on a une friteuse dans le bac, on l'enlève temporairement pour vérifier les conditions de cuisson
                    if (partie->matrice[i][j].objet[BAC_DE_FRITEUSE] == 1) {
                        remettreObjet = 1;
                        partie->matrice[i][j].objet[BAC_DE_FRITEUSE] = 0;
                    }
                    // Si on a un objet sur la plaque et c'est un objet qui peut cuire
                    if(b_objet(partie->matrice[i][j].objet) == 1 && b_verrificationPermission(partie->matrice[i][j].objet, partie->permissionsObjets.cuisson) == 1) {
                        printf("[CUISSON] Objet friteuse cuit\n");
                        if (partie->matrice[i][j].objet[STATU_OBJET] == TICK_CUISSON_FRITTEUSE_MAX) {
                            partie->matrice[i][j].objet[STATU_OBJET] = 0;
                            incrementationObjetTableau(partie->matrice[i][j].objet);
                            partie->matrice[i][j].objet[BAC_DE_FRITEUSE+1] = 0;
                        }
                        else {
                            partie->matrice[i][j].objet[STATU_OBJET]++;
                            printf("[CUISSON] Statu objet friteuse = %d\n",partie->matrice[i][j].objet[STATU_OBJET]);
                        }
                        if (!partie->music.alarm_playing && !partie->music.alarm_played && partie->music.alarm_must_play) {
                            play_sample(RESSOURCES.alarm, 128, 128, 1000, FALSE);
                            partie->music.nbr_alarm_playing++;
                            partie->music.alarm_playing = 1;
                            partie->music.alarm_played = 1;
                            partie->music.alarm_must_play = 0;
                        }
                    }
                    // On remet la friteuse si il y en avait une
                    if (remettreObjet == 1) {
                        partie->matrice[i][j].objet[BAC_DE_FRITEUSE] = 1;
                        remettreObjet = 0;
                    }
                    break;

                case MEUBLE_FRITEUSE_ANCIENNE:
                    if(partie->matrice[i][j].objet[FALAFELS_CRUS] == 1 || partie->matrice[i][j].objet[FALAFELS_CUITS] == 1) {
                        printf("[TIME] Cuisson\n");
                        if (partie->matrice[i][j].objet[STATU_OBJET] == TICK_CUISSON_FRITTEUSE_MAX) {
                            partie->matrice[i][j].objet[STATU_OBJET] = 0;
                            incrementationObjetTableau(partie->matrice[i][j].objet);
                        }
                        else {
                            partie->matrice[i][j].objet[STATU_OBJET]++;
                            printf("[CUISSON] Friteuse Ancienne statu objet = %d\n",partie->matrice[i][j].objet[STATU_OBJET]);
                        }
                    }
                    break;

                case MEUBLE_FOUR:
                    if(partie->matrice[i][j].objet[BASBOUSSA_CRU] == 1 || partie->matrice[i][j].objet[BASBOUSSA_CUIT] == 1) {
                        printf("[TIME] Cuisson\n");
                        if (partie->matrice[i][j].objet[STATU_OBJET] == TICK_CUISSON_FOUR_MAX) {
                            partie->matrice[i][j].objet[STATU_OBJET] = 0;
                            incrementationObjetTableau(partie->matrice[i][j].objet);
                        }
                        else {
                            partie->matrice[i][j].objet[STATU_OBJET]++;
                            printf("[CUISSON] Four statu objet = %d\n",partie->matrice[i][j].objet[STATU_OBJET]);
                        }
                    }
                    break;
            }
        }
    }
}




//////////////////////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : toucheActionJoueur
// Rôle : Gestion des objets quand on appuie sur la touche action face a un meuble spécifique
//////////////////////////////////////////////////////////////////////////////////////////////

void toucheActionJoueur(t_ressources RESSOURCES, t_case *caseMatrice, t_player *joueur, t_partie *partie) {
    printf("[ACTION] Touche presse !\n");

    switch (caseMatrice->id_meuble) {

        case MEUBLE_PLANCHE_A_COUPER:
            if(b_verrificationPermission(caseMatrice->objet, partie->permissionsObjets.decoupage) == 1 && b_objet(joueur->objet) == 0 && b_objet(caseMatrice->objet) == 1) {
                printf("[ACTION] Objet decoupe\n");
                if (caseMatrice->objet[STATU_OBJET] == NOMBRE_CLICK_COUPER-1) {
                    caseMatrice->objet[STATU_OBJET] = 0;
                    incrementationObjetTableau(caseMatrice->objet);
                }
                else {
                    caseMatrice->objet[STATU_OBJET]++;
                    printf("[ACTION] Decoupage - statu objet = %d\n",caseMatrice->objet[STATU_OBJET]);
                }
                play_sample(RESSOURCES.sound_planche, 160, 128, 1000, FALSE);
            }
            break;
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : interractionSpecialMeubleSpecifique
// Rôle : Gestion des interractions spéciales aux meubles spécifiques
//////////////////////////////////////////////////////////////////////////////////////////////

void interractionSpecialMeubleSpecifique(t_partie *partie, t_case *caseMatrice, t_player *joueur, File_commandes *commandes, int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]) {

    switch (caseMatrice->id_meuble) {

        case MEUBLE_GENERATEUR_ASSIETTE:
            if(partie->nombre_assiettes_restante > 0 && b_objet(joueur->objet) == 0) {
                joueur->objet[ASSIETTE_PROPRE] = 1;
                partie->nombre_assiettes_restante--;
            }

            break;

        case MEUBLE_POUBELLE:
            printf("[ACTION - POUBELLE ");
            if (joueur->objet[ASSIETTE_PROPRE] == 1) {
                supprimerObjet(joueur->objet);
                joueur->objet[ASSIETTE_PROPRE] = 1;
            }
            else if (joueur->objet[POELE] == 1) {
                supprimerObjet(joueur->objet);
                joueur->objet[POELE] = 1;
            }
            else if (joueur->objet[BAC_DE_FRITEUSE] == 1) {
                supprimerObjet(joueur->objet);
                joueur->objet[BAC_DE_FRITEUSE] = 1;
            }
            else {
                supprimerObjet(joueur->objet);
            }
            break;

        case MEUBLE_RENDU : // ACTION MEUBLE RENDU
        // Affichage de l'inventaire du joueur lors du rendu de la commande
        for(int i = 1; i < NOMBRE_OBJETS; i++){
            printf("%d", joueur->objet[i]);
        }
            if (joueur->objet[ASSIETTE_PROPRE] == 1) {
                compareCommande(commandes, recettes, joueur->objet); // Vérifie que la commande soit bonne

                supprimerObjet(joueur->objet);
                partie->nombre_assiettes_restante++;

                if (commandes->first->done == 1) { // Si la commande est bonne
                    joueur->score = joueur->score + 10 * commandes->first->chrono;
                    commandes->score = partie->joueur1.score + partie->joueur2.score;
                }
            }
            break;
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////
// Nom du sous-programme : interractionMeubleGenerateur
// Rôle : Gestion de la générations des objets simples
// Commentaire : les assiettes ont une gestion spécifique dans meuble spécifique
//////////////////////////////////////////////////////////////////////////////////////////////

void interractionMeubleGenerateur(t_case *caseMatrice, t_player *joueur) {
    switch (caseMatrice->id_meuble) {
        case MEUBLE_GENERATEUR_PAIN_BURGER :
            joueur->objet[PAIN_BURGER] = 1;
            break;
        case MEUBLE_GENERATEUR_SALADE :
            joueur->objet[SALADE] = 1;
            break;
        case MEUBLE_GENERATEUR_TOMATE :
            joueur->objet[TOMATE] = 1;
            break;
        case MEUBLE_GENERATEUR_FROMAGE :
            joueur->objet[FROMAGE] = 1;
            break;
        case MEUBLE_GENERATEUR_STEAK :
            joueur->objet[STEAK_CRU] = 1;
            break;
        case MEUBLE_GENERATEUR_PATATE :
            joueur->objet[PATATE] = 1;
            break;
        case MEUBLE_GENERATEUR_POISSON :
            joueur->objet[POISSON_CRU] = 1;
            break;
        case MEUBLE_GENERATEUR_FEVES :
            joueur->objet[FEVES] = 1;
            break;
        case MEUBLE_GENERATEUR_OIGNONS :
            joueur->objet[OIGNON] = 1;
            break;
        case MEUBLE_GENERATEUR_AIL :
            joueur->objet[AIL] = 1;
            break;
        case MEUBLE_GENERATEUR_EPICES :
            joueur->objet[EPICES] = 1;
            break;
        case MEUBLE_GENERATEUR_SEMOULE :
            joueur->objet[SEMOULE] = 1;
            break;
        case MEUBLE_GENERATEUR_FARINE :
            joueur->objet[FARINE] = 1;
            break;
        case MEUBLE_GENERATEUR_SUCRE :
            joueur->objet[SUCRE] = 1;
            break;
        case MEUBLE_GENERATEUR_MIEL :
            joueur->objet[MIEL] = 1;
            break;
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////
///
///                                    FONCTIONS DE TEST
///
//////////////////////////////////////////////////////////////////////////////////////////////

//// Verification si le tableau objet a un objet(1) ou si il est vide (0)
int b_objet(short objet[NOMBRE_OBJETS]) {
    for (int i = 1; i < NOMBRE_OBJETS; i++) {
        if (objet[i] != 0) {
            return 1;
        }
    }
    return 0;
}

//// Verification si le meuble est spécifique (1) on si c'est un meuble simple (0)
int b_meubleSpecifique(int IDcaseMatrice) {
    if (
            IDcaseMatrice == MEUBLE_PLAQUE_DE_CUISSON
            || IDcaseMatrice == MEUBLE_FRITEUSE
            || IDcaseMatrice == MEUBLE_FRITEUSE_ANCIENNE
            || IDcaseMatrice == MEUBLE_FOUR
            || IDcaseMatrice == MEUBLE_GENERATEUR_ASSIETTE
            || IDcaseMatrice == MEUBLE_POUBELLE
            || IDcaseMatrice == MEUBLE_PLANCHE_A_COUPER
            || IDcaseMatrice == MEUBLE_RENDU
            ) {
        return 1;
    }
    else {
        return 0;
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////
///
///                                    FONCTIONS DE PERMISSIONS
///
//////////////////////////////////////////////////////////////////////////////////////////////

/// Vérification des permissions pour poser un objet sur un meuble spécifique
int b_poserObjetMeubleSpecifique (int MeubleID, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]) {
    switch (MeubleID) {

        case MEUBLE_PLANCHE_A_COUPER:
            if (objetJoueur[ASSIETTE_PROPRE] == 1) {
                return 0;
            }
            break;

        case MEUBLE_PLAQUE_DE_CUISSON:
            if(objetJoueur[POELE] == 0) {
                return 0;
            }
            break;

        case MEUBLE_FRITEUSE:
            if(objetJoueur[BAC_DE_FRITEUSE] == 0) {
                return 0;
            }
            break;

        case MEUBLE_RENDU:
            if(objetJoueur[ASSIETTE_PROPRE] == 0) {
                return 0;
            }
            break;

        case MEUBLE_POUBELLE:
            return 0;
    }
    return 1;
}

/// Vérification des permissions pour prendre un objet d'un meuble spécifique
int b_prendreObjetMeubleSpecifique (int MeubleID, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]) {
    switch (MeubleID) {
        case MEUBLE_PLANCHE_A_COUPER:
            if (objetMatrice[STATU_OBJET] != 0) {
                return 0;
            }
            break;

        case MEUBLE_PLAQUE_DE_CUISSON:
            break;

        case MEUBLE_FRITEUSE:
            break;

        case MEUBLE_FRITEUSE_ANCIENNE:
            break;

        case MEUBLE_FOUR:
            break;

        case MEUBLE_GENERATEUR_ASSIETTE:
            return 1;

        case MEUBLE_POUBELLE:
            return 0;

        case MEUBLE_RENDU:
            return 0;
    }
    return 1;
}

/// Vérification des permissions pour echanger deux objets
int b_echangerObjetMeubleSpecifique (int MeubleID, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]) {
    if (b_prendreObjetMeubleSpecifique(MeubleID, objetMatrice, objetJoueur) == 1 &&
        b_poserObjetMeubleSpecifique(MeubleID, objetMatrice, objetJoueur) == 1) {
        return 1;
    }
    return 0;
}

/// Vérification des permissions pour combiner deux objets
int b_objetCombinable(short objet1[NOMBRE_OBJETS], short objet2[NOMBRE_OBJETS], t_permissionsObjets permissionsObjets) {
    if (b_objetDejaPresent(objet1, objet2) == 1) {
        return 0;
    }
    if ((objet1[POELE] == 1 && objet2[POELE] == 1) || (objet1[BAC_DE_FRITEUSE] == 1 && objet2[BAC_DE_FRITEUSE] == 1) || (objet1[PAIN_BURGER] == 1 && objet2[PAIN_BURGER] == 1) || (objet1[ASSIETTE_PROPRE] == 1 && objet2[ASSIETTE_PROPRE] == 1) ){
        return 0;
    }
    if ((objet1[POELE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.poel) == 1)) {
        return 1;
    }
    if ((objet1[BAC_DE_FRITEUSE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.friteuse) == 1)) {
        return 1;
    }
    if ((objet1[MEUBLE_FRITEUSE_ANCIENNE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.friteuse_ancienne) == 1)) {
        return 1;
    }
    if ((objet1[MEUBLE_FOUR] == 1) && (b_verrificationPermission(objet2, permissionsObjets.four) == 1)) {
        return 1;
    }
    if ((objet1[PAIN_BURGER] == 1) && (b_verrificationPermission(objet2, permissionsObjets.painBurger) == 1)) {
        return 1;
    }
    if ((objet1[ASSIETTE_PROPRE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.assiette) == 1)) {
        return 1;
    }
    if ((objet1[FEVES_COUPE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.falafels) == 1)) {
        return 1;
    }
    if ((objet1[AIL_COUPE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.falafels) == 1)) {
        return 1;
    }
    if ((objet1[OIGNON_COUPE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.falafels) == 1)) {
        return 1;
    }
    if ((objet1[EPICES] == 1) && (b_verrificationPermission(objet2, permissionsObjets.falafels) == 1)) {
        return 1;
    }
    if ((objet1[SEMOULE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.basboussa) == 1)) {
        return 1;
    }
    if ((objet1[FARINE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.basboussa) == 1)) {
        return 1;
    }
    if ((objet1[SUCRE] == 1) && (b_verrificationPermission(objet2, permissionsObjets.basboussa) == 1)) {
        return 1;
    }
    if ((objet1[MIEL] == 1) && (b_verrificationPermission(objet2, permissionsObjets.basboussa) == 1)) {
        return 1;
    }
    return 0;
}

/// Vérification des permissions pour les interractions, actions, combinaisons, etc... avec une liste de permission
int b_verrificationPermission(short objet[NOMBRE_OBJETS], short permissionObjet[NOMBRE_OBJETS]) {
    for (int i = 1; i < NOMBRE_OBJETS; i++) {
        if (objet[i] == 1 && permissionObjet[i] == 0) {
            return 0; // Combinaison interdit
        }
    }
    return 1; // Combinaison autorisé
}

/// Vérification si un objet est déjà présent dans un autre objet
int b_objetDejaPresent (short objet1[NOMBRE_OBJETS], short objet2[NOMBRE_OBJETS]) {
    for (int i = 1; i < NOMBRE_OBJETS; i++) {
        if (objet1[i] == 1 && objet2[i] == 1) {
            return 1;
        }
    }
    return 0;
}

/// Vérification des permissions pour mélanger les ingrédients lvl4
short b_Melange_aliment(t_partie *partie) {
    for (short i=0; i<NB_LIGNES; i++) {
        for (short j=0; j<NB_COLONNES; j++) {
            if (partie->matrice[i][j].objet[FEVES_COUPE]==1 && partie->matrice[i][j].objet[AIL_COUPE]==1 && partie->matrice[i][j].objet[OIGNON_COUPE]==1 && partie->matrice[i][j].objet[EPICES]==1) {
                return 1;
            }
            else if (partie->matrice[i][j].objet[SEMOULE]==1 && partie->matrice[i][j].objet[FARINE]==1 && partie->matrice[i][j].objet[SUCRE]==1 && partie->matrice[i][j].objet[MIEL]==1) {
                return 2;
            }
        }
    }
    return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////
///
///                                    FONCTIONS OBJETS
///
//////////////////////////////////////////////////////////////////////////////////////////////

/// Met tout un tableau objet à 0
void supprimerObjet(short objet[NOMBRE_OBJETS]) {
    for (int i = 0; i < NOMBRE_OBJETS; i++) {
        objet[i] = 0;
    }
}

/// Echange deux objets entre le joueur et le meuble
void echangerObjet(short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]) {

    if(b_objet(objetMatrice) == 0 && b_objet(objetJoueur) == 0) { // Il n'y a aucun objet
        return;
    }
    else if (b_objet(objetMatrice) == 0) {                         // Il y a un objet
        for (int i = 0; i < NOMBRE_OBJETS; i++) {
            objetMatrice[i] = objetJoueur[i];
        }
        supprimerObjet(objetJoueur);
    }
    else if (b_objet(objetJoueur) == 0) {                         // Il y a un objet
        for (int i = 0; i < NOMBRE_OBJETS; i++) {
            objetJoueur[i] = objetMatrice[i];
        }
        supprimerObjet(objetMatrice);
    }
    else {                                                   // Il y a 2 objets
        short objetTemp[NOMBRE_OBJETS];

        for (int i = 0; i < NOMBRE_OBJETS; i++) {
            objetTemp[i] = objetMatrice[i];
            objetMatrice[i] = objetJoueur[i];
            objetJoueur[i] = objetTemp[i];
        }
    }
}

/// Combinaison spécifique de deux objets entre le joueur et le meuble
int combinaisonObjetPrioritaire(t_partie* partie, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]) {
    // Si on a deux fois le meme objet
    if(b_objetDejaPresent(objetMatrice, objetJoueur) == 1) {
        return 0;
    }
    if(objetJoueur[PAIN_BURGER] == 1 && objetMatrice[ASSIETTE_PROPRE] == 1) {
        combinaisonObjets(partie, objetMatrice, objetJoueur);
        supprimerObjet(objetJoueur);
        return 1;
    }

    if ((objetJoueur[PAIN_BURGER] || objetJoueur[ASSIETTE_PROPRE]) && (objetMatrice[POELE] == 1 || objetMatrice[BAC_DE_FRITEUSE] == 1)) {
        if (objetMatrice[STEAK_CUIT] == 1) {
            objetMatrice[STEAK_CUIT] = 0;
            objetJoueur[STEAK_CUIT] = 1;
        }
        else if (objetMatrice[POISSON_CUIT] == 1) {
            objetMatrice[POISSON_CUIT] = 0;
            objetJoueur[POISSON_CUIT] = 1;
        }
        else if (objetMatrice[FRITES_CUITES] == 1) {
            objetMatrice[FRITES_CUITES] = 0;
            objetJoueur[FRITES_CUITES] = 1;
        }
        objetJoueur[STATU_OBJET] = 0; // On reset le statu des objets
        objetMatrice[STATU_OBJET] = 0; // On reset le statu des objets
        return 1;
    }
    //
    if ((objetJoueur[POELE] == 1 || objetJoueur[BAC_DE_FRITEUSE] == 1) &&  (objetMatrice[PAIN_BURGER] || objetMatrice[ASSIETTE_PROPRE]) ) {
        if (objetJoueur[STEAK_CUIT] == 1) {
            objetMatrice[STEAK_CUIT] = 1;
            objetJoueur[STEAK_CUIT] = 0;
        }
        else if (objetJoueur[POISSON_CUIT] == 1) {
            objetMatrice[POISSON_CUIT] = 1;
            objetJoueur[POISSON_CUIT] = 0;
        }
        else if (objetJoueur[FRITES_CUITES] == 1) {
            objetMatrice[FRITES_CUITES] = 1;
            objetJoueur[FRITES_CUITES] = 0;
        }
        objetJoueur[STATU_OBJET] = 0; // On reset le statu des objets
        objetMatrice[STATU_OBJET] = 0; // On reset le statu des objets
        return 1;
    }

    // On met un steack cuit (avec une poel) dans une assiette ou un burger
    if (objetJoueur[POELE] == 1 && objetJoueur[STEAK_CUIT] == 1 &&
        (objetMatrice[ASSIETTE_PROPRE] == 1 || objetMatrice[PAIN_BURGER] == 1)) {
        objetJoueur[STEAK_CUIT] = 0;
        objetMatrice[STEAK_CUIT] = 1;
        objetJoueur[STATU_OBJET] = 0; // On reset le statu des objets
        objetMatrice[STATU_OBJET] = 0; // On reset le statu des objets
        return 1;
    }
    // On met des frittes cuites (avec bac) dans une assiette
    else if (objetJoueur[BAC_DE_FRITEUSE] == 1 && objetJoueur[FRITES_CUITES] == 1 &&
            (objetMatrice[ASSIETTE_PROPRE] == 1)) {
        objetJoueur[FRITES_CUITES] = 0;
        objetMatrice[FRITES_CUITES] = 1;
        objetJoueur[STATU_OBJET] = 0; // On reset le statu des objets
        objetMatrice[STATU_OBJET] = 0; // On reset le statu des objets
        return 1;
    }
    // On met un steak découpé dans une poele
    else if (objetJoueur[STEAK_DECOUPE] == 1 && objetMatrice[POELE] == 1) {
        objetJoueur[STEAK_DECOUPE] = 0;
        objetMatrice[STEAK_DECOUPE] = 1;
        return 1;
    }
    // On met des frittes crues dans un bac
    else if (objetJoueur[FRITES_CRUES] == 1 && objetMatrice[BAC_DE_FRITEUSE] == 1) {
        objetJoueur[FRITES_CRUES] = 0;
        objetMatrice[FRITES_CRUES] = 1;
        return 1;
    }
    else if (objetJoueur[FEVES_COUPE] == 1 || objetJoueur[AIL_COUPE] == 1 || objetJoueur[OIGNON_COUPE] == 1 || objetJoueur[EPICES] == 1) {
        if (objetJoueur[FEVES_COUPE]) {
            objetJoueur[FEVES_COUPE] = 0;
            objetMatrice[FEVES_COUPE] = 1;
        }
        else if (objetJoueur[AIL_COUPE]) {
            objetJoueur[AIL_COUPE] = 0;
            objetMatrice[AIL_COUPE] = 1;
        }
        else if (objetJoueur[OIGNON_COUPE]) {
            objetJoueur[OIGNON_COUPE] = 0;
            objetMatrice[OIGNON_COUPE] = 1;
        }
        else if (objetJoueur[EPICES]) {
            objetJoueur[EPICES] = 0;
            objetMatrice[EPICES] = 1;
        }
        return 1;
    }
    else if (objetJoueur[SEMOULE] == 1 || objetJoueur[FARINE] == 1 || objetJoueur[SUCRE] == 1 || objetJoueur[MIEL] == 1) {
        if (objetJoueur[SEMOULE]) {
            objetJoueur[SEMOULE] = 0;
            objetMatrice[SEMOULE] = 1;
        }
        else if (objetJoueur[FARINE]) {
            objetJoueur[FARINE] = 0;
            objetMatrice[FARINE] = 1;
        }
        else if (objetJoueur[SUCRE]) {
            objetJoueur[SUCRE] = 0;
            objetMatrice[SUCRE] = 1;
        }
        else if (objetJoueur[MIEL]) {
            objetJoueur[MIEL] = 0;
            objetMatrice[MIEL] = 1;
        }
        return 1;
    }
    // On met des falafels crus dans la marmite de friture
    else if (objetJoueur[FALAFELS_CRUS] == 1 && objetMatrice[MEUBLE_FRITEUSE_ANCIENNE] == 1) {
        objetJoueur[FALAFELS_CRUS] = 0;
        objetMatrice[FALAFELS_CRUS] = 1;
        return 1;
    }
    // On met un basboussa cru dans le four
    else if (objetJoueur[BASBOUSSA_CRU] == 1 && objetMatrice[MEUBLE_FOUR] == 1) {
        objetJoueur[BASBOUSSA_CRU] = 0;
        objetMatrice[BASBOUSSA_CRU] = 1;
        return 1;
    }
    else {
        return 0;
    }
}

/// Combinaison de deux objets entre le joueur et le meuble
void combinaisonObjets(t_partie* partie, short objetMatrice[NOMBRE_OBJETS], short objetJoueur[NOMBRE_OBJETS]) {
    if (objetMatrice[POELE] == 1 && objetJoueur[PAIN_BURGER]);
    if (objetMatrice[ASSIETTE_PROPRE] == 1 || objetMatrice[BAC_DE_FRITEUSE] == 1 || objetMatrice[POELE] == 1 || objetMatrice[PAIN_BURGER] == 1) {
        for (int i = 0; i < NOMBRE_OBJETS; ++i) {
            objetMatrice[i] += objetJoueur[i];
        }
        supprimerObjet(objetJoueur);
    }
}

/// Incrémente les objets d'un tableau, permet de cuire, de couper, etc...
void incrementationObjetTableau(short objet[NOMBRE_OBJETS]) {

    int objetTemp[NOMBRE_OBJETS];
    for (int i = 0; i < NOMBRE_OBJETS; ++i) {
        objetTemp[i] = objet[i];
    }
    for (int i = 1; i < NOMBRE_OBJETS; ++i) {
        objet[i] = objetTemp[i-1];
    }
}



//////////////////////////////////////////////////////////////////////////////////////////////
///
///                       FONCTIONS AFFICHAGE ET DEPLACEMENT
///
//////////////////////////////////////////////////////////////////////////////////////////////

#define TAILLE_STATU_OBJET_X 50
#define TAILLE_STATU_OBJET_Y 10
#define DECALAGE_STATU_OBJET_X 10
#define DECALAGE_STATU_OBJET_Y -40
#define BORDURE_JAUGE 2
#define DECALAGE_BARRE 1

void afficherStatuObjets(BITMAP *buffer, t_partie *partie) {
    int statuObjet;
    int incrementJaugeCuisson = (TAILLE_STATU_OBJET_X - 2*BORDURE_JAUGE) / TICK_CUISSON_PLAQUE_MAX; // On calcule l'incrementation de la jauge, taille de la jauge / nombre de tick max.
    int incrementJaugeDecoupage = (TAILLE_STATU_OBJET_X - 2*BORDURE_JAUGE) / NOMBRE_CLICK_COUPER+DECALAGE_BARRE; // On calcule l'incrementation de la jauge, taille de la jauge / nombre de tick max.
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            statuObjet = partie->matrice[i][j].objet[STATU_OBJET];
            int couleurBarre = couleurVert();

            if (partie->matrice[i][j].objet[STEAK_CUIT] == 1 || partie->matrice[i][j].objet[FRITES_CUITES] == 1 || partie->matrice[i][j].objet[FALAFELS_CUITS] == 1 || partie->matrice[i][j].objet[BASBOUSSA_CUIT] == 1|| partie->matrice[i][j].objet[POISSON_CUIT] == 1) {
                couleurBarre = couleurRouge();
                if (!partie->music.alarm_playing && !partie->music.alarm_played && (partie->matrice[i][j].id_meuble == MEUBLE_PLAQUE_DE_CUISSON || partie->matrice[i][j].id_meuble == MEUBLE_FRITEUSE) ) {
                    partie->music.alarm_must_play = 1;
                }
            }

            if ((partie->matrice[i][j].id_meuble == MEUBLE_PLAQUE_DE_CUISSON || partie->matrice[i][j].id_meuble == MEUBLE_FRITEUSE || partie->matrice[i][j].id_meuble == MEUBLE_FOUR || partie->matrice[i][j].id_meuble == MEUBLE_FRITEUSE_ANCIENNE) && partie->matrice[i][j].objet[STATU_OBJET] != 0) {
                rectfill(buffer, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+TAILLE_STATU_OBJET_X, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+TAILLE_STATU_OBJET_Y, couleurGrisTresClair());
                rectfill(buffer, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+BORDURE_JAUGE, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+BORDURE_JAUGE, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+TAILLE_STATU_OBJET_X-BORDURE_JAUGE, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+TAILLE_STATU_OBJET_Y-BORDURE_JAUGE, couleurNoir());
                rectfill(buffer, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+BORDURE_JAUGE, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+BORDURE_JAUGE, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+BORDURE_JAUGE+((statuObjet)*incrementJaugeCuisson), i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+TAILLE_STATU_OBJET_Y-BORDURE_JAUGE, couleurBarre);
            }
            if (partie->matrice[i][j].id_meuble == MEUBLE_PLANCHE_A_COUPER && partie->matrice[i][j].objet[STATU_OBJET] != 0) {
                rectfill(buffer, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+TAILLE_STATU_OBJET_X, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+TAILLE_STATU_OBJET_Y, couleurGrisTresClair());
                rectfill(buffer, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+BORDURE_JAUGE, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+BORDURE_JAUGE, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+TAILLE_STATU_OBJET_X-BORDURE_JAUGE, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+TAILLE_STATU_OBJET_Y-BORDURE_JAUGE, couleurNoir());
                rectfill(buffer, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+BORDURE_JAUGE, i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+BORDURE_JAUGE, j*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_X+BORDURE_JAUGE+((statuObjet)*incrementJaugeDecoupage), i*NB_PIXELS_CASE+DECALAGE_STATU_OBJET_Y+TAILLE_STATU_OBJET_Y-BORDURE_JAUGE, couleurBarre);
            }
        }
    }
}



/*
if(tmp->chrono > TEMPS_COMMANDES/2){
            r = 255 - (255/(TEMPS_COMMANDES/2))*(tmp->chrono-tmp->chrono/2);
            g = 255;
        }
        else if(tmp->chrono == TEMPS_COMMANDES/2){
            r = 255;
            g = 255;
        }
        else if(tmp->chrono < TEMPS_COMMANDES/2){
            r = 255;
            g = (255/(TEMPS_COMMANDES/2))*(tmp->chrono);
        }
        b = 0;
 */

BITMAP* imageObjet(t_ressources RESSOURCES, int id_objet) {
    switch (id_objet) {
        case PAIN_BURGER      : { break; }
        case STATU_OBJET      : { break; }
        case ASSIETTE_PROPRE  : { return RESSOURCES.assiette_propre; }
////////case ASSIETTE_SALE    : { return RESSOURCES.;                }
        case POELE            : { return RESSOURCES.poele;           }
        case BAC_DE_FRITEUSE  : { return RESSOURCES.bac_de_friteuse; }
        case SALADE           : { return RESSOURCES.salade;          }
        case SALADE_COUPE     : { return RESSOURCES.salade_coupe;    }
        case TOMATE           : { return RESSOURCES.tomates;         }
        case TOMATE_COUPE     : { return RESSOURCES.tomates_coupe;   }
        case FROMAGE          : { return RESSOURCES.fromage;         }
        case FROMAGE_COUPE    : { return RESSOURCES.fromage_coupe;   }
        case STEAK_CRU        : { return RESSOURCES.steak_cru;       }
        case STEAK_DECOUPE    : { return RESSOURCES.steak_decoupe;   }
        case STEAK_CUIT       : { return RESSOURCES.steak_cuit;      }
        case STEAK_CRAME      : { return RESSOURCES.steak_crame;     }
        case PATATE           : { return RESSOURCES.patate_crue;     }
        case FRITES_CRUES     : { return RESSOURCES.frites_crue;     }
        case FRITES_CUITES    : { return RESSOURCES.frites_cuite;    }
        case FRITES_CRAMEES   : { return RESSOURCES.frites_crame;    }
////////case POISSON_CRU      : { return RESSOURCES.poisson_crue;    }
////////case POISSON_COUPE    : { return RESSOURCES.poisson_coupe;   }
////////case POISSON_CUIT     : { return RESSOURCES.poisson_cuit;    }
////////case POISSON_CRAME    : { return RESSOURCES.poisson_crame;   }

// Objets niveau 4
        case FALAFELS_CRUS    : { return RESSOURCES.falafels_crus;   }
        case FALAFELS_CUITS   : { return RESSOURCES.falafels_cuits;  }
        case FALAFELS_CRAMES  : { return RESSOURCES.falafels_crames; }
        case FEVES            : { return RESSOURCES.feves;           }
        case FEVES_COUPE      : { return RESSOURCES.feves_coupees;   }
        case OIGNON           : { return RESSOURCES.oignon;          }
        case OIGNON_COUPE     : { return RESSOURCES.oignon_coupe;    }
        case AIL              : { return RESSOURCES.ail;             }
        case AIL_COUPE        : { return RESSOURCES.ail_coupe;       }
        case EPICES           : { return RESSOURCES.epices;          }
        case BASBOUSSA_CRU    : { return RESSOURCES.basboussa_cru;   }
        case BASBOUSSA_CUIT   : { return RESSOURCES.basboussa_cuit;  }
        case BASBOUSSA_CRAME  : { return RESSOURCES.basboussa_crame; }
        case SEMOULE          : { return RESSOURCES.semoule;         }
        case FARINE           : { return RESSOURCES.farine;          }
        case SUCRE            : { return RESSOURCES.sucre;           }
        case MIEL             : { return RESSOURCES.miel;            }

       default: {
            allegro_message("ERREUR : id objet inconnu pour la recuperation de son image: %d",id_objet);
            allegro_exit();
            exit(EXIT_FAILURE);
            break;
        }
    }
    return NULL;
}


void dessineMatriceObjets(t_ressources RESSOURCES, BITMAP *buffer, short objetMatrice[NOMBRE_OBJETS], int origX, int origY, int id_meuble, int bJoueur, int orientationJoueur) {
    BITMAP* tmp = NULL;
    int nb = 0;
    int bBurger = 0;
    int bSurMeubleHaut = bMeubleHaut(id_meuble);
    int bPoele = (id_meuble==MEUBLE_PLAQUE_DE_CUISSON);
    int deltaX = 0;
    int deltaY = 0;
    if (bSurMeubleHaut==1) deltaY = DECALAGE_EFFET_3D;

    for (int id_objet = 1; id_objet < NOMBRE_OBJETS; id_objet++) {
        if (objetMatrice[id_objet] > 0) {
            tmp = imageObjet(RESSOURCES,id_objet);

            if (id_objet==POELE) {
                bPoele = 1;
            }

            if ((id_objet==POELE) && (id_meuble==MEUBLE_PLAQUE_DE_CUISSON)) {
                deltaX += 10;
                deltaY += -6;
            }
            if (( (id_objet==STEAK_CRAME) || (id_objet==STEAK_CUIT) || (id_objet==STEAK_DECOUPE) )  && bPoele) {
                if ((bJoueur==1) && (orientationJoueur!=1)) deltaX += 10; else deltaX -= 10;
                deltaY += 0;
            }
            if (id_objet==PAIN_BURGER) {
                bBurger=1;
                tmp = RESSOURCES.pain_burger_bas;
            }
            if (tmp!=NULL) {
                if ((bJoueur==1) && (bPoele==1) && (orientationJoueur!=1))
                    draw_sprite_h_flip(buffer, tmp, origX+deltaX,origY+deltaY-nb*4);
                else
                    masked_blit(tmp,buffer, 0,0,origX+deltaX,origY+deltaY-nb*4,tmp->w,tmp->h);
                nb++;
            }
        }
    }
    if (bBurger==1) {
        tmp = RESSOURCES.pain_burger_haut;
        masked_blit(tmp,buffer, 0,0,origX,origY+deltaY-nb*4,tmp->w,tmp->h);
    }
}

void dessineObjetsSurPlateau(t_ressources RESSOURCES, BITMAP *buffer, t_case matrice[NB_LIGNES][NB_COLONNES], int bDessineEnHauteur) {
    int id_meuble = 0;
    int b_meubleHaut = 0;
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            id_meuble = matrice[i][j].id_meuble;
            b_meubleHaut = bMeubleHaut(id_meuble);
            if (b_meubleHaut==bDessineEnHauteur) dessineMatriceObjets(RESSOURCES, buffer,matrice[i][j].objet,j*NB_PIXELS_CASE,i*NB_PIXELS_CASE, id_meuble,0,0);
        }
    }
}

void  dessineObjetsPlateauSurSol(t_ressources RESSOURCES, BITMAP *buffer, t_case matrice[NB_LIGNES][NB_COLONNES]) {
    dessineObjetsSurPlateau(RESSOURCES, buffer, matrice, 0);
}
void  dessineObjetsPlateauEnHauteur(t_ressources RESSOURCES, BITMAP *buffer, t_case matrice[NB_LIGNES][NB_COLONNES]) {
    dessineObjetsSurPlateau(RESSOURCES, buffer, matrice, 1);
}


///-----------------------------------------------------------------------------------///
///                            Fonctions pour les Meubles                             ///
///-----------------------------------------------------------------------------------///

int bMeubleExiste(int idMeuble) {

    if ( idMeuble == MEUBLE_SOL_SPAWN_JOUEUR1        ) return 1;
    if ( idMeuble == MEUBLE_SOL_SPAWN_JOUEUR2        ) return 1;
    if ( idMeuble == MEUBLE_SOL                      ) return 1;
    if ( idMeuble == MEUBLE_PLAN_DE_TRAVAIL          ) return 1;
    if ( idMeuble == MEUBLE_TABLE_GRISE              ) return 1;
    if ( idMeuble == MEUBLE_PLANCHE_A_COUPER         ) return 1;
    if ( idMeuble == MEUBLE_POUBELLE                 ) return 1;
    if ( idMeuble == MEUBLE_PLAQUE_DE_CUISSON        ) return 1;
    if ( idMeuble == MEUBLE_FRITEUSE                 ) return 1;
    if ( idMeuble == MEUBLE_FRITEUSE_ANCIENNE        ) return 1;
    if ( idMeuble == MEUBLE_FOUR                     ) return 1;
    if ( idMeuble == MEUBLE_RENDU                    ) return 1;

    if ( idMeuble == MEUBLE_GENERATEUR_PAIN_BURGER   ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_SALADE        ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_TOMATE        ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_FROMAGE       ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_STEAK         ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_PATATE        ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_POISSON       ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_ASSIETTE      ) return 1;

    // Meubles niveau 4
    if ( idMeuble == MEUBLE_FRESQUE_EGYPTIENNE       ) return 1;
    if ( idMeuble == MEUBLE_PALMIER                  ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_FEVES         ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_OIGNONS       ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_AIL           ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_EPICES        ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_SEMOULE       ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_FARINE        ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_SUCRE         ) return 1;
    if ( idMeuble == MEUBLE_GENERATEUR_MIEL          ) return 1;

    allegro_message("ERREUR : id meuble inconnu dans le fichier texte de niveau: %d",idMeuble);
    return 0;
}

int bMeubleHaut(int idMeuble) {
    if ( idMeuble == MEUBLE_SOL_SPAWN_JOUEUR1        ) return 0;
    if ( idMeuble == MEUBLE_SOL_SPAWN_JOUEUR2        ) return 0;
    if ( idMeuble == MEUBLE_SOL                      ) return 0;

    // Meubles niveau 4
    if ( idMeuble == MEUBLE_FRESQUE_EGYPTIENNE       ) return 0;
    if ( idMeuble == MEUBLE_PALMIER                  ) return 0;
    if ( idMeuble == MEUBLE_GENERATEUR_FEVES         ) return 0;
    if ( idMeuble == MEUBLE_GENERATEUR_OIGNONS       ) return 0;
    if ( idMeuble == MEUBLE_GENERATEUR_AIL           ) return 0;
    if ( idMeuble == MEUBLE_GENERATEUR_EPICES        ) return 0;
    if ( idMeuble == MEUBLE_GENERATEUR_SEMOULE       ) return 0;
    if ( idMeuble == MEUBLE_GENERATEUR_FARINE        ) return 0;
    if ( idMeuble == MEUBLE_GENERATEUR_SUCRE         ) return 0;
    if ( idMeuble == MEUBLE_GENERATEUR_MIEL          ) return 1;

    if ( idMeuble == MEUBLE_FRITEUSE_ANCIENNE        ) return 0;
    if ( idMeuble == MEUBLE_FOUR                     ) return 0;

    return 1;
}


int bMeubleInfranchissable(int idMeuble) {
    if ( idMeuble == MEUBLE_SOL_SPAWN_JOUEUR1        ) return 0;
    if ( idMeuble == MEUBLE_SOL_SPAWN_JOUEUR2        ) return 0;
    if ( idMeuble == MEUBLE_SOL                      ) return 0;
    return 1;
}



//////////////////////////////////////////////////////////////////////////////////////////////
///
///                                    FONCTIONS INITIALISATION
///
//////////////////////////////////////////////////////////////////////////////////////////////

/// Met tout les objets de la matrice partie a 0
void initialiserObjetMatrice(t_case matrice[NB_LIGNES][NB_COLONNES]) {
    matrice[5][5].objet[2] = 1; // TEST DE LA BONNE INITIALISATION
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            supprimerObjet(matrice[i][j].objet);
        }
    }
}

/// Met des poel, des bacs de friteuse, etc... dans les meubles spécifiques
void initialiserObjetMeublesMatrice(t_case matrice[NB_LIGNES][NB_COLONNES]) {
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            switch (matrice[i][j].id_meuble) {
                case MEUBLE_PLAQUE_DE_CUISSON :
                    matrice[i][j].objet[POELE] = 1;
                    break;
                case MEUBLE_FRITEUSE :
                    matrice[i][j].objet[BAC_DE_FRITEUSE] = 1;
                    break;
            }
        }
    }
}

/// Initialisation des permissions des objets
void initialisationPermissionsObjets(t_permissionsObjets *permissionsObjets) {

    for (int i = 0; i < NOMBRE_OBJETS; ++i) {
        permissionsObjets->assiette[i] = 0;
        permissionsObjets->painBurger[i] = 0;
        permissionsObjets->poel[i] = 0;
        permissionsObjets->friteuse[i] = 0;
        permissionsObjets->friteuse_ancienne[i] = 0;
        permissionsObjets->four[i] = 0;
        permissionsObjets->decoupage[i] = 0;
        permissionsObjets->cuisson[i] = 0;
        permissionsObjets->falafels[i] = 0;
        permissionsObjets->basboussa[i] = 0;
    }

    permissionsObjets->assiette[PAIN_BURGER] = 1;
    permissionsObjets->assiette[SALADE_COUPE] = 1;
    permissionsObjets->assiette[TOMATE_COUPE] = 1;
    permissionsObjets->assiette[FROMAGE_COUPE] = 1;
    permissionsObjets->assiette[STEAK_CUIT] = 1;
    permissionsObjets->assiette[FRITES_CUITES] = 1;
    permissionsObjets->assiette[POISSON_CUIT] = 1;
    permissionsObjets->assiette[FALAFELS_CUITS] = 1;
    permissionsObjets->assiette[BASBOUSSA_CUIT] = 1;

    permissionsObjets->painBurger[ASSIETTE_PROPRE] = 1;
    permissionsObjets->painBurger[SALADE_COUPE] = 1;
    permissionsObjets->painBurger[TOMATE_COUPE] = 1;
    permissionsObjets->painBurger[FROMAGE_COUPE] = 1;
    permissionsObjets->painBurger[STEAK_CUIT] = 1;
    permissionsObjets->painBurger[FRITES_CUITES] = 1;

    permissionsObjets->poel[STEAK_DECOUPE] = 1;
    permissionsObjets->poel[STEAK_CUIT] = 1;
    permissionsObjets->poel[STEAK_CRAME] = 1;
    permissionsObjets->poel[POISSON_COUPE] = 1;
    permissionsObjets->poel[POISSON_CUIT] = 1;
    permissionsObjets->poel[POISSON_CRAME] = 1;

    permissionsObjets->friteuse[FRITES_CRUES] = 1;
    permissionsObjets->friteuse[FRITES_CUITES] = 1;
    permissionsObjets->friteuse[FRITES_CRAMEES] = 1;

    permissionsObjets->friteuse_ancienne[FALAFELS_CRUS] = 1;
    permissionsObjets->friteuse_ancienne[FALAFELS_CUITS] = 1;
    permissionsObjets->friteuse_ancienne[FALAFELS_CRAMES] = 1;

    permissionsObjets->four[BASBOUSSA_CRU] = 1;
    permissionsObjets->four[BASBOUSSA_CUIT] = 1;
    permissionsObjets->four[BASBOUSSA_CRAME] = 1;

    permissionsObjets->decoupage[SALADE] = 1;
    permissionsObjets->decoupage[TOMATE] = 1;
    permissionsObjets->decoupage[FROMAGE] = 1;
    permissionsObjets->decoupage[STEAK_CRU] = 1;
    permissionsObjets->decoupage[PATATE] = 1;
    permissionsObjets->decoupage[FEVES] = 1;
    permissionsObjets->decoupage[OIGNON] = 1;
    permissionsObjets->decoupage[AIL] = 1;

    permissionsObjets->cuisson[STEAK_DECOUPE] = 1;
    permissionsObjets->cuisson[STEAK_CUIT] = 1;
    permissionsObjets->cuisson[FRITES_CRUES] = 1;
    permissionsObjets->cuisson[FRITES_CUITES] = 1;
    permissionsObjets->cuisson[POISSON_CRU] = 1;
    permissionsObjets->cuisson[POISSON_COUPE] = 1;
    permissionsObjets->cuisson[FALAFELS_CRUS] = 1;
    permissionsObjets->cuisson[FALAFELS_CUITS] = 1;
    permissionsObjets->cuisson[BASBOUSSA_CRU] = 1;
    permissionsObjets->cuisson[BASBOUSSA_CUIT] = 1;

    permissionsObjets->falafels[FEVES_COUPE] = 1;
    permissionsObjets->falafels[AIL_COUPE] = 1;
    permissionsObjets->falafels[OIGNON_COUPE] = 1;
    permissionsObjets->falafels[EPICES] = 1;

    permissionsObjets->basboussa[SEMOULE] = 1;
    permissionsObjets->basboussa[FARINE] = 1;
    permissionsObjets->basboussa[SUCRE] = 1;
    permissionsObjets->basboussa[MIEL] = 1;
}

//////////////////////////////////////////////////////////////////////////////////////////////
///
///                                    FONCTIONS DEBUG
///
//////////////////////////////////////////////////////////////////////////////////////////////

/// Affiche la matrice avec les objets stocké dans chaque case
void afficherObjetMatriceConsole(t_case matrice[NB_LIGNES][NB_COLONNES]) {
    for (int i = 0; i < NB_LIGNES; i++) {
        for (int j = 0; j < NB_COLONNES; ++j) {
            printf("[");
            for (int k = 1; k < NOMBRE_OBJETS; k++) {
                if (matrice[i][j].objet[k] != 0) {
                    printf("%d", k);
                }
            }
        }
        printf("\n");
    }
}

/// Affche les objets dans la main du joueur
void afficherObjetJoueurConsole(t_player joueur, int numeroJoueur) {
    printf("Objets joueur %d :\n", numeroJoueur);

    for (int i = 0; i < NOMBRE_OBJETS; i++) {
        if (joueur.objet[i] != 0) {
            printf("Case [%d] = 1\n", i, joueur.objet[i]);
        }
    }
    printf("\n");
}