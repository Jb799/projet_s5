/* 
 * search_motor.c
 * 
 * Contient des procedures et fonctions permettant la recherche par mots 
 * de fichiers indéxés.
 * La fonction principale est startSearchMotor().
 * 
 * Auteurs : Jean-Baptiste, Mohamed, Duncan & Mila 
 * Date de création : 05/01/2023
 * Dernière modification : 12/01/2023
 * 
 */

#include "search_motor.h"
#include "menu.h"

// Permet de charger les fichiers CRI en mémoire:
void setCriTab(CRI * criTab, unsigned * tabSize){
    char cri_dir_name[DIR_SIZE];
    DIR * dirCRI = NULL;

    // Demander le chemin d'accès aux fichiers .CRI:
    getDir(dirCRI, cri_dir_name, "Donnez le chemin d'acces a votre base de donnee CRI (contenant les fichiers .CRI) :\n => ");

    getCRIFromFileToTab(cri_dir_name, criTab, tabSize);
}

// Fonction principale pour lancer le moteur de recherche:
void startSearchMotor(){
    CRI * criTab = NULL;
    unsigned tabSize = 0;

    setCriTab(criTab, &tabSize);

    for (unsigned i = 0; i < tabSize; i++){
        printf("File: %s\n", criTab[i].name);
        free(criTab[i].dir);
        free(criTab[i].name);
    }
    free(criTab);

    wait();
}