/* 
 * index_motor.c
 * 
 * Contient des fonctions et procedures permetant le fonctionnement
 * du moteur d'indexation du programme. La fonction principale est
 * indexFilesFromFolder().
 * 
 * Auteur : Jean-Baptiste & Duncan
 * Date de création : 03/01/2023
 * Dernière modification : 11/01/2023
 * 
 */

#include "index_motor.h"
#include "menu.h"

// Charger en mémoire les fichiers CRI:
/*void getCRIFromFileToTab(char dir_cri[], CRI * criTab, unsigned * tabSize){
    DIR * dirCRI = opendir(dir_cri);
    struct dirent* file;
    char path[DIR_SIZE] = "";
    char line[CRI_LINE_SIZE] = "";
    unsigned i, worldlistSize;

    *tabSize = 0;

    // Boucler pour chaque fichier dans le dossier
    while((file = readdir(dirCRI)) != NULL){
        if(strstr(file->d_name, ".CRI") != NULL){
            WORD * wordList = NULL;
            i = worldlistSize = 0;
            CRI new_cri;
            FILE * criFile = NULL;

            // Initialise path
            memset(path, 0, sizeof(path));
            strcpy(path, dir_cri);
            strcat(path, file->d_name);

            // Ouvre le fichier
            criFile = fopen(path, "r");

            if (criFile == NULL){
                printf("[WARNING] - Impossible d'ouvrir le fichier %s...\n", file->d_name);
                continue;
            }

            i = 0;

            printf("%s\n", file->d_name);
            
            // Lire le fichier ligne par ligne:
            while (fgets(line, CRI_LINE_SIZE, criFile) != NULL) {
                int len = strlen(line);
                if(line[len-1] == '\n') line[len-1] = '\0';

                if(i == 0){
                    new_cri.dir = (char *)malloc(len+1);
                    strcpy(new_cri.dir, line);
                }else if(i == 1){
                    new_cri.name = (char *)malloc(len+1);
                    strcpy(new_cri.name, line);
                }else{
                    WORD new_word;
                    sscanf(line, "%s %d", new_word.word, &new_word.count);

                    wlPushBack(&wordList, &worldlistSize, new_word);
                }
                i++;
            }

            new_cri.wordlistSize = worldlistSize;
            new_cri.words = wordList;

            criPushBack(&criTab, tabSize, new_cri);

            fclose(criFile);
            free(wordList);
        }
    }

    closedir(dirCRI);
}*/

// Charger en mémoire les fichiers CRI:
void getCRIFromFileToTab(char dir_cri[], CRI * criTab, unsigned * tabSize){
    DIR * dirCRI = opendir(dir_cri);
    char line[LINE_SIZE] = "";
    struct dirent* file;
    unsigned i;
    WORD * wordList = NULL;

    // Boucler pour chaque fichier dans le dossier
    while((file = readdir(dirCRI)) != NULL){
        if(strstr(file->d_name, ".CRI") != NULL){
            char criPath[DIR_SIZE] = "";

            strcpy(criPath, dir_cri);
            strcat(criPath, file->d_name);

            // Lire le fichier CRI:
            FILE * Crifile = fopen(criPath, "r");
            if(Crifile == NULL){
                printf("[WARNING] Impossible d'ouvrir le fichier %s...\n", criPath);
                continue;
            }

            CRI new_cri;
            new_cri.wordlistSize = 0;

            i = 0;

            // Lire ligne par ligne :
            while (fgets(line, LINE_SIZE, Crifile) != NULL)
            {
                if(i == 0){
                    new_cri.dir = strdup(line);
                    printf("DEB\n");
                }else if(i == 1){
                    new_cri.name = strdup(line);
                    printf("DEB2\n");
                }else{
                    WORD new_word;
                    sscanf(line, "%s %d", &new_word.word, &new_word.count);

                    printf("DEB3\n");

                    wlPushBack(&wordList, &new_cri.wordlistSize, new_word);

                    printf("DEB4\n");
                }

                i++;
            }

            printf("DEB5\n");

            printf("Size: %d\n", new_cri.wordlistSize);
            
            free(wordList);
            wordList = NULL;
            
            fclose(Crifile);
        }
    }

    closedir(dirCRI);
}

// Ajouter un CRI à un tableau de CRI:
void criPushBack(CRI ** tab, unsigned * size, CRI cri){
    (*size)++;

    *tab = (CRI *)realloc(*tab, (*size) * sizeof(CRI));

    if(*tab == NULL){
        printf("Erreur d'allocation memoire (newCri)\n");
        exit(EXIT_FAILURE);
    }

    (*tab)[*size - 1] = cri;
}

// Ajouter un mot à une chaine de mots (Wordlist):
void wlPushBack(WORD ** wordList, unsigned * size, WORD word){
    (*size)++;

    *wordList = (WORD *)realloc(*wordList, (*size) * sizeof(WORD));

    if(*wordList == NULL){
        printf("Erreur d'allocation memoire (wlPushBack)\n");
        exit(EXIT_FAILURE);
    }

    (*wordList)[*size - 1] = word;
}

