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
void setCriTab(CRI ** criTab, unsigned * tabSize){
    char cri_dir_name[DIR_SIZE];
    DIR * dirCRI = NULL;

    // Demander le chemin d'accès aux fichiers .CRI:
    getDir(dirCRI, cri_dir_name, "Donnez le chemin d'acces a votre base de donnee CRI (contenant les fichiers .CRI) :\n => ");

    getCRIFromFileToTab(cri_dir_name, criTab, tabSize);
}

// Permet de réaliser des recherches de mots dans les fichiers indéxés:
void searchWords(CRI * criTab, unsigned tabSize){
    char sWord[100], cWord[100];
    getWordsSearch(sWord, cWord);

    printf("\n\n Voici les resultats pour le mot %s: \n\n", cWord);

    for (unsigned i = 0; i < tabSize; i++)
    {
        for (unsigned j = 0; j < criTab[i].wordlistSize; j++)
        {
            if(strcmp(criTab[i].words[j].word, sWord) == 0){
                printf("%s  %dx\n\n", criTab[i].dir, criTab[i].words[j].count);
            }
        }
    }
    
}

// Fonction principale pour lancer le moteur de recherche:
void startSearchMotor(){
    CRI * criTab = NULL;
    unsigned tabSize = 0;

    setCriTab(&criTab, &tabSize);
    
    wait();

    searchWords(criTab, tabSize);

    wait();
}
