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

void clear(){
    // Renvoie le chemin d'accès vers le shell win sinon NULL donc Linux ou MacOs:
    char *env_value = getenv("COMSPEC"); 

    if(env_value != NULL)
        system("cls");
    else
        system("clear");
}

void wait(){
    // Renvoie le chemin d'accès vers le shell win sinon NULL donc Linux ou MacOs:
    char *env_value = getenv("COMSPEC"); 

    if(env_value != NULL)
        system("PAUSE");
    else
        system("read");
}

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