// Ajouter un mot dans une Wordlist:
void addWordToList(WORD ** wordList, unsigned * size, char * word){
    for (unsigned i = 0; i < *size; i++){
        if(strcmp((*wordList)[i].word, word) == 0){ 
            (*wordList)[i].count++;
            return; 
        }
    }

    WORD s_word;
    s_word.word = strdup(word);
    s_word.count = 1;

    wlPushBack(wordList, size, s_word);
}

// Permet de netoyer un mot :
void cleanWord(char * word){
    unsigned len = strlen(word);
    for (int i = 0; i < len; i++) {
        if(!isalpha(word[i])) {
            // Enlever le caractère s'il n'est pas de l'alphabet
            for (int j = i; j < len; j++) {
                if(j == len - 1){
                    word[j] = ' ';
                }else
                    word[j] = word[j + 1];
            }
            
            len--;
            i--;
        }else{
            // Transformer les majuscules en minuscules
            word[i] = tolower(word[i]);
        }
    }

    // Retirer les espaces (généralement en fin de chaine):
    int i, j;
    for (i = j = 0; word[i]; i++)
        if (word[i] != ' ')
            word[j++] = word[i];
    word[j] = '\0';
}

// Récupérer les mots d'une ligne (chaîne):
void getWords(WORD ** wordList, unsigned * size, char * line){
    char * word = strtok(line, " ");

    while(word){
        cleanWord(word);
        if(strcmp(word, "") != 0) addWordToList(wordList, size, word);
        word = strtok(NULL, " ");
    }
}

// Convertir les contenues de fichiers en fichiers CRI:
void indexFilesFromFolder(){
    char txt_dir_name[DIR_SIZE], cri_dir_name[DIR_SIZE];
    DIR * dirTxt = NULL;
    DIR * dirCRI = NULL;
    char line[LINE_SIZE] = "";
    char dirFile[DIR_SIZE] = "";
    char dirCriFile[DIR_SIZE] = "";
    char str_temp[CRI_LINE_SIZE] = "";
    char itos[20];
    struct dirent* file;

    // Demander les chemins d'accès:
    getDir(dirTxt, txt_dir_name, "Donnez le chemin d'acces contenant les fichiers .txt a indexer :\n => ");
    getDir(dirCRI, cri_dir_name, "Donnez le chemin d'acces ou seront enregistrer les fichiers .CRI d'indexation :\n => ");

    clear(); displayLogo();

    printf("[INDEX MOTOR] - Demarrage de l'indexation des fichiers .txt du repertoire %s\n", txt_dir_name);

    dirTxt = opendir(txt_dir_name);

    // Boucler pour chaque fichier dans le dossier
    while((file = readdir(dirTxt)) != NULL){
        if(strstr(file->d_name, ".txt") != NULL){
            char * fileName = strtok(file->d_name, ".");
            if(fileName == NULL) continue;

            strcpy(dirCriFile, "");
            strcat(dirCriFile, cri_dir_name);
            strcat(dirCriFile, fileName);
            strcat(dirCriFile, ".CRI");

            // Vérifier si le fichier CRI existe déjà:
            FILE * CRIfile;
            if ((CRIfile = fopen(dirCriFile, "r"))) {
                fclose(CRIfile);
                continue;
            }

            strcpy(dirFile, "");
            strcat(dirFile, txt_dir_name);
            strcat(dirFile, file->d_name);
            strcat(dirFile, ".txt");

            // Fichier txt:
            FILE * Ffile = fopen(dirFile, "r");
            if(Ffile == NULL){
                printf("[WARNING] Impossible d'ouvrir le fichier %s...\n", dirFile);
                continue;
            }

            WORD * wordList = NULL;
            unsigned wlSize = 0;

            // Lire ligne par ligne :
            while (fgets(line, LINE_SIZE, Ffile) != NULL)
            {
                getWords(&wordList, &wlSize, line);
            }

            // Création du fichier CRI:
            CRIfile = fopen(dirCriFile, "w");
            if (CRIfile == NULL) {
                printf("[WARNING] Impossible d'indexer le fichier %s...\n", dirFile);
                continue;
            }

            // Entrer le chemin vers le fichier .txt:
            fprintf(CRIfile, dirFile);

            fprintf(CRIfile, "\n");

            // Entrer le nom du fichier .txt:
            fprintf(CRIfile, file->d_name);

            for (unsigned j = 0; j < wlSize; j++)
            {
                itoa(wordList[j].count, itos, 10);

                strcpy(str_temp, "");
                strcat(str_temp, wordList[j].word);
                strcat(str_temp, " ");
                strcat(str_temp, itos);

                fprintf(CRIfile, "\n");
                fprintf(CRIfile, str_temp);
            }

            printf("    [INDEX MOTOR] Fichier %s indexer !\n", dirFile);
            
            free(wordList);
            fclose(CRIfile);
            fclose(Ffile);
        }
    }

    closedir(dirTxt);

    printf("[INDEX MOTOR] - Fin de l'indexation des fichiers !\n\n");
    wait();
}