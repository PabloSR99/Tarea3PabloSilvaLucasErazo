#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"
#include "list.h"
#define MAXCHAR 20
#define barrita "\n======================================\n"
#define barrita2 "\n--------------------------------------\n"
#define confirmar(cad) (strcmp(cad, "Si") == 0 || strcmp(cad, "SI") == 0 || strcmp(cad, "si") == 0 || strcmp(cad, "sI") == 0)



typedef struct{ 
    char nombreTarea[MAXCHAR + 1];
    int prioridad;
    char (*precedentes)[MAXCHAR + 1];
    int contPrecedentes;
} tipoTarea;

typedef struct{
    Stack *ultimaAccion;
}tipoHistorial;

void agregarTarea(Heap* monticulo,tipoHistorial* historial){

    tipoTarea *tarea = (tipoTarea*) malloc(sizeof(tipoTarea));
    
    printf("Ingrese el nombre de la tarea:\n");
    scanf(" %[^\n]s", tarea->nombreTarea);
    while (getchar() != '\n');
    
    int cont=get_size(monticulo);
    for(int i=0;i<cont;i++){
        tipoTarea *aux = get_data(monticulo,i);
        if(strcmp(aux->nombreTarea,tarea->nombreTarea)==0){
            printf("ya existe esta tarea.\n");
            return;
        }
        
    }
    printf("Ingrese la prioridad de la tarea:\n");
    scanf("%d", &tarea->prioridad);
    tarea->contPrecedentes = 0;
    heap_push(monticulo, tarea, tarea->prioridad);
    push(historial->ultimaAccion, monticulo);
    
}

void establecerPrecedencia(Heap *monticulo,tipoHistorial* historial){
   
    char tarea1[MAXCHAR +1];
    char tarea2[MAXCHAR +1];
    bool valido=false;
    printf("Ingrese el nombre de la tarea1:\n");
    scanf(" %[^\n]s", tarea1);
    while (getchar() != '\n');
    printf("Ingrese el nombre de la tarea2:\n");
    scanf(" %[^\n]s", tarea2);
    while (getchar() != '\n');
    
    int cont = get_size(monticulo);

    for(int i=0;i<cont;i++){
        
        tipoTarea *aux = get_data(monticulo,i);
        
        if(strcmp(aux->nombreTarea,tarea1)==0){
            
            for(int f=0;f<cont;f++){
                
                tipoTarea *aux2 = get_data(monticulo,f);
        
                if(strcmp(aux2->nombreTarea,tarea2)==0){
                    aux2->precedentes = realloc(aux2->precedentes,(aux2->contPrecedentes+1) * sizeof(char[MAXCHAR+1]));
                    strcpy(aux2->precedentes[aux2->contPrecedentes],tarea1);
                    aux2->contPrecedentes++;
                    valido=true;
                }
            }
        }
    }
    if(valido==false){
        printf("No es posible hacer esto\n");
        return;
    }
    push(historial->ultimaAccion, monticulo);
}

void mostrarTareas(Heap* monticulo){
    tipoTarea *aux = heap_top(monticulo);
    int size = get_size(monticulo);
    int cont = 0, posiciones = 1;
    
    printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n\n");
    do{
        if (aux->contPrecedentes == 0){
            printf("%d. Tarea%s (Prioridad: %d)\n", posiciones, aux->nombreTarea, aux->prioridad);
            posiciones++;
        }
        cont++;
        aux = get_data(monticulo,cont);
    }while(cont < size);

    aux = heap_top(monticulo);
    cont = 0;
    posiciones = 1;
    do{
        if (aux->contPrecedentes != 0){
            printf("%d. Tarea%s (Prioridad: %d) - ", posiciones, aux->nombreTarea, aux->prioridad);
            posiciones++;
            printf("Precedente(s): ");
            for (int i = 0; i < aux->contPrecedentes; i++){
                printf("Tarea%s ", aux->precedentes[i]);
            }
            printf("\n");
        }
        cont++;
        aux = get_data(monticulo,cont);
    }while(cont < size);
}

void borrarDePrecedentes(Heap* monticulo,char* tarea){

    int cont=get_size(monticulo);

    for(int i=0;i<cont;i++){

        tipoTarea *aux = get_data(monticulo,i);

        if(aux->contPrecedentes!=0){

            for(int c=0;c<aux->contPrecedentes;c++){
                if(strcmp(aux->precedentes[c],tarea)==0){
                    for(;c<aux->contPrecedentes;c++){
                         strcpy(aux->precedentes[c], aux->precedentes[c+1]);
                    }
                    aux->contPrecedentes--;
                }
            }
        }
    }
}

