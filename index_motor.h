#ifndef __INDEX_MOTOR__
#define __INDEX_MOTOR__

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#define LINE_SIZE 1000
#define DIR_SIZE 200
#define CRI_LINE_SIZE 50

// Structure pour un fichier CRI:
typedef struct cri_file {
	char * name;
} FCri;

// Permet de créer des WordList:
typedef struct word {
	char * word;
	unsigned count;
} WORD;

// Convertir les contenues de fichiers en fichiers CRI:
void getCriTabFromFolder(FCri * tab, unsigned * size, char * dir_name, char * dir_cri);

// Récupérer les mots d'une ligne (chaîne):
void getWords(WORD ** wordList, unsigned * size, char * line);

// Ajouter un mot dans une Wordlist:
void addWordToList(WORD ** wordList, unsigned * size, char * word);

// Ajouter un mot à une chaine de mots (Wordlist):
void wlPushBack(WORD ** wordList, unsigned * size, WORD word);

// Permet de netoyer un mot :
void cleanWord(char * word);

#endif /*__INDEX_MOTOR__*/