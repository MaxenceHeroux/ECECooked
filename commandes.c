//
// Created by OLIVIER, Lucas, Maxence, Ethan on 10/04/2024.
//

#include "config.h"

int alea_type_commande_niv1(){ //génère aléatoirement un nombre entre 0 et 3 inclus pour le type des commandes du niveau 1
    return rand() % (3-0+1) + 0;
}

int alea_type_commande_niv4(){ //génère aléatoirement un nombre entre 4 et 8 inclus pour le type des commandes du niveau 4
    return rand() % (8-4+1) + 4;
}

int alea_type_commande(int niveau){
    switch (niveau) {
        case 1 ... 3 : { //génère aléatoirement un nombre entre 0 et 3 inclus pour le type des commandes du niveau 1 à 3
            return rand() % (3 - 0 + 1) + 0;
        }
        /*case 2:{ //génère aléatoirement un nombre entre 8 et 11 inclus pour le type des commandes du niveau 2
            return rand() % (11 - 8 + 1) + 8;
        }
        case 3:{ //génère aléatoirement un nombre entre 12 et 15 inclus pour le type des commandes du niveau 3
            return rand() % (15 - 12 + 1) + 12;
        }*/
        case 4: { //génère aléatoirement un nombre entre 4 et 5 inclus pour le type des commandes du niveau 4
            return rand() % (5 - 4 + 1) + 4;
        }
        case 5: { //génère aléatoirement un nombre entre 0 et 3 inclus pour le type des commandes du niveau 5
            return rand() % (3 - 0 + 1) + 0;
        }
        default: {
            allegro_message("attention alea_type_commande");
            exit(1); //quitte le main prq ce n'est pas possible normalement
        }
    }
}

int alea_temps_commande(){ //génère aléatoirement un nombre entre 5 et 15 inclus pour l'apparition des commandes
    return rand() % (15-7+1) + 7;
}

void ajout_maillon(File_commandes* tete, t_commande* commande){
    tete->nb_commande++;
    t_commande* temp = tete->first;

    if (temp == NULL) {
        tete->first = commande;
        return;
    }

    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = commande;
}

void supprimer_maillon(File_commandes* file){
    assert(file != NULL);
    file->nb_commande--;

    if (file->first != NULL) {
        t_commande* temp = file->first;
        file->first = temp->next;
        free(temp);
        temp = NULL;
    }
}

void supprimer_tous_maillons(File_commandes* file){
    if (file == NULL) {
        return;
    }

    t_commande* current = file->first;
    t_commande* suivant;

    while(current != NULL){
        suivant = current->next;
        file->nb_commande--;
        free(current);
        current = suivant;
    }
    file->first = NULL;
}

void liberation(File_commandes* fc_tete){
    t_commande* tmp = fc_tete->first;
    t_commande* tete = tmp;

    if (tmp == NULL) {
        return;
    }
    while(tmp->next != NULL){
        tmp = tmp->next;
        free(tete);
        tete = tmp;
    }
    tete = NULL;
}

void complete_commande(File_commandes* commandes, t_commande* commande){
    int type = alea_type_commande(commandes->niveau);

    commande->done = 0;

    switch (type) {
        case 0 ... 3: { //niv 1
            commande->type_commande = type;
            commande->chrono = TEMPS_COMMANDES;
            break;
        }
        case 4 ... 5: { //niv 4
            commande->type_commande = type;
            commande->chrono = TEMPS_COMMANDES;
            break;
        }
        case 6 ... 9: { //niv 2
            commande->type_commande = type;
            commande->chrono = TEMPS_COMMANDES;
            break;
        }
        case 10 ... 13: { //niv 3
            commande->type_commande = type;
            commande->chrono = TEMPS_COMMANDES;
            break;
        }
        default : {
            break;
        }
    }
}

t_commande* creerMaillon(File_commandes* fileCommandes){
    t_commande* M = (t_commande*) malloc(sizeof(t_commande));
    M->next = NULL;
    complete_commande(fileCommandes, M);

    return M;
}

