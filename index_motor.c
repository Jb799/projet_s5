#include "index_motor.h"

// Ajouter un mot à une chaine de mots (Wordlist):
void wlPushBack(WORD ** wordList, unsigned * size, WORD word){
    (*size)++;

    *wordList = (WORD *)realloc(*wordList, (*size) * sizeof(WORD));

    if(*wordList == NULL) {
        printf("Erreur d'allocation mémoire (wlPushBack)\n");
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
void getCriTabFromFolder(FCri * tab, unsigned * size, char * dir_name, char * dir_cri){
    DIR * dir = opendir(dir_name);
    char line[LINE_SIZE] = "";
    char dirFile[DIR_SIZE] = "";
    char dirCriFile[DIR_SIZE] = "";
    char str_temp[CRI_LINE_SIZE] = "";
    char itos[20]; 
    unsigned i = 0;

    if(dir == NULL){ // Si le dossier ne peut pas être ouvert
        *size = 0;
        return;
    }

    struct dirent* file;

    // Boucler pour chaque fichier dans le dossier
    while((file = readdir(dir)) != NULL){
        if(strstr(file->d_name, ".txt") != NULL){
            char * fileName = strtok(file->d_name, ".");
            if(fileName == NULL) continue;

            strcpy(dirCriFile, "");
            strcat(dirCriFile, dir_cri);
            strcat(dirCriFile, fileName);
            strcat(dirCriFile, ".cri");

            // Vérifier si le fichier CRI existe déjà:
            FILE * CRIfile;
            if ((CRIfile = fopen(dirCriFile, "r"))) {
                fclose(CRIfile);
                continue;
            }

            strcpy(dirFile, "");
            strcat(dirFile, dir_name);
            strcat(dirFile, file->d_name);
            strcat(dirFile, ".txt");

            // Fichier txt:
            FILE * Ffile = fopen(dirFile, "r");
            if(Ffile == NULL){
                *size = 0;
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
            CRIfile = fopen(dirCriFile, "wb");
            if (CRIfile == NULL) {
                printf("Une erreur lors de la création des fichiers .CRI!\n");
                exit(EXIT_FAILURE);
            }

            for (unsigned j = 0; j < wlSize; j++)
            {
                itoa(wordList[j].count, itos, 10);

                strcpy(str_temp, "");
                strcat(str_temp, wordList[j].word);
                strcat(str_temp, ":");
                strcat(str_temp, itos);

                fwrite(str_temp, sizeof(char), sizeof(str_temp), CRIfile);
            }
            
            free(wordList);
            fclose(CRIfile);
            fclose(Ffile);
        }

        i++; // i défini le ième fichier
    }
    
    closedir(dir);
}