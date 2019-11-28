#include <stdio.h>
#include <stdlib.h>

typedef struct nodo
{
    int dato;
    struct nodo *ste;
} ST_NODO;

/**
 * @param int dato es el valor a insertar.
 */
ST_NODO *crearNodo(int dato)
{
    ST_NODO *nodo = (ST_NODO*) malloc(sizeof(ST_NODO)); // Pido memoria para un nodo nuevo
    nodo->dato = dato; // @param int dato va al dato del nodo
    nodo->ste = NULL; // El siguiente del nodo nuevo es NULO

    return nodo;
}

/**
 * @param ST_NODO **list es el puntero a mi lista.
 * @param int dato es el valor a insertar.
 */
ST_NODO *insertFront(ST_NODO **list, int dato)
{
    ST_NODO *nodo = crearNodo(dato);
    nodo->ste = *list;
    *list = nodo;

    return nodo;
}

/**
 * @param ST_NODO **list es el puntero a mi lista.
 * @param int dato es el valor a insertar.
 */
ST_NODO *insertEnd(ST_NODO **list, int dato)
{
    ST_NODO *nodo = crearNodo(dato); // Pido memoria para un nodo nuevo
    ST_NODO *aux = *list; // Creo un puntero auxiliar que apunta a la lista (al comienzo)

    while(aux && aux->ste != NULL) // Mientras que aux != NULL y haya un nodo después del que estoy leyendo...
        aux = aux->ste; // El auxiliar avanza a leer el nodo siguiente
    
    if(aux == NULL) // Si el auxiliar apunta a NULL, quiere decir que *list es nula, por ende...
        *list = nodo; // La lista recibe el puntero del nodo nuevo creado
    else // Si el auxiliar no apunta a NULL
        aux->ste = nodo; // Linkeamos el último nodo que existía (y esto es así porque "aux" avanzó dentro del while()) al "nodo" que creamos en la primer línea de la función
    
    return nodo; // Devolvemos la dirección de "nodo"
}

ST_NODO *insertOrder(ST_NODO **list, int dato)
{
    ST_NODO *nodo = crearNodo(dato); // Pido memoria para un nodo nuevo
    ST_NODO *aux = *list; // Creo un puntero auxiliar que apunta a la lista (al comienzo)
    ST_NODO *nodoAnt = NULL; // Creo otro puntero auxiliar

    while(aux && dato > aux->dato) // Mientras que aux != NULL y el dato sea mayor al dato que estoy analizando en la lista
    {
        nodoAnt = aux;
        aux = aux->ste;
    }
    if(nodoAnt == NULL)
    { *list = nodo; }
    else
    { nodoAnt->ste = nodo; }

    nodo->ste = aux;

    return nodo;   
}

ST_NODO *search(ST_NODO *list, int dato)
{
    ST_NODO *aux = list;

    while(aux && dato != list->dato)
    {
        aux = aux->ste;
    }

    return aux;
}

ST_NODO *insertNotDuplicate(ST_NODO **list, int dato)
{
    ST_NODO *nodo = search(*list, dato);
    if(nodo == NULL)
    {
        nodo = insertOrder(*list, dato);
    }

    return nodo;
}
int deleteFirst(ST_NODO **list)
{
    ST_NODO *aux = *list;
    list = aux->ste;
    int valor  = aux->dato;
    free(aux);
    
    return valor;
}
void sortList(ST_NODO **list)
{
    ST_NODO *aux = NULL;
    while(list != NULL)
    {
        int dato = deleteFirst(list);
        insertOrder(&aux, dato);
    }
    *list = aux;
}