void lancer_commandes(File_commandes* commandes, t_ressources RESSOURCES, BITMAP* buffer, t_partie* partie){
    partie->time.temps = maintenantEnMs(); //mets à jour le temps actuel en milli seconde

    if(partie->time.pause == 1){ // si la pause est activée cela compte le temps durant lequel elle est activée
        partie->time.decalage_pause = maintenantEnSec() - partie->time.temps_pause_ON;
    }

    if(partie->time.pause == 0){ // si la pause n'est pas activée ça soustrait à partie->time.seconde le décalage pause et remet le partie->time.decalage_pause à 0
        partie->time.temps_pause_ON = maintenantEnSec(); //moment juste avant de mettre pause
        partie->time.duree_totale_pause += partie->time.decalage_pause;
        partie->time.decalage_pause = 0;
    }

    //Gestion d'une seconde et des chronos des commandes
    partie->time.seconde = maintenantEnSec() - (partie->time.decalage + partie->time.duree_totale_pause); //mets à jour les secondes depuis le lancement du jeu s'incrémente chaque seconde
    if((partie->time.seconde_prec + 1 <= partie->time.seconde) && (partie->time.pause == 0)){ //si partie->time.seconde est supérieur ou égale à partie->time.seconde_prec plus une seconde
        partie->time.seconde_prec = partie->time.seconde; //annule l'écart d'une seconde entre seconde et seconde_prec
        partie->time.timer = TIMER_PARTIE-partie->time.seconde; //TIMER_PARTIE est le début du chrono

        //retire 1s sur le chrono de chaque commande
        t_commande* tmp = commandes->first;
        if (tmp == NULL) {
            return;
        }
        while(tmp != NULL){
            tmp->chrono--;
            tmp = tmp->next;
        }
    }

    //Gestion de l'ajout d'une commande

    if(((partie->time.seconde - partie->time.temps_prec_commande) >= partie->time.temps_pro_commande) && (commandes->nb_commande < 5) && (partie->time.pause == 0)){ //compare l'intervalle de temps (entre la dernière commande et mtn) avec le temps avant d'ajouter une commande
        ajout_maillon(commandes, creerMaillon(commandes));
        partie->time.temps_prec_commande = partie->time.seconde;
        partie->time.temps_pro_commande = alea_temps_commande(); //temps avant la prochaine commande en seconde
    }

    if(commandes->nb_commande >= 5){ //pour pas qu'une commande spawn instant après qu'une commande part quand la file est full
        partie->time.temps_prec_commande = partie->time.seconde;
    }

    //Gestion de retirer une commande
    if (commandes->first != NULL) {
        // Si la commande est faite à temps
        if (commandes->first->done == 1){ //vérifie que commande->first existe
            play_sample(RESSOURCES.ding, 255, 128, 1000, FALSE);
            supprimer_maillon(commandes);
        }
    }

    // Commande non-préparée à temps : suppression et malus de score
    if (commandes->first != NULL) {
        if (commandes->first->chrono <= 0) {
            play_sample(RESSOURCES.fail_buzzer, 62, 128, 1000, FALSE);
            partie->joueur1.score -= 50;
            partie->joueur2.score -= 50;
            commandes->score = partie->joueur1.score + partie->joueur2.score;
            supprimer_maillon(commandes);
            if (partie->niveau_select == 4) { //Si niveau 4 alors une commande ratée provoque le Game Over
                partie->time.timer = 0;
                partie->lvl4_succes = 0;
            }
        }
    }

    afficher_commandes(commandes, RESSOURCES, buffer);
}

