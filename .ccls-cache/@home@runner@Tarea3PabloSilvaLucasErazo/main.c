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

    heap_push(monticulo, tarea, tarea->prioridad);
}

void establecerPrecedencia(Heap* monticulo){

    char tarea1;
    
    printf("Ingrese el nombre de la tarea:\n");
    scanf(" %[^\n]s", tarea->nombreTarea);
    while (getchar() != '\n');
}

void mostrarTareas(Heap* monticulo){
    
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