void marcarTareaCompletada(Heap* monticulo,tipoHistorial* historial){
    
    char tarea[MAXCHAR +1];
    bool valido=false;
    char respuesta[3];
    printf("Ingrese el nombre de la tarea:\n");
    scanf(" %[^\n]s", tarea);
    while (getchar() != '\n');

    int cont = get_size(monticulo);

    for(int i=0;i<cont;i++){

        tipoTarea *aux2 = get_data(monticulo,i);
    
        if(strcmp(aux2->nombreTarea,tarea)==0){
            valido=true;
            printf("Seguro que quieres borrar la tarea\n");
            scanf("%2s",respuesta);
            while (getchar() != '\n');
            if (!confirmar(respuesta)){
                printf("No se borro la tarea");
                return;
            }else{
                heap_pop(monticulo, i);
                borrarDePrecedentes(monticulo,tarea);
            }
        }    
    }
    if(valido==false){
        printf("La tarea no existe\n");
        return;
    }

    push(historial->ultimaAccion, monticulo);
}

Heap *deshacerUltimaAccion(Heap* monticulo,tipoHistorial* historial){
    //usar la pila , y llevar al top a las funciones como aux y despues insertarl al top
    pop(historial->ultimaAccion);
    return top(historial->ultimaAccion);
    
}

void importarArchivo(Heap* monticulo){

    tipoTarea *tarea;
    char nombreArchivoImport[MAXCHAR + 1];
    printf("Ingrese el nombre del archivo.csv del que se importarán las tareas.\n");
    scanf("%20[^\n]s", nombreArchivoImport);
    printf("a");
    while(getchar() != '\n');
    
    FILE* file = fopen(nombreArchivoImport, "r");
    if (file == NULL){
        printf("No existe el archivo");
        return;
    }
    char *titular = (char*) malloc(sizeof(char)*MAXCHAR*5);
    bool indicadorFinArchivo = false;
    char caracterAux;
    char numero[MAXCHAR];
    int cont = 0;
    fscanf(file,"%[^\n]s",titular);
    printf("%s",titular);
    while (fgetc(file) != '\n');

    tarea = (tipoTarea*) malloc(sizeof(tipoTarea));
    printf("a");
    
    while (!indicadorFinArchivo){
        printf("a");
        fscanf(file, "%20[^,]s", tarea->nombreTarea);
        while (fgetc(file) != ',');
        fgetc(file);
        fscanf(file, "%19[^,]s", numero);
        tarea->prioridad = atoi(numero);
        printf("%d", tarea->prioridad);
        while (fgetc(file) != ',');
        cont=0;
        while(fgetc(file) != '\n'){
            tarea->precedentes = realloc(tarea->precedentes, sizeof(char[MAXCHAR + 1]) * tarea->contPrecedentes+1);
            fscanf(file, "%[^ ]s", tarea->precedentes[cont]);
            cont++;
        }
        tarea->contPrecedentes=cont;
        
        heap_push(monticulo, tarea, tarea->prioridad);

        while (caracterAux != '\n' && caracterAux != EOF)
        {
            caracterAux = fgetc(file);
            if (caracterAux == EOF)
                indicadorFinArchivo = true;
        }
    }
    fclose(file);
}

int main(void){

    Heap* monticulo = createHeap();
    tipoHistorial* historial = malloc (sizeof(tipoHistorial));
    historial->ultimaAccion = createStack(sizeof(Heap*));
   
    int opcionMenu = -1;
   
    printf("Bienvenido al control de tareas\n");
        
    while (opcionMenu != 0){
        puts(barrita);
        printf("Elija una opción del menú.\n");
        puts(barrita);
        printf("1. Agregar tarea\n");
        printf("2. Establecer precedencia entre tareas\n");
        printf("3. Mostrar tareas por hacer\n");
        printf("4. Marcar tarea como completada\n");
        printf("5. Deshacer ultima acción\n");
        printf("6. Cargar datos de tareas desde un archivo de texto\n");
        printf("0.- Salir del menú\n");
        printf("Indique la opcion: \n");
        scanf("%d", &opcionMenu);
        while(getchar() != '\n');

            switch(opcionMenu){
                case 1:
                    {
                        agregarTarea(monticulo,historial);
                        break;
                    } 
                case 2:
                    {
                        establecerPrecedencia(monticulo,historial);
                        break;
                    }
                case 3: 
                    {
                        mostrarTareas(monticulo);
                        break;
                    }
                case 4: 
                    {
                        marcarTareaCompletada(monticulo,historial);
                        break;
                    }
                case 5: 
                    {
                        monticulo=deshacerUltimaAccion(monticulo,historial);
                        free(monticulo);
                        monticulo=malloc(monticulo,sizeof(Heap)*top(historial->ultimaAccion));
                        if(monticulo==NULL){
                            monticulo=createHeap();
                        }
                        break;
                    }
                case 6: 
                        importarArchivo(monticulo);
                        break;
                    {
                case 0: 
                    {
                        printf("\nSaliste del menú.");
                        return 0;
                    }
                default: 
                    {
                        printf("No ingreso opción válida.");
                        break;
                    }
            }
             
            }
        opcionMenu=-1;
    }
    return 0;
}