void afficher_commandes(File_commandes* commandes, t_ressources RESSOURCES, BITMAP* buffer){
    t_commande* tmp = commandes->first;
    int compteur = -1, x = 20, y = 20;
    float r = 0, g = 0, b = 0;

    if(tmp == NULL){ //si la liste est vide on affiche rien
        return;
    }
    while(tmp != NULL){
        compteur++;
        //mise à jour des coordonnées en fonction de la position du maillon dans la file
        x = 20 + 120*compteur; //20 = marge à gauche // 120 = espacement entre les coins haut-gauche de 2 commandes
        y = 20; // 20 = marge en haut

        //règle la couleur de la barre de temps en fonction du temps restant
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

        //affichage selon le type de la commande
        switch (tmp->type_commande) {
            case 0:{ // burger viande
                draw_sprite(buffer, RESSOURCES.commande_burger_viande, x, y);
                break;
            }
            case 1:{ // steak frites
                draw_sprite(buffer, RESSOURCES.commande_steak_frites, x, y);
                break;
            }
            case 2:{ // salade
                draw_sprite(buffer, RESSOURCES.commande_salade, x, y);
                break;
            }
            case 3:{ // frites
                draw_sprite(buffer, RESSOURCES.commande_frites, x, y);
                break;
            }
            case 4: { //falafel
                draw_sprite(buffer, RESSOURCES.commande_falafel, x, y);
                break;
            }
            case 5: { //basboussa
                draw_sprite(buffer, RESSOURCES.commande_basboussa, x, y);
                break;
            }
            case 6:{ // pas encore de commande
                draw_sprite(buffer, RESSOURCES.commande_assiette_propre, x, y);
                break;
            }
            default:{
                break;
            }
        }
        rect(buffer, x, y+TAILLE_Y_COMMANDE, x+TAILLE_X_COMMANDE, y+TAILLE_Y_COMMANDE+20, makecol(0,0,0)); //contour de la barre de temps, 20 est la largeur de la barre de temps
        rectfill(buffer, x+1, y+TAILLE_Y_COMMANDE+1, x+(TAILLE_X_COMMANDE*tmp->chrono)/TEMPS_COMMANDES, y+TAILLE_Y_COMMANDE+20-1, makecol(r,g,b)); //remplissage de la barre de temps
        rectfill(buffer, x+(TAILLE_X_COMMANDE*tmp->chrono)/TEMPS_COMMANDES+1, y+TAILLE_Y_COMMANDE+20-1, x+TAILLE_X_COMMANDE-1, y+TAILLE_Y_COMMANDE+1, makecol(128,128,128)); //remplissage de l'autre partie de la barre de temps en gris

        tmp = tmp->next;
    }
}

/*void afficher_console(File_commandes* File_commande){
    t_commande* tmp = File_commande->first;

    if (tmp == NULL) { //File vide
        return;
    }
    while(tmp->next != NULL){
        printf("\n%d",tmp->type_commande);
        tmp = tmp->next;
    }
    if (tmp->next == NULL) {
        printf("\n%d",tmp->type_commande);
        return;
    }
}*/

