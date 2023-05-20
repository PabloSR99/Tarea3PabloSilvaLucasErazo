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
    int ultimaAccion;
    tipoTarea *tarea;
}tipoHistorial;

void agregarTarea(Heap* monticulo,Stack* historial){

    tipoTarea *tarea = (tipoTarea*) malloc(sizeof(tipoTarea));
    tipoHistorial *nodoHistorial = malloc (sizeof(tipoHistorial));
    
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
    tarea->prioridad*=(-1);
    tarea->contPrecedentes = 0;
    heap_push(monticulo, tarea, tarea->prioridad);
   
    nodoHistorial->ultimaAccion = 1;
    nodoHistorial->tarea = tarea;
    push(historial, nodoHistorial);
}

void establecerPrecedencia(Heap *monticulo,Stack* historial){

    
    tipoTarea *aux = malloc(sizeof(tipoTarea));
    tipoTarea *aux2 = malloc(sizeof(tipoTarea));
    tipoHistorial *nodoHistorial = malloc (sizeof(tipoHistorial));
    
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
        
        aux = get_data(monticulo,i);
        
        if(strcmp(aux->nombreTarea,tarea1)==0){
            
            for(int f=0;f<cont;f++){
                
                aux2 = get_data(monticulo,f);
        
                if(strcmp(aux2->nombreTarea,tarea2)==0){
                    nodoHistorial->ultimaAccion = 2;
                    nodoHistorial->tarea = aux2;
                    push(historial, nodoHistorial);
                    aux2->precedentes = realloc(aux2->precedentes,(aux2->contPrecedentes+1) * sizeof(char[MAXCHAR+1]));
                    strcpy(aux2->precedentes[aux2->contPrecedentes],tarea1);
                    aux2->contPrecedentes++;
                    valido=true;
                    return;
                }
            }
        }
    }
    if(valido==false){
        printf("No es posible hacer esto\n");
        return;
    }

}

/*char* copiar_Precedentes(tipoTarea* tarea){
    char (*copia) = (char*)realloc(tarea->precedentes,(tarea->contPrecedentes+1) * sizeof(char[MAXCHAR+1]));

    for (int i = 0; i < tarea->contPrecedentes; i++){
        strcpy(copia[i],tarea->precedentes[i]);
    }
    return copia;
}*/

