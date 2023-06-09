#include <stdio.h>
#include <stdlib.h>
#include "list.h"

//Funcion para leer el k-esimo elemento de un string (separado por comas)
const char *get_csv_field (char * tmp, int k) {
    int open_mark = 0;
    char* ret=(char*) malloc (100*sizeof(char));
    int ini_i=0, i=0;
    int j=0;
    while(tmp[i+1]!='\0'){

        if(tmp[i]== '\"'){
            open_mark = 1-open_mark;
            if(open_mark) ini_i = i+1;
            i++;
            continue;
        }

        if(open_mark || tmp[i]!= ','){
            if(k==j) ret[i-ini_i] = tmp[i];
            i++;
            continue;
        }

        if(tmp[i]== ','){
            if(k==j) {
               ret[i-ini_i] = 0;
               return ret;
            }
            j++; ini_i = i+1;
        }

        i++;
    }

    if(k==j) {
       ret[i-ini_i] = 0;
       return ret;
    }


    return NULL;
}


int main()
{
    // Se abre el archivo de mundos csv en modo lectura "r"
    FILE *fp = fopen ("ratings.csv", "r");

    // Cadena para guardar la linea completa del archivo csv
    char linea[1024];
    int i;

    fgets (linea, 1023, fp);
    int k=0;
    while (fgets (linea, 1023, fp) != NULL) { // Se lee la linea
        for(i=0;i<13;i++){
            char *aux = get_csv_field(linea, i); // Se obtiene el nombre
            printf("%s ",aux);
        }

        printf("\n");
        k++; if(k==10) break;
    }

    return 0;
}
