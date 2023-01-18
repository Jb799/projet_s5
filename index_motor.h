/* 
 * index_motor.h
 * 
 * En-tête du fichier index_motor.c
 * 
 * Auteur : Jean-Baptiste & Duncan
 * Date de création : 03/01/2023
 * Dernière modification : 11/01/2023
 * 
 */

#ifndef __INDEX_MOTOR__
#define __INDEX_MOTOR__

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>

#define LINE_SIZE 1000
#define DIR_SIZE 200
#define CRI_LINE_SIZE 100

// Permet de créer des WordList:
typedef struct word {
	char * word;
	unsigned count;
} WORD;

// Structure pour un fichier CRI:
typedef struct cri_file {
	char * dir;
	char * name;
	unsigned wordlistSize;
	WORD * words;
} CRI;

// Charger en mémoire les fichiers CRI:
void getCRIFromFileToTab(char dir_cri[], CRI ** criTab, unsigned * tabSize);

// Indexer des fichiers .txt en .CRI:
void indexFilesFromFolder();

// Récupérer les mots d'une ligne (chaîne):
void getWords(WORD ** wordList, unsigned * size, char * line);

// Ajouter un mot dans une Wordlist:
void addWordToList(WORD ** wordList, unsigned * size, char * word);

// Ajouter un CRI à un tableau de CRI:
void criPushBack(CRI ** tab, unsigned * size, CRI cri);

// Ajouter un mot à une chaine de mots (Wordlist):
void wlPushBack(WORD ** wordList, unsigned * size, WORD word);

// Permet de netoyer un mot :
void cleanWord(char * word);

#endif /*__INDEX_MOTOR__*/