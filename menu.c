/* 
 * menu.c
 * 
 * Contient des fonctions et des procedures permettant l'affichage de menus  
 * du programme sur le terminal. Les procedures s'adaptent au système 
 * d'exploitation pour permettre un bon affichage sur tous les OS.
 * 
 * Auteur : Mohamed & Mila
 * Date de création : 11/01/2023
 * Dernière modification : 11/01/2023
 * 
 */

#include "menu.h"
#include "index_motor.h"

// Permet de clear la console de tous les OS:
void clear(){
    // Renvoie le chemin d'accès vers le shell win sinon NULL donc Linux ou MacOs:
    char *env_value = getenv("COMSPEC"); 

    if(env_value != NULL)
        system("cls");
    else
        system("clear");
}

// Attendre une entrée de l'utilisateur:
void wait(){
    // Renvoie le chemin d'accès vers le shell win sinon NULL donc Linux ou MacOs:
    char *env_value = getenv("COMSPEC"); 
    char w[100];

    if(env_value != NULL)
        system("PAUSE");
    else{
        printf("[Y] pour continuer...");
        scanf("%s", w);
    }
}

// Afficher le logo du programme:
void displayLogo(){
    printf("--------------------------------------------------------------------------------------\n");
    printf("|  __    __   ___   ____   ___   _____      _____   ___   ____  ____      __  __ __  |\n");
    printf("| |  |__|  | /   \\ |    \\ |   \\ / ___/     / ___/  /  _] /    ||    \\    /  ]|  |  | |\n");                            
    printf("| |  |  |  ||     ||  D  )|    (   \\_     (   \\_  /  [_ |  o  ||  D  )  /  / |  |  | |\n");
    printf("| |  |  |  ||  O  ||    / |  D  \\__  |     \\__  ||    _]|     ||    /  /  /  |  _  | |\n");
    printf("| |  `  '  ||     ||    \\ |     /  \\ |     /  \\ ||   [_ |  _  ||    \\ /   \\_ |  |  | |\n");
    printf("|  \\      / |     ||  .  \\|     \\    |     \\    ||     ||  |  ||  .  \\      ||  |  | |\n");
    printf("|   \\_/\\_/   \\___/ |__|\\_||_____|\\___|      \\___||_____||__|__||__|\\_| \\____||__|__| |\n");
    printf("|                                                                                    |\n");
    printf("|                   By Jean-Baptiste, Mohamed, Duncan & Mila                         |\n");
    printf("--------------------------------------------------------------------------------------\n");
    printf("\n\n");
}

// Afficher le menu principal:
int displayMainMenu(){
    int select = -1;

    while (select < 0 || select > 2)
    {
        clear();
        displayLogo();

        printf("Veuillez choisir une option : \n");
        printf("-----------------------------\n");
        printf("| [0] ~ Quitter             |\n");
        printf("| [1] ~ Moteur d'indexation |\n");
        printf("| [2] ~ Moteur de recherche |\n");
        printf("-----------------------------\n\n");

        printf("=> ");
        scanf("%d", &select);
    }

    return select;
}

// Permet de récupérer un chemin d'accès:
void getDir(DIR * dir, char dir_name[], char * msg){
    unsigned err = 0;

    while(dir == NULL){
        clear(); displayLogo();
        
        if(err == 1)
            printf("[Erreur] - Chemin d'acces introuvable (%s).\n\n", dir_name);

        printf("%s", msg);

        scanf("%s", dir_name);
        dir = opendir(dir_name);
        err = 1;
    }

    closedir(dir);
}

// Permet de récupérer des mots pour une recherche:
void getWordsSearch(char words[], char cWord[]){
    clear(); displayLogo();
    
    printf("Barre de recherche:\n   => ");
    scanf("%s", cWord);

    strcpy(words, cWord);
    
    cleanWord(words);
}