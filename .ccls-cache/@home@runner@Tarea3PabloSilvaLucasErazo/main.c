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
//structs para las tareas del monticulo
typedef struct{ 
    char nombreTarea[MAXCHAR + 1];
    int prioridad;
    List* precedentes;
    bool hayPrecedentes;
} tipoTarea;
//struct para el historial de acciones incluida en las funciones 1, 2 y 4.
typedef struct{
    int ultimaAccion;
    tipoTarea *tarea;
}tipoHistorial;
/*En la funcion agregarTarea se crea y se inicializan los datos de una tarea en una variable auxiliar,para luego ser insertados en el monticulo*/
void agregarTarea(Heap* monticulo,List* historial){

    tipoTarea *tarea = (tipoTarea*) malloc(sizeof(tipoTarea));//variable auxiliar
    tipoHistorial *nodoHistorial1 = malloc (sizeof(tipoHistorial));
    
    printf("Ingrese el nombre de la tarea:\n");
    scanf(" %[^\n]s", tarea->nombreTarea);
    while (getchar() != '\n');
    
    int cont=get_size(monticulo);//se accede al size del monticulo
    for(int i=0;i<cont;i++){
        tipoTarea *aux = get_data(monticulo,i);
        if(strcmp(aux->nombreTarea,tarea->nombreTarea)==0){
            printf("ya existe esta tarea.\n");
            return;
        }
    }
    printf("Ingrese la prioridad de la tarea:\n");
    scanf("%d", &tarea->prioridad);
    tarea->hayPrecedentes = false;
    tarea->precedentes = createList();
    heap_push(monticulo, tarea, tarea->prioridad);//se inserta el auxiiar en el monticulo
   
    nodoHistorial1->ultimaAccion = 1;
    nodoHistorial1->tarea = tarea;
    pushFront(historial, nodoHistorial1);//se inseerta la accion en la pila de acciones
}
/*En esta funcion se le asignara una precedencia de "Tarea 1" a "Tarea 2", es decir que para hacer la "Tarea 2" hay que hacer antes la "Tarea 1". Guardamos los nombres de las tareas en variables char y los buscamos dentro del monticulo para asignarlo a la lista correspondiente*/
void establecerPrecedencia(Heap *monticulo, List* historial){

    
    tipoTarea *aux = malloc(sizeof(tipoTarea));
    tipoTarea *aux2 = malloc(sizeof(tipoTarea));
    tipoHistorial *nodoHistorial2 = malloc (sizeof(tipoHistorial));
    
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
    //en un ciclo analizará los nombres de los nodos del monticulo hasta encontrar los correspondientes e ingresar el precedente a la lista.
    for(int i=0;i<cont;i++){
        
        aux = get_data(monticulo,i);
        
        if(strcmp(aux->nombreTarea,tarea1)==0){
            
            for(int f=0;f<cont;f++){
                
                aux2 = get_data(monticulo,f);
        
                if(strcmp(aux2->nombreTarea,tarea2)==0){
                    nodoHistorial2->ultimaAccion = 2;
                    nodoHistorial2->tarea = aux2;
                    pushFront(historial, nodoHistorial2);
                    
                    if(aux2->hayPrecedentes == false){//se inserta la tarea en al lista de precendentes a la que se le indica
                    
                        pushFront(aux2->precedentes,aux);
                        aux2->hayPrecedentes = true;
                    }else{
                        pushCurrent(aux2->precedentes,aux);
                    }
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
/*Esta funcion ve todos las tareas del monticulo,y las mostrara todas en en orden de menor a mayor por su prioridad*/
void mostrarTareas(Heap* monticulo){

    Heap* copia = heap_clone(monticulo);
    int size = get_size(monticulo);

    if(size == 0)
        return;

    tipoTarea *aux = heap_top(copia);
    int cont = 0;
    int posicion = 0;

    printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n\n");
    //lee los sin precedentes
    do {
        if (aux->hayPrecedentes == false){
            printf("%d.-Tarea %s (Prioridad: %d)\n", posicion+1, aux->nombreTarea, (aux->prioridad));
            
            posicion++;
        }
        cont++;
        heap_pop(copia, 0);
        aux = heap_top(copia);
    } while (cont < size);

    Heap* otraCopia = heap_clone(monticulo);
    
    cont = 0;
    
    tipoTarea *otroAux = heap_top(otraCopia);
    //lee los con precedentes
    do {
        if (otroAux->hayPrecedentes == true){
            printf("%d.-Tarea %s (Prioridad: %d)", posicion+1, otroAux->nombreTarea, otroAux->prioridad);
            printf(" - Precedente(s): ");
            
            tipoTarea* nodo=firstList(otroAux->precedentes);
            
            while(nodo!=NULL){
                printf("Tarea %s ",nodo->nombreTarea);
                nodo=nextList(otroAux->precedentes);
            }
            printf("\n");
            posicion++;
        }
        cont++;
        heap_pop(otraCopia, 0);
        otroAux = heap_top(otraCopia);
    } while (cont < size);
}
/*La esta funcion borrarDePrecedentes borra una tarea de precedente de las demas tareas que la tengan de predecente */
void borrarDePrecedentes(Heap* monticulo,char* tarea){

    int cont=get_size(monticulo);

    for(int i=0;i<cont;i++){

        tipoTarea *aux = get_data(monticulo,i);

        if(aux->hayPrecedentes == true){
            tipoTarea* nodo = firstList(aux->precedentes);
            while(nodo != NULL){
                if(strcmp(nodo->nombreTarea,tarea)==0){
                    popCurrent(aux->precedentes);//borra la tarea de la lista de precedentes
                    break;
                }
                nextList(aux->precedentes);
            }
        }
        if (firstList(aux->precedentes) == NULL){
            aux->hayPrecedentes = false;
        }
    }
    return;
}
/*La funcion marcarTareaCompletada busca la tarea indicada en el monticuo para borrarla,y se confirma que sera borrada en caso que tenga precedentes*/
void marcarTareaCompletada(Heap* monticulo,List* historial){
    
    tipoTarea *aux = malloc(sizeof(tipoTarea));
    tipoHistorial *nodoHistorial3 = malloc (sizeof(tipoHistorial));
    
    char tarea[MAXCHAR +1];
    bool valido=false;
    char respuesta[3];
    printf("Ingrese el nombre de la tarea:\n");
    scanf(" %[^\n]s", tarea);
    while (getchar() != '\n');

    int cont = get_size(monticulo);

    for(int i=0;i<cont;i++){//recorrer monticulo

        aux = get_data(monticulo,i);
    
        if(strcmp(aux->nombreTarea,tarea)==0){
            valido=true;
            if (aux->hayPrecedentes){
                printf("Seguro que quieres borrar la tarea\n");
                scanf("%2s",respuesta);
                while (getchar() != '\n');
                if (!confirmar(respuesta)){
                    printf("No se borro la tarea");
                    return;
                }else{
                    nodoHistorial3->ultimaAccion = 3;
                    nodoHistorial3->tarea = aux;
                    pushFront(historial, nodoHistorial3);
                    
                    heap_pop(monticulo,i);//se borra de monticulo
                    borrarDePrecedentes(monticulo,tarea);//funcion para borrar tarea indicada de precedente de las demas
                }
            }else{
                nodoHistorial3->ultimaAccion = 3;
                nodoHistorial3->tarea = aux;
                pushFront(historial, nodoHistorial3);
                
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
/*Esta funcion deshace la ultima accion reemplazando el nodo tipoTarea con la posicion en especifico de el nodo editado anteriormente, en caso de una tarea completada se hace heap_Push para volver a integrarla.*/
void deshacerUltimaAccion(Heap* monticulo, List* historial){
    tipoHistorial *ultimo = firstList(historial);
    int cont = get_size(monticulo);
    int indicador = ultimo->ultimaAccion;

    // case 1: hubo un agregarTarea; case 2: hubo un establecerPrecedente; case 3: hubo un marcarTareaCompletada
    
    printf("%d", ultimo->ultimaAccion);
    if (ultimo != NULL){ 
        switch(indicador){
            case 1:
                {
                    for (int i = 0; i < cont; i++){
                        tipoTarea *aux = get_data(monticulo, i);
                        if (strcmp(aux->nombreTarea, ultimo->tarea->nombreTarea) == 0){
                            heap_pop(monticulo, i);
                            popCurrent(historial);
                            break;
                        }
                        
                    }
                    break;
                }
            case 2:
                {
                    for (int i = 0; i < cont; i++){
                        tipoTarea *aux = get_data(monticulo, i);
                        if (strcmp(aux->nombreTarea, ultimo->tarea->nombreTarea) == 0){
                            popBack(aux->precedentes);
                            if (firstList(aux->precedentes)==NULL) aux->hayPrecedentes = false;
                            popCurrent(historial);
                            break;
                        }
                        
                    }
                    break;
                }
            case 3:
                {
                    heap_push(monticulo, ultimo->tarea, ultimo->tarea->prioridad);
                    popCurrent(historial);
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
/*ayuda a leer el archivo*/
char *gets_csv_field(char *tmp, int k) {
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
/*Esta funcion importa un archivo csv,guarda los datos indicados en una variable auxiiar para luego ser insertado en el monticulo*/
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
        tarea->precedentes = createList();
        tarea->hayPrecedentes=false;
        
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
                    char* auxPrecedentes=strtok(aux,delimit);
                    int cont = get_size(monticulo);
                    
                    while (auxPrecedentes != NULL){
                        
                        for (int i = 0; i < cont; i++){
                            
                            tipoTarea* nodo = get_data(monticulo, i);
                            
                            if (strcmp(nodo->nombreTarea, auxPrecedentes)==0){
                                
                                if (tarea->hayPrecedentes == false){
                                    pushFront(tarea->precedentes, nodo);
                                    tarea->hayPrecedentes = true;     
                                }else{
                                    pushCurrent(tarea->precedentes, nodo);
                                }
                            }
                        }
                        auxPrecedentes=strtok(NULL, delimit);
                    }
                }
            }
        }
        heap_push(monticulo, tarea, tarea->prioridad);
    }
    fclose(file);
}

int main(void){

    Heap* monticulo = createHeap();
    List* historial = createList();
   
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
                    { 
                        importarArchivo(monticulo);
                        break;
                    }
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
        opcionMenu=-1;
    }
    return 0;
}