#include <printf.h>
#include "../headers/List.h"

/*--------------------------------------------------------------------------------------------------------------------*/


Node *newNode(void *data)
{
    // Crea un nodo
    Node *n = malloc(sizeof(Node));
    n->next = n->prev = NULL;
    n->data = data;
    return n;
}

/*--------------------------------------------------------------------------------------------------------------------*/

List *newList()
{
    // Crea una lista
    List *l = malloc(sizeof(List));
    l->head = l->tail = NULL;
    l->size = 0;
    return l;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void add(List *l, void *data)
{
    // Agrega un nodo al final de la lista
    Node *n = newNode(data);
    if(l->size == 0)
        l->head = l->tail = n;
    else
    {
        l->tail->next = n;
        n->prev = l->tail;
        l->tail = n;
    }
    l->size++;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void addAux(List *l, void *data)
{
    // Agrega un nodo al final de la lista
    Node * element = l->head;
    while(element != NULL){
        if(strcmp(element->data, data) == 0){
            return;
        }

        element = element->next;
    }

    add(l,data);

}



/*--------------------------------------------------------------------------------------------------------------------*/


void push(List *l, void *data)
{
    // Agrega un noto al inicio de la lista
    Node *n = newNode(data);
    if(l->size == 0)
        l->head = l->tail = n;
    else
    {
        n->next = l->head;
        n->next->prev = n;
        l->head = n;
    }
    l->size++;
}

/*--------------------------------------------------------------------------------------------------------------------*/
void *peek(List *l)
{
    // Retorna la informacion de la cabeza de la lista
    if(l->size == 0)
        return NULL;
    else
    {
        Node *node = l->head;
        return node->data;
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/

void *pop(List *l)
{
    // Elimina el ultimo elemento de la lista
    Node *pop = l->head;
    if (l->size == 0)
        return NULL;
    else if(l->size == 1)
        l->head = l->tail = NULL;
    else
    {
        l->head = l->head->next;
        pop->next->prev = NULL;
        pop->next = NULL;
    }
    l->size--;
    return pop->data;
}

/*--------------------------------------------------------------------------------------------------------------------*/

void printList(List *l, int (*func)(const char*, ...))
{
    // Muestra el contenido de la lista
    Node *temp = l->head;
    while(temp != NULL) {
        func(temp->data);
        temp = temp->next;
        if (temp != NULL)
            printf("->");
    }
}

/*--------------------------------------------------------------------------------------------------------------------*/