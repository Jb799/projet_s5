/* 
 * main.c
 * 
 * Contient la fonction principale uniquement afin
 * de faciliter les tests et les modifications.
 * 
 * Auteur : Jean-Baptiste, Duncan, Mohamed & Mila
 * Date de création : 03/01/2023
 * Dernière modification : 11/01/2023
 * 
 */

#include <stdio.h>
#include "index_motor.h"
#include "menu.h"
#include "search_motor.h"

int main(int argc, char *argv[]){
    while(1){
        switch (displayMainMenu())
        {
        case 1:
            indexFilesFromFolder();
            break;

        case 2:
            startSearchMotor();
            break;

        default:
            return 0;
            break;
        }
    }

    return 0;
}