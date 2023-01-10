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
void getCriTabFromFolder(FCri * tab, unsigned * size, char * dir_name){
    DIR * dir = opendir(dir_name);
    char line[LINE_SIZE] = "";
    unsigned i = 0;

    if(dir == NULL){ // Si le dossier ne peut pas être ouvert
        *size = 0;
        return;
    }

    struct dirent* file;

    // Boucler pour chaque fichier dans le dossier
    while((file = readdir(dir)) != NULL){
        if(strstr(file->d_name, ".txt") != NULL){
            strcpy(line, "");
            strcat(line, dir_name);
            strcat(line, file->d_name);
 
            FILE * Ffile = fopen(line, "r");
            WORD * wordList = NULL;
            unsigned wlSize = 0;

            if(Ffile == NULL){
                *size = 0;
                return;
            }

            // Lire ligne par ligne :
            while (fgets(line, LINE_SIZE, Ffile) != NULL)
            {
                getWords(&wordList, &wlSize, line);
            }

            printf("Size: %d\n", wlSize);
            printf("WordList for %s: \n", file->d_name);

            printf("\n###################\n");
            for (unsigned j = 0; j < wlSize; j++)
            {
                printf("%s:%d\n", wordList[j].word, wordList[j].count);
            }
            printf("\n###################\n");
            
            free(wordList);
            fclose(Ffile);
        }

        i++; // i défini le ième fichier mais aussi sa place dans le tableau

        if(i > 2) return; // DEBUG
    }
    
    closedir(dir);
}