void mostrarTareas(Heap* monticulo){

    /*Heap* copia = heap_clone(monticulo);
    Heap* copia2 = heap_clone(monticulo);
     int posicion = 0;
    while((heap_top(copia))!=NULL){

        tipoTarea* tarea=(tipoTarea*)heap_top(copia);
        
        if(tarea->contPrecedentes==0){
            printf("%d. Tarea%s (Prioridad: %d)\n", posicion+1, tarea->nombreTarea, (tarea->prioridad)*(-1));
            posicion++;
        }
        heap_pop(copia, 0);
    }

    while((heap_top(copia2))!=NULL){

        tipoTarea* tarea=(tipoTarea*)heap_top(copia);
        //char *copiaArreglo= copiar_Precedentes(tarea);
        if(tarea->contPrecedentes!=0){
            printf("%d. Tarea%s (Prioridad: %d)", posicion+1, tarea->nombreTarea, (tarea->prioridad)*(-1));
            printf("Precedente(s): ");
            posicion++;
            for(int i=0;i<tarea->contPrecedentes;i++){
                 printf("Tarea %s ", tarea->precedentes[i]);
            }
        }
        heap_pop(copia2, 0);
    }

    printf("\n");
    free(copia);
    free(copia2);*/

    Heap* copia = heap_clone(monticulo);
    int size = get_size(monticulo);

    if(size == 0)
        return;

    tipoTarea *aux = heap_top(copia);
    int cont = 0;
    int posicion = 0;

    printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n\n");

    do {
        if (aux->contPrecedentes == 0){
            printf("%d. Tarea%s (Prioridad: %d)\n", posicion+1, aux->nombreTarea, (aux->prioridad));
            
            posicion++;
        }
        cont++;
        heap_pop(copia, 0);
        aux = heap_top(copia);
    } while (cont < size);

    aux = heap_top(monticulo);
    cont = 0;

    do {
        if (aux->contPrecedentes != 0){
            
            printf("%d. Tarea%s (Prioridad: %d)", posicion, aux->nombreTarea, aux->prioridad);
            printf("Precedente(s): ");
            for (int i = 0; i < aux->contPrecedentes; i++){
                printf("Tarea %s ", aux->precedentes[i]);
            }
            printf("\n");
            posicion++;
        }
        cont++;
        heap_pop(monticulo, 0);
        aux = heap_top(monticulo);
    } while (cont < size);
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

void marcarTareaCompletada(Heap* monticulo,Stack* historial){
    
    tipoTarea *aux = malloc(sizeof(tipoTarea));
    tipoHistorial *nodoHistorial = malloc (sizeof(tipoHistorial));
    
    char tarea[MAXCHAR +1];
    bool valido=false;
    char respuesta[3];
    printf("Ingrese el nombre de la tarea:\n");
    scanf(" %[^\n]s", tarea);
    while (getchar() != '\n');

    int cont = get_size(monticulo);

    for(int i=0;i<cont;i++){

        aux = get_data(monticulo,i);
    
        if(strcmp(aux->nombreTarea,tarea)==0){
            valido=true;
            printf("Seguro que quieres borrar la tarea\n");
            scanf("%2s",respuesta);
            while (getchar() != '\n');
            if (!confirmar(respuesta)){
                printf("No se borro la tarea");
                return;
            }else{
                nodoHistorial->ultimaAccion = 3;
                nodoHistorial->tarea = aux;
                push(historial, nodoHistorial);
                heap_pop(monticulo,i);
                borrarDePrecedentes(monticulo,tarea);
            }
        }    
    }
    if(valido==false){
        printf("La tarea no existe\n");
        return;
    }

}

void deshacerUltimaAccion(Heap* monticulo, Stack* historial){
    tipoHistorial *ultimo = top(historial);
    int cont = get_size(monticulo);
    int indicador = ultimo->ultimaAccion;

    printf("%s", ultimo->tarea->nombreTarea);
    printf("%d", ultimo->tarea->contPrecedentes);
    printf("%d", ultimo->tarea->prioridad);
    
    if (ultimo != NULL){ 
        switch(indicador){
            case 1:
                {
                    for (int i = 0; i < cont; i++){
                        tipoTarea *aux = get_data(monticulo, i);
                        if (strcmp(aux->nombreTarea, ultimo->tarea->nombreTarea)){
                            heap_pop(monticulo,i);
                        }
                    }
                    pop(historial);
                    break;
                }
            case 2:
                {
                    for (int i = 0; i < cont; i++){
                        tipoTarea *aux = get_data(monticulo, i);
                        if (strcmp(aux->nombreTarea, ultimo->tarea->nombreTarea)){
                            aux->contPrecedentes--;
                        }
                    }
                    pop(historial);
                    break;
                }
            case 3:
                {
                    for (int i = 0; i < cont; i++){
                        tipoTarea *aux = get_data(monticulo, i);
                        if (strcmp(aux->nombreTarea, ultimo->tarea->nombreTarea)){
                            heap_push(monticulo, ultimo->tarea, ultimo->tarea->prioridad);
                        }
                    }
                    pop(historial);
                    break;
                }
            default:
                {
                    break;
                }
        }
    }else{
        printf("No han habido acciones anteriores.");
    }
}

char *gets_csv_field(char *tmp, int k) 
{
  int open_mark = 0;
  char *ret = (char*) malloc(100 * sizeof(char));
  int ini_i = 0, i = 0;
  int j = 0;
  int last_field = 0;
  
  while (tmp[i + 1] != '\0')
  {  
    if(tmp[i] == '\"')
    {
      open_mark = 1 - open_mark;
      if(open_mark) ini_i = i + 1;
      i++;
      continue;
    }
    
    if(open_mark || tmp[i] != ',')
    {
      if(k == j) ret[i - ini_i] = tmp[i];
      i++;
      continue;
    }

    if(tmp[i] == ',')
    {
      if(k == j) 
      {
        ret[i - ini_i] = 0;
        return ret;
      }
      j++; 
      ini_i = i + 1;
    }
    i++;
  }

  if(k == j) 
  {
    last_field = 1;
    ret[i - ini_i] = 0;
    return ret;
  }

  if (last_field && k == j)
  {
    strcpy(ret + strlen(ret), tmp + ini_i);
    return ret;
  }
  
  return NULL;
}
void importarArchivo(Heap* monticulo) {
    
    char nombreArchivoImport[MAXCHAR + 1];
    printf("Ingrese el nombre del archivo.csv del que se importarán las tareas.\n");
    scanf("%[^\n]s", nombreArchivoImport);
    while (getchar() != '\n');

    FILE* file = fopen(nombreArchivoImport, "r");
    if (file == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
    
    char lineaArchivo[1024];
    fgets(lineaArchivo, 1023, file); // Ignorar la línea de título
    while (fgets(lineaArchivo,1023, file)!=NULL) {
        tipoTarea* tarea = (tipoTarea*) malloc(sizeof(tipoTarea));
        
        for(int i=0;i<3;i++){

            char *aux=gets_csv_field(lineaArchivo,i);
            
            if(i==0){
                strcpy(tarea->nombreTarea,aux);
            }

            if(i==1){
                tarea->prioridad=atol(aux);
            }
            
            if(i==2){
                if(strlen(aux)>1){
                    char delimit[]=" \t\r\v\n\f";
                    char*auxPrecedentes=strtok(aux,delimit);
                    
                    while(auxPrecedentes!=NULL){
                        tarea->precedentes = realloc(tarea->precedentes, sizeof(char*) * (tarea->contPrecedentes + 1));
                        strcpy(tarea->precedentes[tarea->contPrecedentes],auxPrecedentes);
                        tarea->contPrecedentes++;
                        auxPrecedentes=strtok(NULL,delimit);
                    }
                }
            }
        }
        heap_push(monticulo, tarea, tarea->prioridad);
    }
}

int main(void){

    Heap* monticulo = createHeap();
    Stack* historial = createStack();
   
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
                        deshacerUltimaAccion(monticulo,historial);
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