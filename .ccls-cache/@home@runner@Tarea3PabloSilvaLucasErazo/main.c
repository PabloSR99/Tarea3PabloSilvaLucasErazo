#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"
#include "stack.h"
#define MAXCHAR 20
#define barrita "\n======================================\n"
#define barrita2 "\n--------------------------------------\n"


typedef struct{ 
    char nombreTarea[MAXCHAR + 1];
    int prioridad ;
    char (*precedentes)[MAXCHAR + 1];
    int contPrecedentes;
    stack *historial;
} tipoTarea;



void agregarTarea(Heap* monticulo){

    tipoTarea *tarea = (tipoTarea*) malloc(sizeof(tipoTarea));
    
    printf("Ingrese el nombre de la tarea:\n");
    scanf(" %[^\n]s", tarea->nombreTarea);
    while (getchar() != '\n');
    printf("Ingrese la prioridad de la tarea:\n");
    scanf("%d", &tarea->prioridad);
    tarea->precedentes = malloc(sizeof(char[MAXCHAR +1]));
    tarea->contPrecedentes = 0;
    tarea->historial = createStack(sizeof(char[MAXCHAR + 1]));

    heap_push(monticulo, tarea, tarea->prioridad);
}

void establecerPrecedencia(Heap *monticulo){
   
    char tarea1[MAXCHAR +1];
    char tarea2[MAXCHAR +1];
    
    printf("Ingrese el nombre de la tarea1:\n");
    scanf(" %[^\n]s", tarea1);
    while (getchar() != '\n');
    printf("Ingrese el nombre de la tarea1:\n");
    scanf(" %[^\n]s", tarea2);
    while (getchar() != '\n');
    
    int cont = get_size(monticulo);
    printf("%d",cont);

    for(int i=0;i<cont;i++){
        
        tipoTarea *aux = get_data(monticulo,i);
        
        if(strcmp(aux->nombreTarea,tarea2)==0){
            
            for(int f=0;f<cont;f++){
                
                tipoTarea *aux2 = get_data(monticulo,f);
        
                if(strcmp(aux2->nombreTarea,tarea1)==0){
                    aux->precedentes = realloc(aux->precedentes,(aux->contPrecedentes+1) * sizeof(char[MAXCHAR+1]));
                    strcpy(aux->precedentes[aux->contPrecedentes],tarea1);
                    aux->contPrecedentes++;
                    printf("asa");
                }
            }
        }
    }
    
    
}

void mostrarTareas(Heap* monticulo){
    tipoTarea *aux = heap_top(monticulo);
    int size = get_size(monticulo);
    int cont = 0;

    do{
        printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n");
        printf("%d. Tarea%s (Prioridad: %d) - ", cont+1, aux->nombreTarea, aux->prioridad);
        if (aux->contPrecedentes != 0){
            for (int i = 0; i < aux->contPrecedentes; i++){
                
            }
        }

        
        
    }while(cont < size);
    
    
    
}

void marcarTareaCompletada(Heap* monticulo){

}

void deshacerUltimaAccion(Heap* monticulo){
    
}

void importarArchivo(Heap* monticulo){
    
}

int main(void){

    Heap* monticulo = createHeap();
   
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

            switch(opcionMenu){
                case 1:
                    {
                        agregarTarea(monticulo);
                        break;
                    } 
                case 2:
                    {
                        establecerPrecedencia(monticulo);
                        break;
                    }
                case 3: 
                    {
                        mostrarTareas(monticulo);
                        break;
                    }
                case 4: 
                    {
                        marcarTareaCompletada(monticulo);
                        break;
                    }
                case 5: 
                    {
                        deshacerUltimaAccion(monticulo);
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
    }
    return 0;
}