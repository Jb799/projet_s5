/* 
 * menu.h
 * 
 * En-tête du fichier menu.c
 * 
 * Auteur : Mohamed & Mila
 * Date de création : 11/01/2023
 * Dernière modification : 11/01/2023
 * 
 */

#ifndef __MENU__
#define __MENU__

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

// Permet de récupérer un chemin d'accès:
void getDir(DIR * dir, char dir_name[], char * msg);

// Afficher le menu principal:
int displayMainMenu();

// Afficher le logo du programme:
void displayLogo();

// Permet de clear la console de tous les OS:
void clear();

// Attendre une entrée de l'utilisateur:
void wait();

#endif /*__MENU__*/