void initialise_recettes(int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS]){
    //Création d'un compteur pour parcourir la matrice recettes
    int compteur = 1;

    //Création du pointeur
    FILE* type_commande0 = NULL;
    FILE* type_commande1 = NULL;
    FILE* type_commande2 = NULL;
    FILE* type_commande3 = NULL;
    FILE* type_commande4 = NULL;
    FILE* type_commande5 = NULL;

    //Ouverture des fichiers
    type_commande0 = fopen("../Type_commande0.txt", "r");
    type_commande1 = fopen("../Type_commande1.txt", "r");
    type_commande2 = fopen("../Type_commande2.txt", "r");
    type_commande3 = fopen("../Type_commande3.txt", "r");
    type_commande4 = fopen("../Type_commande4.txt", "r");
    type_commande5 = fopen("../Type_commande5.txt", "r");

    //Debug
    if(type_commande0 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande0.txt");
        exit(1);
    }
    if(type_commande1 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande1.txt");
        exit(1);
    }
    if(type_commande2 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande2.txt");
        exit(1);
    }
    if(type_commande3 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande3.txt");
        exit(1);
    }
    if(type_commande4 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande4.txt");
        exit(1);
    }
    if(type_commande5 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande5.txt");
        exit(1);
    }

    //Lis les fichiers et les stocks dans recettes
    //Ingrédients recette 0 : burger_viande, niv 1
    compteur = 1;
    while(compteur < NOMBRE_OBJETS && fscanf(type_commande0, "%d", &recettes[0][compteur]) == 1){
        compteur = compteur+1;
    }
    //Ingrédients recette 1 : burger_poisson, niv 1
    compteur = 1;
    while(compteur < NOMBRE_OBJETS && fscanf(type_commande1, "%d", &recettes[1][compteur]) == 1){
        compteur = compteur+1;
    }
    //Ingrédients recette 2 : salade, niv 1
    compteur = 1;
    while(compteur < NOMBRE_OBJETS && fscanf(type_commande2, "%d", &recettes[2][compteur]) == 1){
        compteur = compteur+1;
    }
    //Ingrédients recette 3 : frites, niv 1
    compteur = 1;
    while(compteur < NOMBRE_OBJETS && fscanf(type_commande3, "%d", &recettes[3][compteur]) == 1){
        compteur = compteur+1;
    }
    //Ingrédients recette 4 : falafel, niv 4
    compteur = 1;
    while(compteur < NOMBRE_OBJETS && fscanf(type_commande4, "%d", &recettes[4][compteur]) == 1){
        compteur = compteur+1;
    }
    //Ingrédients recette 5 : basboussa, niv 4
    compteur = 1;
    while(compteur < NOMBRE_OBJETS && fscanf(type_commande5, "%d", &recettes[5][compteur]) == 1){
        compteur = compteur+1;
    }

    //Fermeture des fichiers
    fclose(type_commande0);
    fclose(type_commande1);
    fclose(type_commande2);
    fclose(type_commande3);
    fclose(type_commande4);
    fclose(type_commande5);

    /*Affichage des recettes
    for(int i = 0; i < NOMBRE_COMMANDES; i++) {
        for (int j = 1; j < NOMBRE_OBJETS; j++) {
            printf("%d", recettes[i][j]);
        }
        printf("\n");
    }*/

    /*//Liste ingrédients par recette
    //Ingrédients recette 0 : burger_viande, niv 1
    recettes[0][ASSIETTE_PROPRE] = 1;
    recettes[0][PAIN_BURGER] = 1;
    recettes[0][STEAK_CUIT] = 1;
    recettes[0][FROMAGE_COUPE] = 1;
    recettes[0][SALADE_COUPE] = 1;

    //Ingrédients recette 1 : burger_poisson, niv 1
    recettes[1][ASSIETTE_PROPRE] = 1;
    recettes[1][FRITES_CUITES] = 1;
    recettes[1][STEAK_CUIT] = 1;

    //Ingrédients recette 2 : salade, niv 1
    recettes[2][ASSIETTE_PROPRE] = 1;
    recettes[2][TOMATE_COUPE] = 1;
    recettes[2][SALADE_COUPE] = 1;

    //Ingrédients recette 3 : frites, niv 1
    recettes[3][ASSIETTE_PROPRE] = 1;
    recettes[3][FRITES_CUITES] = 1;
    recettes[3][FROMAGE_COUPE] = 1;

    //Ingrédients recette 4 : falafel, niv 4
    recettes[4][ASSIETTE_PROPRE] = 1;
    recettes[4][FALAFELS_CUITS] = 1;

    //Ingrédients recette 5 : basboussa, niv 4
    recettes[5][ASSIETTE_PROPRE] = 1;
    recettes[5][BASBOUSSA_CUIT] = 1;*/
}

void initialisation_fichiers_commandes(){
    //Initialisation des fichiers
    FILE* type_commande0 = NULL;
    FILE* type_commande1 = NULL;
    FILE* type_commande2 = NULL;
    FILE* type_commande3 = NULL;
    FILE* type_commande4 = NULL;
    FILE* type_commande5 = NULL;

    //Ouverture des fichiers
    type_commande0 = fopen("../Type_commande0.txt", "r");
    type_commande1 = fopen("../Type_commande1.txt", "r");
    type_commande2 = fopen("../Type_commande2.txt", "r");
    type_commande3 = fopen("../Type_commande3.txt", "r");
    type_commande4 = fopen("../Type_commande4.txt", "r");
    type_commande5 = fopen("../Type_commande5.txt", "r");

    //Debug
    if(type_commande0 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande0.txt");
        exit(1);
    }
    if(type_commande1 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande1.txt");
        exit(1);
    }
    if(type_commande2 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande2.txt");
        exit(1);
    }
    if(type_commande3 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande3.txt");
        exit(1);
    }
    if(type_commande4 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande4.txt");
        exit(1);
    }
    if(type_commande5 == NULL){
        allegro_message("Erreur ouverture fichier Type_commande5.txt");
        exit(1);
    }

    //Fermeture des fichiers
    fclose(type_commande0);
    fclose(type_commande1);
    fclose(type_commande2);
    fclose(type_commande3);
    fclose(type_commande4);
    fclose(type_commande5);
}

