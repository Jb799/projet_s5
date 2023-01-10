#include <stdio.h>
#include "index_motor.h"

int main(){
    FCri tab;
    unsigned size = 0;

    getCriTabFromFolder(&tab, &size, "./files/");

    if(size == 0){
        printf("Une erreur lors de la lecture du dossier");
    }else{
        printf("Tout est bon !");
    }

    return 0;
}