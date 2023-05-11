#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "heap.h"
#include "stack.h"
#define barrita "\n======================================\n"
#define barrita2 "\n--------------------------------------\n"

void agregarTarea(){

}

void establecerPrecedencia(){
    
}

void mostrarTareas(){
    
}

void marcarTareaCompletada(){

}

void deshacerUltimaAccion(){
    
}

void importarArchivo(){
    
}

int main(void){

   
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
                        agregarTarea();
                        break;
                    } 
                case 2:
                    {
                        establecerPrecedencia();
                        break;
                    }
                case 3: 
                    {
                        mostrarTareas();
                        break;
                    }
                case 4: 
                    {
                        marcarTareaCompletada();
                        break;
                    }
                case 5: 
                    {
                        deshacerUltimaAccion();
                        break;
                    }
                case 6: 
                        importarArchivo();
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