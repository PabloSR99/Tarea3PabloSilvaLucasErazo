
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct n{
    void* data;
    struct n* next;
    struct n* prev;
} node;

struct List{
    node* first;
    node* last;
    node* current;
    int size;
};

int get_size_list(List* list){
    return list->size;
}

void clean(List* list){
    while(is_empty(list)==0)
        pop(list);
}

List* createList(){
   List* list=(List*) malloc(sizeof(List));
   list -> first = NULL;
   list -> last = NULL;
   list -> size = 0;
   return list;
}

Stack* createStack(){
    return createList();
}

node* _createNode(void* data){
    node* t;
    t=(node*) malloc (sizeof(node));
    t -> data = data;
    t -> next = NULL;
    t -> prev = NULL;
    return t;
}

int is_empty(List* list){
    return (list->first==NULL);
}

void popFront(List* list){
    if(!is_empty(list)){
        node *a = list->first;
        list->first=list->first->next;
        if(list->first!=NULL) list->first->prev=NULL;
        else list->last=NULL;
        free(a);
        list -> size--;
    }
}

void popBack(List* list){
    if(!is_empty(list)){
        node *a = list->last;
        list->last=list->last->prev;
        if(list->last!=NULL) list->last->next=NULL;
        else list->first=NULL;
        free(a);
        list -> size-- ;
    }
}

void pushFront(List* list, void* data){
    node *a;
    a=_createNode(data);
    if(is_empty(list))
        list -> last = a;
    else
        list -> first -> prev = a;

    a -> next = list -> first;
    list -> first = a;
    list -> size++;
}

void pushBack(List* list, void* data){
    node *a;
    a=_createNode(data);
    if(is_empty(list))
        list -> first = a;
    else
        list -> last -> next = a;

    a -> prev = list -> last;
    list -> last = a;
    list -> size++;
}

List* copyList(List* originalList) {
    List* newList = createList();
    node* currentNode = malloc(sizeof(node));
    if (originalList == NULL || originalList->size == 0) {
        return newList; // Devuelve la lista vacía
    }
    
    currentNode = originalList->first;
    while (currentNode != NULL) {
        // Crear un nuevo nodo
        node* newNode = (node*)malloc(sizeof(node));
        newNode->data = currentNode->data;
        newNode->next = NULL;
        newNode->prev = NULL;
        
        // Agregar el nuevo nodo a la lista nueva
        if (newList->first == NULL) {
            newList->first = newNode;
            newList->last = newNode;
            newList->current = newNode;
        } else {
            newList->last->next = newNode;
            newNode->prev = newList->last;
            newList->last = newNode;
        }
        
        newList->size++;
        currentNode = currentNode->next;
    }
    
    return newList;
}

List *List_clone(List *src)
{
  if (src == NULL) {
    return NULL;
  }

  List *dst = createList();

  List *tempStack = createList();
  while (!is_empty(src)) 
  {
    void* element = popFront(src);
    pushFront(dst, element);
    pushFront(tempStack, element);
  }

  while (!is_empty(tempStack)) 
  {
    pushFront(src, popFront(tempStack));
  }

  free(tempStack);

  return dst;
}

void pushCurrent(List* list, void* data){
    if(!list->current) return;

    node* a=_createNode(data);
    a->next=list->current->next;
    list->current->next=a;
    if(a->next) a->next->prev=a;
    a->prev=list->current;
    if(list->current==list->last) list->last=a;

    list->current=a;
    list -> size++;
}

void popCurrent(List* list){
    if(!list->current) return;

    if (list->current->prev) list->current->prev->next=list->current->next;
    if(list->current->next) list->current->next->prev=list->current->prev;
    if(list->first==list->current) list->first=list->current->next;
    if(list->last==list->current) list->last=list->current->prev;
    free(list->current);
    list -> size--; 
}


void pop(Stack* s){
  popBack(s);
}


void* front(List* list){
    if(is_empty(list)) {
        return NULL;
    }
    list->current=list->first;
    if(list->first)
       return (list->first->data);
    else return NULL;
}



void* first(List* list){
    return front(list);
}

void* next(List* list){
    if(list->current)
       list->current=list->current->next;
    if(list->current)
       return list->current->data;
    else return NULL;
}

void* last(List* list){
    if(list->last){
        list->current=list->last;
        return list->last->data;
    }
    else return NULL;
}

void* top(Stack* s){
  return last(s);
}

void* prev(List* list){
    if(list->current)
       list->current=list->current->prev;
    if(list->current)
       return list->current->data;
    else return NULL;
}



void push(Stack* s, void* data){
  pushBack(s,data);
}