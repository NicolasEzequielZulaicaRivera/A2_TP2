#ifndef __HEAP_H__
#define __HEAP_H__

#include <stddef.h>

// HEAP MINIMAL: EL PADRE SIEMPRE ES MENO QUE LOS HIJOS

#define MAX_HEAP 255 // 127?

/*
 * Comparador de elementos. Recibe dos elementos del heap y devuelve
 * 0 en caso de ser iguales, n>0 si el primer elemento es mayor al
 * segundo o n<0 si el primer elemento es menor al segundo.
 */
typedef int (*heap_comparador)(void*, void*);

/*
 * Destructor de elementos. Cada vez que un elemento deja el heap
 * (heap_borrar o heap_destruir) se invoca al destructor pasandole
 * el elemento.
 */
typedef void (*heap_liberar_elemento)(void*);

typedef struct heap{
  void* heap[MAX_HEAP];
  heap_comparador comparador;
  heap_liberar_elemento destructor;
  size_t tamanio;
} heap_t;

/*
 * Crea un heap reservando la memoria necesaria.
 * Devuelve un puntero al heap creado o NULL en caso de error.
 */
heap_t* heap_crear( heap_comparador comparador, heap_liberar_elemento destructor );

/*
 * Devuelve la raiz del heap.
 */
void* heap_raiz(heap_t* heap);

/*
 * Inserta un elemento al heap.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 */
int heap_insertar(heap_t* heap, void* elemento);

/*
 * Elimina un elemento del heap.
 * Devuelve 0 si pudo borrar o -1 si no pudo.
 */
int heap_borrar_raiz(heap_t* heap );


/*
 * Libera la memoria reservada por el heap.
 */
void heap_destruir( heap_t* heap );

#endif /* __HEAP_H__ */
