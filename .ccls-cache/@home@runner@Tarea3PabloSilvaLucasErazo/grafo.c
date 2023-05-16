#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"


typedef struct{
    char nombreTarea[21];
    int prioridad;
    bool visited;
    bool explored;
    List* adj_edges;
}Node;

Node* createNode(){
  Node* n = (Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
    
    return 1;
}


List* get_adj_nodes(Node* n){
    List* list = createList();
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                int k;
                for (k = 1; k <= 9; k++) {
                    Node* new_node = copy(n);
                    new_node->sudo[i][j] = k;
                    if (is_valid(new_node)) {
                        pushBack(list, new_node);
                    } else {
                        free(new_node);
                    }
                }
                return list;
            }
        }
    }
    return list;
}


int is_final(Node* n){
    int i, j;
    for (i = 0; i < 9; i++) {
        for (j = 0; j < 9; j++) {
            if (n->sudo[i][j] == 0) {
                return 0;
            }
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack* S = createStack();
    push(S, initial);

    while(!is_empty(S)){
        Node* current = (Node*) top(S);
        pop(S);
        (*cont)++;

        if(is_final(current)){
            clean(S);
            return current;
        }

        List* adj = get_adj_nodes(current);
        Node* adjacente = first(adj);
        while(adjacente){
            push(S, adjacente);
            adjacente = next(adj);
        }
        clean(adj);
        free(current);
    }

    return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/