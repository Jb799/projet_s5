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

// Permet de trier le tableau de résultats:
void sortResultsTab(RESULT * resultsTab, unsigned resTabSize) {
    for (unsigned i = 0; i < resTabSize - 1; i++) {
        for (unsigned j = i + 1; j < resTabSize; j++) {
            if (resultsTab[i].count < resultsTab[j].count) {
                RESULT temp = resultsTab[i];
                resultsTab[i] = resultsTab[j];
                resultsTab[j] = temp;
            }
        }
    }
}

// Permet de réaliser des recherches de mots dans les fichiers indéxés:
void searchWords(CRI * criTab, unsigned tabSize){
    char sWord[100]= "", cWord[100] = "";
    
    while (strcmp(cWord, "exit;") != 0)
    {
        getWordsSearch(sWord, cWord);

        if(strcmp(cWord, "exit;") == 0) break;

        clear(); displayLogo();

        printf("\n\n Voici les occurences pour le mot \"%s\": \n\n", cWord);

        RESULT * resultsTab = NULL;
        unsigned resTabSize = 0;

        // Récupérer les résultats:
        for (unsigned i = 0; i < tabSize; i++)
        {
            for (unsigned j = 0; j < criTab[i].wordlistSize; j++)
            {
                if(strcmp(criTab[i].words[j].word, sWord) == 0){
                    RESULT res;
                    
                    res.dir = strdup(criTab[i].dir);
                    res.count = criTab[i].words[j].count;

                    resTabSize++;
                    resultsTab = realloc(resultsTab, resTabSize * sizeof(RESULT));
                    resultsTab[resTabSize - 1] = res;
                    break;
                }
            }
        }

        sortResultsTab(resultsTab, resTabSize);

        for (unsigned i = 0; i < resTabSize; i++) {
            printf("[%s] | %dx\n", resultsTab[i].dir, resultsTab[i].count);
            printf("------------------------------------\n");
        }

        wait();
    }
}

// Fonction principale pour lancer le moteur de recherche:
void startSearchMotor(){
    CRI * criTab = NULL;
    unsigned tabSize = 0;

    setCriTab(&criTab, &tabSize);
    
    wait();

    searchWords(criTab, tabSize);
}