void compareCommande(File_commandes* commandes ,const int recettes[NOMBRE_COMMANDES][NOMBRE_OBJETS],const short objet[NOMBRE_OBJETS]){
    int valide = 1;

    for(int i = 1; i < NOMBRE_OBJETS; i++) {
        printf("%d", objet[i]);
    }
    printf("\n");
    for(int i = 1; i < NOMBRE_OBJETS; i++){
        printf("%d", recettes[commandes->first->type_commande][i]);
    }

    //Compare si c'est la même recette
    for(int i = 1; i < NOMBRE_OBJETS; i++){
            if(recettes[commandes->first->type_commande][i] != objet[i]){
                valide = 0;
            }
    }

    //Met à jour si la commande est faite/bonne
    if(valide == 1){
        commandes->first->done = 1;
    }
    else if(valide == 0){
        commandes->first->done = 0;
    }
}

int meilleur_score(File_commandes* commandes){
    int ancien_score;
    FILE* meilleur_score = NULL;

    //Ouverture du fichier Score.dat en fonction du niveau
    switch (commandes->niveau) {
        case 1:{
            meilleur_score = fopen("../Scores1.dat", "r+");
            break;
        }
        case 2:{
            meilleur_score = fopen("../Scores2.dat", "r+");
            break;
        }
        case 3:{
            meilleur_score = fopen("../Scores3.dat", "r+");
            break;
        }
        case 4:{
            meilleur_score = fopen("../Scores4.dat", "r+");
            break;
        }
        case 5:{
            meilleur_score = fopen("../Scores5.dat", "r+");
            break;
        }
        default:{
            break;
        }
    }

    //Debug
    if(meilleur_score == NULL){
        allegro_message("Erreur lecture fichier score");
    }

    //Se positionner au début du fichier
    fseek(meilleur_score, 0, SEEK_SET);
    //Lire le fichier et stocke l'ancien meilleur score
    fread(&ancien_score, sizeof(int), 1, meilleur_score);

    //Réécrit le meilleur score si le nouveau score est meilleur
    if(commandes->score > ancien_score){
        fseek(meilleur_score, 0, SEEK_SET);
        fwrite(&commandes->score, sizeof(int), 1, meilleur_score);
    }

    //Fermeture fichier Score.dat
    fclose(meilleur_score);

    return ancien_score;
}

void initialisation_fichier_score(){ //Créer des fichiers scores avec -1000 comme meilleur score
    //Valeur initiale dans les fichiers
    int ancien_score = -1000;

    //Initialisation des fichiers
    FILE* meilleur_score1 = NULL;
    FILE* meilleur_score2 = NULL;
    FILE* meilleur_score3 = NULL;
    FILE* meilleur_score4 = NULL;
    FILE* meilleur_score5 = NULL;

    //Ouverture des fichiers
    meilleur_score1 = fopen("../Scores1.dat", "w");
    meilleur_score2 = fopen("../Scores2.dat", "w");
    meilleur_score3 = fopen("../Scores3.dat", "w");
    meilleur_score4 = fopen("../Scores4.dat", "w");
    meilleur_score5 = fopen("../Scores5.dat", "w");

    //Debug
    if(meilleur_score1 == NULL){
        allegro_message("Erreur ouverture fichier Scores1.dat");
        exit(1);
    }
    if(meilleur_score2 == NULL){
        allegro_message("Erreur ouverture fichier Scores2.dat");
        exit(1);
    }
    if(meilleur_score3 == NULL){
        allegro_message("Erreur ouverture fichier Scores3.dat");
        exit(1);
    }
    if(meilleur_score4 == NULL){
        allegro_message("Erreur ouverture fichier Scores4.dat");
        exit(1);
    }
    if(meilleur_score5 == NULL){
        allegro_message("Erreur ouverture fichier Scores4.dat");
        exit(1);
    }

    //Ecriture dans les fichiers
    fwrite(&ancien_score, sizeof(int), 1, meilleur_score1);
    fwrite(&ancien_score, sizeof(int), 1, meilleur_score2);
    fwrite(&ancien_score, sizeof(int), 1, meilleur_score3);
    fwrite(&ancien_score, sizeof(int), 1, meilleur_score4);
    fwrite(&ancien_score, sizeof(int), 1, meilleur_score5);

    //Fermeture des fichiers
    fclose(meilleur_score1);
    fclose(meilleur_score2);
    fclose(meilleur_score3);
    fclose(meilleur_score4);
    fclose(meilleur_score5);
}
