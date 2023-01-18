/* 
 * search_motor.h
 * 
 * En-tête du fichier search_motor.c
 * 
 * Auteur : Jean-Baptiste, Mohamed, Duncan & Mila 
 * Date de création : 05/01/2023
 * Dernière modification : 12/01/2023
 * 
 */

#ifndef __SEARCHMOTOR__
#define __SEARCHMOTOR__

#include <stdio.h>
#include <stdlib.h>
#include "index_motor.h"

#define DIR_SIZE 200

// Fonction principale pour lancer le moteur de recherche:
void startSearchMotor();

// Permet de charger les fichiers CRI en mémoire:
void setCriTab(CRI ** criTab, unsigned * tabSize);

// Permet de réaliser des recherches de mots dans les fichiers indéxés:
void searchWords(CRI * criTab, unsigned tabSize);

#endif /*__SEARCHMOTOR__*/